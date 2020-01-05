import tensorflow as tf

hparams = tf.contrib.training.HParams(
    char_dims = 25,
    char_lstm_dim = 25,
    char_bidirect = True,
    word_dim = 100,
    word_lstm_dim = 100,
    word_bidirect = True,
    cap_dim = False,
    dropout = 0.5,
    lr_method = "sgd-lr_.005"
)

def hparams_debug_string():
  values = hparams.values()
  hp = ['  %s: %s' % (name, values[name]) for name in sorted(values)]
  return 'Hyperparameters:\n' + '\n'.join(hp)