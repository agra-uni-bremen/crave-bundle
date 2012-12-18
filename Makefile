SRCDIR:=$(shell pwd)
BUILD:=$(SRCDIR)/build

ifndef MAKECMDGOALS
MAKECMDGOALS=all
endif

${MAKECMDGOALS}: ${BUILD}/Makefile
	@${MAKE} -q -s -C ${BUILD}  ${MAKECMDGOALS}|| ${MAKE} -s -C ${BUILD} ${MAKECMDGOALS}


BOOSTRAP_ARGS :=
ifdef CMAKE
  BOOSTRAP_ARGS += --cmake=${CMAKE}
endif

ifdef CACHE
  BOOSTRAP_ARGS += --cache ${CACHE}
endif

${BUILD}/Makefile:
	./bootstrap.sh -d ${SRCDIR}/deps -m RELEASE ${BUILD} ${BOOSTRAP_ARGS}

.PHONY: update
update:
	git pull
	git submodule update

.PHONY: distclean
distclean:
	rm -rf $(BUILD)
