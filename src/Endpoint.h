#ifndef __ENDPOINT_H__
#define __ENDPOINT_H__

#include "ProxyBase.h"

NAMESPACE_BEG(proxy)

union EndpointID
{
	struct
	{
		uint proxyId:8;
		uint index:24;
	} asStruct;
	uint asInt;
};

enum EEndpointType
{
	EndpointType_Unknown,
	
	EndpointType_Server,
	EndpointType_Client,

	EndpointType_Max,
};

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

	static EEndpointType getType()
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
