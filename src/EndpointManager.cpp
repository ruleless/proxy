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
	for (int t = 1; t < EndpointType_Max; ++t)
	{
		mEndptList[t].clear();
	}	
}

bool EndpointManager::addEndpt(SockID sockId, EndpointID id, Endpoint *ep)
{
	assert(ep && "add endpoint(ep != NULL)");
	
	int index = id.asStruct.index;
	if (index < 0 || index >= MAX_ENDPOINT)
		return false;
	for (int t = 1; t < EndpointType_Max; ++t)
	{
		if (mEndptList[t].find(sockId) != mEndptList[t].end())
			return false;
	}	

	if (mEndptArray[index])
	{
		mEndptArray[index]->onLeave();
		delete mEndptArray[index];
	}

	mEndptArray[index] = ep;
	mEndptList[ep->getType()].insert(std::make_pair(sockId, ep));
	return true;
}

Endpoint* EndpointManager::getEndptById(EndpointID id) const
{
	int index = id.asStruct.index;
	if (index >= 0 && index < MAX_ENDPOINT)
		return mEndptArray[index];
	return NULL;
}

Endpoint* EndpointManager::getEndptBySockId(SockID sockId) const
{
	for (int t = 1; t < EndpointType_Max; ++t)
	{
		EndptList::const_iterator it = mEndptList[t].find(sockId);
		if (it != mEndptList[t].end())
			return it->second;
	}
	return NULL;
}

EndpointManager::EndptIterator EndpointManager::getIterator(EEndpointType tpy)
{
	return EndptIterator(mEndptList[tpy].begin(), mEndptList[tpy].end());
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
	bool findNoEp = true;
	for (int t = 1; t < EndpointType_Max; ++t)
	{
		EndptList::iterator it = mEndptList[t].find(sockId);
		if (it != mEndptList[t].end())
		{
			Endpoint *ep = it->second;
			if (ep)
			{				
				mEndptArray[ep->getId().asStruct.index] = NULL;
				ep->onLeave();
				delete ep;
			}
			mEndptList[t].erase(it);
			findNoEp = false;
			break;
		}
	}
   
	if (findNoEp)
	{
		logErrorLn("EndpointManager::onLeave()  find no endpoint! sockid="<<sockId);
	}
}

NAMESPACE_END // namespace proxy
