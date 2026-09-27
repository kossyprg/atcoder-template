# C++23 Dev Container

競技プログラミング用 c++ 環境

- C++23 / GCC 15.2.0
- AC Library 1.6
- `a`, `g`, `start` の alias
- `start` で `a.cpp` ～ `g.cpp` を生成

## Quick Start

1. VS Code を右クリック、「New Window」を押下
2. 「Open Folder」から本フォルダを開く
3. Ctrl + Shift + P で `Dev Containers: Rebuild Without Cache and Reopen in Container` を実行する。

### ABCを始めるとき

```bash
start
```

カレントディレクトリに `a.cpp` ～ `g.cpp` が生成されます。既存ファイルは上書きしません。

`template.cpp` は Dev Container 作成時に `~/atcoder/template.cpp` へシンボリックリンクされます。

### ビルド・実行

ビルド:

```bash
g a.cpp
```

実行:

```bash
a
```
