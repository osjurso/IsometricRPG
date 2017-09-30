cmake_minimum_required(VERSION 3.8)
project(isoRPG)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        include/gameEngine/resource_holder.h include/gameEngine/resource_holder.inl
        src/gamEngine/state_stack.cpp include/gameEngine/state_stack.h
        include/states/state_base.h src/states/state_base.cpp
        include/gameEngine/state_identifiers.h
        src/application.cpp include/application.h
        include/gameEngine/resource_identifiers.h
        src/states/state_title.cpp include/states/state_title.h
        src/states/state_menu.cpp include/states/state_menu.h
        src/states/state_settings.cpp include/states/state_settings.h
        src/states/state_game.cpp include/states/state_game.h
        src/util/utility.cpp include/util/utility.h
        src/states/state_pause.cpp include/states/state_pause.h
        src/map/map.cpp include/map/map.h
        src/map/object.cpp include/map/object.h
        src/map/layer.cpp include/map/layer.h
        src/map/sprite.cpp include/map/sprite.h
        src/map/isometric_sprite.cpp include/map/isometric_sprite.h
        include/util/maths.h
        )

add_executable(isoRPG ${SOURCE_FILES})
target_include_directories(isoRPG PUBLIC .)

target_link_libraries (isoRPG jsoncpp sfml-graphics sfml-audio sfml-window sfml-system)