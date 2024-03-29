/*----------------------------------------------------------
 - クラス名: BIT(Binary Indexed Tree)
 - 機能    : 1点更新と区間和の計算をO(logN)で計算する
 - 備考    : Segment treeを簡素化したデータ構造
----------------------------------------------------------*/
template<typename T>
class BIT
{
    public:

    /*----------------------------------------------------------
     - 関数名: BIT
     - 機能  : コンストラクタ
     - 引数  : int n : 頂点の数 (n >= 1)
     - 使用例: BIT<int> b(100);
    ----------------------------------------------------------*/
    explicit BIT(int n) : _n(n), data(n, 0) {}

    /*----------------------------------------------------------
     - 関数名: add
     - 機能  : p 番目の要素に w を加える(1点更新)
     - 引数  : int p: 更新する要素番号(0 <= p <= n - 1)
               T w: 加算する値
     - 戻り値: なし
     - 備考  : x & -x は x を2進表現したとき、1が立っている最も下位のビットのみを1とした数
               e.g., x = 0110, -x = 1010, x & -x = 0010 = 3
     - 計算量: O(log(n)) 
     - 使用例: b.add(2, 3); 
    ----------------------------------------------------------*/
    void add(int p, T w){
        if (p < 0 || p >= _n) {
            printf("[BIT] Error: argument of add function is inappropriate.\n");
            printf("p: %d\n", p);
            return;
        }

        p++; // 1 オリジンで計算して、0 オリジンのdataを更新する
        for(int x = p; x <= _n; x += x & -x) {
            data[x - 1] += w;
        }
    }

    /*----------------------------------------------------------
     - 関数名: sum
     - 機能  : 半開区間 [l,r) の区間和を求める
     - 引数  : int l, r: 半開区間の端点 (0 <= l <= r <= n)
     - 戻り値: 半開区間 [l,r) の区間和
     - 計算量: O(log(n)) 
     - 使用例: cout << b.sum(3,6) << endl;
    ----------------------------------------------------------*/
    T sum(int l, int r){
        if (l < 0 || r < l || _n < r) {
            printf("[BIT] Error: argument of sum function is inappropriate.\n");
            printf("l: %d, r: %d\n", l, r);
            return T(0);
        }
        return _sum(r) - _sum(l);
    }

    /*----------------------------------------------------------
     - 関数名: displayBIT
     - 機能  : (デバッグ用)BITのデータを表示する
     - 引数  : なし
     - 戻り値: なし
    ----------------------------------------------------------*/
    void displayBIT() {
        for(int i = 0; i < _n; i++) {
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    private:
    int _n;
    std::vector<T> data;

    /*----------------------------------------------------------
     - 関数名: _sum
     - 機能  : 半開区間 [0,r) の区間和を求める
     - 引数  : int r: 半開区間の端点 (0 <= r <= n)
     - 戻り値: 半開区間 [0,r) の区間和
     - 備考  :
     - 計算量: O(log(N)) 
    ----------------------------------------------------------*/
    T _sum(int r) {
        T ret = 0;
        for(int x = r; x > 0; x -= x & -x) {
            ret += data[x - 1];
        }
        return ret;
    }
};