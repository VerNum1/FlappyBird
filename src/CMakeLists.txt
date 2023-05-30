add_executable(FlappyBird)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)
target_sources(FlappyBird PRIVATE ${SOURCE_FILES})
target_link_libraries(FlappyBird sfml-system sfml-window sfml-graphics sfml-audio)
