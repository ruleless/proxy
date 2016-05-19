#ifndef __PROXYDEF_H__
#define __PROXYDEF_H__

NAMESPACE_BEG(proxy)

union EndpointID
{
	struct
	{
		uint proxyId:8;
		uint index:24;
	} asStruct;
	uint asInt;
};

enum EEndpointType
{
	EndpointType_Unknown,
	
	EndpointType_Server,
	EndpointType_Client,

	EndpointType_Max,
};

NAMESPACE_END // namespace proxy

#endif // __PROXYDEF_H__
