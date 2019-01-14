all:
	g++ -std=c++11  -o FractionProgram.out FractionProgram.cpp Fraction.cpp
clean:
	rm FractionProgram.out
