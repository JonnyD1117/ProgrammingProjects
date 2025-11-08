.PHONY: deps, deps_rel, config, build, run, clean  test, autogen


deps:
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Debug

deps_rel:
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Release

config:
	cmake --preset=debug

build: config
	cmake --build . --preset=debug

run:
	./bin/ArgumentParser --test_int 3 --test_double 5.25 --test_string whatever_123 --test_bool --h

test:
	cd ./build && ctest --verbose

autogen: 
	python3 ./src/autogen/instruction_set.py

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*