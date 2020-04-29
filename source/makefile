CC = g++
CFLAGS = -g -Wall -O3
LIBS = -lm -lglut -lGL -lGLU

OBJ = misc.o  obj.o base.o cam.o pin.o moviment.o menu.o
all: $(OBJ)
	${CC} source.cpp ${CFLAGS} 	${OBJ} -o resta_um.run ${LIBS}
misc.o: misc.h misc.cc	
	g++ ${LIBS} -c misc.cc

obj.o: obj.h obj.cc
	g++ ${LIBS} -c obj.cc

base.o: base.h base.cpp
	g++ ${LIBS} -c base.cpp

cam.o: cam.h cam.cpp
	g++ ${LIBS} -c cam.cpp

pin.o: pin.h pin.cpp
	g++  ${LIBS} -c pin.cpp

moviment.o: moviment.h moviment.cpp
	g++ ${LIBS} -c moviment.cpp

menu.o: menu.h menu.cpp
	g++ ${LIBS} -c menu.cpp