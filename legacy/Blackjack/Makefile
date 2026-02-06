all: Blackjack

Blackjack: Test.o Card.o Dealer.o Deck.o Gambler.o Game.o \
		MacauSimulation.o Player.o ShuffleMachine.o Table.o \
		ContinuousShufflingMachine.o Hand.o Statistics.o StreamLog.o \
		Strategy.o BasicStrategy.o  NoStrategy.o LongTermStats.o \
		EnhancedStrategy.o UsedCard.o ManipulatedCardSequence.o \
		BettingSystem.o FixedBet.o PenetrationShuffler.o FlowCounting.o \
		SydneySimulation.o
	g++ ${CFLAGS} $^ -o $@

%.o: %.cpp
	g++ ${CFLAGS} -std=c++11 $< -c -o $@

clean:
	rm -f *.o Blackjack
