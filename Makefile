SRCDIR:=$(shell pwd)
BUILD:=$(SRCDIR)/build


ifndef
  ifeq (x86_64,$(shell uname -m))
    BW:=64
  else
    BW:=32
  endif
endif

ifndef MAKECMDGOALS
MAKECMDGOALS=all
endif

${MAKECMDGOALS}: ${BUILD}/Makefile
	@${MAKE} -q -s -C ${BUILD}  ${MAKECMDGOALS}|| ${MAKE} -s -C ${BUILD} ${MAKECMDGOALS}


${BUILD}/Makefile: 
	./bootstrap.sh -d ${SRCDIR}/deps -m RELEASE ${BUILD}

.PHONY: update
update:
	git pull
	git submodule update

.PHONY: distclean
distclean:
	rm -rf $(BUILD)
