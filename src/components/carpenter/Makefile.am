current = $(PWD)

dist-hook:
	mkdir -p $(distdir)
	(cd $(top_srcdir)/src/components/ogre/carpenter; tar cf - `find . -name \*.xml` | ( cd $(current); cd $(distdir); tar xf -))

install-data-local:
	mkdir -p $(DESTDIR)$(datadir)/ember/carpenter 
	(cd $(top_srcdir)/src/components/ogre/carpenter; tar cf - `find . -name \*.xml`) | (cd $(DESTDIR)$(datadir)/ember/carpenter/; tar xf -)

uninstall-local:
	find $(DESTDIR)$(datadir)/ember/carpenter/ -name  \*.xml | xargs rm



AM_CPPFLAGS = -I$(top_srcdir)/src  -I$(top_builddir)/src
METASOURCES = AUTO
noinst_HEADERS = Carpenter.h BluePrint.h
noinst_LIBRARIES = libCarpenter.a
libCarpenter_a_SOURCES = Carpenter.cpp BluePrint.cpp

