all: EV

EV: Test.o ProbabilityCalculator.o SimpleCalculator.o AdvancedFastCalculator.o \
		SimpleFastCalculator.o AdvancedCalculator.o Card.o UsedCard.o
	g++ ${CFLAGS} $^ -o $@

%.o: %.cpp
	g++ ${CFLAGS} -std=c++11 $< -c -o $@

clean:
	rm -f *.o EV
