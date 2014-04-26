file(GLOB bc_top_SOURCES src/*.*)
file(GLOB bc_components_SOURCES src/Components/*.*)
file(GLOB bc_events_SOURCES src/Events/*.*)

file(GLOB bc_renderer_SOURCES src/Renderer/*.*)
file(GLOB bc_renderer_main_SOURCES src/Renderer/MainRenderer/*.*)
file(GLOB bc_renderer_utils_SOURCES src/Renderer/Utils/*.*)

file(GLOB bc_resource_SOURCES src/Resource/*.*)
file(GLOB bc_scene_SOURCES src/Scene/*.*)

file(GLOB bc_system_SOURCES src/System/*.*)
file(GLOB bc_system_os_SOURCES src/System/OS/*.*)
file(GLOB bc_system_file_SOURCES src/System/File/*.*)
file(GLOB bc_system_states_SOURCES src/System/StateManagement/*.*)

file(GLOB bc_utils_SOURCES src/Utils/*.*)
file(GLOB bc_utils_math_SOURCES src/Utils/Math/*.*)

file(GLOB bc_gui_SOURCES src/Gui/*.*)

if(BUILD_STATIC)
    set(BUILD_MODE STATIC)
else()
    set(BUILD_MODE SHARED)
endif()

add_library(BearClaw ${BUILD_MODE} ${bc_top_SOURCES} ${bc_components_SOURCES} ${bc_events_SOURCES} ${bc_renderer_SOURCES} ${bc_renderer_main_SOURCES} ${bc_renderer_utils_SOURCES} ${bc_resource_SOURCES} ${bc_scene_SOURCES} ${bc_system_SOURCES} ${bc_system_os_SOURCES} ${bc_system_file_SOURCES} ${bc_utils_SOURCES} ${bc_utils_math_SOURCES} ${bc_system_states_SOURCES} ${bc_gui_SOURCES})

target_link_libraries(BearClaw Soil Glew Glfw assimp zlib ${GL_LIBRARIES} ${GLFW_LIBRARIES})

source_group("BearClaw" FILES ${bc_top_SOURCES})
source_group("BearClaw\\Components" FILES ${bc_components_SOURCES})
source_group("BearClaw\\Events" FILES ${bc_events_SOURCES})

source_group("BearClaw\\Renderer" FILES ${bc_renderer_SOURCES})
source_group("BearClaw\\Renderer\\Utils" FILES ${bc_renderer_utils_SOURCES})
source_group("BearClaw\\Renderer\\MainRenderer" FILES ${bc_renderer_main_SOURCES})

source_group("BearClaw\\Resource" FILES ${bc_resource_SOURCES})
source_group("BearClaw\\Scene" FILES ${bc_scene_SOURCES})

source_group("BearClaw\\System" FILES ${bc_system_SOURCES})
source_group("BearClaw\\System\\File" FILES ${bc_system_file_SOURCES})
source_group("BearClaw\\System\\OS" FILES ${bc_system_os_SOURCES})
source_group("BearClaw\\System\\StateManagement" FILES ${bc_system_states_SOURCES})

source_group("BearClaw\\Utils" FILES ${bc_utils_SOURCES})
source_group("BearClaw\\Utils\\Math" FILES ${bc_utils_math_SOURCES})

source_group("BearClaw\\Gui" FILES ${bc_gui_SOURCES})

#install(TARGETS MethCasting RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
