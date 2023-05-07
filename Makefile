ifeq ($(OS),Windows_NT)
    EXE=.exe
    DEL=del
    SHELL=CMD.EXE
else
    EXE=
    DEL=rm
endif

all: main$(EXE) cmain$(EXE) main2$(EXE) main0_$(EXE) main0$(EXE)

clean:
	$(DEL) *.o main$(EXE) cmain$(EXE) *~ *.exe

main$(EXE): main.o sub.o
	g++ -o $@ $^

cmain$(EXE): cmain.o sub.o
	g++ -o $@ $^

main2$(EXE): main2.o sub2.o
	g++ -o $@ $^

main0$(EXE): main0.o sub0.o
	g++ -o $@ $^

main0_$(EXE): main0_.o sub0_.o
	g++ -o $@ $^

main.o: main.cpp enumerate.h
sub.o : sub.cpp enumerate.h
cmain.o: cmain.cpp cenumerate.h

main2.o: main2.cpp enumerate2.h
sub2.o : sub2.cpp enumerate2.h

main0.o : main0.cpp
sub0.o : sub0.cpp

main0_.o : main0_.cpp
sub0_.o : sub0_.cpp

docs:
	example-into-readme
