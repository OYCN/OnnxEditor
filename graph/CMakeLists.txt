set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(.)

add_library(graph STATIC
    graphedge.cpp
    graphnode.cpp
    graphscene.cpp
    graphview.cpp
)

target_link_libraries(
    graph
    PUBLIC
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
)
