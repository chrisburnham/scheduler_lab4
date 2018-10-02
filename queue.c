#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_QUEUE_LENGTH 256
static Job jobs[MAX_QUEUE_LENGTH];
static int nextJob = 0;
static int numJobs = 0; 
static int firstJob = 0;

void queueAdd(Job job)
{
  if (numJobs == MAX_QUEUE_LENGTH)
    {
       fprintf(stderr,"Help! job queue is full\n");
       exit(-1);
    }
  jobs[nextJob] = job;
  nextJob = (nextJob+1)%MAX_QUEUE_LENGTH;
  numJobs++;
}
    
int queueLength()
{
  return numJobs;
}



Job queueRemoveFirst()
{
  if (numJobs == 0)
    {
      fprintf(stderr,"Removing job from an empty queue\n");
      exit(-2);
    }
  int jobNo = firstJob;
  firstJob = (firstJob+1)%MAX_QUEUE_LENGTH;
  numJobs--;
  return jobs[jobNo];
}
  
Job queueRemoveShortest()
{
  if (numJobs == 0)
    {
      fprintf(stderr,"Removing job from an empty queue\n");
      exit(-2);
    }
  int s = firstJob;
  if (nextJob > firstJob)
     {
        for (int i = firstJob; i < nextJob; i++)
           {
             if (jobs[i].duration < jobs[s].duration)
               s = i;
           }
     }
   else
     {
        for (int i = firstJob; i < MAX_QUEUE_LENGTH; i++)
           {
             if (jobs[i].duration < jobs[s].duration)
               s = i;
           }
        for (int i = 0; i < nextJob; i++)
           {
             if (jobs[i].duration < jobs[s].duration)
               s = i;
           }
     }
     
  if (s == firstJob)
    return queueRemoveFirst();
     
  Job shortest = jobs[s];
  
  if (nextJob > firstJob)
     {
        for (int i = s+1; i < nextJob; i++)
           jobs[i-1] = jobs[i];
     }
   else
     {
        if (s > firstJob)
          {
            for (int i = s+1; i < MAX_QUEUE_LENGTH; i++)
               jobs[i-1] = jobs[i];
            s = 0;
            jobs[MAX_QUEUE_LENGTH-1] = jobs[0];
          }
        for (int i = s+1; i < nextJob; i++)
          jobs[i-1] = jobs[i];
     }

   nextJob = (nextJob + MAX_QUEUE_LENGTH-1)%MAX_QUEUE_LENGTH;
   numJobs--;
   return shortest;
}
  

void queueIncrementWaitTimes()
{
   if (numJobs == 0)
     return;
   if (nextJob > firstJob)
     {
        for (int i = firstJob; i < nextJob; i++)
           jobs[i].waitTime++;
     }
   else
     {
        for (int i = firstJob; i < MAX_QUEUE_LENGTH; i++)
           jobs[i].waitTime++;
        for (int i = 0; i < nextJob; i++)
           jobs[i].waitTime++;
     }
}


void queuePrint()
{
   printf("Queue length %d\n",numJobs);
   if (numJobs == 0)
     return;
   if (nextJob > firstJob)
     {
        for (int i = firstJob; i < nextJob; i++)
           printf("dur=%d  wait=%d\n",jobs[i].duration,jobs[i].waitTime);
      }
   else
     {
        for (int i = firstJob; i < MAX_QUEUE_LENGTH; i++)
           printf("dur=%d  wait=%d\n",jobs[i].duration,jobs[i].waitTime);
        for (int i = 0; i < nextJob; i++)
           printf("dur=%d  wait=%d\n",jobs[i].duration,jobs[i].waitTime);
     }
}
  
