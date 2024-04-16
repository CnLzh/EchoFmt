# EchoFmt

一个C++格式化的库，用更简单高效的使用方式替代`stdio`和`iostream`。

这个项目的意义是为了参考和学习[fmt](https://github.com/fmtlib/fmt)，从中理解基本实现原理，并封装一个功能更简单的格式化库。

## 环境

该项目基于C++20标准。目前为止，该项目没有考虑兼容C++20以下版本以及不同操作系统和不同编译器环境下的兼容性表现。

以下是项目开发所使用的环境：

- OS: Ubuntu 22.04 LTS
- Architecture: x86_64
- CMake: 3.28.4
- Toolchain: LLVM 18.1.2

## 构建

这是一个head-only的库， 使用 `git clone https://github.com/CnLzh/EchoFmt.git` 拷贝该项目，并直接包含`include`中的头文件即可使用。

或使用CMake添加到项目中：

```
add_subdirectory(echofmt)
target_link_libraries(YourProject PRIVATE echofmt::echofmt)
```

## 测试

该项目依赖[googletest](https://github.com/google/googletest)和[benchmark](https://github.com/google/benchmark)进行测试。
