#include "SimpleProxy.h"
#include "EndpointManager.h"
#include "AutoRegisterProxy.h"

NAMESPACE_BEG(proxy)

//--------------------------------------------------------------------------
PROXY_FACTORY_REGISTRATION(1, SimpleClientProxy);

SimpleClientProxy::~SimpleClientProxy()
{}
	
void SimpleClientProxy::onRecv(void* data, long datalen)
{
	MemoryStream *stream = MemoryStream::ObjPool().createObject();
	(*stream)<<(uint32)mId.asInt;
	stream->append((uint8 *)data, datalen);

	bool hasServer = false;
	EndpointManager::EndptIterator it = mpEndptMgr->getSvrListIterator();
	for (; it.hasMoreElements(); it.moveNext())
	{
		Endpoint *ep = it.peekNextValue();
		ep->send(stream->data(), stream->length());
		hasServer = true;
		break;
	}
	if (!hasServer)
	{
		logErrorLn("no server connect to this proxy! proto-type="<<gProxyProtocolType);
	}

	MemoryStream::ObjPool().reclaimObject(stream);
}

void SimpleClientProxy::onLeave()
{
	logWarningLn("client leave! (sockid="<<mSockId<<",id="<<mId.asInt<<")");
}
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
PROXY_FACTORY_REGISTRATION(1, SimpleServerProxy);

SimpleServerProxy::~SimpleServerProxy()
{}

void SimpleServerProxy::onRecv(void* data, long datalen)
{
	if (datalen > sizeof(uint))
	{
		MemoryStream *stream = MemoryStream::ObjPool().createObject();
		stream->append(data, sizeof(uint));

		EndpointID cliid;
		(*stream)>>cliid.asInt;
		Endpoint *ep = mpEndptMgr->getEndptByIndex(cliid);
		if (ep)
		{
			ep->send((char *)data+stream->rpos(), datalen-stream->rpos());
		}
		else
		{
			logWarningLn("SimpleServerProxy::onRecv()  find no client! "
						 "(sockId="<<mSockId<<",id="<<mId.asInt<<")");
		}

		MemoryStream::ObjPool().reclaimObject(stream);
	}	
}

void SimpleServerProxy::onLeave()
{
	logWarningLn("server leave! (sockid="<<mSockId<<",id="<<mId.asInt<<")");
}
//--------------------------------------------------------------------------

NAMESPACE_END // namespace proxy
