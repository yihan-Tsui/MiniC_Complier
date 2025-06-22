cmake_minimum_required(VERSION 3.14)
project(SeuYacc)  # 修改项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Windows子系统为控制台
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()

# 添加源文件列表
set(SOURCE_FILES
    main.cpp
    yaccSource.cpp
)

# 添加头文件目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 创建可执行文件
add_executable(SeuYacc ${SOURCE_FILES})