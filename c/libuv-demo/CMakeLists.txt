cmake_minimum_required (VERSION 2.8.12)

# 项目信息
project (App)

# 指定头文件搜索路径
INCLUDE_DIRECTORIES(/opt/homebrew/include)

# 指定引用的外部库的搜索路径
LINK_DIRECTORIES(/opt/homebrew/lib)

# 指定可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} uv http_parser)