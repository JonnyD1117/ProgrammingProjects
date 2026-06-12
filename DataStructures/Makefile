.PHONY: deps config build clean test test_gdb

# Compilation Mode: (release/debug)
CMAKE_MODE ?=debug
CONAN_MODE := $(shell echo $(CMAKE_MODE) | sed 's/./\U&/')
CONAN_PROFILE_MODE  = $(shell echo "$(CONAN_MODE)" | tr 'A-Z' 'a-z')

deps:

	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing \
	-c tools.system.package_manager:mode=install -s build_type=$(CONAN_MODE) \
	-pr=./conan/profiles/clang_std23_$(CONAN_PROFILE_MODE);\

config:
	cmake --preset=$(CMAKE_MODE)

build: config
	cmake --build --preset=$(CMAKE_MODE)

test:
	./bin/unit_tests

test_gdb:
	gdb ./bin/unit_tests

clean:
	rm -rf ./bin/* 
	rm -rf ./build/*
	rm -rf ./conan/build
	rm -f ConanPresets.json