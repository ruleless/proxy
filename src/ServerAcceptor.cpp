#include "ServerAcceptor.h"
#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

ServerAcceptor::~ServerAcceptor()
{}

Endpoint* ServerAcceptor::createEndpt(SockID sockId, EndpointID id)
{
	ProxyFactory *factory = ProxyFactoryRegister::getRegister()->getProxyFactory(EndpointType_Server, gProxyProtocolType);
	if (factory)
	{
		Endpoint *ep = factory->createProxy(mpEndptMgr);
		ep->setSockId(sockId);
		ep->setId(id);
		return ep;
	}
	else
	{
		logErrorLn("got no related proxy for server! proxy-proto-type="<<gProxyProtocolType);
	}

	return NULL;	
}

NAMESPACE_END // namespace proxy
