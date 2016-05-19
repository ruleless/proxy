#include "NetWraper.h"

NAMESPACE_BEG(proxy)

static NetWraper _s_netwraper;
NetWraper *gNetWraper = &_s_netwraper;

NetWraper::~NetWraper()
{}

bool NetWraper::initialise()
{
	mpAsnCore = asn_core_new();
	assert(mpAsnCore != NULL && "new AsyncCore");
	return true;
}

void NetWraper::finalise()
{
	asn_core_delete(mpAsnCore);
}

long NetWraper::read(int *event, long *wparam, long *lparam, void *data, long size)
{
	return asn_core_read(mpAsnCore, event, wparam, lparam, data, size);
}

long NetWraper::send(SockID sockId, const void *ptr, long len)
{
	return asn_core_send(mpAsnCore, sockId, ptr, len);
}

void NetWraper::wait(unsigned long millisec)
{
	return asn_core_wait(mpAsnCore, millisec);
}

long NetWraper::connect(const char *ip, int port, int header)
{
	return asn_core_new_connect(mpAsnCore, ip, port, header);
}

long NetWraper::listen(const char *ip, int port, int header)
{
	return asn_core_new_listen(mpAsnCore, ip, port, header);
}

int NetWraper::close(SockID sockId, int code)
{
	return asn_core_close(mpAsnCore, sockId, code);
}

NAMESPACE_END // namespace proxy
