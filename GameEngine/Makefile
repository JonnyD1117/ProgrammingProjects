.PHONY: install_deps, config, build, run, clean_build, clean_bin, clean_conan, clean_all, clean_venv, test, site, serve, docs, venv

venv:
	@if [ ! -d .venv ]; then \
		echo "Creating virtual environment..."; \
		python3 -m venv .venv; \
		bash -c "source .venv/bin/activate && pip install -r requirements.txt" \
	else \
		echo "Virtual environment already exists."; \
	fi

install_deps:
	CONAN_SYSREQUIRES_SUDO=1 conan install . --output-folder=conan --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

config:
	cmake --preset=default

build: config
	cmake --build . --preset=default

run:
	./bin/my_app

test:
	cd ./build && ctest

site:
	firefox ./docs/.site/index.html

docs: venv
	bash -c "source .venv/bin/activate && mkdocs build"

serve:
	bash -c "source .venv/bin/activate && mkdocs serve"

clean_all:
	rm -rf ./bin/*
	rm -rf ./build/*
	rm -rf ./conan/*
	rm -rf .venv/

clean_venv:
	rm -rf .venv/

clean_bin:
	rm -rf ./bin/*

clean_build:
	rm -rf ./build/*

clean_conan:
	rm -rf ./conan/*
