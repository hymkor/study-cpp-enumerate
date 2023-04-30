ifeq ($(OS),Windows_NT)
    EXE=.exe
    DEL=del
    SHELL=CMD.EXE
else
    EXE=
    DEL=rm
endif

all: main$(EXE) cmain$(EXE) main2$(EXE)

clean:
	$(DEL) *.o main$(EXE) cmain$(EXE) *~

main$(EXE): main.o sub.o
	g++ -o $@ $^

cmain$(EXE): cmain.o sub.o
	g++ -o $@ $^

main2$(EXE): main2.o sub2.o
	g++ -o $@ $^

main.o: main.cpp enumerate.h
sub.o : sub.cpp enumerate.h
cmain.o: cmain.cpp cenumerate.h
main2.o: main2.cpp enumerate2.h
sub2.o : sub2.cpp enumerate2.h

docs:
	example-into-readme
