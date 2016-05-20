#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class EndpointManager;

class Acceptor
{
  public:
    Acceptor(EndpointManager *pEndptMgr, int listenPort, EEndpointType acceptType = EndpointType_Client)
			:mpEndptMgr(pEndptMgr)
			,mListenPort(listenPort)
			,mSockId(0)
			,mAcceptType(acceptType)
	{
		assert(mpEndptMgr && "mpEndptMgr != NULL");
	}
	
    virtual ~Acceptor();

	bool initialise();
	void finalise();

	EProxyCode tryAccept(SockID newSock, SockID listenSock, Endpoint *retEp = NULL);

	Endpoint* createEndpt(SockID sockId, EndpointID id);
  protected:
	EndpointManager *mpEndptMgr;
	int mListenPort;
	SockID mSockId;
	EEndpointType mAcceptType;
};

NAMESPACE_END // namespace proxy

#endif // __ACCEPTOR_H__
