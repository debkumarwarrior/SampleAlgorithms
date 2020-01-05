import numpy as np
import sys
from model import BiLSTMModel
import os,argparse

from shutil import copyfile as copy_file
from utils import  load_hparams,save_hparams,get_time
from hparams import hparams, hparams_debug_string


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

    return

def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('--log_dir',default='log-dir')
    parser.add_argument('--train_file',required=True)
    parser.add_argument('--val_file',required=True)

    parser.add_argument('--batch_size',default=32)
    parser.add_argument('--n_epochs',default=4)
    parser.add_argument('--learning_rate',default=0.005)
    parser.add_argument('--learning_rate_decay',default=np.sqrt(2.0))
    parser.add_argument('--dropout_keep_probability',default=0.9)

    config = parser.parse_args()

    prepare_dirs(config,hparams=hparams)

    train(config)





if __name__ == 'main':
    main()