qt_add_library(core STATIC
    clipboardmanager.cpp
)

target_link_libraries(core PRIVATE 
    Qt6::Core
)

target_include_directories(core INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)