add_library(Othello
    Othello.cpp
)

target_include_directories(Othello
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)