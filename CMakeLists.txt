cmake_minimum_required(VERSION 3.16)

# -- vcpkg fallback (if toolchain wasn't passed via -DCMAKE_TOOLCHAIN_FILE) ----
if(WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()

project(Tankz LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- Sources --------------------------------------------------------------------
set(SOURCES
    Tankz.cpp
    Camera.cpp
    GameObject.cpp
    Player.cpp
    Projectile.cpp
    stb_image.cpp
)

add_executable(Tankz ${SOURCES})

# -- Include dirs --------------------------------------------------------------─
target_include_directories(Tankz PRIVATE ${CMAKE_SOURCE_DIR}/Headers)

# MSVC doesn't define M_PI by default — this enables it from <cmath>
if(MSVC)
    target_compile_definitions(Tankz PRIVATE _USE_MATH_DEFINES)
endif()

# -- Find & link dependencies --------------------------------------------------─

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(Tankz PRIVATE OpenGL::GL)

if(WIN32)
    # -- Windows ----------------------------------------------------------------
    # Expects freeglut and GLEW installed via vcpkg:
    #   vcpkg install freeglut glew

    find_package(GLUT REQUIRED)
    find_package(GLEW REQUIRED)

    if(NOT GLUT_FOUND)
        message(FATAL_ERROR "freeglut not found. Run: vcpkg install freeglut")
    endif()
    if(NOT GLEW_FOUND)
        message(FATAL_ERROR "GLEW not found. Run: vcpkg install glew")
    endif()

    # vcpkg freeglut puts headers at <include>/GL/glut.h, but the source
    # includes bare <glut.h>, so we expose both the root and the GL/ subdir.
    get_target_property(_glut_inc GLUT::GLUT INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(Tankz PRIVATE ${_glut_inc} ${_glut_inc}/GL)

    target_link_libraries(Tankz PRIVATE GLUT::GLUT GLEW::GLEW OpenGL::GLU)

elseif(APPLE)
    # -- macOS ------------------------------------------------------------------
    find_library(GLUT_LIBRARY GLUT REQUIRED)
    target_link_libraries(Tankz PRIVATE ${GLUT_LIBRARY} OpenGL::GLU)
    target_compile_options(Tankz PRIVATE -Wno-deprecated)

else()
    # -- Linux ------------------------------------------------------------------
    find_package(GLUT REQUIRED)
    target_link_libraries(Tankz PRIVATE GLUT::GLUT OpenGL::GLU)
endif()

# -- Copy assets next to the executable ----------------------------------------
add_custom_command(TARGET Tankz POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Images $<TARGET_FILE_DIR:Tankz>/Images
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/3DObjects $<TARGET_FILE_DIR:Tankz>/3DObjects
    COMMENT "Copying assets to build directory..."
)

# -- Install rules (used by CPack) --------------------------------------------─
install(TARGETS Tankz RUNTIME DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Images    DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/3DObjects DESTINATION .)
install(FILES     ${CMAKE_SOURCE_DIR}/README.md DESTINATION .)

if(WIN32)
    # Copy runtime DLLs (freeglut, GLEW) next to the executable at install time.
    # GLUT::GLUT is an UNKNOWN imported target so IMPORTED_RUNTIME_ARTIFACTS
    # won't work — glob the DLLs directly from the vcpkg bin directory instead.
    get_filename_component(_vcpkg_bin "${CMAKE_TOOLCHAIN_FILE}" DIRECTORY)
    set(_vcpkg_bin "${_vcpkg_bin}/../../installed/x64-windows/bin")
    file(GLOB _runtime_dlls
        "${_vcpkg_bin}/freeglut.dll"
        "${_vcpkg_bin}/glew32.dll"
    )
    install(FILES ${_runtime_dlls} DESTINATION .)
endif()

# -- CPack ----------------------------------------------------------------------
set(CPACK_PACKAGE_NAME        "Tankz")
set(CPACK_PACKAGE_VERSION     "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "A C++/OpenGL tank game")
set(CPACK_PACKAGE_VENDOR      "Tankz")
set(CPACK_PACKAGE_FILE_NAME   "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "ZIP;DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tankz")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS    "freeglut3, libglu1-mesa")
endif()

include(CPack)
