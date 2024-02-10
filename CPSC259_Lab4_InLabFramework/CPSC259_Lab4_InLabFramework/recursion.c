/*
 File:          recursion.c
 Purpose:       Exercises for CPSC259 lab 4
 Author:		Sarah Rerecich
 Student #s:	65693236
 CWLs:		    sarahr25
 Date:			Nov 2023
 */

 /******************************************************************
	PLEASE EDIT THIS FILE

	Comments that start with // should be replaced with code
	Comments that are surrounded by * are hints
	******************************************************************/

//_CRT_SECURE_NO_WARNINGS

	/* Preprocessor directives */
#include "recursion.h"
//#define INT_MAX 1000

//#include <string.h>


/*
 Calculates the power.
 PARAM:     base is an integer
 PARAM:     power is an integer
 PRE:       power >= 0
 PRE:       base != 0
 RETURN:    base^power
 */
int calculate_power(int base, int power)
{

	//base case power 0, which is 1
	if (power == 0) {
		return 1;
	}
	
	//recursive part: base, then base*base, then base*base*base until occurences of base = power
	//also think of it like previous answer, previous answer * base, that previous answer * base
	else {
		return(base * (calculate_power(base, power - 1)));
	}
}

/*
 Returns the number of digits in an integer
 PARAM:     number is an integer
 PRE:       0 < number <= INT_MAX
 RETURN:    the number of digits in the number
 */
int count_digits(int number)
{
	if (number/10 == 0) {
		return 1;
	}

	else {
		return(1 + count_digits(number / 10));
	}
}

/*
 Returns the length of the specified string.
 PARAM:  string, a pointer to an array of char
 PRE:    the string pointer is not a dangling pointer
 RETURN: the length of the string passed as a parameter
 */
int string_length(char* string)
{
	//int i = 0;
	if (*string == '\0') {
 		return 0;
	}

	else {
		return(1 + string_length(string + 1));
	}
}

/*
 Determines if a string is a palindrome.  DOES NOT skip spaces!
 For example,
 ""     -> returns 1 (an empty string is a palindrome)
 "the"  -> returns 0
 "abba" -> returns 1
 "Abba" -> returns 0
 "never odd or even" -> returns 0
 For the recursive call, be aware that both parameters can be modified.
 PARAM:  string, a pointer to an array of char
 PARAM:  string_length, the length of the string
 PRE:    the string pointer is not a dangling pointer
 PRE:    string_length is the correct length of the string
 RETURN: IF string is a palindrome
				 THEN 1
		 END 0
 */
int is_palindrome(char* string, int string_length)
{
	if (string_length <= 1) {
		return 1;
	}

	else {
		if (*string == *(string + (string_length - 1))) {
			return(is_palindrome(string + 1, string_length - 2));
		}
		else {
			return 0;
		}
	}
}

/*
 Draws a ramp.  The length of the longest rows is specified by the parameter.
 For the recursive call, be aware that both parameters can be modified.
 PARAM:     number, an integer
 PARAM:     buffer, a character array of sufficient length
 PRE:       number >= 1
						buffer has sufficient length and contains null characters from the buffer
						address to the end of its length
 POST:      draws a ramp whose height is the specified number into buffer
 RETURN:    the number of characters written into buffer. Don't forget to count your
						newline characters!
 */
int draw_ramp(int number, char* buffer)
{
	int count = 0;


	if (number == 1) { //this could mean size is one or that we are at half way point
		draw_row(number, buffer);
		return 1;
	}
	
	else {
		count += draw_row(number, buffer); //count += number of characters in row
		
		*(buffer + number) = '\n';
		count++; //for the newline character
		
		count += draw_ramp(number - 1, buffer + count); //going down
		*(buffer + count) = '\n'; //once number is 1, the original if statement doesn't add a newline character
		count++;

		count += draw_row(number, buffer + count); //going up
		return count;
		}
	}


//if (number == 1) { //this could mean size is one or that we are at half way point
//	if (count == 0) { //if the starting size is 1
//		draw_row(number, buffer);
//		return 1;
//	}
//
//	else { //if we're half way and moving to upward pointed triangle
//		count += number;
//		draw_row(number, buffer);
//		*(buffer + number) = '\n';
//		count += draw_ramp(number + 1, buffer + (number + 1));
//
//	}
//}
//
//else {
//	count += number;
//	draw_row(number, buffer);
//	*(buffer + number) = '\n';
//	count += draw_ramp(number - 1, buffer + (number + 1));
//
//}
	
	
	
	





/*
 Draws a row of asterisks of the specified length
 For the recursive call, be aware that both parameters can be modified.
 PARAM:  size, an integer
 PARAM:  buffer, a character array of sufficient length
 PRE:    size >= 1
				 buffer has sufficient length and contains null characters from the buffer
				 address to the end of its length
 POST:   draws a row of asterisks of specified length to buffer
 RETURN: the number of characters drawn
 */
int draw_row(int size, char* buffer)
{
	//int i = 0;
	//
	//for (i = 0; i < size; i++) {
	//	strcat(buffer, "*");
	//}
	//strcat(buffer, "\n");
	//
	//return 0;

	if (size == 1) {
		*buffer = '*';
		return 1;
	}

	else {
		*buffer = '*';
		return (1 + draw_row(size - 1, buffer + 1));
	}
}