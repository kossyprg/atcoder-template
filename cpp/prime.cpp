class SieveOfEratosthenes {
    public:
    std::vector<int> primes; // 素数テーブル

    /*----------------------------------------------------------
     - 関数名: SieveOfEratosthenes
     - 機能  : コンストラクタ
     - 引数  : int n : 求める素数テーブルの最大値
     - 備考  : エラトステネスのふるいにより計算
     - 計算量: O(NloglogN) ほとんど O(N)
     - 使用例: SieveOfEratosthenes se(100);     
    ----------------------------------------------------------*/
    SieveOfEratosthenes(int n = 1) : _n(n), factor(n+1, 0) {
        // 0 と 1 は素数でない
        factor[0] = factor[1] = -1;

        for(long long i = 2; i <= _n; i++) {
            // i は素数でないときパス
            if(factor[i] != 0) continue;

            // 素数テーブルに追加
            factor[i] = i;
            primes.push_back(i);

            // 素数 i の倍数を除去
            for(long long j = i*i; j <= _n; j += i) {
                // j の最小の約数を格納する
                if(factor[j] == 0) factor[j] = i;
            }
        }
    }

    /*----------------------------------------------------------
     - 関数名: isPrime
     - 機能  : 素数なら true を返す
     - 引数  : int x : 調べる値
     - 戻り値: x が素数なら true
    ----------------------------------------------------------*/
    bool isPrime(int x) {
        if (x < 0 || _n < x) {
            std::cout << "[SieveOfEratosthenes] Error: argument of isPrime is inappropriate." << std::endl;
            return false;
        }
        return factor[x] == x;
    }

    /*----------------------------------------------------------
     - 関数名: factorize
     - 機能  : 値 x の素因数分解を配列として返す
     - 引数  : int x : 調べる値 (x >= 2)
     - 戻り値: x の素因数分解を格納した配列
     - 備考  : result[i] <= result[i+1] が成立
     - 計算量: O(logn) 
    ----------------------------------------------------------*/
    std::vector<int> factorize(int x) {
        std::vector<int> result;
        if (x < 2 || _n < x) {
            std::cout << "[SieveOfEratosthenes] Error: argument of factorize is inappropriate." << std::endl;
            return result;
        }

        while(x != 1) {
            result.push_back(factor[x]);
            x /= factor[x];
        }
        return result;
    }

    private:
    int _n;
    std::vector<int> factor;
};