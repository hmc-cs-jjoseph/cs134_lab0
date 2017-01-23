#include "lab0.h"

int main(int argc, char **argv) {
  
  char* inputFile = NULL;
  char* outputFile = NULL;
  int segFaultFlag = 0;
  int catchFlag = 0;
  char opt;
  int optind = 0;

  struct option longOptions[] = {
    {"input", required_argument, 0, 'i'},
    {"output", required_argument, 0, 'o'},
    {"segfault", no_argument, 0, 's'},
    {"catch", no_argument, 0, 'c'},
    {0, 0, 0, 0}};
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
  redirectAndCopy(inputFile, outputFile);
  if(catchFlag) {
    signal(SIGSEGV, signalHandler);
  }
  if(segFaultFlag) {
    segfault();
  }
  return 0;
}




int redirectAndCopy(char * inFile, char * outFile) {
  int ifd = open(inFile, O_RDONLY);
  if (ifd < 0) {
    fprintf(stderr, "Could not open input file %s.\n", inFile);
    exit(1);
  }
  int ofd = creat(outFile, 0666);
  if (ofd < 0) {
    fprintf(stderr, "Could not open output file %s.\n", outFile);
    exit(2);
  }

  close(0);
  dup(ifd);
  close(ifd);

  close(1);
  dup(ofd);
  close(ofd);

  int bufferSize = 512;
  char readBuffer[bufferSize];
  int bytesRead = 1;
  while (bytesRead > 0) {
    bytesRead = read(0, readBuffer, bufferSize);
    if (bytesRead > 0) {
      write(1, readBuffer, bytesRead);
    }
  }
  return 0;
}
  


void signalHandler(int signalNumber) {
  fprintf(stderr, "Caught signal SIGSEGV (segmentation fault)\n");
  exit(3);
}

void segfault() {
  char* x = NULL;
  *x = 'a';
}


