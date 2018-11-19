/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "nfs.h"

bool_t
xdr_fileName (XDR *xdrs, fileName *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->name, 100,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_contentsOut (XDR *xdrs, contentsOut *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->content, 1000,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}
