qt_add_library(texteditor STATIC
    mainwindow.cpp
)

target_link_libraries(texteditor PRIVATE 
    core
    Qt6::Widgets
)

target_include_directories(texteditor INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)