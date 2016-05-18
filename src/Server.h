#ifndef __SERVER_H__
#define __SERVER_H__

#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class Server : public Endpoint
{
  public:
    Server() {}
	
    virtual ~Server();

	virtual EEndpointType getType() const
	{
		return EndpointType_Server;
	}
	
	virtual void onRecv(void* data, long datalen);
	virtual void onLeave();
};

NAMESPACE_END // namespace proxy

#endif // __SERVER_H__
