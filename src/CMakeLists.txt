project(ws-server LANGUAGES CXX C)

include_directories(${3RD_PARTY_INCLUDE_DIRS})

file(GLOB_RECURSE _SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${3RD_PARTY_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME}/bin)
