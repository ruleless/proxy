#include "ProxyBase.h"

int main(int argc, char *argv[])
{
    createTrace(levelInfo|levelTrace|levelWarning|levelError|levelEmphasis);
	output2Console();
	output2Html("proxy.html");

	AsyncCore *asncore = asn_core_new();
	assert(asncore != NULL && "new AsyncCore");

	static const int DEF_RECV_BUFSZ = 1024;
	char defRecvBuf[DEF_RECV_BUFSZ] = {0};
	void *recvBuf = NULL;
	int bufLen = DEF_RECV_BUFSZ;
	
	int evt = 0;
	long wparam = 0, lparam = 0, hr = 0;
	while (true)
	{
		asn_core_wait(asncore, 16);

		recvBuf = defRecvBuf;
		bufLen = DEF_RECV_BUFSZ;

  process_beg:
		hr = asn_core_read(asncore, &evt, &wparam, &lparam, recvBuf, bufLen);

		if (-1 == hr)
		{
			if (recvBuf != defRecvBuf) free(recvBuf);
			continue;
		}

		if (-2 == hr)
		{
			if (recvBuf != defRecvBuf) free(recvBuf);
			bufLen = asn_core_read(asncore, &evt, &wparam, &lparam, NULL, 0);
			recvBuf = malloc(bufLen);
			goto process_beg;
		}
		assert(hr >= 0 && "hr >= 0");

		switch (hr)
		{
		case ASYNCCORE_EVT_NEW:
			break;
		case ASYNCCORE_EVT_LEAVE:
			break;
		case ASYNCCORE_EVT_DATA:
			break;
		default:
			break;
		}

		if (recvBuf != defRecvBuf) free(recvBuf);
	}
	
	asn_core_delete(asncore);	
	closeTrace();
	
    return 0;
}
