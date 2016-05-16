#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "ProxyBase.h"

NAMESPACE_BEG(proxy)

class Acceptor : public core::Thre
{
  public:
    Acceptor();
    virtual ~Acceptor();

	
  protected:
};

NAMESPACE_END // namespace proxy

#endif // __ACCEPTOR_H__
