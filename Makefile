MAKEFLAGS += -s

all:
	make board.o
	make consts.o
	make engine.o
	make eval.o
	make eval_params.o
	make globals.o
	make main.o
	make tbprobe.o
	make tt.o
	make uci.o
	make utils.o
	g++ -std=c++11 -O3 board.o consts.o engine.o eval.o eval_params.o globals.o main.o tbprobe.o tt.o uci.o utils.o -o main.out
	make run

run:
	./main.out

run_test:
	./tests.out

run_tune:
	./tuner.out

test: tests.cpp
	make board.o
	make consts.o
	make eval_params.o
	make globals.o
	make tt.o
	make utils.o
	g++ -std=c++11 -O3 -w -c tests.cpp -o tests.o
	g++ -std=c++11 -O3 board.o consts.o eval_params.o globals.o tests.o tt.o utils.o -o tests.out

tune:
	make board.o
	make consts.o
	make engine.o
	make eval.o
	make eval_params.o
	make globals.o
	make tt.o
	make tuning.o
	make uci.o
	make utils.o
	g++ -std=c++11 -O3 board.o consts.o engine.o eval.o eval_params.o globals.o tt.o tuning.o utils.o -o tuner.out

clean:
	rm *.o ||:
	rm *.out ||:

board.o: board.cpp board.h
	g++ -std=c++11 -O3 -w -c board.cpp -o board.o

consts.o: consts.cpp consts.h
	g++ -std=c++11 -O3 -w -c consts.cpp -o consts.o

engine.o: engine.cpp engine.h
	g++ -std=c++11 -O3 -w -c engine.cpp -o engine.o

eval.o: eval.cpp eval.h
	g++ -std=c++11 -O3 -w -c eval.cpp -o eval.o

eval_params.o: eval_params.cpp eval_params.h
	g++ -std=c++11 -O3 -w -c eval_params.cpp -o eval_params.o

globals.o: globals.cpp globals.h
	g++ -std=c++11 -O3 -w -c globals.cpp -o globals.o

main.o: main.cpp *.h
	g++ -std=c++11 -O3 -w -c main.cpp -o main.o

tbprobe.o: syzygy/tbprobe.c
	g++ -std=c++11 -O3 -w -c syzygy/tbprobe.c -o tbprobe.o

tt.o: tt.cpp tt.h
	g++ -std=c++11 -O3 -w -c tt.cpp -o tt.o

tuning.o: tuning.cpp tuning.h
	g++ -std=c++11 -O3 -w -c tuning.cpp -o tuning.o

uci.o: uci.cpp uci.h
	g++ -std=c++11 -O3 -w -c uci.cpp -o uci.o

utils.o: utils.cpp utils.h
	g++ -std=c++11 -O3 -w -c utils.cpp -o utils.o
