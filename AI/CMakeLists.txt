add_library(AI
    AIBase.cpp
    evaluate.cpp
    TreeSearchAI.cpp
)

target_include_directories(AI
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Othello/include
)

target_link_libraries(AI Othello)