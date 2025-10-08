.PHONY: config build test clean debug release

# docs:
# 	doxygen ./docs/Doxyfile

debug:
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug

build: debug
	cmake --build ./build 

test: build
# ctest --test-dir ./build
	./build/src/http_lib_exe
	
clean:
	rm -rf ./build/*
	rm -rf ./bin/*