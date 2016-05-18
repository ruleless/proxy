#ifndef __AUTOREGISTERPROXY_H__
#define __AUTOREGISTERPROXY_H__

#include "ProxyBase.h"
#include "ProxyFactoryImpl.h"
#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

template <int proxyIns, class ProxyT>
class AutoRegisterProxy
{
  public:
    AutoRegisterProxy()
			:mRegister(ProxyFactoryRegister::getRegister())
	{
		mRegister->registerFactory(mFactory.getType(), proxyIns, &mFactory);
	}
	
    virtual ~AutoRegisterProxy()
	{
		mRegister->unregisterFactory(mFactory.getType(), proxyIns, &mFactory);
	}
  protected:
	ProxyFactoryRegister *mRegister;
	ProxyFactoryImpl<ProxyT> mFactory;
};

NAMESPACE_END // namespace proxy


#define PROXY_DECLARATION(ProxyT)

#define PROXY_IMPLEMENTION(ProxyT)
	
#define PROXY_FACTORY_REGISTRATION(proxyIns, ProxyT)				\
	static proxy::AutoRegisterProxy<proxyIns, ProxyT> _autoRegisterProxy_##ProxyT

#endif // __AUTOREGISTERPROXY_H__
