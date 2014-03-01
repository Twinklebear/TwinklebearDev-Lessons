project(Lesson0)
add_executable(Lesson0 src/main.cpp)
target_link_libraries(Lesson0 ${SDL2_LIBRARY})
install(TARGETS Lesson0 RUNTIME DESTINATION ${BIN_DIR})

