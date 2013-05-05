cmake_minimum_required(VERSION 2.6)

set(PROGRAMS Controller.cpp Game.cpp Logic.cpp Level.cpp Main.cpp Player.cpp Tile.cpp Timer.cpp View.cpp)

add_executable(Demo ${PROGRAMS})

target_link_libraries(Demo optimized ${GEA_Demo_SOURCE_DIR}/SDL-1.2.15/lib/x86/SDL.lib ${GEA_Demo_SOURCE_DIR}/SDL-1.2.15/lib/x86/SDL_image.lib ${GEA_Demo_SOURCE_DIR}/SDL-1.2.15/lib/x86/SDLmain.lib ${GEA_Demo_SOURCE_DIR}/SaveSystem/lib/SaveSystem.lib ${GEA_Demo_SOURCE_DIR}/SDL-1.2.15/lib/x86/SDL_ttf.lib)

include_directories(${GEA_Demo_SOURCE_DIR}/SDL-1.2.15/include ${GEA_Demo_SOURCE_DIR}/rapidxml-1.13 ${GEA_Demo_SOURCE_DIR}/SaveSystem/include)