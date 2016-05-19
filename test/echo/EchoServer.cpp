#include "core/CillCore.h"

#include "Proxydef.h"
#include "core/CillCore.h"
#include "asyncnet/AsyncNet.h"
#include "asyncnet/TraceLog.h"
#include "asyncnet/system.h"

using namespace core;

int main()
{
	core::createTrace(levelTrace|levelWarning|levelError|levelEmphasis);
	core::output2Console();
	core::output2Html("EchoServer.html");

	AsyncCore *asncore = asn_core_new();
	long hidConn = asn_core_new_connect(asncore, "127.0.0.1", 20001, 0);
	if (hidConn < 0)
	{
		logError("connect to proxy err:"<<coreStrError(coreLastError()));
		closeTrace();
		return 1;
	}

	ostrbuf osb;
	char buf[MAX_BUF], peername[MAX_BUF];
	int evt = 0;
	long wparam = 0, lparam = 0, hr = 0;
	bool bloop = true;
	while (bloop)
	{
		asn_core_wait(asncore, -1);
		
		hr = asn_core_read(asncore, &evt, &wparam, &lparam, buf, MAX_BUF-1);
		while (hr != -1)
		{
			switch (evt)
			{
			case ASYNC_CORE_EVT_NEW:		/* new: (hid, tag)   */
				{
					logTraceLn("new! hid="<<wparam);
				}
				break;
			case ASYNC_CORE_EVT_LEAVE:		/* leave: (hid, tag) */
				{
					logWarningLn("leave! hid="<<wparam);
					bloop = false;
					break;
				}
				break;
			case ASYNC_CORE_EVT_ESTAB:		/* estab: (hid, tag) */
				{
					logTraceLn("estabed! hid="<<wparam);
				}
				break;
			case ASYNC_CORE_EVT_DATA:		/* data: (hid, tag)  */
				{
					proxy::EndpointID cliid;
					MemoryStream *pStream = MemoryStream::ObjPool().createObject();
					pStream->append(buf, sizeof(cliid));
					(*pStream)>>cliid.asInt;
					
					osb.clear();
					if (0 == asn_core_peername(asncore, wparam, peername))
					{
						osb<<"from:"<<peername<<"  ";
					}
					buf[hr] = 0;
					osb<<"say:"<<(buf+sizeof(cliid));
					logInfoLn(osb.c_str());
					asn_core_send(asncore, wparam, buf, hr);
				}
				break;
			}
			
			hr = asn_core_read(asncore, &evt, &wparam, &lparam, buf, MAX_BUF-1);
		}
	}

	core::closeTrace();
	return 0;
}
