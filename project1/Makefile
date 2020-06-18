all: phase2

phase2:
	g++ -std=c++11 $(filter-out main.cpp, $(wildcard *.cpp)) -o $@

clean:
	rm phase2