add_executable(FlappyBird ../classBird/Bird.h ../Entity/Entity.h ../MainWindow/MainWindow.h ../classPoint/Point.h ../classCar/Car.h ../classPipes/Pipes.h)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.h)
target_sources(FlappyBird PRIVATE ${SOURCE_FILES})
target_link_libraries(FlappyBird sfml-system sfml-window sfml-graphics sfml-audio)
