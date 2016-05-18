#include "EndpointManager.h"

NAMESPACE_BEG(proxy)

EndpointManager::~EndpointManager()
{}

bool EndpointManager::initialise()
{
	return true;
}

void EndpointManager::finalise()
{
	for (int i = 0; i < MAX_ENDPOINT; ++i)
	{
		if (mEndptArray[i])
		{
			mEndptArray[i]->onLeave();
			delete mEndptArray[i];
			mEndptArray[i] = NULL;
		}
	}
	mEndptList.clear();
}

bool EndpointManager::addEndpt(SockID sockId, EndpointID id, Endpoint *ep)
{
	assert(ep && "add endpoint(ep != NULL)");
	
	int index = id.asStruct.index;
	if (index < 0 || index >= MAX_ENDPOINT)
		return false;
	if (mEndptList.find(sockId) != mEndptList.end())
		return false;

	if (mEndptArray[index])
	{
		mEndptArray[index]->onLeave();
		delete mEndptArray[index];
	}

	mEndptArray[index] = ep;
	mEndptList.insert(std::make_pair(sockId, ep));
	return true;
}

Endpoint* EndpointManager::getEndptByIndex(EndpointID id) const
{
	int index = id.asStruct.index;
	if (index >= 0 && index < MAX_ENDPOINT)
		return mEndptArray[index];
	return NULL;
}

Endpoint* EndpointManager::getEndptBySockId(SockID sockId) const
{
	EndptList::const_iterator it = mEndptList.find(sockId);
	if (it != mEndptList.end())
		return it->second;
	return NULL;
}

void EndpointManager::onRecv(SockID sockId, void *data, long datalen)
{
	Endpoint *endpt = getEndptBySockId(sockId);
	if (endpt)
	{
		endpt->onRecv(data, datalen);
	}
	else
	{
		logErrorLn("EndpointManager::onRecv()  find no endpoint! sockid="<<sockId);
	}
}

void EndpointManager::onLeave(SockID sockId)
{
	EndptList::iterator it = mEndptList.find(sockId);
	if (it != mEndptList.end())
	{
		Endpoint *ep = it->second;
		if (ep)
		{
			ep->onLeave();
			delete ep;
		}
		mEndptList.erase(it);
	}
	else
	{
		logErrorLn("EndpointManager::onLeave()  find no endpoint! sockid="<<sockId);
	}
}

NAMESPACE_END // namespace proxy
