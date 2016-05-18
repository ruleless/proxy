#include "ClientAcceptor.h"
#include "Client.h"

NAMESPACE_BEG(proxy)

ClientAcceptor::~ClientAcceptor()
{}

Endpoint* ClientAcceptor::createEndpt(SockID sockId, EndpointID id)
{
	Client *client = new Client();
	assert(client && "new Client");
	
	client->setSockId(sockId);
	client->setId(id);

	return client;
}

NAMESPACE_END // namespace proxy
