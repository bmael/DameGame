#############################################################################
# Makefile for building: QTDameGame
# Generated by qmake (2.01a) (Qt 4.8.3) on: lun. mars 11 01:19:39 2013
# Project:  QTDameGame.pro
# Template: subdirs
# Command: /usr/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile QTDameGame.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame \
		sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm

DameGame//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) DameGame/ || $(MKDIR) DameGame/ 
	cd DameGame/ && $(QMAKE) /home/mael/Bureau/M1_ALMA/reseaux/QTDameGame/DameGame/DameGame.pro -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) DameGame/ || $(MKDIR) DameGame/ 
	cd DameGame/ && $(QMAKE) /home/mael/Bureau/M1_ALMA/reseaux/QTDameGame/DameGame/DameGame.pro -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_default-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) 
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_default: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) 
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_first-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) first
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_first: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) first
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-all-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) all
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-all: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) all
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-clean-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) clean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-clean: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) clean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-distclean-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) distclean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-distclean: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) distclean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-install_subtargets-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) install
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-install_subtargets: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) install
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-uninstall_subtargets-ordered: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) uninstall
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-uninstall_subtargets: DameGame//$(MAKEFILE) FORCE
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) uninstall
ihm//$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) ihm/ || $(MKDIR) ihm/ 
	cd ihm/ && $(QMAKE) /home/mael/Bureau/M1_ALMA/reseaux/QTDameGame/ihm/ihm.pro -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) ihm/ || $(MKDIR) ihm/ 
	cd ihm/ && $(QMAKE) /home/mael/Bureau/M1_ALMA/reseaux/QTDameGame/ihm/ihm.pro -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE)
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_default-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_default-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) 
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_default: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) 
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_first-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_first-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) first
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_first: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) first
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-all-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-all-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) all
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-all: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) all
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-clean-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-clean-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) clean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-clean: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) clean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-distclean-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-distclean-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) distclean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-distclean: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) distclean
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-install_subtargets-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-install_subtargets-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) install
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-install_subtargets: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) install
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-uninstall_subtargets-ordered: ihm//$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-uninstall_subtargets-ordered  FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) uninstall
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-uninstall_subtargets: ihm//$(MAKEFILE) FORCE
	cd ihm/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: QTDameGame.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile QTDameGame.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/declarative_debug.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile QTDameGame.pro

qmake_all: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-qmake_all sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-qmake_all FORCE

make_default: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_default-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_default-ordered FORCE
make_first: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-make_first-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-make_first-ordered FORCE
all: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-all-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-all-ordered FORCE
clean: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-clean-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-clean-ordered FORCE
distclean: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-distclean-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-distclean-ordered FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-install_subtargets-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-install_subtargets-ordered FORCE
uninstall_subtargets: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-uninstall_subtargets-ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-uninstall_subtargets-ordered FORCE

sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-check_ordered: DameGame/$(MAKEFILE)
	cd DameGame/ && $(MAKE) -f $(MAKEFILE) check
sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-check_ordered: ihm/$(MAKEFILE) sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-check_ordered 
	cd ihm/ && $(MAKE) -f $(MAKEFILE) check
check: sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-DameGame-check_ordered sub--home-mael-Bureau-M1_ALMA-reseaux-QTDameGame-ihm-check_ordered

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

