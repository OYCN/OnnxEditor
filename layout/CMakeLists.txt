include(FetchContent)

FetchContent_Declare(ogdf
 GIT_REPOSITORY https://github.com/ogdf/ogdf.git
 GIT_TAG        7596a518d2b8a964523c2bbd86af360aa405c6cf
)

FetchContent_GetProperties(ogdf)
if (NOT platform_POPULATED)
    FetchContent_Populate(ogdf)
endif ()

add_subdirectory(${ogdf_SOURCE_DIR} ${ogdf_BINARY_DIR})

include_directories(
    .
    ${ogdf_SOURCE_DIR}/include
    ${ogdf_BINARY_DIR}/include
)

add_library(layout STATIC
    layout.cpp
    ogdf_layout.cpp
)

target_link_libraries(
    layout
    PUBLIC
    ${ogdf_BINARY_DIR}/libOGDF.a
    ${ogdf_BINARY_DIR}/libCOIN.a
)
