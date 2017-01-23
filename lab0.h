/* file lab0.h
 * brief provides interface for lab0.c
 * author Jesse Joseph
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>

/* 
 * brief main executable 
 */
int main(int argc, char **argv);

/*
 * brief redirect file input to output
 */
int redirectAndCopy(char * inFile, char * outFile);

/*
 * brief signal handler for forced segfault
 */
void signalHandler(int signalNumber);

/*
 * brief forces a segmentation fault 
 */
void segfault();




