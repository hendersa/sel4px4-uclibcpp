# AWH
ifndef SOURCE_DIR
SOURCE_DIR = .
endif

CROSS   = $(CROSS_COMPILE)

MAKE    = make
SUBDIRS = $(TOPDIR)/bin $(TOPDIR)/include $(TOPDIR)/src

# User defines:

noconfig_targets := menuconfig config oldconfig silentoldconfig randconfig \
	defconfig allyesconfig allnoconfig clean distclean \
	release tags TAGS

# AWH - Added SOURCE_DIR
TOPDIR=$(SOURCE_DIR)/

TEMP_TOPDIR=$(TOPDIR)
include $(TOPDIR)Rules.mak

all: headers
	for dir in $(SUBDIRS) ; do \
		$(MAKE) -C $$dir all; \
	done;
	@cp $(TEMP_TOPDIR)/src/*.a .
	@cp $(TEMP_TOPDIR)/src/*.a $(STAGE_DIR)/lib

tests: all
	$(MAKE) -C $(TOPDIR)/tests all

check test: tests
	$(MAKE) -C $(TOPDIR)/tests test

clean:
	for dir in $(SUBDIRS) $(TOPDIR)/tests ; do \
		$(MAKE) -C $$dir clean; \
	done
	#$(MAKE) -C extra/locale clean

distclean: clean
	$(MAKE) -C $(TOPDIR)/extra clean
	$(RM) .config .config.cmd .config.old
	$(RM) include/system_configuration.h

release:
	$(RM) ../uClibc++-$(VERSION).tar
	git archive --format=tar --prefix=uClibc++-$(VERSION)/ HEAD \
		> ../uClibc++-$(VERSION).tar
	cat ../uClibc++-$(VERSION).tar | bzip2 -c9 > ../uClibc++-$(VERSION).tar.bz2
	cat ../uClibc++-$(VERSION).tar | xz -e -c8 > ../uClibc++-$(VERSION).tar.xz
	du -b ../uClibc++-$(VERSION).tar.{bz2,xz}

headers: include/system_configuration.h

install:
	for dir in $(SUBDIRS) ; do \
		$(MAKE) -C $$dir install; \
	done


#Menu configuration system

$(TOPDIR)/extra/config/conf:
	@$(MAKE) -C $(TOPDIR)/extra/config conf

extra/config/mconf:
	@$(MAKE) -C $(TOPDIR)/extra/config ncurses mconf

menuconfig: $(TOPDIR)/extra/config/mconf
	@$< extra/Configs/Config.in

config: $(TOPDIR)/extra/config/conf
	@$< extra/Configs/Config.in

oldconfig: $(TOPDIR)/extra/config/conf
	@$< -o extra/Configs/Config.in

silentoldconfig: $(TOPDIR)/extra/config/conf
	@$< -s extra/Configs/Config.in

randconfig: $(TOPDIR)/extra/config/conf
	@$< -r extra/Configs/Config.in

allyesconfig: $(TOPDIR)/extra/config/conf
	@$< -y extra/Configs/Config.in

allnoconfig: $(TOPDIR)/extra/config/conf
	@$< -n extra/Configs/Config.in

defconfig: $(TOPDIR)/extra/config/conf
	@$< -d extra/Configs/Config.in

include/system_configuration.h: .config
	@if [ ! -x $(TOPDIR)/extra/config/conf ] ; then \
		$(MAKE) -C $(TOPDIR)/extra/config conf; \
	fi;
	@cd $(TEMP_TOPDIR) ; ./extra/config/conf -o extra/Configs/Config.in  

.config:
	$(MAKE) -C $(TOPDIR) defconfig
