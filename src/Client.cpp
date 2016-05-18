#include "Client.h"

NAMESPACE_BEG(proxy)

Client::~Client()
{
}
	
void Client::onRecv(void* data, long datalen)
{
	logInfoLn("TODO!  Client::onRecv() datalen="<<datalen);
}

void Client::onLeave()
{
	logInfoLn("TODO!  Client::onLeave()");
}

NAMESPACE_END // namespace proxy
