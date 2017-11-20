cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/VladislavMashkov/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "feabd55227870adfe44776d09e09789860e73e35"
)

project(client)
hunter_add_package(Catch)
find_package(Catch CONFIG REQUIRED)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)


add_library(client STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/client.cpp)

target_include_directories(client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCE})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} client Catch::Catch PRIVATE CURL::libcurl OpenSSL::SSL OpenSSL::Crypto)
    install(TARGETS 
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCE})
endif()

install(TARGETS client
    EXPORT client-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT client-config DESTINATION cmake)

if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES} Catch::Catch OpenSSL::SSL OpenSSL::Crypto)
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()
