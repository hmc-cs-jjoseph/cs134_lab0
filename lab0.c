#include "lab0.h"

int main(int argc, char **argv) {
  // Initialize required variables for unpacking command line arguments
  char* inputFile = NULL;
  char* outputFile = NULL;
  int segFaultFlag = 0;
  int catchFlag = 0;
  char opt;
  int optind = 0;
  
  // We store the long options in an array of option structs, defined
  // in getopt.h
  // I used the getopt_long example, section 25.2.4 of the GNU libc manual.
  // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
  struct option longOptions[] = {
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"segfault", no_argument, 0, 's'},
    {"catch", no_argument, 0, 'c'},
    {0, 0, 0, 0}};
  // Continuous calls to getopt_long(4) increment optind until all options have 
  // been processed. When there are no more options to process, getopt_long(4) 
  // returns -1.
  // Each call to getopt_long also updates the char * variable optarg with each
  // respective argument.
  while((opt = getopt_long(argc, argv, "i:o:sc", longOptions, &optind)) != -1) {
    switch(opt){
      case 'i':
	inputFile = optarg;
	break;
      case 'o':
	outputFile = optarg;
	break;
      case 's':
	segFaultFlag = 1;
	break;
      case 'c':
	catchFlag = 1;
	break;
      case '?':
	if (optopt == 'i' || optopt == 'o')
	  fprintf(stderr, "Option -%c requires an argument.\n",optopt);
	else if (isprint(optopt))
	  fprintf(stderr, "Invalid option '-%c'.\n",optopt);
	else
	  fprintf(stderr, "Unknown option '-%c'.\n",optopt);
	return 1;
      default:
	abort();
    }
  }
  // After processing all arguments, take necessary actions:
  // Always attempt to copy the input file to the output file.
  redirectAndCopy(inputFile, outputFile);
  
  // If the --catch option was specified, raising the catch flag, then register
  // a signal handler.
  if(catchFlag) {
    signal(SIGSEGV, signalHandler);
  }

  // If the --segfault option was specified, raising the segfault flag, then
  // force a segmentation fault.
  if(segFaultFlag) {
    segfault();
  }
  return 0;
}




int redirectAndCopy(char * inFile, char * outFile) {
  // Attempt to open the input file as a read only file. open(2) returns the
  // file identifier - if it returns negative, then the file could not
  // be opened.
  int ifd = open(inFile, O_RDONLY);
  if (ifd < 0) {
    fprintf(stderr, "Could not open input file %s.\n", inFile);
    exit(1);
  }
  
  // Attempt to open the output file. creat(2) returns the
  // file identifier - if it returns negative, then the file could not
  // be opened.
  int ofd = creat(outFile, 0666);
  if (ofd < 0) {
    fprintf(stderr, "Could not open output file %s.\n", outFile);
    exit(2);
  }
  
  // Redirect standard input to the input file by closing stdin, 
  // setting the input file id to be fd0 (stdin), and the closing the 
  // input file.
  close(0);
  dup(ifd);
  close(ifd);
  
  // Do the same with the output file.
  close(1);
  dup(ofd);
  close(ofd);
  
  // Copy the input file to the output file.
  int bufferSize = 512; 	// Standard but arbitrary buffer size
  char readBuffer[bufferSize];	// For storing bytes read from the input file
  int bytesRead = 1;		// Initialize this as 1 to begin the while loop

  while (bytesRead > 0) {	// Keep reading until no more bytes are read from input
    bytesRead = read(0, readBuffer, bufferSize);	// Read 512 bytes
    if (bytesRead > 0) {				// Write all read bytes, if any
      write(1, readBuffer, bytesRead);
    }
  }
  return 0;
}
  


void signalHandler(int signalNumber) {
  // Catch SIGSEGV signal and print it to standard error
  fprintf(stderr, "Caught signal SIGSEGV (segmentation fault)\n");
  exit(3);
}

void segfault() {
  // Simplest way to force a segmentation fault is to assign through a null pointer
  char* x = NULL;
  *x = 'a';
}


