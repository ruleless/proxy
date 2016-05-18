#ifndef __ENDPOINTMANAGER_H__
#define __ENDPOINTMANAGER_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class EndpointManager
{
  public:
    EndpointManager()
			:mEndptList()
	{
		memset(mEndptArray, 0, sizeof(mEndptArray));
	}
	
    virtual ~EndpointManager();

	bool initialise();
	void finalise();

	bool addEndpt(SockID sockId, EndpointID id, Endpoint *ep);
	Endpoint* getEndptByIndex(EndpointID id) const;
	Endpoint* getEndptBySockId(SockID sockId) const;

	void onRecv(SockID sockId, void *data, long datalen);
	void onLeave(SockID sockId);
  private:
	typedef std::map<SockID, Endpoint *> EndptList;
	
	Endpoint* mEndptArray[MAX_ENDPOINT];
	EndptList mEndptList;
};

NAMESPACE_END // namespace proxy

#endif // __ENDPOINTMANAGER_H__
