CXX = clang++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP1 -I../Tests-auto -I.
VPATH = ../Tests-auto:.

EXES = test-P1-auto test-fechacadena-consola
OBJETOS = cadena.o fecha.o

all: $(EXES)

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(OBJETOS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-fechacadena-consola: test-fechacadena-consola.o $(OBJETOS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-fechacadena-consola.o $(OBJETOS): fecha.hpp cadena.hpp 

check:
	$(MAKE) -f Make_check.mk $@
	
valgrind:
	valgrind --quiet ./test-P1-auto --logger=minimal
	valgrind --quiet ./test-fechacadena-consola

clean: 
	@$(RM) $(EXES) fecha_cadena_check *.o
