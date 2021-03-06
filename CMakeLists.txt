cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(PostProcessingModules
  VERSION 0.0.1
  DESCRIPTION "PostProcessingModules"
  LANGUAGES C CXX)

set(TARGET_NAME "PostProcessingModules")
set(DEFAULT_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON} -O1 " )

set(CMAKE_AUTOMOC ON)

cmake_policy(SET CMP0054 NEW)
if (UNIX)
	
endif (UNIX)

if (WIN32)
	set (CMAKE_PREFIX_PATH "E:\\repo\\opencvBuild")
	list(APPEND CMAKE_PREFIX_PATH "E:\\Qt\\5.12.8\\msvc2017_64")
	list(APPEND CMAKE_PREFIX_PATH "E:\\repo\\ConfigReader\\build")
endif (WIN32)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(ConfigReader REQUIRED)
find_package(Threads REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV  REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified")
    set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

  file(GLOB_RECURSE COMPARE_SRC src/Compare/*.cc src/Compare/*.c)
  file(GLOB_RECURSE COMPARE_HEADERS src/Compare/*.h src/Compare/*.hpp)

  file(GLOB_RECURSE TRACKER_SRC src/Tracker/*.cc src/Tracker/*.c)
  file(GLOB_RECURSE TRACKER_HEADERS src/Tracker/*.h src/Tracker/*.hpp)

  file(GLOB_RECURSE FITNESS_SRC src/Fitness/*.cc src/Fitness/*.c)
  file(GLOB_RECURSE FITNESS_HEADERS src/Fitness/*.h src/Fitness/*.hpp)

  file(GLOB_RECURSE ENCODER_SRC src/Encoder/*.cc src/Encoder/*.c)
  file(GLOB_RECURSE ENCODER_HEADERS src/Encoder/*.h src/Encoder/*.hpp)

set(SRC
   src/postprocessing.cc
)

set(HEADERS
  include/postprocessing.h
)

add_library(${PROJECT_NAME} STATIC
    ${SRC} ${HEADERS}
    ${COMPARE_SRC} ${COMPARE_HEADERS}
    ${TRACKER_SRC} ${TRACKER_HEADERS}
    ${FITNESS_SRC} ${FITNESS_HEADERS}
    ${ENCODER_SRC} ${ENCODER_HEADERS}
)

qt5_use_modules(${PROJECT_NAME} Widgets)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


if (UNIX)
	target_link_libraries(${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS} Threads::Threads)
endif (UNIX)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS} Threads::Threads ConfigReader)
endif (WIN32)


install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)