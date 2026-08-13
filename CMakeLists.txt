cmake_minimum_required(VERSION 3.26)
project(hollow)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)
set(SFML_DIR "C://SFML//SFML-2.6.1//lib//cmake//SFML")

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
add_executable(hollow main.cpp
        knight.h
        knight.cpp
        enemy.h
        enemy.cpp
        largerEnemy.h
        largerEnemy.cpp
        theLargestEnemy.h
        theLargestEnemy.cpp
        Grimm.h
        fireball.h
        fireball.cpp
)
target_link_libraries(hollow sfml-system sfml-window sfml-graphics sfml-network sfml-audio)