#ifndef __ENDPOINTMANAGER_H__
#define __ENDPOINTMANAGER_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class EndpointManager
{
  public:
	typedef std::map<SockID, Endpoint *> EndptList;
	typedef MapIterator<EndptList> EndptIterator;
	
    EndpointManager()
			:mEndptList()
	{
		memset(mEndptArray, 0, sizeof(mEndptArray));
	}
	
    virtual ~EndpointManager();

	bool initialise();
	void finalise();

	bool addEndpt(SockID sockId, EndpointID id, Endpoint *ep);
	Endpoint* getEndptById(EndpointID id) const;
	Endpoint* getEndptBySockId(SockID sockId) const;
	EndptIterator getIterator(EEndpointType tpy);

	void onRecv(SockID sockId, void *data, long datalen);
	void onLeave(SockID sockId);
  private:	
	Endpoint* mEndptArray[MAX_ENDPOINT];
	EndptList mEndptList[EndpointType_Max];
};

NAMESPACE_END // namespace proxy

#endif // __ENDPOINTMANAGER_H__
