#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class Client : public Endpoint
{
  public:
    Client() {}
	
    virtual ~Client();

	virtual EEndpointType getType() const
	{
		return EndpointType_Client;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

NAMESPACE_END // namespace proxy

#endif // __CLIENT_H__
