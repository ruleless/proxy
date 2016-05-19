#ifndef __CLIENTACCEPTOR_H__
#define __CLIENTACCEPTOR_H__

#include "ProxyBase.h"
#include "Acceptor.h"

NAMESPACE_BEG(proxy)

class ClientAcceptor : public Acceptor
{
  public:
    ClientAcceptor(EndpointManager *pEndptMgr, int listenPort)
			:Acceptor(pEndptMgr, listenPort)
	{}
	
    virtual ~ClientAcceptor();

	virtual Endpoint* createEndpt(SockID sockId, EndpointID id);
};

NAMESPACE_END // namespace proxy

#endif // __CLIENTACCEPTOR_H__
