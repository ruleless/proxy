#include "Acceptor.h"
#include "NetWraper.h"
#include "ProxyFactoryRegister.h"
#include "EndptIDGenerator.h"
#include "EndpointManager.h"

NAMESPACE_BEG(proxy)

Acceptor::~Acceptor()
{
}

bool Acceptor::initialise()
{
	mSockId = gNetWraper->listen("0.0.0.0", mListenPort, 0);
	if (mSockId < 0)
	{
		mSockId = 0;
		return false;
	}

	return true;
}

void Acceptor::finalise()
{
	if (mSockId != 0)
	{
		gNetWraper->close(mSockId, 0);
		mSockId = 0;	
	}
}

EProxyCode Acceptor::tryAccept(SockID newSock, SockID listenSock, Endpoint *retEp)
{
	if (mSockId != listenSock)
	{
		return ProxyCode_Mismatch;
	}

	EndpointID id = EndptIDGenerator::getSingletonPtr()->genNewId();
	if (0 == id.asInt)
	{
		return ProxyCode_NoMoreID;
	}

	Endpoint *endpt = createEndpt(newSock, id);
	if (NULL == endpt)
	{
		EndptIDGenerator::getSingletonPtr()->restorId(id);
		return ProxyCode_CreateEndptFailed;
	}

	if (!mpEndptMgr->addEndpt(newSock, id, endpt))
	{
		EndptIDGenerator::getSingletonPtr()->restorId(id);
		return ProxyCode_AddEndptFailed;
	}
	
	return ProxyCode_Success;
}

Endpoint* Acceptor::createEndpt(SockID sockId, EndpointID id)
{
	ProxyFactory *factory = ProxyFactoryRegister::getRegister()->getProxyFactory(mAcceptType, gProxyProtocolType);
	if (factory)
	{
		Endpoint *ep = factory->createProxy(mpEndptMgr);
		ep->setSockId(sockId);
		ep->setId(id);
		return ep;
	}
	else
	{
		logErrorLn("got no related proxy! accept-type="<<mAcceptType<<"  protocol-type="<<gProxyProtocolType);
	}

	return NULL;
}

NAMESPACE_END // namespace proxy
