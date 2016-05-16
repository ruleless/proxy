#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

#include "ProxyBase.h"

NAMESPACE_BEG(proxy)

union EndpointID
{
	struct
	{
		uint proxyId:8;
		uint idnex:24;
	} asStruct;
	uint asInt;
};

class Endpoint
{
  public:
	EndpointID id;
	
    Endpoint();
    virtual ~Endpoint();
};

NAMESPACE_END // namespace proxy

#endif // __ENDPOINT_H__
