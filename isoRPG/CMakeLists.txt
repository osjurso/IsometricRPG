cmake_minimum_required(VERSION 3.5.2)
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
        include/util/maths.h
        src/states/state_character.cpp include/states/state_character.h
        include/components/Comp_position.h
        include/components/Comp_size.h
        src/systems/mouse_clicked.cpp
        include/components/Comp_animation.h
        include/systems/mouse_clicked.h
        include/components/Comp_mousedOver.h
        include/components/Comp_Texture.h
        include/systems/drawEntety.h
        include/components/Comp_healt.h
        include/collections/drawable.h
        src/states/state_character.cpp
        include/states/state_character.h
        src/gamEngine/music_player.cpp
        include/gameEngine/music_player.h
        src/gamEngine/sound_player.cpp
        include/gameEngine/sound_player.h include/systems/collsion.h include/components/Comp_moveble.h include/systems/attack.h include/collections/setUpCreature.h include/systems/resolve_movment.h include/components/Comp_State.h include/components/Comp_looteble.h include/systems/loot.h src/collection/setUpCreature.cpp include/components/Comp_talk.h include/collections/addDialoge.h include/systems/talk.h include/systems/pathfinding.h include/components/PathfindingNode.h include/systems/moveCreatures.h include/collections/pathfinfigVariables.h)


add_executable(isoRPG ${SOURCE_FILES})
target_include_directories(isoRPG PUBLIC . include)

target_link_libraries (isoRPG jsoncpp sfml-graphics sfml-audio sfml-window sfml-system anax)