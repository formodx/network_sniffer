mkdir -p bin/
g++ -c -o bin/ip.o src/ip.cpp
g++ -c -o bin/arp.o src/arp.cpp
g++ -c -o bin/main.o src/main.cpp
g++ -o sniffer.out bin/ip.o bin/arp.o bin/main.o