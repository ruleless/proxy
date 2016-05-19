#ifndef __SIMPLEPROXY_H__
#define __SIMPLEPROXY_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

//--------------------------------------------------------------------------
class SimpleClientProxy : public Endpoint
{
  public:
    SimpleClientProxy(EndpointManager *pEndptMgr=NULL)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~SimpleClientProxy();

	virtual EEndpointType getType() const
	{
		return EndpointType_Client;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
class SimpleServerProxy : public Endpoint
{
  public:
    SimpleServerProxy(EndpointManager *pEndptMgr=NULL)
			:Endpoint(pEndptMgr)
	{}
	
    virtual ~SimpleServerProxy();

	virtual EEndpointType getType() const
	{
		return EndpointType_Server;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};
//--------------------------------------------------------------------------

NAMESPACE_END // namespace proxy

#endif // __SIMPLEPROXY_H__
