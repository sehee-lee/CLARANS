GCC=g++

debug: clarans.o record.o stringtokenizer.o
	$(GCC) -ggdb -o clarans clarans.o record.o stringtokenizer.o
clarans.o : clarans.cpp clarans.h record.h
	$(GCC) -ggdb -c clarans.cpp
record.o : record.cpp record.h
	$(GCC) -ggdb -c record.cpp
stringtokenizer.o : stringtokenizer.cpp stringtokenizer.h
	$(GCC) -ggdb -c stringtokenizer.cpp
