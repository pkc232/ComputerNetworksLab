/* dateproc.c - remote procedures; called by server stub. */
#include <rpc/rpc.h> /* standard RPC include file */
#include "date.h" /* this file is generated by rpcgen */
/* Return the binary date and time. */
long * bin_date_1( )
{
 static long timeval; /* must be static */
 long time(); /* Unix system call */
 timeval = time((long *) 0); /* returns time in seconds since 00:00:00, January 1, 1970 */
 return(&timeval);
}
/* Convert a binary time and return a human readable string. */
char **str_date_1(bintime)
long *bintime;
{
 static char *ptr; /* must be static */
 char *ctime(); /*c standard function */
 ptr = ctime(bintime); /* convert to local time */
 return(&ptr); /* return the address of pointer */
} 