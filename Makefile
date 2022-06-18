current_dir = $(shell pwd)
default:
	echo "Invalid Make Input"
final: main.cc
	g++ -std=c++17 -Wshadow -Wall -o "mme.out" "main.cc" -O2 -Wno-unused-result -static -lgmpxx -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
	strip mme.out
debug: main.cc
	g++ -std=c++17 -Wshadow -Wall -o "mme.out" "main.cc" -O2 -Wno-unused-result -static -lgmpxx -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
	# no stripping binary
debug_clean:
	rm *.sto && \
	rm *.ekey && \
	rm *.key && \
	rm core
clean:
	rm *.exe
	rm *.out
	rm *.o
