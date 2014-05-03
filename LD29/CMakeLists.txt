file(GLOB game_top_SOURCES src/*.*)
file(GLOB game_component_SOURCES src/Components/*.*)
file(GLOB game_state_SOURCES src/States/*.*)
file(GLOB game_node_SOURCES src/Nodes/*.*)

include_directories(src/ src/Components src/States src/Nodes)

add_executable(LD29 ${game_top_SOURCES} ${game_node_SOURCES} ${game_component_SOURCES} ${game_state_SOURCES})

source_group("LD29\\" FILES ${game_top_SOURCES})
source_group("LD29\\Components" FILES ${game_component_SOURCES})
source_group("LD29\\States" FILES ${game_state_SOURCES})
source_group("LD29\\Nodes" FILES ${game_node_SOURCES})

target_link_libraries(LD29 BearClaw SDL2 SoLoud)
