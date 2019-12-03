OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=dll
BINEXT?=exe
else
SOEXT?=so
BINEXT?=out
endif
ifneq (,$(findstring mingw,$(OS)))
RUNENV=
else
RUNENV=
endif

ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
BUILDDIR=./bin/build
BIN=./bin/a.$(BINEXT)
SRCDIR=src
SRC:=$(shell find $(SRCDIR) -name '*.cpp')
OBJS:=$(addprefix $(BUILDDIR)/,$(SRC:%.cpp=%.o))
CFLAGS=\
	-I./include
LDFLAGS=
ifneq (,$(findstring android,$(OS)))
LDFLAGS+=\
	-llog
endif
LDFLAGS=\
	-lPocoFoundation
all:\
	$(BIN)
$(BIN):$(OBJS)
	@$(CXX)\
		$(CFLAGS)\
		$(OBJS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin
	@rm -r ./log/*
run: $(BIN)
	$(RUNENV) $(BIN)
lsvar:
	@echo $(BIN)
	@echo $(OBJS)
	@echo $(SRC)
	@echo $(SRCDIR)
	@echo $(PREFIX)




