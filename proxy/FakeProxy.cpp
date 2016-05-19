#include "FakeProxy.h"
#include "AutoRegisterProxy.h"

NAMESPACE_BEG(proxy)

//--------------------------------------------------------------------------
PROXY_FACTORY_REGISTRATION(0, FakeClientProxy);
FakeClientProxy::~FakeClientProxy()
{
}
	
void FakeClientProxy::onRecv(void* data, long datalen)
{
	ostrbuf osb;
	osb.push_back(data, datalen);
	osb<<"\0";
	logInfoLn("recv from client! (sockid="<<mSockId<<",id="<<mId.asInt<<") datalen:"<<datalen<<" buf:"<<osb.c_str());
}

void FakeClientProxy::onLeave()
{
	logWarningLn("client leave! (sockid="<<mSockId<<",id="<<mId.asInt<<")");
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
PROXY_FACTORY_REGISTRATION(0, FakeServerProxy);
FakeServerProxy::~FakeServerProxy()
{
}
	
void FakeServerProxy::onRecv(void* data, long datalen)
{
}

void FakeServerProxy::onLeave()
{
}
//--------------------------------------------------------------------------

NAMESPACE_END // namespace proxy
