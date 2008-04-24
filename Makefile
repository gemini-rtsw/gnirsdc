# $Id$
#

include .applTop/config/CONFIG

APPLIC_DIR_TYPE = sys

include .applTop/config/RULES.Dirs

PROD =	$(notdir $(shell pwd))
TAR =	/usr/bin/tar
COMPRESS = gzip

release:
	$(RM) $(PROD).tar $(PROD).tar.Z .xfile
	find * \
	    \( -name bin -o -name config -o -name db -o -name epics \
		-o -name include/rec -o -name 'O.*' -o -name '*.dctsdr' \
		-o -name '*.sdrSum' -o -name .applTop -o -name .cvsignore \
		-o -name .epics -o -name .version  -o -name '...*' \
		-o -name '*%' -o -name '*~' -o -name '*.Z' -o -name '*.gz' \
		-o -name 'core' -o -name 'CVS' -o -name bad -o -name '.src'\
		-o -name old \
	    \) -prune -print > .xfile
	find 'data' -name '*.db' -o -name '*.dl' -print >> .xfile
	echo 'capfast/cad.rc' >> .xfile
	echo 'dl/template.adl' >> .xfile
	echo 'dl/colors.adl' >> .xfile
	echo 'startup/local.vws' >> .xfile
	echo 'startup/resource.def' >> .xfile
	$(TAR) cvXf .xfile $(PROD).tar *
	$(COMPRESS) $(PROD).tar
	$(RM) .xfile
