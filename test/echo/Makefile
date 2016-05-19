CC=clang
CXX=clang++
MAKE=make

CFLAGS+=-g -Wall
CXXFLAGS+=-g -Wall

TOPDIR:=../..
CILLDIR:=$(TOPDIR)/cill

CXXFLAGS:=-I $(CILLDIR) -I $(CILLDIR)/kmem -I $(TOPDIR)/src
LDFLAGS:=-L $(CILLDIR)/lib -lcill -lasyncnet -lkmem -lpthread -lrt -ldl

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
TARGETS:=$(SRCS:%.cpp=%.out)


all:$(TARGETS)

EchoServer.out:EchoServer.o
	$(CXX) -o $@ $^ $(LDFLAGS)

EchoClient.out:EchoClient.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJS):%.o:%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	-rm $(OBJS) $(TARGETS)

fake:
	@echo $(OBJS)
