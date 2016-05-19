#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

#include "ProxyBase.h"
#include "Proxydef.h"

NAMESPACE_BEG(proxy)

class EndpointManager;

class Endpoint
{
  public:
    Endpoint(EndpointManager *pEndptMgr)
			:mSockId(0)
			,mpEndptMgr(pEndptMgr)
	{
		mId.asInt = 0;
	}
	
    virtual ~Endpoint();

	EndpointID getId() const;
	void setId(EndpointID id);

	SockID getSockId() const;
	void setSockId(SockID sockId);

	void send(void *data, long datalen);
	void kickout(int code = 0);

	virtual EEndpointType getType() const
	{
		return EndpointType_Unknown;
	}
	
	virtual void onRecv(void* data, long datalen) = 0;
	virtual void onLeave() = 0;
  protected:	
	EndpointID mId;
	SockID mSockId;
	
	EndpointManager *mpEndptMgr;
};

NAMESPACE_END // namespace proxy

#endif // __ENDPOINT_H__
