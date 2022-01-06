CXXFLAGS := -Ofast -s
CXXFLAGS += -Wall -Wextra -Wpedantic -Werror -Wno-unknown-pragmas
LINK = -lpqxx -lpq ./external/OpenXLSX/output/libOpenXLSX.a
INCLUDES = -L/usr/local/lib -L./external/OpenXLSX/output -I./external/OpenXLSX/OpenXLSX -I./external/OpenXLSX/OpenXLSX/headers -I./external/rapidxml

all: bin test

bin:
	g++ -std=c++17 $(CXXFLAGS) $(INCLUDES) *.cpp components/*.cpp $(LINK) -o bin/program

clean:
	rm bin/program

test: bin
	./bin/program ./tests/example_config.xml ./tests/data.xlsx

push:
	git push git@github.com:LollyBomb-hub/project_oop.git

.PHONY: bin
