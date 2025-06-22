# SeuLex/CMakeLists.txt
project(SeuLex CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 源文件列表
set(SOURCE_FILES
        DFA.cpp
        lexSource.cpp
        main.cpp
        NFA.cpp
)

# 添加可执行文件
add_executable(SeuLex ${SOURCE_FILES})

# 包含当前目录下的头文件
target_include_directories(SeuLex PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
