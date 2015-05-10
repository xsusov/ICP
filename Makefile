CC            	= gcc
CXX           	= g++
CFLAGS        = -pipe -g -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -std=c++11 -g -Wall -W $(DEFINES)
QMAKE         	= /usr/bin/qmake-qt4
ALLDIRS		= ./src/* ./docu/* ./examples/*
ALLFILES	= Makefile README.txt
PACKNAME	= xsusov01-xbandz00
GUI		= labyrinth2015
CLI		= labyrinth2015-cli
SERVER		= labyrinth2015-server
ALLBIN		= $(GUI) $(CLI) $(SERVER)

### CLI
SOURCES_CLI	= src/server.cpp \
		src/player.cpp \
		src/card.cpp \
		src/gameobject.cpp \
		src/gameitem.cpp \
		src/boardfield.cpp \
		src/gameboard.cpp \
		src/deck.cpp \
		src/iboardfield.cpp \
		src/tboardfield.cpp \
		src/lboardfield.cpp \
		src/clienthandler.cpp \
		src/game.cpp \
		src/viewer.cpp \
		src/viewercli.cpp \
		src/controller.cpp 
OBJECTS_CLI	= server.o \
		player.o \
		card.o \
		gameobject.o \
		gameitem.o \
		boardfield.o \
		gameboard.o \
		deck.o \
		iboardfield.o \
		tboardfield.o \
		lboardfield.o \
		clienthandler.o \
		game.o \
		viewer.o \
		viewercli.o \
		controller.o

all:	gui cli server

.PHONY: gui
gui:		
	@echo "Making some " $(GUI);	


.PHONY: cli
cli:	$(SOURCES_CLI) $(OBJECT_CLI)
	@echo "Making some " $(CLI);
	@echo "CLI sources:";
	@echo $(SOURCES_CLI);
	@echo "CLI objects:";
	@echo $(OBJECTS_CLI);

.PHONY: server
server:		
	echo "Making some " . $(SERVER);


.PHONY:	run
run:	gui
	./$(GUI)

.PHONY:	pack
pack:
	zip $(PACKNAME) $(ALLFILES) $(ALLDIRS)

.PHONY:	doxygen 
doxygen:	
	cd ./src; doxygen;
	
.PHONY: clean
clean:
	rm -rf *.o $(ALLBIN) ./docu/html


