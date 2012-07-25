CRAVE_HOME = ../../build/crave
include $(CRAVE_HOME)/share/crave/crave.makefile
include $(CRAVE_HOME)/share/metaSMT/metaSMT.makefile

SYSTEMC_INCLUDE = $(SYSTEMC_HOME)/include
SYSTEMC_LIB = $(SYSTEMC_HOME)/lib-linux/libsystemc.a
ifeq (${shell getconf LONG_BIT}, 64)
        SYSTEMC_LIB = $(SYSTEMC_HOME)/lib-linux64/libsystemc.a
endif

TLM_INCLUDE = $(TLM_HOME)/include/tlm
