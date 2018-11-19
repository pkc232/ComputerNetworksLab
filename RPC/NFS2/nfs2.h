/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _NFS2_H_RPCGEN
#define _NFS2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct input {
	char data[100];
};
typedef struct input input;

struct output {
	char data[1000];
};
typedef struct output output;

#define nfsDir 0x23451111
#define dir_vers 1

#if defined(__STDC__) || defined(__cplusplus)
#define getDir 1
extern  output * getdir_1(input *, CLIENT *);
extern  output * getdir_1_svc(input *, struct svc_req *);
extern int nfsdir_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define getDir 1
extern  output * getdir_1();
extern  output * getdir_1_svc();
extern int nfsdir_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_input (XDR *, input*);
extern  bool_t xdr_output (XDR *, output*);

#else /* K&R C */
extern bool_t xdr_input ();
extern bool_t xdr_output ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_NFS2_H_RPCGEN */