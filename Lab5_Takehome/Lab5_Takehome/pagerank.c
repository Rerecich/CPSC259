/*
File:         pagerank.c
Purpose:      
Author:		 Sarah Rerecich
Student #s:		65693236
CS Accounts:	sarahr25
Date:			Dec. 2023
*/
//*****************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "engine.h"

#define FILE_NAME           "web.txt"
#define BUF_SIZE 256

void printMatrix(mxArray* inputMatrix, size_t size);
double* parseMatrix(FILE* pointer_to_data_file, size_t size);
size_t get_dimension(FILE* fp);
void calculate_page_rank(Engine* fp);
void print_result(mxArray*, size_t size);
void debugging(Engine* ep, size_t rows, size_t columns, char* variable);


int main()
{
	/*---------------------------------------------------*/
	/****************************************************/
	/*----------------------Variables-------------------*/
	
	/*Funcitonal*/
	size_t size;

	/*Input/Output*/
	double* input_file = NULL; // Copy the data file to this array
	FILE* txt_file = NULL;
	
	/*MATLAB Considerations*/
	Engine* ep = NULL; // A pointer to a MATLAB engine object
	mxArray* mx_web_matrix = NULL;
	double* vs_web_matrix = NULL; //Visual Studio-friendly matrix
	mxArray* result = NULL;
	char buffer[BUF_SIZE + 1];

	/*---------------------------------------------------*/
	/****************************************************/
	/*---------------------I/O--------------------------*/

	/*Open file, read*/
	printf("Opening file...");
	if (fopen_s(&txt_file, FILE_NAME, "r")) {
		fprintf(stderr, "Unable to open file: %s\n", FILE_NAME);
		system("pause");
	}
	printf("Complete\n");

	/*Get matrix size*/
	if (txt_file) {
		size = get_dimension(txt_file);

		if (size <= 0) {
			fprintf(stderr, "Invalid dimensions\n");
			system("pause");
			exit(1);
		}
	}

	/*Translate file contents into array*/
	printf("Parsing matrix to memory...");
	vs_web_matrix = parseMatrix(txt_file, size);
	printf("Successfully processed file: %s\n", FILE_NAME); 
	
	if (txt_file != NULL) {
		fclose(txt_file);
	}

	/*---------------------------------------------------*/
	/****************************************************/
	/*------------------MATLAB fun----------------------*/


	
	/*Starting MATLAB*/
	printf("Starting matlab engine...");
	if (!(ep = engOpen(NULL))) {
		fprintf(stderr, "\nCannot start MATLAB\n");
		system("pause");
		exit(1);
	}
	printf("Complete\n");

	mx_web_matrix = mxCreateDoubleMatrix(size, size, mxREAL); //2D double-precision floating point array initialized to 0, or returns NULL on failure
	memcpy(mxGetPr(mx_web_matrix), vs_web_matrix, (size*size) * sizeof(double));

	//printf("web matrix: \n");
	//printMatrix(mx_web_matrix, size);

	/*Places test arrays into MATLAB workspace*/
	printf("Writing connection matrix to MATLAB...");
	if (engPutVariable(ep, "ConnectivityMatrix", mx_web_matrix)) {
		fprintf(stderr, "\nCannot write connection matrix to MATLAB \n");
		system("pause");
		exit(1); 
	}
	printf("Complete\n");
	
	printf("Retrieving PageRank...\n");
	calculate_page_rank(ep);
	if ((result = engGetVariable(ep, "PageRank")) == NULL) {
		fprintf(stderr, "\nFailed to retrieve PageRank\n");
		system("pause");
		exit(1);
	}

	print_result(result, size);
	
	/*Free memory, close connection to MATLAB*/
	mxDestroyArray(mx_web_matrix);
	mx_web_matrix = NULL;

	if (engClose(ep)) {
		fprintf(stderr, "\nFailed to close MATLAB engine\n");
	}

	system("pause"); // So the terminal window remains open long enough for you to read it
	return 0; // Because main returns 0 for successful completion

}

