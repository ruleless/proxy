#include "ServerAcceptor.h"
#include "Server.h"

NAMESPACE_BEG(proxy)

ServerAcceptor::~ServerAcceptor()
{}

Endpoint* ServerAcceptor::createEndpt(SockID sockId, EndpointID id)
{
	Server *svr = new Server();
	assert(svr && "new Server");
	
	svr->setSockId(sockId);
	svr->setId(id);

	return svr;
}

NAMESPACE_END // namespace proxy
