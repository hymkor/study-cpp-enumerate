ifeq ($(OS),Windows_NT)
    EXE=.exe
    DEL=del
    SHELL=CMD.EXE
else
    EXE=
    DEL=rm
endif

all: main$(EXE) cmain$(EXE)

clean:
	$(DEL) *.o main$(EXE) cmain$(EXE) *~

main$(EXE): main.o sub.o
	g++ -o $@ $^

cmain$(EXE): cmain.o sub.o
	g++ -o $@ $^

cmain.o: cmain.cpp cenumerate.h
main.o: main.cpp enumerate.h

docs:
	example-into-readme
