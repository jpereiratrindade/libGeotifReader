cmake_minimum_required(VERSION 3.0)
project(libGeotifReader VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# Find GDAL library
find_package(GDAL REQUIRED)
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)
endif()

# Add the include directories
include_directories(${GDAL_INCLUDE_DIRS})

# Create the library target (as a static library)
file(GLOB SOURCES "*.cpp")
add_library(GeotifReader STATIC ${SOURCES})

# Link the GDAL library
target_link_libraries(GeotifReader ${GDAL_LIBRARIES})

# Installation rules
install(TARGETS GeotifReader
        LIBRARY DESTINATION /usr/lib64
        ARCHIVE DESTINATION /usr/lib64)
install(FILES GeotifReader.h DESTINATION /usr/include)
install(FILES README.md DESTINATION /usr/share/libGeotifReader)

