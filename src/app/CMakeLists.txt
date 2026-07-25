qt_add_executable(
    hello
    main_window.cpp
    main.cpp
)

target_link_libraries(hello PRIVATE 
    core
    Qt6::Widgets
)

set_target_properties(hello PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)