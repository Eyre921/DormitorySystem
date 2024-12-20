# 设置最低版本的 CMake
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(DormitoryManagementSystem)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置 C++ 编译器标志（如果需要的话）
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# 添加包含目录
include_directories(
        src
        sqlite3  # sqlite3 头文件路径
)

# 添加源文件
set(SOURCE_FILES
        src/main.cpp
        src/UserManager.cpp
        sqlite3/sqlite3.c
        src/Database.cpp
        src/Database.h
        # SQLite 源文件
)

# 创建可执行文件
add_executable(DormitoryManagementSystem ${SOURCE_FILES})

# 如果有需要链接的库（如 SQLite），可以在这里链接
# 如果sqlite3.c在项目中使用，它已经包含在了源文件列表中，无需额外链接

# 链接 SQLite3 库，如果使用 DLL 版本，还需要确保 SQLite3 DLL 文件可以找到
# 如果使用 SQLite3 的库文件（例如 .lib 或 .a），需要指定路径
target_link_libraries(DormitoryManagementSystem)


# 如果需要调试或发布版本，请添加相应的构建配置
set_target_properties(DormitoryManagementSystem PROPERTIES
        DEBUG_POSTFIX "_d"  # 调试版本后缀（可选）
        RELEASE_POSTFIX "_release"  # 发行版本后缀（可选）
)
