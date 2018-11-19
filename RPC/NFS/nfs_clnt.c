/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "nfs.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

contentsOut *
getcontent_1(fileName *argp, CLIENT *clnt)
{
	static contentsOut clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, getContent,
		(xdrproc_t) xdr_fileName, (caddr_t) argp,
		(xdrproc_t) xdr_contentsOut, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
