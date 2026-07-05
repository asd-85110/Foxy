cmake_minimum_required(VERSION 3.20)
project(Foxy)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
if(WIN32)
    set(CMAKE_RC_COMPILER windres)
    enable_language(RC)
endif()
include_directories(${CMAKE_SOURCE_DIR}/package/include)
link_directories(${CMAKE_SOURCE_DIR}/package/lib)
add_executable(game
    ${CMAKE_SOURCE_DIR}/src/game/main.cpp
    ${CMAKE_SOURCE_DIR}/src/game/sprite.cpp
    ${CMAKE_SOURCE_DIR}/src/game/ev.cpp)
add_executable(modifier
    ${CMAKE_SOURCE_DIR}/src/modifier/main.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/src/modifier/tools.cpp)
target_compile_options(game PRIVATE -Wno-enum-compare)
if(WIN32)
    target_sources(game PRIVATE ${CMAKE_SOURCE_DIR}/src/game/ResC.rc)
    target_sources(modifier PRIVATE ${CMAKE_SOURCE_DIR}/src/modifier/ResC.rc)
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_link_options(game PRIVATE -mwindows)
    target_link_options(modifier PRIVATE -mwindows)
elseif(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_options(game PRIVATE -ggdb -O0)
    target_compile_options(modifier PRIVATE -ggdb -O0)
endif()
target_link_libraries(modifier PRIVATE glfw3dll z png18 iconv intl)
target_link_libraries(game PRIVATE raylib iconv intl)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE})
install(TARGETS game modifier DESTINATION bin)
install(FILES
    ${CMAKE_SOURCE_DIR}/package/lib/glfw3.dll
    ${CMAKE_SOURCE_DIR}/package/lib/libraylib.dll
    ${CMAKE_SOURCE_DIR}/package/lib/libpng18.dll
    ${CMAKE_SOURCE_DIR}/package/lib/libz.dll
    ${CMAKE_SOURCE_DIR}/package/lib/libintl-8.dll
    ${CMAKE_SOURCE_DIR}/package/lib/libiconv-2.dll
DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/docs DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/res DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/locale DESTINATION .)