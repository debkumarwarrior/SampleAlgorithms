import tensorflow as tf
import numpy as np

class BiLSTMModel:
    def init(self):
        with tf.variable_scope('placehoders'):
            # Placeholders for input and ground truth output.
            self.word_batch = tf.placeholder(dtype=tf.int32, shape=[None, None], name='word_batch')
            self.char_batch = tf.placeholder(dtype=tf.int32, shape=[None, None], name='word_batch')
            self.ground_truth_tags = tf.placeholder(dtype=tf.int32, shape=[None, None],
                                            name='ground_truth_tags')
            # Placeholder for lengths of the sequences.
            self.lengths = tf.placeholder(dtype=tf.int32, shape=[None], name='lengths')

            # Placeholder for a dropout keep probability. If we don't feed
            # a value for this placeholder, it will be equal to 1.0.
            self.dropout_ph = tf.placeholder_with_default(tf.cast(1.0, tf.float32), shape=[])

            # Placeholder for a learning rate (tf.float32).
            self.learning_rate_ph = tf.placeholder(dtype=tf.float32, shape=[],
                                                   name='learning_rate_ph')


    def build_layers(self, hparams, vocabulary_size, n_chars, n_tags):
        input_dim = 0
        inputs = []
        if hparams.word_dim:
            input_dim += hparams.word_dim
            with tf.variable_scope('word_embedding'):
                initial_embedding_matrix = np.random.randn(vocabulary_size, hparams.word_dim) / np.sqrt(hparams.word_dim)
                embedding_matrix_variable = tf.Variable(initial_value=initial_embedding_matrix,
                                                        name='embeddings_matrix',
                                                        dtype=tf.float32)
                word_embedding = tf.nn.embedding_lookup(params=embedding_matrix_variable, ids=self.word_batch)
                inputs.append(word_embedding)

        if hparams.char_dim:
            input_dim += hparams.char_dim
            with tf.variable_scope('char_embedding'):
                initial_embedding_matrix = np.random.randn(n_chars, hparams.word_dim) / np.sqrt(hparams.char_dim)
                embedding_matrix_variable = tf.Variable(initial_value=initial_embedding_matrix,
                                                        name='embeddings_matrix',
                                                        dtype=tf.float32)
                char_embedding = tf.nn.embedding_lookup(params=embedding_matrix_variable, ids=self.char_batch)

                char_lstm_forward = tf.nn.rnn_cell.BasicLSTMCell(num_units=hparams.char_lstm_dim,name='forward_cell')
                char_lstm_backward = tf.nn.rnn_cell.BasicLSTMCell(num_units=hparams.char_lstm_dim,name='backward_cell')

                char_forward_output = tf.transpose(char_lstm_forward, perm=[1, 0, 2], name='forward_transpose')
                char_backward_output = tf.transpose(char_lstm_backward, perm=[1, 0, 2], name='backward_transpose')

                inputs.append(char_forward_output)
                if hparams.char_bidirect:
                    inputs.append(char_backward_output)
                    input_dim += hparams.char_dim

        inputs = tf.concat(inputs,axis=1) if len(inputs) != 1 else inputs[0]


        with tf.variable_scope('encoder'):
            forward_cell = tf.nn.rnn_cell.DropoutWrapper(
                cell=tf.nn.rnn_cell.BasicLSTMCell(num_units=hparams.word_lstm_dim),
                input_keep_prob=self.dropout_ph,
                output_keep_prob=self.dropout_ph,
                state_keep_prob=self.dropout_ph)
            backward_cell = tf.nn.rnn_cell.DropoutWrapper(
                cell=tf.nn.rnn_cell.BasicLSTMCell(num_units=hparams.word_lstm_dim),
                input_keep_prob=self.dropout_ph,
                output_keep_prob=self.dropout_ph,
                state_keep_prob=self.dropout_ph)

            (rnn_output_fw, rnn_output_bw), _ =  tf.nn.bidirectional_dynamic_rnn(cell_fw=forward_cell,
                                                                                 cell_bw=backward_cell,
                                                                                 inputs=inputs,
                                                                                 sequence_length=self.lengths,
                                                                                 dtype=tf.float32)
            rnn_output = tf.concat([rnn_output_fw, rnn_output_bw], axis=2)

            self.logits = tf.layers.dense(rnn_output, n_tags, activation=None)


    def compute_predictions(self):
        softmax_output = tf.nn.softmax(self.logits, name='softmax_output')
        self.predictions = tf.argmax(softmax_output, axis=-1, name='predictions')


    def compute_loss(self, n_tags, PAD_index):
        # Create cross entropy function function (tf.nn.softmax_cross_entropy_with_logits_v2)
        ground_truth_tags_one_hot = tf.one_hot(self.ground_truth_tags, n_tags)
        loss_tensor = tf.nn.softmax_cross_entropy_with_logits(logits=self.logits,
                                                          labels=ground_truth_tags_one_hot)

        mask = tf.cast(tf.not_equal(self.word_batch, PAD_index), tf.float32)
        self.loss = tf.reduce_mean(mask * loss_tensor)


    def perform_optimization(self):
        """Specifies the optimizer and train_op for the model."""

        # Create an optimizer (tf.train.AdamOptimizer)
        self.optimizer = tf.train.AdamOptimizer(learning_rate=self.learning_rate_ph)
        self.grads_and_vars = self.optimizer.compute_gradients(self.loss)

        clip_norm = tf.cast(1.0, tf.float32)
        self.grads_and_vars = [(tf.clip_by_norm(grad, clip_norm), var) for grad, var in
                                                 self.grads_and_vars]

        self.train_op = self.optimizer.apply_gradients(self.grads_and_vars)


    def train_on_batch(self, session, words,chars, tags, lengths, learning_rate, dropout_keep_probability):
        feed_dict = {self.word_batch: words,
                     self.char_batch: chars,
                     self.ground_truth_tags: tags,
                     self.learning_rate_ph: learning_rate,
                     self.dropout_ph: dropout_keep_probability,
                     self.lengths: lengths}

        session.run(self.train_op, feed_dict=feed_dict)

    def predict_for_batch(self, session, words, chars, lengths):
        predictions = session.run(self.predictions, feed_dict={self.word_batch: words,
                                                               self.char_batch:chars,
                                                               self.lengths: lengths})

        return predictions

