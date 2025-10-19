.PHONY: install_deps, config, build, clean_build, clean_bin, clean_conan, clean,  test, test_ci


install_deps:
# 	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Release
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -s build_type=Debug

config:
	cmake --preset=debug

build: config
	cmake --build . --preset=debug

test:
	./bin/unit_tests

test_ci:
	cd ./build && ctest --test-arguments="--gtest_color=yes"

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*
	rm ./build/.ninja_log
	rm ./build/.ninja_deps

clean_bin:
	rm -rf ./bin/*

clean_build:
	rm -rf ./build/*

clean_conan:
	rm -rf ./conan/*
