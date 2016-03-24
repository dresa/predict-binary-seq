/* Esa Junttila, 25.4.2006 */

/*
Program gets a sequence of digits and learns from it.
Program then tries to predict following digits.

 Input: sequence of zeros and ones
Output: prediction accuracy
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_DIGITS 20
#define MAX_DIGITS 10000

/* Change following constants simultaneously: */
#define CONTEXT_LENGTH 4
#define CONTEXT_COMBINATIONS 16 /*  = 2 ^ CONTEXT_LENGTH  */

#define INITIAL_FREQUENCY 1
#define END_OF_SEQUENCE '-'


/* function prototypes */
void printPrompt(FILE *pOut);
void setRandom(void);
void processSequence(FILE *pIn, FILE *pOut);
void checkAndConvertSequence(char sequence[]);
void predict(char sequence[], FILE *pOut);
int getContextCode(char sequence[], int contextIndex);


int main() {
	FILE *pIn = stdin;
	FILE *pOut = stdout;

	printPrompt(pOut);
	setRandom();

	processSequence(pIn, pOut);

  /* generate some random numbers between 0 and 32767 */
/*	rand()*/
}


void printPrompt(FILE *pOut) {
	fprintf(pOut, "\n");
	fprintf(pOut, " ************ BINARY PREDICTOR ************\n");
	fprintf(pOut, " * - Type a sequence of at least %d zeros"
		" and ones.\n", MIN_DIGITS);
	fprintf(pOut, " * - Use a sequence that you consider 'randomized'.\n");
	fprintf(pOut, " * - Do not use any other characters than"
		"zeros and ones.\n");
	fprintf(pOut, " * - Are you able to create such a sequence so that\n");
	fprintf(pOut, " *   the program predicts it poorly,"
		" that is [prediction accuracy] < 52%%?\n");
	fprintf(pOut, " ******************************************\n");
	fprintf(pOut, "\n");
	fprintf(pOut, "--> ");
}


void setRandom() {
  /* initialize random number generator with current timestamp */
  srand ( time(NULL) );
}


void processSequence(FILE *pIn, FILE *pOut) {
	char sequence[MAX_DIGITS + 1];

	fscanf(pIn, "%s", &sequence);
	checkAndConvertSequence(sequence);

	/* convert to numbers */
	predict(sequence, pOut);
}


void checkAndConvertSequence(char sequence[]) {
	int c;
	int i = 0;

	while ( (c = sequence[i]) != '\0') {
		if (c != '1' && c != '0') {
			fprintf(stderr, "Illegal input digit: '%c'\n", c);
			exit(EXIT_FAILURE);
		}

		/* convert ascii numbers '0' and '1' to numbers 0 and 1*/
		sequence[i] = c - '0';
		i++;
	}
	sequence[i] = END_OF_SEQUENCE;

	if (i < MIN_DIGITS) {
		fprintf(stderr, "Too short input sequence"
			" (at least %d digits required)\n", MIN_DIGITS);
		exit(EXIT_FAILURE);
	}
}


void predict(char sequence[], FILE *pOut) {
	int frequencyOne[CONTEXT_COMBINATIONS];
	int frequencyZero[CONTEXT_COMBINATIONS];
	int i;
	int dig;
	int digitIndex;
	int code;
	float percentage;
	float averagePercentage;

	/* check first CONTEXT_LENGTH digits */
	for (i = 0; i < CONTEXT_LENGTH; i++) {
		if (sequence[i] != 1 && sequence[i] != 0) {
			fprintf(stderr, "Internal error: predictor()");
			exit(EXIT_FAILURE);
		}
	}

	/* initialize frequency tables */
	for (i = 0; i < CONTEXT_COMBINATIONS; i++) {
		frequencyOne[i] = INITIAL_FREQUENCY;
		frequencyZero[i] = INITIAL_FREQUENCY;
	}

	for (i = 0; i < CONTEXT_LENGTH; i++) {
		if (i == 0) {
			fprintf(pOut, "(50%%)");
		}
		else {
			fprintf(pOut, ", (50%%)");
		}
	}
	averagePercentage = CONTEXT_LENGTH * 50.0;

	digitIndex = CONTEXT_LENGTH;
	while ( (dig = sequence[digitIndex]) != END_OF_SEQUENCE) {
		/* for each digit with index >= 3 */
/*printf("[%d]", dig);*/
		code = getContextCode(sequence, digitIndex);

		if (dig == 0) {
			percentage = 100.0 * frequencyZero[code] /
				(frequencyOne[code] + frequencyZero[code]);
			frequencyZero[code]++;
		}
		else if (dig == 1) {
			percentage = 100.0 * frequencyOne[code] /
				(frequencyOne[code] + frequencyZero[code]);
			frequencyOne[code]++;
		}
		else {
			fprintf(stderr, "Internal error: predictor2()");
			printf("ERROR(%d)", dig);
			exit(EXIT_FAILURE);
		}

		if (digitIndex == 0) {
			fprintf(pOut, "%.2f%%", percentage);
		}
		else {
			fprintf(pOut, ", %.2f%%", percentage);
		}
		averagePercentage += percentage;
		digitIndex++;
	}
	averagePercentage /= digitIndex;
	fprintf(pOut, "\n\n Average prediction accuracy:"
		" %.2f%%\n", averagePercentage);
}


int getContextCode(char sequence[], int contextIndex) {
	int code;
	int i;

	if (contextIndex < CONTEXT_LENGTH) {
		fprintf(stderr, "Internal error: contextCode()");
		exit(EXIT_FAILURE);
	}

	code = 0;
	for (i = 1; i < CONTEXT_LENGTH + 1; i++) {
		code = 2 * code + sequence[contextIndex - i];
	}

	return code;
}
