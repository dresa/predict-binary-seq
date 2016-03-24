# predict-binary-seq
Predictor for a binary sequence: is your sequence of 0's and 1's truly random?

People often have a biased understanding of randomness. In fact, many sequences that
humans consider truly random actually contain patterns that can be easily
identified by even simplest machine learning methods.

For example, here are example binary sequences and the prediction
accuracy achieved by the predictor program:

| Sequence of 0's and 1's                                                          | Prediction accuracy |
| -------------------------------------------------------------------------------- | ------------------- |
| ``1111111110000000001111111111000000000000111111111111100000000000``             | 68.59%              |
| ``1110101010110001001010011110101010101010101100100010101010101010101010100101`` | 63.09%              |
| from file binary.txt                                                             | 56.32%              |
| ``1011010010010010001101010100111010001001010101010111010101110010100101010111`` | 55.06%              |
| ``11100000111101000011000100010000000100100101011001`` from a rnd generator      | 48.46%              |

After building the source, running the main program prompts the user to input a sequence
of 0's and 1's without whitepace. To give the program a chance, the sequence needs
to have at least 20 digits. The longer the sequence is, the better the accuracy.

As far as methodology goes, the program learns a simple n-context Markov model
that it uses to predict the numbers you entered. As it turns out, people tend
to avoid repeating a digit many times, which makes the sequence less random.
The model exploits the fact that following digit can sometimes be deduced from
the recent history of digits.

Using a decent random number generator to form a binary sequence (of length 60+)
should lead to a prediction accuracy close to 50%. If the accuracy
is below 47% or above 53%, then I daresay the sequence is not truly random.

The program has been written in C, namely original ANSI C.
As a simple program, I kept everything within a single file.

