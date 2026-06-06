.PHONY: deps config build clean run run_valgrind run_gdb test test_gdb valgrind #clang_analyze

# Compilation Mode: (release/debug)
CMAKE_MODE ?=debug
CONAN_MODE := $(shell echo $(CMAKE_MODE) | sed 's/./\U&/')

deps:
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing \
	-c tools.system.package_manager:mode=install -s build_type=$(CONAN_MODE);

config:
	cmake --preset=$(CMAKE_MODE)

build: config
	cmake --build ./build --preset=$(CMAKE_MODE) 

run: 
	./bin/main

run_gdb:
	gdb ./bin/main

valgrind: clean deps
	cmake --preset=debug-valgrind
	cmake --build . --preset=debug-valgrind
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes --log-file=valgrind.log ./bin/main

# clang_analyze:
# 	CodeChecker analyze ./build/compile_commands.json -o results
# 	CodeChecker server --workspace Default --port 8080 --host 0.0.0.0
# 	CodeChecker store results/run1 -n Default --url http://localhost:8080/Default


test:
	ctest --preset=normal-tests

test_valgrind: valgrind
# 	cd build && ctest -T memcheck
	valgrind  --leak-check=full --track-origins=yes --show-reachable=yes --log-file=test_valgrind.log ./bin/unit_tests

test_gdb:
	gdb ./bin/unit_tests

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*