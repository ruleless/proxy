#include "Acceptor.h"
#include "EndptIDGenerator.h"
#include "EndpointManager.h"

NAMESPACE_BEG(proxy)

Acceptor::~Acceptor()
{
}

bool Acceptor::initialise()
{
	mSockId = asn_core_new_listen(mpAsnCore, "0.0.0.0", mListenPort, 0);
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
		asn_core_close(mpAsnCore, mSockId, 0);
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

NAMESPACE_END // namespace proxy
