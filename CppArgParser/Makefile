.PHONY: deps, config, build, run, clean  test, autogen


deps:
# 	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Release
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Debug

config:
	cmake --preset=debug

build: config
	cmake --build . --preset=debug

run:
	./bin/atari800

test:
	cd ./build && ctest

autogen: 
	python3 ./src/autogen/instruction_set.py

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*