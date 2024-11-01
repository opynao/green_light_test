file(GLOB SRC_FILES *.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

add_library(${PROJECT_NAME}_lib ${SRC_FILES})