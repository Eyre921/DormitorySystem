# 设置最低版本的 CMake
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(DormitoryManagementSystem)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置 C++ 编译器标志（如果需要的话）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# 设置构建类型为 Release
set(CMAKE_BUILD_TYPE Release)
# 或者设置 CMake 默认的构建选项为优化
set(CMAKE_CXX_FLAGS_RELEASE "-O3")  # O3 是最高级别的优化

# 添加包含目录
include_directories(
        src
        sqlite3  # sqlite3 头文件路径
)

# 添加源文件
set(SOURCE_FILES
        sqlite3/sqlite3.c
        src/main.cpp
        src/UserManager.cpp
        src/Database.cpp
        src/globals.cpp
        src/specialPrint.cpp
)

# 创建可执行文件
add_executable(DormitoryManagementSystem ${SOURCE_FILES})

target_link_libraries(DormitoryManagementSystem)

# 如果需要调试或发布版本，请添加相应的构建配置
set_target_properties(DormitoryManagementSystem PROPERTIES
        DEBUG_POSTFIX "_d"  # 调试版本后缀（可选）
        RELEASE_POSTFIX "_release"  # 发行版本后缀（可选）
)
