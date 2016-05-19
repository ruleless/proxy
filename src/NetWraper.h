#ifndef __NETWRAPER_H__
#define __NETWRAPER_H__

#include "ProxyBase.h"
#include "asyncnet/AsyncNet.h"
#include "asyncnet/system.h"

NAMESPACE_BEG(proxy)

class NetWraper
{
  public:
    NetWraper()
			:mpAsnCore(NULL)
	{}
	
    virtual ~NetWraper();

	bool initialise();
	void finalise();

	long read(int *event, long *wparam, long *lparam, void *data, long size);
	long send(SockID sockId, const void *ptr, long len);
	void wait(unsigned long millisec);

	long connect(const char *ip, int port, int header);
	long listen(const char *ip, int port, int header);
	int close(SockID sockId, int code);
  private:
	AsyncCore *mpAsnCore;
};

extern NetWraper *gNetWraper;

NAMESPACE_END // namespace proxy

#endif // __NETWRAPER_H__
