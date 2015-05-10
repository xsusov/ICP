CC            	= gcc
CXX           	= g++
LINK		= g++
CFLAGS        	= -pipe -g -Wall -W $(DEFINES)
CXXFLAGS      	= -pipe -std=c++11 -g -Wall -W $(DEFINES)
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

server.o: src/server.cpp src/constants.h \
		src/strings.h \
		src/clienthandler.h \
		src/player.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h \
		src/deck.h \
		src/boardfield.h \
		src/controller.h \
		src/game.h \
		src/gameboard.h \
		src/lboardfield.h \
		src/tboardfield.h \
		src/iboardfield.h \
		src/viewer.h \
		src/viewercli.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o server.o src/server.cpp

player.o: src/player.cpp src/player.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h \
		src/deck.h \
		src/boardfield.h \
		src/constants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o player.o src/player.cpp

card.o: src/card.cpp src/card.h \
		src/gameitem.h \
		src/gameobject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o card.o src/card.cpp

gameobject.o: src/gameobject.cpp src/gameobject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gameobject.o src/gameobject.cpp

gameitem.o: src/gameitem.cpp src/gameitem.h \
		src/gameobject.h \
		src/constants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gameitem.o src/gameitem.cpp

boardfield.o: src/boardfield.cpp src/boardfield.h \
		src/constants.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o boardfield.o src/boardfield.cpp

gameboard.o: src/gameboard.cpp src/constants.h \
		src/strings.h \
		src/gameboard.h \
		src/boardfield.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h \
		src/lboardfield.h \
		src/tboardfield.h \
		src/iboardfield.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gameboard.o src/gameboard.cpp

deck.o: src/deck.cpp src/deck.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o deck.o src/deck.cpp

iboardfield.o: src/iboardfield.cpp src/iboardfield.h \
		src/boardfield.h \
		src/constants.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o iboardfield.o src/iboardfield.cpp

tboardfield.o: src/tboardfield.cpp src/tboardfield.h \
		src/boardfield.h \
		src/constants.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tboardfield.o src/tboardfield.cpp

lboardfield.o: src/lboardfield.cpp src/lboardfield.h \
		src/boardfield.h \
		src/constants.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lboardfield.o src/lboardfield.cpp

clienthandler.o: src/clienthandler.cpp src/clienthandler.h \
		src/player.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h \
		src/deck.h \
		src/boardfield.h \
		src/constants.h \
		src/controller.h \
		src/game.h \
		src/gameboard.h \
		src/lboardfield.h \
		src/tboardfield.h \
		src/iboardfield.h \
		src/strings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o clienthandler.o src/clienthandler.cpp

game.o: src/game.cpp src/game.h \
		src/gameboard.h \
		src/boardfield.h \
		src/constants.h \
		src/gameobject.h \
		src/gameitem.h \
		src/player.h \
		src/card.h \
		src/deck.h \
		src/lboardfield.h \
		src/tboardfield.h \
		src/iboardfield.h \
		src/strings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o game.o src/game.cpp

viewer.o: src/viewer.cpp src/viewer.h \
		src/player.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h \
		src/deck.h \
		src/boardfield.h \
		src/constants.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o viewer.o src/viewer.cpp

viewercli.o: src/viewercli.cpp src/viewercli.h \
		src/viewer.h \
		src/player.h \
		src/card.h \
		src/gameitem.h \
		src/gameobject.h \
		src/deck.h \
		src/boardfield.h \
		src/constants.h \
		src/strings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o viewercli.o src/viewercli.cpp

controller.o: src/controller.cpp src/controller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o controller.o src/controller.cpp

all:	gui cli server

.PHONY: gui
gui:		
	@echo "Making some " $(GUI);	


.PHONY: cli
cli:	$(SOURCES_CLI) $(OBJECTS_CLI)
	@echo "Making some " $(CLI);
	$(LINK) $(LFLAGS) -o $(CLI) $(OBJECTS_CLI) $(OBJCOMP) $(LIBS)

.PHONY: server
server:	$(SOURCES_CLI) $(OBJECTS_CLI)	
	echo "Making some " . $(SERVER);
	$(LINK) $(LFLAGS) -o $(SERVER) $(OBJECTS_CLI) $(OBJCOMP) $(LIBS)


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
	rm -rf *.o $(ALLBIN) ./docu/html *.log *.tmp


