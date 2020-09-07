cmake_minimum_required(VERSION 3.16)

# Define the library
add_library (libflog SHARED
    src/flog.cpp
    src/semaphore.cpp
    # Headers
    include/flog.hpp
    include/flog-export.hpp
    include/semaphore.hpp
)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Compile Flags
if (CMAKE_CXX_COMPILER MATCHES ".*MSVC")
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
elseif(CMAKE_CXX_COMPILER MATCHES ".*gcc" OR CMAKE_CXX_COMPILER MATCHES ".*clang")
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Include directories
include_directories("include")

# Add 'd' suffix to debug builds
set_property(TARGET libflog PROPERTY DEBUG_POSTFIX d)

# Set version
set_target_properties(libflog PROPERTIES VERSION 0.2.0)
set_target_properties(libflog PROPERTIES SOVERSION 0)

# pkg-config
configure_file(libflog.pc.in libflog.pc @ONLY)

# Define symbol exporter
target_compile_definitions(libflog PRIVATE -DLIBFLOG_EXPORT)

# Install and export
include(GNUInstallDirs)
target_include_directories(libflog PUBLIC  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>  
    $<INSTALL_INTERFACE:include/>
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/flog)

install(TARGETS libflog
    EXPORT libflogConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(TARGETS libflog FILE libflogConfig.cmake)

install(EXPORT libflogConfig
    FILE libflogConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libflog.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

