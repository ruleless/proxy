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

	void registerFactory(EEndpointType t, int protoType, ProxyFactory *factory);
	void unregisterFactory(EEndpointType t, int protoType, ProxyFactory *factory);

	ProxyFactory* getProxyFactory(EEndpointType t, int protoType);
  protected:
	typedef std::map<int, ProxyFactory *> FactoryList;

	FactoryList mFactories[EndpointType_Max];
	static bool mbValid;
};

NAMESPACE_END // namespace proxy

#endif // __PROXYFACTORYREGISTER_H__
