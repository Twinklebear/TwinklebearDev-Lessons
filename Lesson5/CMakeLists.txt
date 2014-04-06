project(Lesson5)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(Lesson5 src/main.cpp)
target_link_libraries(Lesson5 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
install(TARGETS Lesson5 RUNTIME DESTINATION ${BIN_DIR})

