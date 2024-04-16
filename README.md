# EchoFmt

一个C++格式化的库，用更简单高效的使用方式替代`stdio`和`iostream`。

这个项目的意义是为了参考和学习[fmt](https://github.com/fmtlib/fmt)，从中理解基本实现原理，并封装一个功能更简单的格式化库。

## 环境

该项目基于C++20标准。目前为止，该项目只考虑`Linux`平台，并且在未来计划支持`Windows`平台。

以下是项目开发所使用的环境：

- OS: Ubuntu 22.04 LTS
- Architecture: x86_64
- CMake: 3.28.4
- Toolchain: LLVM 18.1.2

## 构建

这是一个head-only的库， 直接包含`include`中的头文件即可使用。

也可以使用以下方式安装到本地目录：


```
git clone https://github.com/CnLzh/EchoFmt.git
cd EchoFmt
mkdir build
cd build
cmake ..
sudo make install
```

## 测试

该项目依赖[googletest](https://github.com/google/googletest)和[benchmark](https://github.com/google/benchmark)进行测试。其默认是关闭的，如果需要开启，可以执行以下操作：


```
cmake  -DECHOFMT_BUILD_TESTS=ON  -DECHOFMT_BUILD_BENCHMARKS=ON ..
sudo make
```

这将会生成`echo_fmt_tests`和`echo_fmt_benchmark`可执行文件。你可以在`build`文件夹中找到并执行它们，或者使用`ctest -V`通过CMake的测试驱动程序执行`echo_fmt_tests`进行测试。

