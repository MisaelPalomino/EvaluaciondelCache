CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall

SRCS = utils.cpp \
       bucles_pacheco.cpp \
       matriz_clasica.cpp \
       matriz_bloques.cpp \
       main.cpp

all: analisis

analisis: $(SRCS)
	$(CXX) $(CXXFLAGS) -o analisis $(SRCS)

run: analisis
	./analisis todo

clean:
	rm -f analisis cachegrind.out.*

.PHONY: all run clean