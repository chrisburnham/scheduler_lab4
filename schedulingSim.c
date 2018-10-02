/*
 * schedulingSim.c
 *
 *  Updated on: Oct 2, 2018
 *      Author: ldamon
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

FILE * fd;   // input file descriptor
bool done = false;

/*
 Function to determine if a job is arriving during this particular time step.
 Returns 0 if no job is arriving
 Returns the duration of the job that arrives if a job does arrive
 */
int jobArrives(int timestep)
{
	static int nextJobTime = -1;
	static int nextDuration;

	if (nextJobTime == -1)
		{
		if (fscanf(fd, "%d %d", &nextJobTime, &nextDuration) == EOF)
			{
			done = true;
			}
		// else have something to work with, so continue....
		}

	if (nextJobTime == timestep)
	{
		nextJobTime = -1;
		return nextDuration;
	}
	else // not up to nextJobTime yet
		return 0;
}

/*
 This is the main function of the simulation.   It should move the time along step by step,
 calling jobArrives(timestep) for each step in time.  If a job arrives, it should be added
 to the job queue.
 
 Additionally, during each time step, the processor should be kept busy if possible.  If it
 is not already busy, a job should be removed from the queue and should start to run.  If a
 job is already running, then the amount of time remaining should be decremented.  You'll also
 need to be sure to update the wait time on any jobs in the queue.
 
 There is a global variable, done, which will be set when the entire input file has
 been read and the last job has been returned to the simulation.  You can use that variable to
 control when your simulation should end.
 
 INPUT shortestFirst:  boolean  true means it should run a shortest job first simulation
                                false means it should run a first come first serve simulation

 NOTE: if you are a grad student, you will probably want to change the signature of this 
 function to allow for all three scheduling options. 
 
 OUTPUT: void, but the function should print all the required output (see the lab information)
 */
void doSimulation(bool shortestFirst)
{
// this is where you do your work!
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <FCFS|SJF> <scheduleFile>\n", argv[0]);
		exit(1);
	}

	char * filename = argv[2];
        fd = fopen(filename, "r");
	if (fd == NULL)
	{
		printf("Can't open input file: %s\n", filename);
		exit(1);
	}

	if (strcmp(argv[1], "FCFS") == 0)
		{
		printf("Running simulation for first come first serve\n");
		doSimulation(false);
		}
	else if (strcmp(argv[1], "SJF") == 0)
		{
		printf("Running simulation for shortest job first\n");
		doSimulation(true);
		}
	else
		printf("Oops, bad scheduling type: %s", argv[1]);

}

