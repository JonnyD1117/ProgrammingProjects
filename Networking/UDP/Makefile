.PHONY: config build clean 

config:
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug

build:
	cmake --build ./build 
	
clean: 
	rm -rf ./build/*
	rm -rf ./bin/*