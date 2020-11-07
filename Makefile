LD=g++
CXX=g++ -g -c 

EXEC_SRC=\
	testColorImage2D.cpp
	save-all-channel.cpp
	testGrayLevelImage2D.cpp
	cathodique.cpp
	histogrammeColor.cpp
	histogrammeGrey.cpp


MODULE_SRC=\

MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

testColorImage2D: testColorImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}
