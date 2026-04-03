cmake_minimum_required(VERSION 3.11)

project(hello C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_executable(${PROJECT_NAME}
    src/main.c
    src/controller/userInput.c
    src/graphics/allocateVram.c
    src/graphics/graphicsBoilerplate.c
    src/states/stateManager.c
    src/states/title/title_screen.c
    common/callbacks.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    src
    common
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    pspgu
    pspctrl
)

# Create an EBOOT.PBP file
create_pbp_file(
    TARGET ${PROJECT_NAME}
    ICON_PATH NULL
    BACKGROUND_PATH NULL
    PREVIEW_PATH NULL
    TITLE ${PROJECT_NAME}
    VERSION 01.00
)
