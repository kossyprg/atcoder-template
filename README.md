# AtCoder C++23 Dev Container

最小構成の AtCoder 用 Dev Container です。

- C++23 / GCC 15.2.0
- AC Library 1.6
- `a`, `g`, `start` の alias
- `start` で `a.cpp` ～ `g.cpp` を生成

## 使い方

1. `template.cpp` を自分のテンプレートに置き換える。
2. VS Code でこのフォルダを開く。
3. `Dev Containers: Reopen in Container` を実行する。
4. ターミナルで `start` を実行する。

```bash
start
```

カレントディレクトリに `a.cpp` ～ `g.cpp` が生成されます。既存ファイルは上書きしません。

ビルド例:

```bash
g a.cpp
```

実行:

```bash
a
```

`template.cpp` は Dev Container 作成時に `~/atcoder/template.cpp` へシンボリックリンクされます。
