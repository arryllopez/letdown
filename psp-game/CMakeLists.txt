cmake_minimum_required(VERSION 3.14)
project(letdown LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PSPSDK toolchain sets these, but guard just in case
if(NOT DEFINED PSPSDK)
    execute_process(
        COMMAND psp-config --pspsdk-path
        OUTPUT_VARIABLE PSPSDK
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

if(NOT DEFINED PSPDEV)
    execute_process(
        COMMAND psp-config --pspdev-path
        OUTPUT_VARIABLE PSPDEV
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

include_directories(
    ${PSPSDK}/include
    ${PSPDEV}/include
    ${CMAKE_SOURCE_DIR}/src
)

link_directories(
    ${PSPSDK}/lib
    ${PSPDEV}/lib
)

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
set(ENGINE_SOURCES
    src/engine/memory/pool_allocator.cpp
    src/engine/memory/stack_allocator.cpp
    src/engine/assets/asset_manager.cpp
    src/engine/input/input.cpp
    src/engine/graphics/renderer.cpp
    src/engine/graphics/sprite.cpp
    src/engine/graphics/animator.cpp
    src/engine/cutscene/cutscene.cpp
    src/engine/core/game_loop.cpp
)

set(GAME_SOURCES
    src/game/world/tile_map.cpp
    src/game/world/player.cpp
    src/game/scenes/title_screen.cpp
    src/game/scenes/overworld.cpp
)

set(ALL_SOURCES
    src/main.cpp
    ${ENGINE_SOURCES}
    ${GAME_SOURCES}
)

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# ---------------------------------------------------------------------------
# PSP libraries
# ---------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    osl            # OSLib
    png
    z
    pspgu
    pspge
    pspdisplay
    pspctrl
    psprtc
    pspaudio
    psppower
    pspsdk
    pspuser
    pspkernel
    m
)

# ---------------------------------------------------------------------------
# EBOOT.PBP generation
# ---------------------------------------------------------------------------
# PSP module info — needed by the PSPSDK build system
set(PSP_EBOOT_TITLE "letdown")
set(PSP_EBOOT_ICON  NULL)
set(PSP_EBOOT_PIC1  NULL)
set(PSP_EBOOT_SND0  NULL)

# After building the ELF, strip it and pack into EBOOT.PBP
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Fixing ELF..."
    COMMAND psp-fixup-imports ${PROJECT_NAME}
    COMMAND mksfo "${PSP_EBOOT_TITLE}" PARAM.SFO
    COMMAND pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL ${PROJECT_NAME} NULL
    COMMENT "Generating EBOOT.PBP"
)
