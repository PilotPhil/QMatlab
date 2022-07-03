cmake_minimum_required(VERSION 3.14)

project(QMatlab LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/install/lib)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

find_package(Matlab REQUIRED COMPONENTS MAT_LIBRARY ENG_LIBRARY MEX_COMPILER)

message(${Matlab_ROOT_DIR})
message(${Matlab_INCLUDE_DIRS})
message(${Matlab_LIBRARIES})
message(${Matlab_MAT_LIBRARY})

SET(Eigen3_Include_Dir D:/Dev/eigen)

include_directories(${CMAKE_CURRENT_LIST_DIR}/source
                    ${Matlab_INCLUDE_DIRS}
                    ${Eigen3_Include_Dir})

file(GLOB_RECURSE PROJECT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/source/*.*)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/source/*.h)

file(COPY ${HEADER_FILES} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/install/include FOLLOW_SYMLINK_CHAIN)


add_executable(QMatlab
  ${PROJECT_SOURCES}
)



target_link_libraries(QMatlab Qt${QT_VERSION_MAJOR}::Core
    ${Matlab_MAT_LIBRARY}
    ${Matlab_MEX_LIBRARY}
    ${Matlab_MX_LIBRARY}
    ${Matlab_ENG_LIBRARY})



if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    add_library(LibQMatlabD
        STATIC
    ${PROJECT_SOURCES})

    target_link_libraries(LibQMatlabD Qt${QT_VERSION_MAJOR}::Core
        ${Matlab_MAT_LIBRARY}
        ${Matlab_MEX_LIBRARY}
        ${Matlab_MX_LIBRARY}
        ${Matlab_ENG_LIBRARY})

elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_library(LibQMatlab
        STATIC
    ${PROJECT_SOURCES})

    target_link_libraries(LibQMatlab Qt${QT_VERSION_MAJOR}::Core
        ${Matlab_MAT_LIBRARY}
        ${Matlab_MEX_LIBRARY}
        ${Matlab_MX_LIBRARY}
        ${Matlab_ENG_LIBRARY})

else()
endif()


