/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "addLinkedList.h"

int *
add_1_svc(numbers *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	printf("Fuction called with head %d\n",argp->x);
	numbers* temp=argp;
	result=0;
	while(temp){
		printf("temp->x : %d\n",temp->x);
		result+=temp->x;
		temp=temp->next;
	}

	return &result;
}