/*
 Parses matrix from webfile to a local 1D array; some code taken from my lab 1, lab 4
 PARM:      webfile is a file pointer to a formatted connectivity matrix
 PARM:      size is a size_t data type holding the side length of the matrix, excluding white spaces
 PRE:       webfile properly formatted, exactly one space between sequential entries
 POST:      none
 RETURN:    webmatrix, a pointer to a dynamically allocated 1D array in memory
 */
double* parseMatrix(FILE* webfile, size_t size) {
	
	char line_buffer[BUF_SIZE];
	int row, column;
	double* webmatrix = NULL;

	/*Memory allocation*/
	webmatrix = malloc((size*size) * sizeof(double));

	/*Copying data to memory*/
	row = 0;
	while (fgets(line_buffer, BUF_SIZE, webfile)) {
		for (column = 0; column < size; column++) {
			// column * 2 to account for whitespace
			webmatrix[column * size + row] = line_buffer[column * 2] - 48;
		}
		row++;
	}
	return webmatrix;
}


/*
 Prints given matrix
 PARM:      inputMatrix is a mxArray* data type
 PARM:      size is a size_t data type holding the side length of the matrix, excluding white spaces
 PRE:       inputMatrix is a square matrix, size > 0
 POST:      contents of inputMatrix are printed in terminal, appropriately formatted
 RETURN:    none
 */
void printMatrix(mxArray* inputMatrix, size_t size) {
	size_t row = 0;
	size_t column = 0;

	for (row = 0; row < size; row++) {
		printf(" ");
		for (column = 0; column < size; column++) {
			printf("%1.0f ", mxGetPr(inputMatrix)[column * size + row]);
		}
		printf("\n");
	}
}


/*
 Returns the size of the matrix contained in a file pointed to by FILE* fp
 PARM:      webfile is a file pointer to a square formatted connectivity matrix
 PRE:       webfile is a square matrix with equally spaced entries
 POST:      if webfile is improperly formatted (ie not exactly one space between indices), program exits
 RETURN:    size, a size_t variable type containing the side length of the matrix
 */
size_t get_dimension(FILE* fp)
{
	size_t size;
	int spaces = 0;
	int i = 0;
	char line_buffer[BUF_SIZE] = { NULL };


	fgets(line_buffer, BUF_SIZE, fp);
	fseek(fp, 0, SEEK_SET);

	while (line_buffer[i] != '\n') {
		if (line_buffer[i] == ' ') {
			spaces++;
		}
		i++;
	}

	if (spaces != (strlen(line_buffer)-1)/2) {
		fprintf(stderr, "Error: Improper formatting of matrix.\n");
		system("pause");
		exit(1);
	}

	size = strlen(line_buffer) - spaces - 1;

	return size;
}


/*
 Calculates the Google PageRank algorithm using the MATLAB engine
 PARM:      ep is an Engine* that points to a connectivity matrix variable in the MATLAB environment
 PRE:       ep contains a properly formatted square connectivity matrix
 POST:      the variable PageRank in the MATLAB environments contains the 1 x size matrix with the PageRank for given file
 RETURN:    none
 */
