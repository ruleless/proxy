#include "ClientAcceptor.h"
#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

ClientAcceptor::~ClientAcceptor()
{}

Endpoint* ClientAcceptor::createEndpt(SockID sockId, EndpointID id)
{	
	ProxyFactory *factory = ProxyFactoryRegister::getRegister()->getProxyFactory(EndpointType_Client, gProxyProtocolType);
	if (factory)
	{
		Endpoint *ep = factory->createProxy(mpEndptMgr);
		ep->setSockId(sockId);
		ep->setId(id);
		return ep;
	}
	else
	{
		logErrorLn("got no related proxy for client! proxy-protocol-type="<<gProxyProtocolType);
	}

	return NULL;
}

NAMESPACE_END // namespace proxy
