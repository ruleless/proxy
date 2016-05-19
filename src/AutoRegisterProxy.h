#ifndef __AUTOREGISTERPROXY_H__
#define __AUTOREGISTERPROXY_H__

#include "ProxyBase.h"
#include "ProxyFactoryImpl.h"
#include "ProxyFactoryRegister.h"

NAMESPACE_BEG(proxy)

template <int ProtocolType, class ProxyT>
class AutoRegisterProxy
{
  public:
    AutoRegisterProxy()
			:mRegister(ProxyFactoryRegister::getRegister())
	{
		mRegister->registerFactory(mFactory.getType(), ProtocolType, &mFactory);
	}
	
    virtual ~AutoRegisterProxy()
	{
		mRegister->unregisterFactory(mFactory.getType(), ProtocolType, &mFactory);
	}
  protected:
	ProxyFactoryRegister *mRegister;
	ProxyFactoryImpl<ProxyT> mFactory;
};

NAMESPACE_END // namespace proxy


#define PROXY_DECLARATION(ProxyT)

#define PROXY_IMPLEMENTION(ProxyT)
	
#define PROXY_FACTORY_REGISTRATION(protoType, ProxyT)				\
	static proxy::AutoRegisterProxy<protoType, ProxyT> _autoRegisterProxy_##ProxyT

#endif // __AUTOREGISTERPROXY_H__
