# 動かし方
## CMakeによるC++ファイルのビルド
1. CMake をインストールする.
2. カレントディレクトリを main に移動する.
3. main ディレクトリの CMakLists.txt のコンパイラのパスを指定する.
4. cmake -S . -B build -G "MinGW Makefiles" を実行. Configuring と Generating を行う. Generator は適宜指定する.
5. cmake --build build を実行して build する.

## 実行方法
1. カレントディレクトリを Game に移動する. 
2. main.py を実行する.

# ディレクトリ構成
## Othello

## AI

## main

## Game