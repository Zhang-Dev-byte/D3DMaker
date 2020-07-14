cmake_minimum_required(VERSION 3.15)

add_subdirectory(D3DW)


project(D3DMaker)

add_subdirectory(D3DMaker)

target_link_libraries(D3DMaker D3DW)

target_include_directories(D3DMaker PRIVATE D3DW/D3DW/src)

set_target_properties(D3DMaker PROPERTIES
LINK_FLAGS /SUBSYSTEM:WINDOWS
)

set_target_properties( D3DMaker
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(Sandbox)

target_link_libraries(Sandbox D3DW)

target_link_libraries(Sandbox D3DMaker)

target_include_directories(Sandbox PRIVATE D3DW/D3DW/src)

target_include_directories(Sandbox PRIVATE D3DMaker/src)

set_target_properties(Sandbox PROPERTIES
LINK_FLAGS /SUBSYSTEM:WINDOWS
)

set_target_properties( Sandbox
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)