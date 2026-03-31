cmake_minimum_required(VERSION 3.11)

project(hello)

add_executable(${PROJECT_NAME}
    src/main.c
    src/graphics/allocateVram.c
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
