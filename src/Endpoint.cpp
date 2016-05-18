#include "Endpoint.h"

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

NAMESPACE_END // namespace proxy
