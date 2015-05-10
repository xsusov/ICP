ALLDIRS		= ./src/* ./docu/* ./examples/*
ALLFILES	= Makefile README.txt
PACKNAME	= xsusov01-xbandz00

.PHONY:
pack:
	zip $(PACKNAME) $(ALLFILES) $(ALLDIRS)

