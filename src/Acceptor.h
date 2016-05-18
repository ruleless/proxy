#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class EndpointManager;

class Acceptor
{
  public:
    Acceptor(AsyncCore *pAsnCore, EndpointManager *pEndptMgr, int listenPort)
			:mpAsnCore(pAsnCore)
			,mpEndptMgr(pEndptMgr)
			,mListenPort(listenPort)
			,mSockId(0)
	{
		assert(mpAsnCore && "mpAsnCore != NULL");
		assert(mpEndptMgr && "mpEndptMgr != NULL");
	}
	
    virtual ~Acceptor();

	bool initialise();
	void finalise();

	EProxyCode tryAccept(SockID newSock, SockID listenSock, Endpoint *retEp = NULL);

	virtual Endpoint* createEndpt(SockID sockId, EndpointID id) = NULL;
  protected:
	AsyncCore *mpAsnCore;
	EndpointManager *mpEndptMgr;
	int mListenPort;
	SockID mSockId;
};

NAMESPACE_END // namespace proxy

#endif // __ACCEPTOR_H__
