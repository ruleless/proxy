#include "Server.h"

NAMESPACE_BEG(proxy)

Server::~Server()
{}
	
void Server::onRecv(void* data, long datalen)
{
	logInfoLn("TODO!  Server::onRecv() datalen="<<datalen);
}

void Server::onLeave()
{
	logInfoLn("TODO!  Server::onLeave() datalen=");
}

NAMESPACE_END // namespace proxy
