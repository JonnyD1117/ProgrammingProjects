.PHONY: deps, config, build, clean  test, test_gdb, run, venv run_gdb, site, serve, docs, venv

# Compilation Mode: (release/debug)
CMAKE_MODE ?=debug
CONAN_MODE := $(shell echo $(CMAKE_MODE) | sed 's/./\U&/')

venv:
	@if [ ! -d .venv ]; then \
		echo "Creating virtual environment..."; \
		python3 -m venv .venv; \
		bash -c "source .venv/bin/activate && pip install -r requirements.txt" \
	else \
		echo "Virtual environment already exists."; \
	fi

deps:
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing \
	-c tools.system.package_manager:mode=install -s build_type=$(CONAN_MODE); \

config:
	cmake --preset=$(CMAKE_MODE);

build: config
	cmake --build . --preset=$(CMAKE_MODE); 

run:
	./bin/my_app

run_gdb: 
	gdb ./bin/my_app

test:
	cd ./build && ctest

test_gdb:
	gdb ./bin/unit_tests

clean:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*
	rm -rf .venv/

site:
	firefox ./docs/.site/index.html

docs: venv
	bash -c "source .venv/bin/activate && mkdocs build"

serve:
	bash -c "source .venv/bin/activate && mkdocs serve"