.PHONY: all configure build package clean rebuild

# -- Windows | vcpkg toolchain detection -------------------------------------------------
ifeq ($(OS),Windows_NT)
    VCPKG_ROOT ?= C:/vcpkg
    TOOLCHAIN  := -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake
else
    TOOLCHAIN  :=
endif

# -- Targets -------------------------------------------------------------------
all: configure build package

configure:
	cmake --fresh -S . -B build $(TOOLCHAIN)

build: configure
	cmake --build build --config Release

rebuild: clean all

package: build
	cd build && cpack .

clean:
	rm -rf build
