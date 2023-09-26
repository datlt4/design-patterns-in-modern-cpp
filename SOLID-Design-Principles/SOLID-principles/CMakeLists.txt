cmake_minimum_required(VERSION 3.10.2)

project(SOLID-principles LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

# Boost
find_package(Boost REQUIRED filesystem program_options regex timer chrono)
set(INC ${INC} ${Boost_INCLUDE_DIR})
set(LIB ${LIB} ${Boost_LIBRARIES})
set(LIB ${LIB} -lboost_system -lboost_thread -lboost_filesystem -lpthread)

message(STATUS "Source directories:  ${SRC}")
message(STATUS "Include directories: ${INC}")
message(STATUS "Library directories: ${LIB}")

# Add sources List of target names
set(TARGET_NAMES
  "Creational.Creational.SRP"
  "Creational.Creational.OCP"
  "Creational.Creational.LSP"
  "Creational.Creational.ISP"
)

# Loop through the target names and add sources for each
foreach(APP ${TARGET_NAMES})
  add_executable(${APP} ${APP}.cpp)
  target_include_directories(${APP} PRIVATE ${INC})
  target_link_libraries(${APP} PRIVATE ${LIB})
endforeach()
