
cmake_minimum_required(VERSION 3.20)
cmake_policy(VERSION 3.15)

# ---------------Project name---------------------------------------------------------------
project(Controller_projects LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(RELEASE "Optimize the builds with the release specs" OFF)
option(DEBUG "Make a debug build" ON)
option(BUILD_DOCS "Create code documentation" OFF)
option(GIT_SUBMODULE "Check submodules during build" ON)
option(ENABLE_QT6 "Use Qt6 instead of Qt5" OFF)

# ----------------------------------------------------------------------------------------

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Printer/src")
set(SRC_DIR "${SOURCE_DIR}/Printer")
set(3RD_PARTY_DIR "${PROJECT_SOURCE_DIR}/Printer/vendor")
set(DATA_DIR "${PROJECT_SOURCE_DIR}/Controller/data")


set(DEFAULT_BUILD_TYPE "Debug")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Turn on the verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set build type
IF(RELEASE AND DEBUG)
    MESSAGE(FATAL_ERROR "You can only make a release OR and debug build.")
ENDIF()

IF(RELEASE)
    SET(CMAKE_BUILD_TYPE Release)
ELSEIF(DEBUG)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

IF(RELEASE AND ENABLE_COVERAGE)
    MESSAGE(FATAL_ERROR "Building code coverage needs debug build to be turned on")
ENDIF()

set(CMAKE_CXX_STANDARD 20) #TODO make these compile options target specific 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "PROJECT_NAME               :" ${PROJECT_NAME})
message(STATUS "CMAKE_HOST_SYSTEM          :" ${CMAKE_HOST_SYSTEM})
message(STATUS "ARCHITECTURE               :" ${ARCH})
message(STATUS "CMAKE_BUILD_TYPE           :" ${CMAKE_BUILD_TYPE})
message(STATUS "CMAKE_CXX_COMPILER         :" ${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_CXX_COMPILER_ID      :" ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_CXX_COMPILER_VERSION :" ${CMAKE_CXX_COMPILER_VERSION})
message(STATUS "CMAKE_CXX_FLAGS            :" ${CMAKE_CXX_FLAGS})
message(STATUS "CMAKE_MODULE_PATH:         :" ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_CURRENT_SOURCE_DIR   :" ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "CMAKE_CURRENT_BINARY_DIR   :" ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "CMAKE_CURRENT_LIST_DIR     :" ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "CMAKE_EXE_LINKER_FLAGS     :" ${CMAKE_EXE_LINKER_FLAGS})
message(STATUS "CMAKE_INSTALL_PREFIX       :" ${CMAKE_INSTALL_PREFIX})
message(STATUS "SOURCE_DIRECTORY           :" ${SOURCE_DIR})
message(STATUS "3RD_PARTY_DIRECTORTY       :" ${3RD_PARTY_DIR})
message(STATUS "DATA_DIRECTORTY            :" ${DATA_DIR})
message(STATUS "CHECK GIT SUBMODULES       :" ${GIT_SUBMODULE})

# # #------------------Looking for git and updating submodules-------------------
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Git version
    execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE PACKAGE_GIT_VERSION
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    # Update submodules as needed
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(WARNING "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# ------------------------------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_subdirectory(${3RD_PARTY_DIR}/spdlog)

option(BUILD_EXAMPLES "Build example programs" OFF)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_SHARED_LIBS "Build as shared library" OFF)

add_subdirectory(${3RD_PARTY_DIR}/ruckig)

add_subdirectory("Printer/src/Printer")
add_subdirectory("Printer-Runtime/")