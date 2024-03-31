cmake_minimum_required(VERSION 3.28.4)
project(echo_fmt VERSION 1.1.0 LANGUAGES C CXX)

# 使用C++20标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 只允许导出显示声明为可见的符号
if (BUILD_SHARED_LIBS)
    add_compile_options(-fvisibility=hidden)
endif (BUILD_SHARED_LIBS)

# googletest单元测试
option(ECHOFMT_BUILD_TESTS "Build EchoFmt unit tests" ON)

# 检查编译器是否支持忽略字段初始化的警告
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Wno-missing-field-initializers
        ECHOFMT_MISSING_FIELD_INITIALIZERS)

# googletest
if (ECHOFMT_BUILD_TESTS)

    # 启用cmake测试
    enable_testing()

    # 使用共享CRT，防止在windows上覆盖编译器和链接器的设置
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # 不安装googletest和googlemock
    set(install_gtest OFF)
    set(install_gmock OFF)
    set(build_gmock ON)

    add_subdirectory("third_party/googletest")

    # 忽略googletest和googlemock的字段初始化警告
    # 避免不必要的编译器警告干扰
    if (ECHOFMT_MISSING_FIELD_INITIALIZERS)
        set_property(TARGET gtest
                APPEND PROPERTY COMPILE_OPTIONS -Wno-missing-field-initializers)
        set_property(TARGET gmock
                APPEND PROPERTY COMPILE_OPTIONS -Wno-missing-field-initializers)
    endif (ECHOFMT_MISSING_FIELD_INITIALIZERS)

    # 添加测试文件
    add_executable(efmt_tests "")

    # 如果不编译为动态库，则编译单元测试文件
    if (NOT BUILD_SHARED_LIBS)
        # 添加全部测试文件
        target_sources(efmt_tests
                PRIVATE
                src/test.cc
        )
    endif (NOT BUILD_SHARED_LIBS)

    # 链接
    target_link_libraries(efmt_tests gmock gtest gtest_main)

    # 添加到cmake
    add_test(NAME "efmt_tests" COMMAND "efmt_tests")

endif (ECHOFMT_BUILD_TESTS)
