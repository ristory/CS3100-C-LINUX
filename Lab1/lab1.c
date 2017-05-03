#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>


// usage() prints a standard usage statement

void usage(char *path)
 {
    
    fprintf(stderr, "Usage: %s -n name\n", path);
}


int main(int argc, char *argv[])
{
	char *name;

	if (argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}
	
	// read the input parameter and exit on error
	int c;
	opterr = 0;
	while ((c = getopt(argc, argv, "n:")) != -1) 
	{
		switch (c) 
		{
			case 'n':
				name = optarg;
				break;
			default:
				usage(argv[0]);
				exit(1);
		}
	}
		
	printf("Welcome to Lab 1, written by %s\n",name);

	// output on STDOUT "Hostname: <hostname>"
	char buffer[200];
	gethostname(buffer, sizeof(buffer));
	gethostname(buffer, 200);
	printf("Hostname: %s\n", buffer);
	// output on STDOUT "PID and PPID: nnnnn/nnnnn

	printf("PID and PPID: %d/%d\n", getpid(), getppid());

	// output on STDOUT "Program: <pathToThisProgram>"
	printf("Program: %s\n", argv[0]);
	return 0;
	

	
}

