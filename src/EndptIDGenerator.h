#ifndef __ENDPTIDGENERATOR_H__
#define __ENDPTIDGENERATOR_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class EndptIDGenerator : public Singleton<EndptIDGenerator>
{
  public:
    EndptIDGenerator(uint8 proxyId)
			:mAvailableIds()
			,mProxyId(proxyId)
	{
		assert(mProxyId != 0 && "EndptIDGenerator");
	}
	
	virtual ~EndptIDGenerator() {}

	bool initialise()
	{
		for (int i = 0; i < MAX_ENDPOINT; ++i)
		{
			EndpointID id;
			id.asStruct.proxyId = mProxyId;
			id.asStruct.index = i;
			restorId(id);
		}
		return true;
	}	

	void finalise()
	{
		mAvailableIds.clear();
	}

	EndpointID genNewId()
	{
		if (mAvailableIds.empty())
		{
			EndpointID id;
			id.asInt = 0;
			return id;
		}

		EndpointID id = mAvailableIds.front();
		mAvailableIds.pop_front();
		return id;
	}

	void restorId(EndpointID id)
	{
		mAvailableIds.push_back(id);
	}
  private:
	typedef std::list<EndpointID> IDList;

	IDList mAvailableIds;
	uint8 mProxyId;
};

NAMESPACE_END // namespace proxy

#endif // __ENDPTIDGENERATOR_H__
