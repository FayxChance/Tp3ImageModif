LD=g++
CXX=g++ -g -c 

EXEC_SRC=testColorImage2D.cpp	save-all-channel.cpp	testGrayLevelImage2D.cpp	cathodique.cpp	histogrammeColor.cpp	histogrammeGrey.cpp	invert-blue-red.cpp egaliseur-couleur.cpp

MODULE_SRC=\

MODULE_OBJ=${MODULE_SRC:.cpp=.o}
EXEC_OBJ=${EXEC_SRC:.cpp=.o}

EXEC_PRG=${EXEC_SRC:.cpp=}

all: ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}

testColorImage2D: testColorImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

save-all-channel: save-all-channel.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

testGrayLevelImage2D: testGrayLevelImage2D.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

cathodique: cathodique.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

histogrammeColor: histogrammeColor.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

histogrammeGrey: histogrammeGrey.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

invert-blue-red: invert-blue-red.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

egaliseur-couleur: egaliseur-couleur.o ${MODULE_OBJ}
	${LD} ${MODULE_OBJ} $< -o $@

.cpp.o: %.cpp %.hpp
	${CXX} $<

clean:
	rm -f ${EXEC_PRG} ${MODULE_OBJ} ${EXEC_OBJ}
