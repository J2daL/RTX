/*
 * initialize.c
 *
 *  Created on: Nov 28, 2010
 *      Author: Owner
 */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>			// getpid() definition

#include <fcntl.h>

#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>

//DIE FUNCTION I DON'T KNOW WHERE THIS GOES
void die(){
cleanup();
printf ("Signal Prompts Immediate Exit... Sorry\n");
exit(0);
}

//CLEANUP FUNCTION I DON't KNOW WHERE THIS GOES
void cleanup(){

kill(inputpid, SIGINT);

if (munmap(mmap_pointer, bufsize) == -1){
printf("Bad Cleanup - Munmap\n");
}

if(close(fid)== -1){
printf("Bad Cleanup - Munmap Close\n");
}

if(unlink(fname) == -1){
printf("Bad Cleanup - Unlink\n");
}


//PUT THIS IN INITIALIZATION
void init_helperprocess(){

	int fid1;
	int fid2;
	char fname1 = (char *) malloc(sizeof(char)*10);
	char fname2 = (char *) malloc(sizeof(char)*10);

	//Initialize Keyboard Helper
	fname1 = "KeyboardBuffer";
	fid1 = open(fname1, O_RDWR | O_CREAT, (mode_t) 0755);

	mmap_pointer = mmap((caddr_t) 0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fid1,(off_t) 0);
	    if (mmap_pointer == MAP_FAILED){
	      printf("Memory Map Initialization Failed... Sorry!\n");
		  die();
	    };





	//Initialize CRT Helper
	fname2 = "CRTBuffer";
	fid2 = open(fname2, O_RDWR | O_CREAT, (mode_t) 0755);

	mmap_pointer = mmap((caddr_t) 0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fid2,(off_t) 0);
	    if (mmap_pointer == MAP_FAILED){
	      printf("Memory Map Initialization Failed... Sorry!\n");
		  die();
	    };
}


void init_signals(){
//catch illegal signals and terminate program or
//catch sigalrm, sigusr1, sigusr2 and invoke interrupt handler

sigset(SIGINT,die); //kill signals
sigset(SIGBUS,die); //bus errors
sigset(SIGHUP,die);
sigset(SIGILL,die); //illegal instruction
sigset(SIGQUIT,die);
sigset(SIGABRT,die);
sigset(SIGTERM,die);
sigset(SIGSEGV,die); //seg faults

sigset(SIGALRM, interrupt_handler); //alarm
sigset(SIGUSR1, interrupt_handler); //keyboard
sigset(SIGUSR2, interrupt_handler); //screen
ualarm(100000,100000); //initialize alarm to signal every 100ms
}
