#ifndef __FAKEPROXY_H__
#define __FAKEPROXY_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class FakeClientProxy : public Endpoint
{
  public:
    FakeClientProxy(EndpointManager *pEndptMgr=NULL)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~FakeClientProxy();

	virtual EEndpointType getType() const
	{
		return EndpointType_Client;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

class FakeServerProxy : public Endpoint
{
  public:
    FakeServerProxy(EndpointManager *pEndptMgr=NULL)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~FakeServerProxy();

	virtual EEndpointType getType() const
	{
		return EndpointType_Server;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

NAMESPACE_END // namespace proxy

#endif // __FAKEPROXY_H__
