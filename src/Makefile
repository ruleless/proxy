TOPDIR:=..
CILLDIR:=$(TOPDIR)/cill

CXXFLAGS+=-I $(CILLDIR) -I $(CILLDIR)/kmem
LDFLAGS+=-L $(CILLDIR)/lib -lasyncnet -lcill -lkmem -lpthread -lrt -ldl
TARGET:=proxy.out

include $(TOPDIR)/build.mak
