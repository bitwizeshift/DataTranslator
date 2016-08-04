# flags
CPPFLAGS = -Wall -Wextra -pedantic -Weffc++ -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wfloat-equal

all: data_translator

# clean up
clean:
	rm -fr main.o DataTranslatorTests.o DummyTranslator.o data_translator

#-----------------------------------------------------------------------------
# unit tests
#-----------------------------------------------------------------------------

# build unit tests
main.o: test/main.cpp
	$(CXX) -std=c++11 $(CPPFLAGS) -I include -c test/main.cpp

DataTranslatorTests.o: test/DataTranslatorTests.cpp
	$(CXX) -std=c++11 $(CPPFLAGS) -I include -c test/DataTranslatorTests.cpp

DummyTranslator.o: test/DummyTranslator.cpp
	$(CXX) -std=c++11 $(CPPFLAGS) -I include -c test/DummyTranslator.cpp
	
data_translator: main.o DataTranslatorTests.o DummyTranslator.o test/catch.hpp
	$(CXX) -std=c++11 $(CPPFLAGS) -I include main.o DataTranslatorTests.o DummyTranslator.o -o data_translator