aes: aes_test.o aes_tools.o aes.o aes_tools.h aes.h
	g++ aes_test.o aes_tools.o aes.o -o aes

aes_test.o: aes_test.cpp aes_tools.h aes.h
	g++ -c aes_test.cpp

aes_tools.o: aes_tools.cpp aes_tools.h aes.h
	g++ -c aes_tools.cpp

aes.o: aes.cpp aes.h
	g++ -c aes.cpp

clean:
	rm *.o