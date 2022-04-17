include(FetchContent)

FetchContent_Declare(onnx
 GIT_REPOSITORY https://github.com/onnx/onnx.git
 GIT_TAG        cf6dfad9a770e4d6412ea88f1833c8e0118e163d
)

set(ONNX_ML ON)
add_definitions(-DONNX_ML=1)
add_definitions(-DONNX_NAMESPACE=onnx)
FetchContent_GetProperties(onnx)
if (NOT platform_POPULATED)
    FetchContent_Populate(onnx)
endif ()

add_subdirectory(${onnx_SOURCE_DIR} ${onnx_BINARY_DIR})
message(${onnx_SOURCE_DIR})
include_directories(
    .
    ${onnx_SOURCE_DIR}
    ${onnx_BINARY_DIR}
)

add_library(parser STATIC
    parser.cpp
)

FIND_PACKAGE(Protobuf REQUIRED)

target_link_libraries(parser
    ${onnx_BINARY_DIR}/libonnx_proto.a
    ${onnx_BINARY_DIR}/libonnx.a
    protobuf::libprotobuf
)
