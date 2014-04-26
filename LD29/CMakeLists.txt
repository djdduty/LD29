file(GLOB game_top_SOURCES src/*.*)
file(GLOB game_component_SOURCES src/Components/*.*)
file(GLOB game_state_SOURCES src/States/*.*)

include_directories(src/)
include_directories(src/Components)
include_directories(src/States)

add_executable(LD29 ${game_top_SOURCES} ${game_component_SOURCES} ${game_state_SOURCES})

source_group("LD29\\" FILES ${game_top_SOURCES})
source_group("LD29\\Components" FILES ${game_component_SOURCES})
source_group("LD29\\States" FILES ${game_state_SOURCES})

target_link_libraries(LD29 BearClaw)
