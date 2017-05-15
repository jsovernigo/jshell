/**
 * 	Julian Sovernigo
 * 	0948924
 * 	gsoverni
 * 	gsoverni@mail.uoguelph.ca
 *
 * 	this code is used to run the shell itself.
 */
#ifndef __GSOVERNIGO_DRIVER_H__
#define __GSOVERNIGO_DRIVER_H__

/**
 *	shellMenu
 *	runs the shell menu that will execute other programs and processes.
 *	IN:			none
 *	OUT:		0 on success.
 *	POST:		processes will be killed.
 *	ERROR:		malloc fails, execvp fails, fork fails, etc.
 */
int shellMenu();

/**
 *	add
 *	adds the numerical arguments together, ignoring the non-numerical ones
 *	IN:			args			- a string array that we can use to pull arguments out of.
 *	OUT:		void
 *	POST:		numbers displayed to screen.
 *	ERROR:		args are NULL
 */
void add(char** args);

/**
 *	mult
 *	multiplies the args together, returning nothing, but printing the product
 *	IN:			args			- the arguments strings
 *	OUT:		void
 *	POST:		displays numbers to the screen.
 *	ERROR:		args are NULL
 */
void mult(char** args);

/**
 *	countArgs
 *	counts the args, prints the number of args and what they are.
 *	IN:			args			- the args that were entered
 *	OUT:		void
 *	POST:		args printed to the screen
 *	ERROR:		args are NULL
 */
void countArgs(char** args);

#endif
