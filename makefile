#	tld-makefile
#	Matthew A. Terry (terrym@uwindsor.ca)
###############################################################################
SRCDIR = src

SUBDIRS = $(SRCDIR)

all:
@echo
@echo "############################"
@echo "### BUILDING ALL TARGETS ###"
@echo "############################"
@echo 
for i in $(SUBDIRS) ; do \
( cd $$i ; make ) ;
\ done
#rules for individual targets

libs:
@cd $(SRCDIR) ; make

clean:
rm -f *~
for i in $(SUBDIRS) ; do \
( cd $$i ; make clean) ; \
done
