# To build with any version other than 1.0.0, do this:
# make all VERSION=2.1.0 

.PHONY: all configure build package clean rebuild

# -- Targets -------------------------------------------------------------------
all: configure build package

configure:
	cmake --fresh -S . -B build -DCPACK_PACKAGE_VERSION=$(VERSION)

build:
	cmake --build build --config Release

rebuild: clean all

package: build
	cd build && cpack .

clean:
	rm -rf build
