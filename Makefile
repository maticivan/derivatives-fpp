all:
	g++ -I /usr/local/include -c higherOrderEnvDerivatives.cpp -std=c++17 -lstdc++fs -pthread -fmax-errors=1
	g++ -o hoed higherOrderEnvDerivatives.o -std=c++17 -lcrypto -lstdc++fs -pthread

forMac:
	g++ -I /usr/local/include -c higherOrderEnvDerivatives.cpp -std=c++23 -lstdc++fs -pthread -fmax-errors=1
	g++ -o mhoed higherOrderEnvDerivatives.o -std=c++23 -lstdc++fs -pthread
