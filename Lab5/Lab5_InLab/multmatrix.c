#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define  BUFSIZE 256

void printMatrix(mxArray* inputMatrix);

void main()
{
	/* Variables */
	Engine* ep = NULL; // A pointer to a MATLAB engine object
	mxArray* testArray1 = NULL, * testArray2 = NULL, * result = NULL; // mxArray is the fundamental type underlying MATLAB data
	double matrixOne[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } }; // Our test 'matrix', a 2-D array
	double matrixTwo[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } };
	char buffer[BUFSIZ + 1];

	/* Starts a MATLAB process */
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		system("pause");
		return 1;
	}

	/*Creates MATLAB-friendly variable for test data*/
	testArray1 = mxCreateDoubleMatrix(3, 3, mxREAL); //2D double-precision floating point array initialized to 0, or returns NULL on failure
	testArray2 = mxCreateDoubleMatrix(3, 3, mxREAL); //2D double-precision floating point array initialized to 0, or returns NULL on failure

	/*Copies data from local 2D array matrixOne and matrixTwo to the MATLAB variables testArray1 and testArray2 */
	memcpy((void*)mxGetPr(testArray1), (void*)matrixOne, 9 * sizeof(double));
	memcpy((void*)mxGetPr(testArray2), (void*)matrixTwo, 9 * sizeof(double));

	if (engOutputBuffer(ep, buffer, BUFSIZE)) {
		fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
		system("pause");
		return 1;
	}

	/*Places test arrays into MATLAB workspace*/
	if (engPutVariable(ep, "testArray1", testArray1)) {
		fprintf(stderr, "\nCannot write testArray1 to MATLAB \n");
		system("pause");
		exit(1); // Same as return 1;
	}
	if (engPutVariable(ep, "testArray2", testArray2)) {
		fprintf(stderr, "\nCannot write testArray2 to MATLAB \n");
		system("pause");
		exit(1); // Same as return 1;
	}

	printf("matrixOne = \n");
	printMatrix(testArray1);
	printf("matrixTwo = \n");
	printMatrix(testArray2);

	/*Calculate product with MATLAB engine*/
	if (engEvalString(ep, "testArraysProduct = testArray1 * testArray2")) {
		fprintf(stderr, "\nError calculating eigenvalues  \n");
		system("pause");
		exit(1);
	}

	printf("\nRetrieving product\n");
	if ((result = engGetVariable(ep, "testArraysProduct")) == NULL) {
		fprintf(stderr, "\nFailed to retrieve product\n");
		system("pause");
		exit(1);
	}
	//at this point, /result/ is storing /testArraysProduct/, is the else necessary?
	//else {
	//	size_t sizeOfResult = mxGetNumberOfElements(result);
	//	size_t i = 0;
	//	printf("The product is:\n");
	//	for (i = 0; i < sizeOfResult; ++i) {
	//		printf("%f\n", *(mxGetPr(result) + i));
	//	}
	//}

	printf("Product: \n");
	printMatrix(result);

	/*Echo MATLAB output*/
	//if (engOutputBuffer(ep, buffer, BUFSIZE)) {
	//	fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
	//	system("pause");
	//	return 1;
	//}
	
	buffer[BUFSIZE] = '\0';

	/*
	engEvalString(ep, "whos"); // whos is a handy MATLAB command that generates a list of all current variables
	printf("%s\n", buffer);
	*/

	/*Free memory, close connection to MATLAB*/
	mxDestroyArray(testArray1);
	mxDestroyArray(testArray2);
	mxDestroyArray(result);
	testArray1 = NULL;
	testArray2 = NULL;
	result = NULL;
	if (engClose(ep)) {
		fprintf(stderr, "\nFailed to close MATLAB engine\n");
	}

	system("pause"); // So the terminal window remains open long enough for you to read it
	return 0; // Because main returns 0 for successful completion

}

void printMatrix(mxArray* inputMatrix) {
	size_t row = 0;
	size_t column = 0;

	for (row = 0; row < 3; row++) {
		printf(" ");
		for (column = 0; column < 3; column++) {
			printf("%3.6f ", mxGetPr(inputMatrix)[row * 3 + column]);
		}
		printf("\n");
	}
}