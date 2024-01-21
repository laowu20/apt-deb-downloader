#设置cmake版本
cmake_minimum_required (VERSION 3.5)
#设置项目版本
project (apt-deb-downloader)
#设置C++版本
set(CMAKE_CXX_STANDARD 14)
#设置输出所有文件
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#搜索boost库
#set(CMAKE_MODULE_PATH "../../boost/lib")
#list(APPEND CMAKE_PREFIX_PATH "../../../boost/lib/cmake")
#set(Boost_US_STATIC_LIB ON)
#set(Boost_DEBUG ON)
#set(Boost REQUIRED COMPONENTS filesystem log)
#MESSAGE(STATUS "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
#MESSAGE(STATUS "Boost_LIBRARY_DIRS=${Boost_LIBRARY_DIRS}")
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#设置运行时搜索路径
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

#PROJECT_SOURCE_DIR是关键字，代表的是当前项目文件的路径
#我们可以使用取值符号获取当前目录
message("PROJECT_SOURCE_DIR:")
message(${PROJECT_SOURCE_DIR})
#ORIGIN是关键字,指运行文件所在目录

#添加头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/src)
#将源文件列表写在变量SrcFiles中
aux_source_directory(./src AppFiles)

#添加第三方库头文件
#include_directories(third_party/windows/wpdpack/include)

#添加第三方库文件夹
#link_directories(third_party/windows/wpdpack/lib/x64)
#link_directories(${PROJECT_SOURCE_DIR}/../build/run/Release)

#生成dll库
#add_library(kernel SHARED ${SrcFiles})

#为dll库链接依赖库
#target_link_libraries(kernel pthread)
#set_target_properties(kernel PROPERTIES INSTALL_RPATH "${ORIGIN}/")
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

#设置可执行文件的源文件
#aux_source_directory(./src/main AppFiles)

#生成可执行文件
add_executable(apt-deb-downloader ${AppFiles})

#给可执行文件链接依赖库
#target_link_libraries(wiresharkwrapper kernel)
#target_link_libraries(wiresharkwrapper wireshark)

#拷贝依赖动态库到输出路径
#file(COPY third_party/windows/wpdpack/lib/x64/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#file(COPY ${PROJECT_SOURCE_DIR}/../build/run/Release/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})

#拷贝资源文件到输出路径
#file(COPY data/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#安装命令
#install(TARGETS wiresharkwrapper RUNTIME DESTINATION bin)
#添加子项目文件夹
#add_subdirectory(src/subdir/)
