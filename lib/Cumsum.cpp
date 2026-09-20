/*----------------------------------------------------------
 - クラス名: Cumsum
 - 機能    : 0-indexed の配列の累積和を計算し、区間の和を返す
----------------------------------------------------------*/
class Cumsum {
    public:

    /*----------------------------------------------------------
     - 機能  : コンストラクタ、累積和を計算する
     - 計算量 : O(N)
    ----------------------------------------------------------*/
    template<typename T>
    Cumsum(std::vector<T> array) {
        N = (int)array.size();
        cumsum.assign(N + 1, 0);
        for (int i = 0; i < N; i++) {
            cumsum[i+1] = cumsum[i] + array[i];
        }
    }

    /*----------------------------------------------------------
     - 関数名: sum
     - 機能  : 区間[l,r]の和を返す
     - 引数  : int l, r : データ列 A のインデックス(0 <= l <= r <= N - 1)
     - 戻り値: 区間[l,r]の和
     - 計算量: O(1) 
    ----------------------------------------------------------*/
    long long sum(int l, int r) {
        // l, r は 0-indexed
        if (l > r || r >= N || l < 0) {
            printf("[Cumsum] Error: The arguments of sum function are inappropriate.\n");
            printf("(l,r) = (%d,%d)\n", l, r);
            return 0;
        }
        return cumsum[r+1] - cumsum[l];
    }

    private:
    int N;
    std::vector<long long> cumsum;
};