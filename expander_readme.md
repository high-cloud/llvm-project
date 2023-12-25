# 使用指南

## 编译llvm
首先需要准备编译llvm 所需的环境，如果使用nix，直接在当前目录下运行
`nix-shell` 即可。
如果你不使用nix，请自行补齐（编译过程中应该会提示缺少哪些工具）

运行 `bash mybuild.sh`

成功运行后，进入 build 文件夹， 运行`make -j8`

成功编译之后，需要导出环境变量，建议直接将当前目录下的 build/bin 加入 PATH 中。

## expander 迁移

