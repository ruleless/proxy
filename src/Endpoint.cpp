#include "Endpoint.h"
#include "NetWraper.h"

NAMESPACE_BEG(proxy)

Endpoint::~Endpoint()
{}

EndpointID Endpoint::getId() const
{
	return mId;
}
void Endpoint::setId(EndpointID id)
{
	mId = id;
}

SockID Endpoint::getSockId() const
{
	return mSockId;
}

void Endpoint::setSockId(SockID sockId)
{
	mSockId = sockId;
}

void Endpoint::send(void *data, long datalen)
{
	long sentlen = gNetWraper->send(mSockId, data, datalen);
	if (sentlen != datalen)
	{
		logErrorLn("Endpoint::send()  send no required data length! "<<
				   "sentlen="<<sentlen<<" requirelen="<<datalen);
	}
}

void Endpoint::kickout(int code)
{
	gNetWraper->close(mSockId, code);
}

NAMESPACE_END // namespace proxy
