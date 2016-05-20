#include "ProxyBase.h"
#include "NetWraper.h"
#include "Acceptor.h"
#include "EndptIDGenerator.h"
#include "EndpointManager.h"

using namespace proxy;

int gProxyProtocolType = 1;

//--------------------------------------------------------------------------
// 接入管理
class AcceptorMgr
{
  public:
    AcceptorMgr(EndpointManager *pEndptMgr)
			:mpEndptMgr(pEndptMgr)
			,mAcceptors()
	{		
	}	
	
    virtual ~AcceptorMgr()
	{		
	}

	bool initialise()
	{
		Acceptor *pClientAcceptor = new Acceptor(mpEndptMgr, 20000, EndpointType_Client);
		if (!pClientAcceptor->initialise())
		{
			logErrorLn("initialise client accepor error!");
			return false;
		}

		Acceptor *pServerAcceptor = new Acceptor(mpEndptMgr, 20001, EndpointType_Server);
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
	gNetWraper->initialise();

	// initialise Endpoint Manager
	new EndptIDGenerator(1);
	EndptIDGenerator::getSingletonPtr()->initialise();
	
	EndpointManager *pEndptMgr = new EndpointManager();
	assert(pEndptMgr && pEndptMgr->initialise() && "initialise EndpointManager");

	// initialise acceptor
	AcceptorMgr *pAcceptorMgr = new AcceptorMgr(pEndptMgr);
	assert(pAcceptorMgr && pAcceptorMgr->initialise() && "initialise AcceptorMgr");
	
	static const int DEF_RECV_BUFSZ = 1024;
	char defRecvBuf[DEF_RECV_BUFSZ] = {0};
	void *recvBuf = NULL;
	int bufLen = DEF_RECV_BUFSZ;
	
	int evt = 0;
	long wparam = 0, lparam = 0, hr = 0;
	while (true)
	{
		gNetWraper->wait(-1);

		recvBuf = defRecvBuf;
		bufLen = DEF_RECV_BUFSZ;
		hr = gNetWraper->read(&evt, &wparam, &lparam, recvBuf, bufLen);
		while (hr != -1)
		{
			if (-2 == hr) // short of buf
			{
				if (recvBuf != defRecvBuf) free(recvBuf);
				bufLen = gNetWraper->read(&evt, &wparam, &lparam, NULL, 0);
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
			hr = gNetWraper->read(&evt, &wparam, &lparam, recvBuf, bufLen);
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
	gNetWraper->finalise();
	
	closeTrace();
	
    return 0;
}
