#ifndef __PROXYBASE_H__
#define __PROXYBASE_H__

#include "core/CillCore.h"
#include "asyncnet/AsyncNet.h"
#include "asyncnet/system.h"

using core::mchar;
using core::wchar;
using core::mstring;
using core::wstring;

using core::tchar;
using core::tstring;

using core::uchar;
using core::ushort;
using core::uint;
using core::ulong;

using core::int64;
using core::int32;
using core::int16;
using core::int8;
using core::uint64;
using core::uint32;
using core::uint16;
using core::uint8;
using core::intptr;
using core::uintptr;

using core::intptr;
using core::uintptr;

using core::createTrace;
using core::output2Console;
using core::output2Html;
using core::closeTrace;
using core::levelInfo;
using core::levelTrace;
using core::levelWarning;
using core::levelError;
using core::levelEmphasis;

using core::ostrbuf;

typedef long SockID;

enum
{
	MAX_ENDPOINT = 8192,
};

enum EProxyCode
{
	ProxyCode_Success = 0,

	ProxyCode_Mismatch,
	ProxyCode_NoMoreID,
	ProxyCode_CreateEndptFailed,
	ProxyCode_AddEndptFailed,
};

extern int gProxyInstance;

#endif // __PROXYBASE_H__
