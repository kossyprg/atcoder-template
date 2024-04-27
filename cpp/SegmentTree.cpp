/*----------------------------------------------------------
 - クラス名: SegmentTree
 - 機能    : 1点更新と区間和の計算をO(logN)で計算する
 - 条件    : op は結合律を満たし、単位元 e が存在すること
 - 参考    : ac-library segtree.hpp
             https://drken1215.hatenablog.com/entry/2023/11/14/033300
             ABC343-F
----------------------------------------------------------*/
template <class S, S (*op)(S, S), S (*e)()>
class SegmentTree {
    public:
    using Func = std::function<S(S,S)>;
    
    /*----------------------------------------------------------
     - 機能  : コンストラクタ
     - 引数  : int n : データ列の要素数
     - 使用例: int op(int a, int b) { return max(a,b); }
              int e() { return 0; }
              SegmentTree<int, op, e> Z(N);
    ----------------------------------------------------------*/
    SegmentTree(int n) : _n(n) {
        _size = 1;
        while (_size < _n) _size *= 2;
        data.assign(_size * 2, e()); // 再代入
    }

    /*----------------------------------------------------------
     - 関数名: set
     - 機能  : p 番目の要素を x に更新する
     - 引数  : int p : データ列のインデックス(0 <= p <= n - 1)
               S x : 更新する値
     - 戻り値: なし
     - 計算量: O(log(n)) 
     - 使用例: Z.set(0, 100);
    ----------------------------------------------------------*/
    template<typename T>
    void set(int p, const T &x) {
        // 型チェック
        if (!std::is_same<T, S>::value) {
            throw std::invalid_argument("[SegmentTree] Error: The argument of set function should have the correct type.");
        }

        // 範囲チェック
        if (p < 0 || p >= _n) {
            printf("[SegmentTree] Error: argument of set function is inappropriate.\n");
            printf("p: %d\n", p);
            return;
        }
        
        p += _size;
        data[p] = x;
        while(p >= 2) {
            p >>= 1;
            data[p] = op(data[p * 2], data[p * 2 + 1]);
        }
    }

    /*----------------------------------------------------------
     - 関数名: get
     - 機能  : p 番目の要素を取得する
     - 引数  : int p : データ列 A のインデックス(0 <= p <= n - 1)
     - 戻り値: p 番目の要素
     - 計算量: O(1) 
     - 使用例: S val = Z.get(0);
    ----------------------------------------------------------*/
    S get(int p) {
        if (p < 0 || p >= _n) {
            printf("[SegmentTree] Error: argument of get function is inappropriate.\n");
            printf("p: %d\n", p);
            return e();
        }
        return data[p + _size];
    }

    /*----------------------------------------------------------
     - 関数名: prod
     - 機能  : 半開区間 [l,r) の演算結果を返す
     - 引数  : int l, r: 半開区間の端点 (0 <= l <= r <= n)
     - 戻り値: op({A[l], A[l+1], ..., A[r-1]})
     - 計算量: O(log(n)) 
     - 使用例: cout << Z.prod(3, 5) << endl;
    ----------------------------------------------------------*/
    S prod(int l, int r) {
        if (l < 0 || r < l || _n < r) {
            printf("[SegmentTree] Error: argument of prod function is inappropriate.\n");
            printf("l: %d, r: %d\n", l, r);
            return e();
        }

        // 比較する左側と右側のセルの値
        S vl = e(), vr = e();
        l += _size;
        r += _size;

        while (l < r) {
            if (l & 1) vl = op(vl, data[l++]);
            if (r & 1) vr = op(data[--r], vr);
            l >>= 1;
            r >>= 1;
        }
        return op(vl, vr);
    }

    /*----------------------------------------------------------
     - 関数名: max_right
     - 機能  : (f が単調なら) f(op(A[l], A[l + 1], ..., A[r - 1])) = true となる
               最大の r を返す
     - 引数  : function<bool(S)> f : 二分探索に用いられる関数
               l : 探索範囲の左端
     - 戻り値: f(op(A[l], A[l + 1], ..., A[r - 1])) = true となる最大の r
     - 計算量: O(log(n)) 
     - 使用例: int res = Z.max_right([&](int a) -> bool { return a < v; }, x);
     - 備考  : ac-library segtree.hpp
    ----------------------------------------------------------*/
    int max_right(const function<bool(S)> f, int l = 0) {
        if (l == _n) return _n;
        l += _size;
        S sum = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sum, data[l]))) {
                while (l < _size) {
                    l = l * 2;
                    if (f(op(sum, data[l]))) {
                        sum = op(sum, data[l]);
                        ++l;
                    }
                }
                return l - _size;
            }
            sum = op(sum, data[l]);
            ++l;
        } while ((l & -l) != l);  // stop if l = 2^e
        return _n;
    }

    /*----------------------------------------------------------
     - 関数名: min_left
     - 機能  : (f が単調なら) f(op(A[l], A[l + 1], ..., A[r - 1])) = true となる
               最小の l を返す
     - 引数  : function<bool(S)> f : 二分探索に用いられる関数
               r : 探索範囲の右端
     - 戻り値: f(op(A[l], A[l + 1], ..., A[r - 1])) = true となる最小の l
     - 計算量: O(log(n)) 
     - 使用例: int res = Z.min_left([&](int a) -> bool { return a < v; }, x);
     - 備考  : ac-library segtree.hpp
    ----------------------------------------------------------*/
    int min_left(const function<bool(S)> f, int r = -1) {
        if (r == 0) return 0;
        if (r == -1) r = _n;
        r += _size;
        S sum = e();
        do {
            --r;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(data[r], sum))) {
                while (r < _size) {
                    r = r * 2 + 1;
                    if (f(op(data[r], sum))) {
                        sum = op(data[r], sum);
                        --r;
                    }
                }
                return r + 1 - _size;
            }
            sum = op(data[r], sum);
        } while ((r & -r) != r);
        return 0;
    }

    /*----------------------------------------------------------
     - 関数名: displaySegTree
     - 機能  : (デバッグ用)セグ木の全てのセルを表示する
     - 引数  : なし
     - 戻り値: なし
    ----------------------------------------------------------*/
    void displaySegTree() {
        int k = 1;
        for (int i = 1; i <= _size * 2; i++){
            if((i & (1 << k)) != 0){
                std::cout << std::endl;
                k++;
            }
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    private:
    int _n;
    int _size; // n 以上の 2^k で表される最小の整数
    vector<S> data;
};