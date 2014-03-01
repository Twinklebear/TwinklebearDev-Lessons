project(Lesson3)
add_executable(Lesson3 src/main.cpp)
target_link_libraries(Lesson3 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
install(TARGETS Lesson3 RUNTIME DESTINATION ${BIN_DIR})

