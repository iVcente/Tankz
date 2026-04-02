.PHONY: all configure build package clean rebuild

# -- Targets -------------------------------------------------------------------
all: configure build package

configure:
	cmake --fresh -S . -B build

build: configure
	cmake --build build --config Release

rebuild: clean all

package: build
	cd build && cpack .

clean:
	rm -rf build
