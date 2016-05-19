#ifndef __SERVERACCEPTOR_H__
#define __SERVERACCEPTOR_H__

#include "ProxyBase.h"
#include "Acceptor.h"

NAMESPACE_BEG(proxy)

class ServerAcceptor : public Acceptor
{
  public:
    ServerAcceptor(EndpointManager *pEndptMgr, int listenPort)
			:Acceptor(pEndptMgr, listenPort)
	{}
	
    virtual ~ServerAcceptor();

	virtual Endpoint* createEndpt(SockID sockId, EndpointID id);
};

NAMESPACE_END // namespace proxy

#endif // __SERVERACCEPTOR_H__
