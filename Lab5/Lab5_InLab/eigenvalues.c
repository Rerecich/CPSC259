#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define  BUFSIZE 256

void main()
{
	/* Variables */
	Engine* ep = NULL; // A pointer to a MATLAB engine object
	mxArray* testArray = NULL, * result = NULL; // mxArray is the fundamental type underlying MATLAB data
	double time[3][3] = { { 1.0, 2.0, 3.0 }, {4.0, 5.0, 6.0 }, {7.0, 8.0, 9.0 } }; // Our test 'matrix', a 2-D array
	char buffer[BUFSIZ + 1];

	/* Starts a MATLAB process */
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCan't start MATLAB engine\n");
		system("pause");
		return 1;
	}

	/*Creates MATLAB-friendly variable for test data*/
	testArray = mxCreateDoubleMatrix(3, 3, mxREAL); //2D double-precision floating point array initialized to 0, or returns NULL on failure

	/*Copies data from local 2D array /time/ to the MATLAB variable /testArray/ */
	memcpy((void*)mxGetPr(testArray), (void*)time, 9 * sizeof(double));

	/*Places test array into MATLAB workspace*/
	if (engPutVariable(ep, "testArray", testArray)) {
		fprintf(stderr, "\nCannot write test array to MATLAB \n");
		system("pause");
		exit(1); // Same as return 1;
	}

	/*Calculate eigenvalues with MATLAB engine*/
	if (engEvalString(ep, "testArrayEigen = eig(testArray)")) {
		fprintf(stderr, "\nError calculating eigenvalues  \n");
		system("pause");
		exit(1);
	}

	printf("\nRetrieving eigenvector\n");
	if ((result = engGetVariable(ep, "testArrayEigen")) == NULL) {
		fprintf(stderr, "\nFailed to retrieve eigenvalue vector\n");
		system("pause");
		exit(1);
	}
	else {
		size_t sizeOfResult = mxGetNumberOfElements(result);
		size_t i = 0;
		printf("The eigenvalues are:\n");
		for (i = 0; i < sizeOfResult; ++i) {
			printf("%f\n", *(mxGetPr(result) + i));
		}
	}

	/*Echo MATLAB output*/
	if (engOutputBuffer(ep, buffer, BUFSIZE)) {
		fprintf(stderr, "\nCan't create buffer for MATLAB output\n");
		system("pause");
		return 1;
	}
	
	buffer[BUFSIZE] = '\0';

	/*
	engEvalString(ep, "whos"); // whos is a handy MATLAB command that generates a list of all current variables
	printf("%s\n", buffer);
	*/

	/*Free memory, close connection to MATLAB*/
	mxDestroyArray(testArray);
	mxDestroyArray(result);
	testArray = NULL;
	result = NULL;
	if (engClose(ep)) {
		fprintf(stderr, "\nFailed to close MATLAB engine\n");
	}

	system("pause"); // So the terminal window remains open long enough for you to read it
	return 0; // Because main returns 0 for successful completion

}