import numpy as np
import sys
from model import BiLSTMModel
import os,argparse,traceback

from shutil import copyfile as copy_file
from utils import  load_hparams,save_hparams,get_time
from hparams import hparams, hparams_debug_string
import infolog
import tensorflow as tf

log = infolog.Log
tf.logging.set_verbosity(tf.logging.ERROR)

def prepare_dirs(config, hparams):
    if hasattr(config, "data_paths"):
        config.datasets = [os.path.basename(data_path) for data_path in config.data_paths]
        dataset_desc = "+".join(config.datasets)

    if config.load_path:
        config.model_dir = config.load_path
    else:
        config.model_name = "{}_{}".format(dataset_desc, get_time())
        config.model_dir = os.path.join(config.log_dir, config.model_name)

        for path in [config.log_dir, config.model_dir]:
            if not os.path.exists(path):
                os.makedirs(path)

    if config.load_path:
        load_hparams(hparams, config.model_dir)
    else:
        setattr(hparams, "num_speakers", len(config.datasets))

        save_hparams(config.model_dir, hparams)
        copy_file("hparams.py", os.path.join(config.model_dir, "hparams.py"))

def train(config):
    checkpoint_path = os.path.join(config.log_dir,'model.ckpt')
    data_dirs = config.data_paths

    log.log('='*50)
    log.log('='*50)
    log.log(' [*] Checkpoint path: %s' % checkpoint_path)
    log.log(' [*] Loading training data from: %s' % data_dirs)
    log.log(' [*] Using model: %s' % config.model_dir)  # 'logdir-tacotron\\moon_2018-08-28_13-06-42'
    log.log(hparams_debug_string())

    global_step = tf.Variable(0, name='global_step', trainable=False)
    saver = tf.train.Saver(max_to_keep=None, keep_checkpoint_every_n_hours=2)
    sess_config = tf.ConfigProto(log_device_placement=False,allow_soft_placement=True)
    sess_config.gpu_options.allow_growth=True

    tf.reset_default_graph()
    with tf.variable_scope('model'):
        model = BiLSTMModel()
        model.init()
        model.build_layers()
        model.compute_predictions()
        model.compute_loss()
        model.perform_optimization()

    with tf.Session(config=sess_config) as sess:
        try:
            summary_writer = tf.summary.FileWriter(config.log_dir, sess.graph)
            sess.run(tf.global_variables_initializer())
            start_step = sess.run(global_step)

        except Exception as e:
            log.log('Exiting due to exception: %s' % e)
            traceback.print_exc()

    return

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('--log_dir',default='log-dir')
    parser.add_argument('--data_paths',required=True)

    parser.add_argument('--batch_size',default=32)
    parser.add_argument('--n_epochs',default=4)
    parser.add_argument('--learning_rate',default=0.005)
    parser.add_argument('--learning_rate_decay',default=np.sqrt(2.0))
    parser.add_argument('--dropout_keep_probability',default=0.9)

    config = parser.parse_args()
    log_path = os.path.join(config.model_dir, 'train.log')
    log.init(log_path)

    prepare_dirs(config,hparams=hparams)

    train(config)





if __name__ == 'main':
    main()