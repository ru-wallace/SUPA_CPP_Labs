CC=g++
FLAGS=-std=c++20 -w
TARGET=./bin/AnalyseData
OBJECTS=./obj/AnalyseData.o ./obj/CustomFunctions.o

# Default command compiles all the files
all: 
	@echo "Compiling All"
	@make ${TARGET}
	@make prelims
	@echo "################################## Done ##################################"

# Main assignment and its dependencies, compiled to object files then linked

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

# Preliminary exercises
prelims:
	@echo "#################### Compiling Preliminary exercises #####################"
	@make HelloWorld
	@make prelim2
	@make prelim3



HelloWorld: ./src/prelims/HelloWorld.cxx
	@mkdir -p ./bin
	@echo "Compiling HelloWorld"
	@rm -f ./bin/HelloWorld
	${CC} ${FLAGS} ./src/prelims/HelloWorld.cxx -o ./bin/HelloWorld

prelim2: ./src/prelims/prelim2.cxx
	@mkdir -p ./bin
	@echo "Compiling prelim2"
	@rm -f ./bin/prelim2
	${CC} ${FLAGS} ./src/prelims/prelim2.cxx -o ./bin/prelim2

prelim3: ./src/prelims/prelim3.cxx
	@echo "Prelim 3"
	@mkdir -p ./bin
	@echo "Compiling prelim3"
	@rm -f ./bin/prelim3
	${CC} ${FLAGS} ./src/prelims/prelim3.cxx -o ./bin/prelim3

# Clean up functions

clean:
	@echo "Cleaning up"
	@rm -rf ./obj

cleantarget:
	@echo "Cleaning up target"
	@rm -f ${TARGET}
