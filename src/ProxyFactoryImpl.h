#ifndef __COMMANDFACTORYIMPL_H__
#define __COMMANDFACTORYIMPL_H__

#include "ProxyBase.h"
#include "ProxyFactory.h"

NAMESPACE_BEG(proxy)

template <class ProxyT>
class ProxyFactoryImpl : public ProxyFactory
{
  public:
    virtual ~ProxyFactoryImpl() {}

	virtual Endpoint* createProxy(EndpointManager *pEndptMgr)
	{
		ProxyT *p = new ProxyT(pEndptMgr);
		return p;
	}

	virtual EEndpointType getType()
	{
		return mFakeObj.getType();
	}
  private:
	ProxyT mFakeObj;
};

NAMESPACE_END // namespace proxy

#endif // __COMMANDFACTORYIMPL_H__
