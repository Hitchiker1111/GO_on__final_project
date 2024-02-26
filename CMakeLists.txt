cmake_minimum_required(VERSION 3.10)
project(GO_on)

include_directories("D:/envs/SDL2-2.26.0-allinone/x86_64-w64-mingw32/include")
link_directories("D:/envs/SDL2-2.26.0-allinone/x86_64-w64-mingw32/lib")

add_executable(GO_on
    src/utils/display.c
    src/utils/input.c
    src/utils/audio.c
    src/utils/linkedlist.c
    src/menu.c
    src/game.c
    src/GO_on.c
)
target_link_libraries(GO_on PRIVATE
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
    SDL2_mixer
)

