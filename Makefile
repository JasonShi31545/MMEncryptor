current_dir = $(shell pwd)
default:
	echo "Invalid Make Input"
final: main.cc
	g++                    -std=c++17 -Wshadow -Wall -o "mme.out" "main.cc" -O2 -Wno-unused-result -static -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
	strip mme.out
finald: main.cc
	g++ -std=c++17 -Wshadow -Wall -o "mme.out" "main.cc" -O2 -Wno-unused-result -static -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
	# no stripping
test: test.cc
	g++ test.cc -o test.out -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
windows_final: main.cc
	x86_64-w64-mingw32-g++ -std=c++17 -Wshadow -Wall -o "mme.exe" "main.cc" -O2 -Wno-unused-result -static -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto -I$(current_dir)/cryptopp860/ -L$(current_dir)/cryptopp860/ -lcryptopp
	strip mme.exe
# windows_final: main.cc
# 	x86_64-w64-mingw32-c++ -std=c++17 -Wshadow -Wall -o "main.exe" "main.cc" -O2 -Wno-unused-result -static
sha: sha256.cc
	g++ sha256.cc -o sha256.out -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto
prime: prime.cc
	g++ -static -std=c++17 -Wshadow -Wall prime.cc -o prime.out -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -g -fsanitize=undefined -D_GLIBCXX_DEBUG -pg
rsa: rsa.cc
	g++ -std=c++17 -Wshadow -Wall rsa.cc -o rsa.out -lgmpxx -lgmp -lboost_system -lboost_thread -lboost_random -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -pg
debug_clean:
	rm *.sto && \
	rm *.ekey && \
	rm *.key && \
	rm core
clean:
	rm *.exe
	rm *.out
	rm *.o
