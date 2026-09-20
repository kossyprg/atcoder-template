/*----------------------------------------------------------
 - クラス名  : UnionFind
 - 機能      : 根付き木のグループ分けを高速に行うデータ構造
----------------------------------------------------------*/
class UnionFind {
    public:

    /*----------------------------------------------------------
     - 関数名: UnionFind
     - 機能  : コンストラクタ
     - 引数  : int n : 頂点の数 (n >= 1)
     - 使用例: UnionFind uf(100);
    ----------------------------------------------------------*/
    UnionFind(int n) : _n(n), parent_or_size(n, -1) {}

    /*----------------------------------------------------------
     - 関数名: merge
     - 機能  : 頂点 a、b を結合する
     - 引数  : int a, b : 結合する2頂点 (0 <= a,b < n)
     - 戻り値: なし
     - 備考  : Union by Size を適用している
     - 計算量: O(alpha(n)) (alpha(n) はアッカーマンの逆関数)
     - 使用例: uf.merge(2,3);
    ----------------------------------------------------------*/
    void merge(int a, int b) {
        if (a < 0 || _n <= a || b < 0 || _n <= b) {
            printf("[UnionFind] Error: argument of merge function is inappropriate.\n");
            printf("a: %d, b: %d\n", a, b);
            return;
        }

        int root_a = root(a);
        int root_b = root(b);

        // 既に同じ連結成分なら処理不要
        if (root_a == root_b) return;

        // 頂点数の多い連結成分へ併合する
        int size_a = -parent_or_size[root_a];
        int size_b = -parent_or_size[root_b];
        if (size_a < size_b) std::swap(root_a, root_b);
        parent_or_size[root_a] += parent_or_size[root_b];
        parent_or_size[root_b] = root_a;
        return;
    }
    
    /*----------------------------------------------------------
     - 関数名: same
     - 機能  : 頂点 a、b が同じ連結成分に属するかを返す
     - 引数  : int a, b : 調べる2頂点 (0 <= a,b < n)
     - 戻り値: bool : 同じ連結成分に属するなら true
     - 計算量: O(alpha(n)) (alpha(n) はアッカーマンの逆関数)
     - 使用例: bool isSame = uf.same(2,3);
    ----------------------------------------------------------*/
    bool same(int a, int b) {
        if (a < 0 || _n <= a || b < 0 || _n <= b) {
            printf("[UnionFind] Error: argument of same function is inappropriate.\n");
            printf("a: %d, b: %d\n", a, b);
            return false;
        }
        return root(a) == root(b);
    }

    /*----------------------------------------------------------
     - 関数名: root
     - 機能  : 頂点 a の根を返す
     - 引数  : int a : 調べる頂点 (0 <= a < n)
     - 戻り値: int : a の根
     - 備考  : 経路圧縮を適用している
     - 計算量: O(alpha(n)) (alpha(n) はアッカーマンの逆関数)
     - 使用例: int root_x = uf.root(3);
    ----------------------------------------------------------*/
    int root(int a) {
        if (a < 0 || _n <= a) {
            printf("[UnionFind] Error: argument of root function is inappropriate.\n");
            printf("a: %d\n", a);
            return -1;
        }
        if (parent_or_size[a] < 0) return a;

        // 経路圧縮: a から根までの頂点をつなぎ直しながら、戻り値を返す
        return parent_or_size[a] = root(parent_or_size[a]);
    }

    /*----------------------------------------------------------
     - 関数名: size
     - 機能  : 頂点 a の属する連結成分の大きさを返す
     - 引数  : int a : 調べる頂点 (0 <= a < n)
     - 戻り値: int : 頂点 a の属する連結成分の大きさ (>= 1)
     - 計算量: O(alpha(n)) (alpha(n) はアッカーマンの逆関数)
     - 使用例: int size_x = uf.root(3);
    ----------------------------------------------------------*/
    int size(int a) {
        if (a < 0 || _n <= a) {
            printf("[UnionFind] Error: argument of size function is inappropriate.\n");
            printf("a: %d\n", a);
            return 0;
        }
        return -parent_or_size[root(a)];
    }

    /*----------------------------------------------------------
     - 関数名: groups
     - 機能  : 連結成分ごとにグループ化した2次元配列を求める
     - 引数  : なし
     - 戻り値: 連結成分ごとにグループ化した2次元配列
     - 計算量: O(n) 
     - 参考  : ac-library dsu.hpp
    ----------------------------------------------------------*/
    std::vector<std::vector<int>> groups() {
        std::vector<int> root_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            root_buf[i] = root(i);
            group_size[root_buf[i]]++;
        }

        // メモリを確保した方が高速?
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }

        for (int i = 0; i < _n; i++) {
            result[root_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }

    /*----------------------------------------------------------
     - 関数名: debug
     - 機能  : 生データを表示する
     - 引数  : なし
     - 戻り値: なし
     - 備考  : (r) は root を表す
     - 使用例: uf.debug();
    ----------------------------------------------------------*/
    void debug() {
        if(_n > DEBUG_MAX_LINE) {
            printf("[UnionFind] Error: size is too big to display.\n");
            printf("size: %d\n", _n);
            return;
        }
        std::cout << "-----------------" << std::endl;
        for (int i = 0; i < _n; i++) {
            if (parent_or_size[i] < 0) {
                std::cout << i << "(r) \t" << "size: " << -parent_or_size[i] << std::endl;
            } else {
                std::cout << i << "    \t" << "root: " << parent_or_size[i] << std::endl;
            }
        }
        std::cout << "-----------------" << std::endl;
    }

    private:
    int _n;
    std::vector<int> parent_or_size; // 親なら -(連結成分のサイズ)、子なら親の頂点
    const int DEBUG_MAX_LINE = 100;
};