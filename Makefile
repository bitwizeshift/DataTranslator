all: data_translator

# clean up
clean:
	rm -fr test/main.o src/DataTranslatorTests.o data_translator


##########################################################################
# unit tests
##########################################################################

# additional flags
FLAGS = -Wall -Wextra -pedantic -Weffc++ -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wfloat-equal

# build unit tests (TODO: Does this want its own makefile?)
data_translator: test/main.cpp test/DataTranslatorTests.cpp test/DummyTranslator.cpp test/catch.hpp
	$(CXX) -std=c++11 $(CXXFLAGS) $(FLAGS) $(CPPFLAGS) -I include $< $(LDFLAGS) -o $@
