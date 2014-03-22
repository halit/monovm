TARGET = main
PKG = foo.tar.bz2
#EXTRAS = dull.c.null

SRC_EXT = .c
OBJ_EXT = .o
HDR_EXT = .h

COMPILER = gcc
COMPILER_FLAGS = ${CFLAGS}

SRC = $(shell ls *${SRC_EXT})
HDR = $(shell ls *${HDR_EXT})
OBJ = $(shell ls *${SRC_EXT} | sed s\/${SRC_EXT}$$\/${OBJ_EXT}\/)

all: ${OBJ}
	${COMPILER} ${COMPILER_FLAGS} -o ${TARGET} ${OBJ}

%${OBJ_EXT}: %${SRC_EXT}
	${COMPILER} ${COMPILER_FLAGS} -c $< -o $@

pkg:
	@case "${PKG}" in \
	  *.zip) \
	    pkgdir=$(shell echo ${PKG} | sed s\/.zip$$\/\/); \
	    mkdir $$pkgdir &> /dev/null; \
	    cp ${SRC} ${HDR} $$pkgdir &> /dev/null; \
	    cp -r ${EXTRAS} $$pkgdir &> /dev/null; \
	    zip -r ${PKG} $$pkgdir; \
	    rm -rf $$pkgdir;; \
	  *.tar.gz) \
	    pkgdir=$(shell echo ${PKG} | sed s\/.tar.gz$$\/\/); \
	    mkdir $$pkgdir &> /dev/null; \
	    cp ${SRC} ${HDR} $$pkgdir &> /dev/null; \
	    cp -r ${EXTRAS} $$pkgdir &> /dev/null; \
	    tar cfvz $$pkgdir; \
	    rm -rf ${PKG} $$pkgdir;; \
	  *.tar.bz2) \
	    pkgdir=$(shell echo ${PKG} | sed s\/.tar.bz2$$\/\/); \
	    mkdir $$pkgdir &> /dev/null; \
	    cp ${SRC} ${HDR} $$pkgdir &> /dev/null; \
	    #cp -r ${EXTRAS} $$pkgdir &> /dev/null; \
	    tar cfvj ${PKG} $$pkgdir; \
	    rm -rf $$pkgdir;; \
	esac

clean:
	@if `test -e ${TARGET}`; then \
	  rm ${TARGET}; \
	fi

	@for file in ${OBJ}; do \
	  if `test -e $$file`; \
	    then rm $$file; \
	  fi \
	done

	@if `test -e ${PKG}`; then \
	  rm ${PKG}; \
	fi

.PHONY: clean pkg
