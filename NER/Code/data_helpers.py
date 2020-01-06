import numpy as np
from collections import defaultdict
import re
from evaluation import precision_recall_f1


def build_dict(tokens_or_tags, special_tokens):
    """
        tokens_or_tags: a list of lists of tokens or tags
        special_tokens: some special tokens
    """
    tok2idx = defaultdict(lambda: 0)
    idx2tok = []
    idx = 0
    for tokens in [special_tokens] + tokens_or_tags:
        for tok in tokens:
            if tok not in tok2idx:
                tok2idx[tok] = idx
                idx2tok.append(tok)
                idx += 1

    return tok2idx, idx2tok

class DataHelper:
    def __init__(self, train_tokens, validation_tokens, train_tags):
        special_tokens = ['<UNK>', '<PAD>', '<BOS>', '<EOS>']
        special_tags = ['O']

        self.token2idx, self.idx2token = build_dict(train_tokens + validation_tokens, special_tokens)
        self.tag2idx, self.idx2tag = build_dict(train_tags, special_tags)

    def gettokencount(self):
        return len(self.token2idx)

    def gettagcount(self):
        return len(self.tag2idx)

    def words2idxs(self, tokens_list):
        return [self.token2idx[word] for word in tokens_list]

    def tags2idxs(self, tags_list):
        return [self.tag2idx[tag] for tag in tags_list]

    def word2idx(self, word):
        return self.token2idx[word]

    def tag2idx(self, tag):
        return self.tag2idx[tag]

    def idxs2words(self, idxs):
        return [self.idx2token[idx] for idx in idxs]

    def idxs2tags(self, idxs):
        return [self.idx2tag[idx] for idx in idxs]

    def batches_generator(self, batch_size, tokens, tags,
                          shuffle=True, allow_smaller_last_batch=True):
        """Generates padded batches of tokens and tags."""

        n_samples = len(tokens)
        if shuffle:
            order = np.random.permutation(n_samples)
        else:
            order = np.arange(n_samples)

        n_batches = n_samples // batch_size
        if allow_smaller_last_batch and n_samples % batch_size:
            n_batches += 1

        for k in range(n_batches):
            batch_start = k * batch_size
            batch_end = min((k + 1) * batch_size, n_samples)
            current_batch_size = batch_end - batch_start
            x_list = []
            y_list = []
            max_len_token = 0
            for idx in order[batch_start: batch_end]:
                x_list.append(self.words2idxs(tokens[idx]))
                y_list.append(self.tags2idxs(tags[idx]))
                max_len_token = max(max_len_token, len(tags[idx]))

            # Fill in the data into numpy nd-arrays filled with padding indices.
            x = np.ones([current_batch_size, max_len_token], dtype=np.int32) * self.token2idx['<PAD>']
            y = np.ones([current_batch_size, max_len_token], dtype=np.int32) * self.tag2idx['O']
            lengths = np.zeros(current_batch_size, dtype=np.int32)
            for n in range(current_batch_size):
                utt_len = len(x_list[n])
                x[n, :utt_len] = x_list[n]
                lengths[n] = utt_len
                y[n, :utt_len] = y_list[n]
            yield x, y, lengths

    def predict_tags(self, model, session, token_idxs_batch, lengths):
        """Performs predictions and transforms indices to tokens and tags."""

        tag_idxs_batch = model.predict_for_batch(session, token_idxs_batch, lengths)

        tags_batch, tokens_batch = [], []
        for tag_idxs, token_idxs in zip(tag_idxs_batch, token_idxs_batch):
            tags, tokens = [], []
            for tag_idx, token_idx in zip(tag_idxs, token_idxs):
                tags.append(self.idx2tag[tag_idx])
                tokens.append(self.idx2token[token_idx])
            tags_batch.append(tags)
            tokens_batch.append(tokens)
        return tags_batch, tokens_batch

    def eval_conll(self, model, session, tokens, tags, short_report=True):
        """Computes NER quality measures using CONLL shared task script."""

        y_true, y_pred = [], []
        for x_batch, y_batch, lengths in self.batches_generator(1, tokens, tags):
            tags_batch, tokens_batch = self.predict_tags(model, session, x_batch, lengths)
            if len(x_batch[0]) != len(tags_batch[0]):
                raise Exception("Incorrect length of prediction for the input, "
                                "expected length: %i, got: %i" % (len(x_batch[0]), len(tags_batch[0])))
            predicted_tags = []
            ground_truth_tags = []
            for gt_tag_idx, pred_tag, token in zip(y_batch[0], tags_batch[0], tokens_batch[0]):
                if token != '<PAD>':
                    ground_truth_tags.append(self.idx2tag[gt_tag_idx])
                    predicted_tags.append(pred_tag)

            # We extend every prediction and ground truth sequence with 'O' tag
            # to indicate a possible end of entity.
            y_true.extend(ground_truth_tags + ['O'])
            y_pred.extend(predicted_tags + ['O'])

        results = precision_recall_f1(y_true, y_pred, print_results=True, short_report=short_report)
        return results

