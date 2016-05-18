#include "ProxyBase.h"
#include "EndptIDGenerator.h"
#include "ClientAcceptor.h"
#include "ServerAcceptor.h"
#include "EndpointManager.h"

using namespace proxy;

int gProxyInstance = 0;

//--------------------------------------------------------------------------
// 接入管理
class AcceptorMgr
{
  public:
    AcceptorMgr(AsyncCore *asncore, EndpointManager *pEndptMgr)
			:mpAsnCore(asncore)
			,mpEndptMgr(pEndptMgr)
			,mAcceptors()
	{		
	}	
	
    virtual ~AcceptorMgr()
	{		
	}

	bool initialise()
	{
		ClientAcceptor *pClientAcceptor = new ClientAcceptor(mpAsnCore, mpEndptMgr, 20000);
		if (!pClientAcceptor->initialise())
		{
			logErrorLn("initialise client accepor error!");
			return false;
		}

		ServerAcceptor *pServerAcceptor = new ServerAcceptor(mpAsnCore, mpEndptMgr, 20001);
		if (!pServerAcceptor->initialise())
		{
			pClientAcceptor->finalise();
			logErrorLn("initialise server accepor error!");
			return false;
		}
		
		mAcceptors.push_back(pClientAcceptor);
		mAcceptors.push_back(pServerAcceptor);
		return true;
	}

	void finalise()
	{
		AcceptorList::iterator it = mAcceptors.begin();
		for (; it != mAcceptors.begin(); ++it)
		{
			Acceptor *pAcceptor = *it;
			pAcceptor->finalise();
			delete pAcceptor;
		}
		mAcceptors.clear();
	}

	void accept(SockID newSock, SockID listenSock)
	{
		AcceptorList::iterator it = mAcceptors.begin();
		for (; it != mAcceptors.end(); ++it)
		{
			Acceptor *pAcceptor = *it;
			EProxyCode retCode = pAcceptor->tryAccept(newSock, listenSock);
			if (retCode != ProxyCode_Mismatch)
				break;
		}
	}
  private:
	typedef std::list<Acceptor *> AcceptorList;

	AsyncCore *mpAsnCore;
	EndpointManager *mpEndptMgr;
	AcceptorList mAcceptors;
};
//--------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    createTrace(levelInfo|levelTrace|levelWarning|levelError|levelEmphasis);
	output2Console();
	output2Html("proxy.html");

	// initialise the net library
	AsyncCore *asncore = asn_core_new();
	assert(asncore != NULL && "new AsyncCore");

	// initialise Endpoint Manager
	new EndptIDGenerator(1);
	EndptIDGenerator::getSingletonPtr()->initialise();
	
	EndpointManager *pEndptMgr = new EndpointManager();
	assert(pEndptMgr && pEndptMgr->initialise() && "initialise EndpointManager");

	// initialise acceptor
	AcceptorMgr *pAcceptorMgr = new AcceptorMgr(asncore, pEndptMgr);
	assert(pAcceptorMgr && pAcceptorMgr->initialise() && "initialise AcceptorMgr");
	
	static const int DEF_RECV_BUFSZ = 1024;
	char defRecvBuf[DEF_RECV_BUFSZ] = {0};
	void *recvBuf = NULL;
	int bufLen = DEF_RECV_BUFSZ;
	
	int evt = 0;
	long wparam = 0, lparam = 0, hr = 0;
	while (true)
	{
		asn_core_wait(asncore, -1);

		recvBuf = defRecvBuf;
		bufLen = DEF_RECV_BUFSZ;
		hr = asn_core_read(asncore, &evt, &wparam, &lparam, recvBuf, bufLen);
		while (hr != -1)
		{
			if (-2 == hr) // short of buf
			{
				if (recvBuf != defRecvBuf) free(recvBuf);
				bufLen = asn_core_read(asncore, &evt, &wparam, &lparam, NULL, 0);
				recvBuf = malloc(bufLen);
				goto read_next;
			}
			
			switch (evt)
			{
			case ASYNCCORE_EVT_NEW:
				{
					if (lparam > 0)
					{
						pAcceptorMgr->accept(wparam, lparam);
					}
				}
				break;
			case ASYNCCORE_EVT_LEAVE:
				{
					pEndptMgr->onLeave(wparam);
				}
				break;
			case ASYNCCORE_EVT_DATA:
				{
					pEndptMgr->onRecv(wparam, recvBuf, hr);
				}
				break;
			default:
				break;
			}
	  
			if (recvBuf != defRecvBuf)
			{
				free(recvBuf);
				recvBuf = defRecvBuf;
				bufLen = DEF_RECV_BUFSZ;				
			}
			
	  read_next:
			hr = asn_core_read(asncore, &evt, &wparam, &lparam, recvBuf, bufLen);			
		}		
		if (recvBuf != defRecvBuf) free(recvBuf);
	}

	// uninitialise
	pAcceptorMgr->finalise();
	pEndptMgr->finalise();
	EndptIDGenerator::getSingletonPtr()->finalise();

	delete pAcceptorMgr;
	delete pEndptMgr;
	delete EndptIDGenerator::getSingletonPtr();
	asn_core_delete(asncore);
	
	closeTrace();
	
    return 0;
}
