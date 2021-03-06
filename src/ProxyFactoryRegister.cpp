#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

bool ProxyFactoryRegister::mbValid = false;

ProxyFactoryRegister::ProxyFactoryRegister()
{
	mbValid = true;
}

ProxyFactoryRegister::~ProxyFactoryRegister()
{
	mbValid = false;
}

ProxyFactoryRegister* ProxyFactoryRegister::getRegister()
{
	static ProxyFactoryRegister _s_registry;
	return &_s_registry;
}

bool ProxyFactoryRegister::isValid()
{
	return mbValid;
}

void ProxyFactoryRegister::registerFactory(EEndpointType t, int protoType, ProxyFactory *factory)
{
	assert(t >= 0 && t < EndpointType_Max && factory);

	assert(mFactories[t].find(protoType) == mFactories[t].end() && "ProxyFactory already exist");
	mFactories[t].insert(std::make_pair(protoType, factory));
}

void ProxyFactoryRegister::unregisterFactory(EEndpointType t, int protoType, ProxyFactory *factory)
{
	assert(t >= 0 && t < EndpointType_Max && factory);

	FactoryList::iterator it = mFactories[t].find(protoType);
	if (it != mFactories[t].end())
	{
		mFactories[t].erase(it);
	}	
}

ProxyFactory* ProxyFactoryRegister::getProxyFactory(EEndpointType t, int protoType)
{
	FactoryList::iterator it = mFactories[t].find(protoType);
	if (it != mFactories[t].end())
	{
		return it->second;
	}
	return NULL;
}

NAMESPACE_END // namespace proxy
