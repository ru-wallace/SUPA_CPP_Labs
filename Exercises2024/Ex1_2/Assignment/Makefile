CC=g++
FLAGS=-std=c++20 -w
TARGET=./bin/AnalyseData
OBJECTS=./obj/AnalyseData.o ./obj/CustomFunctions.o

${TARGET}: ${OBJECTS}
	@mkdir -p ./bin
	@echo "Compiling AnalyseData"
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}
	@make clean

./obj/AnalyseData.o: ./src/AnalyseData.cxx
	@mkdir -p ./obj
	@echo "Compiling AnalyseData.o"
	${CC} ${FLAGS} -c ./src/AnalyseData.cxx -o ./obj/AnalyseData.o

./obj/CustomFunctions.o: ./src/CustomFunctions.cxx ./src/CustomFunctions.h
	@mkdir -p ./obj
	@echo "Compiling CustomFunctions.o"
	${CC} ${FLAGS} -c ./src/CustomFunctions.cxx -o ./obj/CustomFunctions.o

clean:
	@echo "Cleaning up"
	@rm -rf ./obj

cleantarget:
	@echo "Cleaning up target"
	@rm -f ${TARGET}
