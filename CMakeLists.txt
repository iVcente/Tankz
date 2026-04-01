cmake_minimum_required(VERSION 3.16)
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
    #   vcpkg install freeglut:x64-windows glew:x64-windows

    find_path(FREEGLUT_INCLUDE_DIR GL/glut.h)
    find_path(GLEW_INCLUDE_DIR GL/glew.h)

    # Explicitly search only the release lib directory so MSVC never tries
    # to link freeglutd.lib (which vcpkg doesn't ship by default).
    find_library(FREEGLUT_LIBRARY
        NAMES freeglut
        NO_DEFAULT_PATH
        PATHS ${FREEGLUT_INCLUDE_DIR}/../lib
              C:/vcpkg/installed/x64-windows/lib)

    find_library(GLEW_LIBRARY
        NAMES glew32
        NO_DEFAULT_PATH
        PATHS ${GLEW_INCLUDE_DIR}/../lib
              C:/vcpkg/installed/x64-windows/lib)

    if(NOT FREEGLUT_INCLUDE_DIR OR NOT FREEGLUT_LIBRARY)
        message(FATAL_ERROR
            "freeglut not found. Run: vcpkg install freeglut:x64-windows")
    endif()
    if(NOT GLEW_INCLUDE_DIR OR NOT GLEW_LIBRARY)
        message(FATAL_ERROR
            "GLEW not found. Run: vcpkg install glew:x64-windows")
    endif()

    # vcpkg freeglut puts headers at <include>/GL/glut.h, but the source
    # includes bare <glut.h>, so we expose both the root and the GL/ subdir.
    target_include_directories(Tankz PRIVATE
        ${FREEGLUT_INCLUDE_DIR}
        ${FREEGLUT_INCLUDE_DIR}/GL
        ${GLEW_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}/GL
    )
    target_link_libraries(Tankz PRIVATE ${FREEGLUT_LIBRARY} ${GLEW_LIBRARY} OpenGL::GLU)

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
    get_filename_component(_freeglut_dir "${FREEGLUT_LIBRARY}" DIRECTORY)
    file(GLOB _freeglut_dlls "${_freeglut_dir}/../bin/*.dll" "${_freeglut_dir}/*.dll")
    get_filename_component(_glew_dir "${GLEW_LIBRARY}" DIRECTORY)
    file(GLOB _glew_dlls    "${_glew_dir}/../bin/*.dll"    "${_glew_dir}/*.dll")
    install(FILES ${_freeglut_dlls} ${_glew_dlls} DESTINATION .)
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
