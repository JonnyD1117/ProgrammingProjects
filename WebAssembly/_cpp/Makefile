.PHONY: deps, config, build, clean  test, test_gdb, run

SHELL := /bin/bash

# Compilation Mode: (release/debug)
CMAKE_MODE ?=debug
CONAN_MODE := $(shell echo $(CMAKE_MODE) | sed 's/./\U&/')

deps:
	CONAN_SYSREQUIRES_SUDO=1 conan install . \
								--profile=./profiles/emscripten_wasm \
								--output-folder=conan \
								--build=missing \
								-c tools.system.package_manager:mode=install \
								-s build_type=$(CONAN_MODE) \
								-g CMakeToolchain	

config:
	source ~/repos/emsdk/emsdk_env.sh \
	&& emcmake cmake --preset=debug

build: config
	cmake --build . --preset=$(CMAKE_MODE);

run: 
	source ~/repos/emsdk/emsdk_env.sh \
	&&  emrun --port 8080 bin/main.html

test:
	cd ./build && ctest

test_gdb:
	gdb ./bin/unit_tests

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*