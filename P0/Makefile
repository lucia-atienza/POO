CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP0 -I../Tests-auto -I.
VPATH = ../Tests-auto:.

EXES = test-P0-auto test-fechacadena-consola
OBJETOS = cadena.o fecha.o

all: $(EXES)

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(OBJETOS)
	$(CXX) $(CXXFLAGS)  $^ -o $@

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

test-P0-consola: test-P0-consola.o $(OBJETOS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-fechacadena-consola : test-fechacadena-consola.o fecha.o cadena.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

test-fechacadena-consola.o fecha.o cadena.o : fecha.hpp cadena.hpp 

check:
	$(MAKE) -f Make_check.mk $@
	
valgrind:
	valgrind --quiet ./test-P0-auto --logger=minimal
	valgrind --quiet ./test-fechacadena-consola

clean: 
	@$(RM) $(EXES) test-fechacadena-consola fecha_cadena_check *.o
