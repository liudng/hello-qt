qt_add_library(filebrowser STATIC
    mainwindow.cpp
)

target_link_libraries(filebrowser PRIVATE 
    Qt6::Widgets
    core
)

target_include_directories(filebrowser INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)