.PHONY: install_deps, config, build, run, clean_build, clean_bin, clean_conan, clean_all,  test, autogen


install_deps:
# 	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Release
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Debug

config:
	cmake --preset=debug

build: config
	cmake --build . --preset=debug

run:
	./bin/emulator

test:
	cd ./build && ctest

autogen: 
	python3 ./src/autogen/instruction_set.py

clean_all:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*

clean_bin:
	rm -rf ./bin/*

clean_build:
	rm -rf ./build/*

clean_conan:
	rm -rf ./conan/*