void calculate_page_rank(Engine* ep)
{
	mxArray* result;
	///*Calculate with MATLAB engine*/
	
	if (engEvalString(ep, "dimension = size(ConnectivityMatrix, 1);")) {
		fprintf(stderr, "\nError calculating dimensions  \n");
		system("pause");
		exit(1);
	}
	printf("\nSuccessfully calculated dimensions...\n");

	//debugging(ep, 1, 1, "dimension");
	//debugging(ep, 6, 6, "ConnectivityMatrix");

	if (engEvalString(ep, "columnsums = sum(ConnectivityMatrix, 1);")) {
		fprintf(stderr, "\nError calculating column sums  \n");
		system("pause");
		exit(1);
	}

	//debugging(ep, 6, 1, "columnsums");

	
	if (engEvalString(ep, "p = 0.85")) {
		fprintf(stderr, "\nError setting random walk probability factor \n");
		system("pause");
		exit(1);
	}


	//debugging(ep, 1, 1, "p");

	/*Generating stochastic matrix*/
	printf("Generating stochastic matrix...");
	if (engEvalString(ep, "zerocolumns = find(columnsums~=0);")) {
		fprintf(stderr, "\nError finding zero columns\n");
		system("pause");
		exit(1);
	}


	//debugging(ep, 6, 1, "zerocolumns");

	if (engEvalString(ep, "D = sparse( zerocolumns, zerocolumns, 1./columnsums(zerocolumns), dimension, dimension);")) {
		fprintf(stderr, "\nError generating sparse matrix\n");
		system("pause");
		exit(1);
	}

	//debugging(ep, 6, 1, "D");

	if (engEvalString(ep, "StochasticMatrix = ConnectivityMatrix * D;")) {
		fprintf(stderr, "\nError generating stochastic matrix\n");
		system("pause");
		exit(1);
	}

	if (engEvalString(ep, "[row, column] = find(columnsums==0)")) {
		fprintf(stderr, "\nError finding columns with 0 sums\n");
		system("pause");
		exit(1);
	}
	printf("Complete\n");

	//debugging(ep, 6, 6, "StochasticMatrix");

	/*Generate transition matrix*/
	printf("Generating transition matrix...");
	if (engEvalString(ep, "StochasticMatrix(:, column) = 1./dimension;")) {
		fprintf(stderr, "\nError generating stochastic matrix\n");
		system("pause");
		exit(1);
	}

	if (engEvalString(ep, "Q = ones(dimension, dimension);")) {
		fprintf(stderr, "\nError generating ones matrix\n");
		system("pause");
		exit(1);
	}

	if (engEvalString(ep, "TransitionMatrix = p * StochasticMatrix + (1 - p) * (Q/dimension);")) {
		fprintf(stderr, "\nError generating transition matrix\n");
		system("pause");
		exit(1);
	}
	printf("Complete\n");

	//debugging(ep, 6, 6, "TransitionMatrix");

	/*Completing pagerank*/
	printf("Computing PageRank...");
	if (engEvalString(ep, "PageRank = ones(dimension, 1);")) {
		fprintf(stderr, "\nError generating ones matrix\n");
		system("pause");
		exit(1);
	}

	if (engEvalString(ep, "for i = 1:100 PageRank = TransitionMatrix * PageRank; end")) {
		fprintf(stderr, "\nError in for loop\n");
		system("pause");
		exit(1);
	}

	if (engEvalString(ep, "PageRank = PageRank / sum(PageRank);")) {
		fprintf(stderr, "\nError calculating PageRank\n");
		system("pause");
		exit(1);
	}
	printf("Complete\n\n");

}


/*
 Prints result from MATLAB in specified format
 PARM:      result is a properly formatted mxArray* pointing to the PageRank 1 x size matrix
 PARM:      size is a size_t data type that contains the number of rows (ie number of links) in the webfile
 PRE:       result properly formatted 1 x size matrix, size contains the non-zero size of the matrix
 POST:      PageRank results are printed to terminal in the requested form
 RETURN:    none
 */
void print_result(mxArray* result, size_t size)
{
	int row;

	printf("\n\nNODE  RANK\n");
	printf("---   ----\n");

	for (row = 0; row < size; row++) {
		printf("%d     ", row + 1);
		printf("%1.4f ", mxGetPr(result)[row]);
		printf("\n");
	}
}


/*
 A helpful function for checking MATLAB variables - prints given variable on terminal screen
 PARM:      ep is an Engine* pointing to MATLAB environment 
 PARM:      rows is a size_t data type containing the number of rows expected in the output
 PARM:      columns is a size_t data type containing the number of columns expected in the output
 PARM:      variable is a string containing the MATLAB variable we are trying to verify
 PRE:       ep* not NULL
 POST:      the MATLAB variable specified in the input is printed into terminal 
 RETURN:	none
 */
void debugging(Engine* ep, size_t rows, size_t columns, char* variable)
{
	mxArray* result;
	int row, column;

	printf("\n\n********IDIOT CHECK************\n\n");

	if ((result = engGetVariable(ep, variable)) == NULL) {
		fprintf(stderr, "\nFailed to retrieve variable\n");
		system("pause");
		exit(1);
	}
	printf("%s: \n", variable);

	if (columns == 1) {
		for (row = 0; row < rows; row++) {
			printf("%1.3f ", mxGetPr(result)[row]);
		}
	}

	else {
		printMatrix(result, rows);
	}

	printf("\n*********************************\n\n");
}