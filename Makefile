all:demo.cpp consistent_hash.cpp
	g++ -o demo demo.cpp consistent_hash.cpp -lcrypto
