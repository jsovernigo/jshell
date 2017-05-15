/**
 * 	Julian Sovernigo
 * 	0948924
 * 	gsoverni
 * 	gsoverni@mail.uoguelph.ca
 *
 * 	this code is used to run the shell itself.
 */
#include"driver.h"
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

/**
 *  function included from lex.c
 */
extern char ** getln(); 

int shellMenu()
{
	short exit;

	int cpid;
	int i;

	int* pid_arr;

	char** args;

	exit = 0;
	args = NULL;

	cpid = 0;
	pid_arr = malloc(sizeof(int) * 1024);
	printf("JShell\nUniversity of Guelph, 2016. Author: Julian Sovernigo\nProduced for CIS*3110\n");

	/* this is the main loop of the program */
	do
	{
		int pid;
		int numargs;
		int nowait;
		int j;

		char** commands;
		char outfile[256];
		char infile[256];

		outfile[0] = '\0';
		infile[0] = '\0';

		numargs = 0;
		nowait = 0;

		commands = malloc(sizeof(char) * 64);

		/* print prompt, then get the args the user offers */
		printf("~$ ");
		args = getln();

		/* check for the > or the & operator which would require additional action. */
		for(j = 0; args[j] != NULL; j++)
		{
			puts(args[j]);
			if(strcmp(args[j], "&") == 0)
			{
				nowait = 1;
			}
			else if(strcmp(args[j], ">") == 0)
			{
				strcpy(outfile, args[j + 1]);
				j++;
			}
			else if(strcmp(args[j], "<") == 0)
			{
				strcpy(infile, args[j + 1]);
				j++;
			}
			else
			{
				/* add the command to the new args array essentially. */
				commands[numargs] = malloc(sizeof(char) * 256);
				strcpy(commands[numargs], args[j]);
				numargs++;
			}	
		}

		if(*args == NULL)
		{
			continue;
		}
		else
		{
			/* get a new process */
			pid = fork();

			if(pid == 0)
			{
				/* if we were asked to redirect input */
				if(strlen(infile) != 0)
				{
					if(freopen(infile, "r", stdin) == NULL)
					{
						printf("child exited with unknown status\n");
						return(1);
					}	
				}

				/* if we are asked to redirect the output to a file */
				if(strlen(outfile) != 0)
				{
					if(freopen(outfile, "a", stdout) == NULL)
					{
						return(1);
					}
				}
				 
				/* if add has been selected */
				if(strcmp(args[0], "add") == 0)
				{
					add(commands);
					return(0);
				}
				/* if the multiply function has been specified */
				else if(strcmp(args[0], "???") == 0)
				{
					mult(commands);
					return(0);
				}
				/* if the args command has been selected */
				else if(strcmp(args[0], "args") == 0)
				{
					countArgs(args);
					return(0);
				}
				/* if we were asked to exit */
				else if(strcmp(commands[0], "exit") == 0 || strcmp(commands[0], "quit") == 0)
				{
					break;
				}
				/* handles all shell calls that are not predefined above */
				else
				{
					execvp(*commands, commands);
				}
			}
			/* this would be the parent's block */
			else if(pid > 0)
			{
				/* creates a new process */
				pid_arr[cpid] = pid;
				cpid ++;

				if(nowait == 0)
				{
					/* waits for the child process to exit. */
					waitpid(pid, NULL, 0);
				}
				else
				{
					continue;
				}
			}
			else
			{
				printf("Process failed.\n");
			}
		}
	}while(exit != 1);

	/* free all pids */
	for(i = 0; i < cpid; i++)
	{
		kill(pid_arr[i], SIGTERM);
	}

	return 0;
}

void add(char** args)
{
	int i;
	long sum;

	sum = 0;

	/* loop through the postceeding arguments */
	for(i = 1; args[i] != NULL; i++)
	{
		/* if this is a hex number */
		if(strstr(args[i], "0x") != NULL)
		{
			sum += strtol(args[i], NULL, 16);
		}
		else
		{
			sum += strtol(args[i], NULL, 10);
		}
		printf("%s ", args[i]);

		/* if we are at the ending arg */
		if(args[i+1] == NULL)
		{
			printf("= ");
		}
		else
		{
			printf("+ ");
		}
	}

	printf("%ld\n",sum);

	return;
}

void mult(char** args)
{
	int i;
	long prod;

	prod = 1;

	/* loop through the args */
	for(i = 1; args[i] != NULL; i++)
	{
		/*  if hex... */
		if(strstr(args[i], "0x") != NULL)
		{
			prod *= strtol(args[i], NULL, 16);
		}
		else
		{
			prod *= strtol(args[i], NULL, 10);
		}
		printf("%s ", args[i]);

		if(args[i+1] == NULL)
		{
			printf("= ");
		}
		else
		{
			printf("* ");
		}
	}

	/* print the long answer */
	printf("%ld\n",prod);

	return;
}

void countArgs(char** args)
{
	int i;
	int numArgs;

	numArgs = 0;

	/* loop through the args. */
	for(i = 1; args[i] != NULL; i++)
	{
		numArgs++;
	}
	printf("argc = %d, args = ", numArgs);
	/* loop through the args following "args" */
	for(i = 1; args[i] != NULL; i++)
	{
		printf("%s", args[i]);

		if(args[i+1] != NULL)
		{
			printf(", ");
		}
	}
	printf("\n");

	return;
}
