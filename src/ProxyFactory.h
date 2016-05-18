#ifndef __PROXYFACTORY_H__
#define __PROXYFACTORY_H__

#include "ProxyBase.h"
#include "Endpoint.h"

NAMESPACE_BEG(proxy)

class ProxyFactory
{
  public:
    virtual ~ProxyFactory() {};

	virtual Endpoint* createProxy(EndpointManager *pEndptMgr) = 0;
	virtual EEndpointType getType() = 0;
};

NAMESPACE_END // namespace proxy

#endif // __PROXYFACTORY_H__
