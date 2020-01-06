from model import BiLSTMModel
import os,argparse,traceback

from shutil import copyfile as copy_file
from utils import  load_hparams,save_hparams,get_time
from hparams import hparams, hparams_debug_string
import infolog
import tensorflow as tf

from data_helpers import DataHelper

log = infolog.Log
tf.logging.set_verbosity(tf.logging.ERROR)

def read_data(file_path):
    import re
    tokens = []
    tags = []

    tweet_tokens = []
    tweet_tags = []
    for line in open(file_path, encoding='utf-8'):
        line = line.strip()
        if not line:
            if tweet_tokens:
                tokens.append(tweet_tokens)
                tags.append(tweet_tags)
            tweet_tokens = []
            tweet_tags = []
        else:
            token, tag = line.split()
            token = re.sub(r'http[s]?://[^ ]{1,}', '<URL>', token)
            token = re.sub(r'^@[A-Za-z]{1,}', '<USR>', token)
            tweet_tokens.append(token)
            tweet_tags.append(tag)

    return tokens, tags

class Train:
    def prepare_dirs(self, hparams):
        self.config.ftrain = os.path.abspath(os.path.join(self.config.data_paths,'train.txt'))
        self.config.fval = os.path.abspath(os.path.join(self.config.data_paths,'validation.txt'))
        self.config.ftest = os.path.abspath(os.path.join(self.config.data_paths,'test.txt'))

        if not os.path.exists(self.config.ftrain) or not os.path.exists(self.config.fval) or not os.path.exists(self.config.ftest):
            exit(0)

        dataset_desc = 'NER'
        self.config.model_name = "{}_{}".format(dataset_desc, get_time())
        self.config.model_dir = os.path.join(self.config.log_dir, self.config.model_name)

        for path in [self.config.log_dir, self.config.model_dir]:
            if not os.path.exists(path):
                os.makedirs(path)

        save_hparams(self.config.model_dir, hparams)
        copy_file("hparams.py", os.path.join(self.config.model_dir, "hparams.py"))

    def prepare_data(self):
        self.train_tokens,self.train_tags = read_data(self.config.ftrain)
        self.validation_tokens,self.validation_tags = read_data(self.config.fval)
        self.test_tokens,self.test_tags = read_data(self.config.ftest)

    def train(self):
        checkpoint_path = os.path.join(self.config.log_dir, 'model.ckpt')
        data_dirs = self.config.data_paths
        data_helper = DataHelper(self.train_tokens, self.validation_tokens, self.train_tags)

        tf.reset_default_graph()
        log.log('=' * 50)
        log.log('=' * 50)
        log.log(' [*] Checkpoint path: %s' % checkpoint_path)
        log.log(' [*] Loading training data from: %s' % data_dirs)
        log.log(' [*] Using model: %s' % self.config.model_dir)
        log.log(hparams_debug_string())

        global_step = tf.Variable(0,name='global_step', trainable=False)
        saver = tf.train.Saver(max_to_keep=None,keep_checkpoint_every_n_hours=2)
        sess_config=tf.ConfigProto(log_device_placement=False, allow_soft_placement=True)
        sess_config.gpu_options.allow_growth=True

        with tf.variable_scope('model'):
            model=BiLSTMModel()
            model.init()
            train_vars=model.build_layers(hparams=hparams,vocabulary_size=data_helper.gettokencount(),
                                          n_tags=data_helper.gettagcount())
            model.compute_loss(n_tags=data_helper.gettagcount(), PAD_index=data_helper.word2idx('<PAD>'))
            model.perform_optimization(global_step)
            train_stat = model.add_stats()

            log.log('No. of trainable variables : %d' % train_vars)

        with tf.Session(config=sess_config) as sess:
            try:
                summary_writer = tf.summary.FileWriter(self.config.model_dir)
                sess.run(tf.global_variables_initializer())

                start_step = sess.run(global_step)
                log.log('-' * 20 + 'Starting new training' + '-' * 20)
                learning_rate = self.config.learning_rate

                for epoch in range(self.config.n_epochs):
                    log.log('-' * 20 + ' Epoch {}'.format(epoch + 1) + '-' * 20)
                    log.log('Train data evaluation')
                    data_helper.eval_conll(model,sess,self.train_tokens,self.train_tags,short_report=True)

                    for x_batch,y_batch,lengths in data_helper.batches_generator(self.config.batch_size,
                                                                                 self.train_tokens,self.train_tags):
                        step,loss,_ = model.train_on_batch(sess,step,x_batch,None,y_batch,lengths,
                                                           learning_rate,self.config.dropout_keep_probability)
                        if step % 100 == 0:
                            log.log('[Step : %d] loss : %f' % (step,loss))

                    learning_rate = learning_rate/self.config.learning_rate_decay

                    if epoch % self.config.checkpoint_interval == 0:
                        log.log('Saving checkpoint to : %s-%d' % (checkpoint_path,epoch))
                        saver.save(sess,checkpoint_path,global_step=epoch)

                    if epoch % self.config.test_interval == 0:
                        log.log('Validation data evaluation:')
                        data_helper.eval_conll(model,sess,self.validation_tokens,self.validation_tags,short_report=True)

            except Exception as e:
                log.log('Exitin due to exception : [%e]!!!' % e)
                traceback.print_exc()

        return

    def __init__(self):
        parser = argparse.ArgumentParser()

        parser.add_argument('--log_dir', default='log-dir')
        parser.add_argument('--data_paths', required=True)

        parser.add_argument('--batch_size', default=32)
        parser.add_argument('--n_epochs', default=4)
        parser.add_argument('--learning_rate', default=0.005)
        parser.add_argument('--learning_rate_decay', default=np.sqrt(2.0))
        parser.add_argument('--dropout_keep_probability', default=0.9)
        parser.add_argument('--summary_interval', type=int, default=100)
        parser.add_argument('--test_interval', type=int, default=500)
        parser.add_argument('--checkpoint_interval', type=int, default=2000)

        self.config = parser.parse_args()
        self.prepare_dirs(hparams=hparams)
        log_path = os.path.join(self.config.model_dir, 'train.log')
        log.init(log_path)


if __name__ == 'main':
    train = Train()
    train.prepare_data()
    train.train()