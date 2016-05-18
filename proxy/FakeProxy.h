#ifndef __FAKEPROXY_H__
#define __FAKEPROXY_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class FakeClientProxy : public Endpoint
{
  public:
    FakeClientProxy(EndpointManager *pEndptMgr)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~FakeClientProxy();

	static EEndpointType getType()
	{
		return EndpointType_Client;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

class FakeServerProxy : public Endpoint
{
  public:
    FakeServerProxy(EndpointManager *pEndptMgr)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~FakeServerProxy();

	static EEndpointType getType()
	{
		return EndpointType_Server;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

NAMESPACE_END // namespace proxy

#endif // __FAKEPROXY_H__
