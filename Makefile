CXXFLAGS := -Ofast -s
CXXFLAGS += -Wall -Wextra -Wpedantic -Werror
LINK = -lpqxx -lpq
INCLUDES = -L/usr/local/lib

all: bin test

bin:
	g++ -std=c++17 $(CXXFLAGS) $(INCLUDES) *.cpp components/*.cpp $(LINK) -o bin/program

clean:
	rm bin/program

test: bin
	./bin/program ./example_config.xml

push:
	git push git@github.com:LollyBomb-hub/project_oop.git

.PHONY: bin
