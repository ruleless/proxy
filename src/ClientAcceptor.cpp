#include "ClientAcceptor.h"
#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

ClientAcceptor::~ClientAcceptor()
{}

Endpoint* ClientAcceptor::createEndpt(SockID sockId, EndpointID id)
{	
	ProxyFactory *factory = ProxyFactoryRegister::getRegister()->getProxyFactory(EndpointType_Client, gProxyInstance);
	if (factory)
	{
		Endpoint *ep = factory->createProxy(mpEndptMgr);
		ep->setSockId(sockId);
		ep->setId(id);
		return ep;
	}
	else
	{
		logErrorLn("got no related proxy for client! proxyins="<<gProxyInstance);
	}

	return NULL;
}

NAMESPACE_END // namespace proxy
