cmake_minimum_required(VERSION 3.28.4)
project(echo_fmt VERSION 1.1.0 LANGUAGES C CXX)

# 使用C++20标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 只允许导出显示声明为可见的符号
if (BUILD_SHARED_LIBS)
    add_compile_options(-fvisibility=hidden)
endif (BUILD_SHARED_LIBS)

# googletest
option(ECHOFMT_BUILD_TESTS "Build EchoFmt unit tests" ON)

# benchmark
option(ECHOFMT_BUILD_BENCHMARKS "Build EchoFmt benchmarks" ON)

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
    # 如果不编译为动态库，则编译单元测试文件
    if (NOT BUILD_SHARED_LIBS)
        # 添加测试可执行文件
        add_executable(echo_fmt_tests "")
        # 添加全部测试文件
        target_sources(echo_fmt_tests
                PRIVATE
                tests/test.cc
        )
        # 链接
        target_link_libraries(echo_fmt_tests gmock gtest gtest_main)
        # 添加到cmake
        add_test(NAME "echo_fmt_tests" COMMAND "echo_fmt_tests")
    endif (NOT BUILD_SHARED_LIBS)
endif (ECHOFMT_BUILD_TESTS)

if (ECHOFMT_BUILD_BENCHMARKS)
    # 使用交叉编译工具链时避免benchmark中cxx_feature_check导致的警告
    include(CheckCXXSourceCompiles)

    # have_thread_safety_attributes
    check_cxx_source_compiles("
    #include <pthread.h>
    int main() {
        __attribute__((thread_safe)) int x;
        return 0;
    }"
            HAVE_THREAD_SAFETY_ATTRIBUTES)

    # have_std_regex
    check_cxx_source_compiles("
    #include <regex>
    int main() {
        std::regex regex;
        return 0;
    }"
            HAVE_STD_REGEX)

    # have_posix_regex
    check_cxx_source_compiles("
    #include <regex.h>
    int main() {
        regex_t regex;
        return 0;
    }"
            HAVE_POSIX_REGEX)

    # have_steady_clock
    check_cxx_source_compiles("
    #include <chrono>
    int main() {
        std::chrono::steady_clock::now();
        return 0;
    }"
            HAVE_STEADY_CLOCK)

    # have_pthread_affinity
    check_cxx_source_compiles("
    #include <pthread.h>
    int main() {
        cpu_set_t cpuset;
        pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
        return 0;
    }"
            HAVE_PTHREAD_AFFINITY)

    # 禁用测试和异常处理
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "" FORCE)
    add_subdirectory("third_party/benchmark")
    # 添加基准测试文件
    if (NOT BUILD_SHARED_LIBS)
        # 添加基准测试可执行文件
        add_executable(echo_fmt_benchmark "")
        # 添加全部测试文件
        target_sources(echo_fmt_benchmark
                PRIVATE
                benchmarks/benchmark.cc
        )
        # 链接
        target_link_libraries(echo_fmt_benchmark gmock gtest benchmark)
    endif (NOT BUILD_SHARED_LIBS)
endif (ECHOFMT_BUILD_BENCHMARKS)
