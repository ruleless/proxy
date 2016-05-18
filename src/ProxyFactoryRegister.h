#ifndef __PROXYFACTORYREGISTER_H__
#define __PROXYFACTORYREGISTER_H__

#include "ProxyBase.h"
#include "ProxyFactory.h"

NAMESPACE_BEG(proxy)

class ProxyFactoryRegister
{
  public:
    ProxyFactoryRegister();
    virtual ~ProxyFactoryRegister();

	static ProxyFactoryRegister* getRegister();
	static bool isValid();

	void registerFactory(EEndpointType t, int proxyIns, ProxyFactory *factory);
	void unregisterFactory(EEndpointType t, int proxyIns, ProxyFactory *factory);

	ProxyFactory* getProxyFactory(EEndpointType t, int proxyIns);
  protected:
	typedef std::map<int, ProxyFactory *> FactoryList;

	FactoryList mFactories[EndpointType_Max];
	static bool mbValid;
};

NAMESPACE_END // namespace proxy

#endif // __PROXYFACTORYREGISTER_H__
