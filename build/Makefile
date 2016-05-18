TOPDIR:=..
CILLDIR:=$(TOPDIR)/cill

DIRS:=$(TOPDIR)/src $(TOPDIR)/proxy
OBJS:=$(foreach v,$(DIRS),$(wildcard $(v)/*.o))

LDFLAGS+=-L $(CILLDIR)/lib -lasyncnet -lcill -lkmem -lpthread -lrt -ldl

TARGET:=proxy.out
EXEPATH:=..

include $(TOPDIR)/link.mak
