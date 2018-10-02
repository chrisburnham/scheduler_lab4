/*
 * queue.h
 *
 *
 *
 *  Created on: Oct 25, 2017
 *      Author: ldamon
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/* a structure representing a Job
 * The queueing user is responsible for setting the
 * duration for the Job, and initializing the waitTime to zero
 */
typedef struct Job
{
	int duration;
	int waitTime;
} Job;

/* add given job to the queue */
extern void queueAdd(Job);

/* return the current length of the queue */
extern int queueLength();

/* remove (and return) the Job at the head of the queue */
extern Job queueRemoveFirst();

/* remove (and return) the shortest Job on the queue */
extern Job queueRemoveShortest();

/* step through the entire queue and increment the wait time */
extern void queueIncrementWaitTimes();

/* print the queue for debugging purposes only */
extern void queuePrint();

#endif /* QUEUE_H_ */
