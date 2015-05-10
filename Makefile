ALLDIRS		= ./src/* ./docu/* ./examples/*
ALLFILES	= Makefile README.txt
PACKNAME	= xsusov01-xbandz00
GUI		= labyrinth2015
CLI		= labyrinth2015-cli
SERVER		= labyrinth2015-server
ALLBIN		= $(GUI) $(CLI) $(SERVER)

.PHONY: all
all:	gui cli server
	

	
.PHONY: gui
gui:		
	echo "Making some " . $(GUI);


.PHONY: cli
cli:	
	echo "Making some " . $(CLI);


.PHONY: server
server:		
	echo "Making some " . $(SERVER);


.PHONY:	run
run:	gui
	./$(GUI)

.PHONY:	pack
pack:
	zip $(PACKNAME) $(ALLFILES) $(ALLDIRS)

.PHONY: clean
clean:
	rm -rf *.o $(ALLBIN) 


