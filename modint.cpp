/*----------------------------------------------------------
 - 構造体名  : modint
 - 機能      : mod 計算を int の演算と同様に扱えるようにするための構造体
 - パラメータ : int MOD : 1 <= MOD <= 32bit整数の最大値(2147483647)
----------------------------------------------------------*/
template<int MOD, std::enable_if_t<(1 <= MOD && MOD <= INT32_MAX)>* = nullptr> struct modint {
    public:

    /*----------------------------------------------------------
     - 関数名: modint
     - 機能  : 引数なしのコンストラクタ
     - 備考  : 0で初期化される
     - 使用例: modint<7> a;
    ----------------------------------------------------------*/
    constexpr modint() noexcept : _v(0) {}

    /*----------------------------------------------------------
     - 関数名: modint
     - 機能  : 引数ありのコンストラクタ
     - 引数  : long long v : 初期値 (内部でmod演算される)
     - 使用例: modint<7> a(9);
              cout << a.val() << endl; // 2
    ----------------------------------------------------------*/
    constexpr modint(long long v) {
        long long p = v % umod();
        if (p < 0) p += umod();
        _v = (unsigned int)(p);
    }

    /*----------------------------------------------------------
     - 関数名: mod
     - 機能  : mod演算の除数を返す
     - 戻り値: int MOD : mod演算の除数
    ----------------------------------------------------------*/
    static constexpr int mod() { return MOD; }

    /*----------------------------------------------------------
     - 関数名: val
     - 機能  : mod演算の演算結果を返す関数
     - 戻り値: long long _v : mod演算の演算結果
    ----------------------------------------------------------*/
    long long val() const { return _v; }

    /*----------------------------------------------------------
     - 機能  : 前置形の++演算子のオーバーロード
     - 使用例: modint<11> a(10);
               modint<11> b = ++a;
               cout << a.val() << endl; // 0
               cout << b.val() << endl; // 0
    ----------------------------------------------------------*/
    modint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }

    /*----------------------------------------------------------
     - 機能  : 後置形の++演算子のオーバーロード
     - 備考  : 引数はダミー
     - 使用例: modint<11> a(10);
               modint<11> b = a++;
               cout << a.val() << endl; // 0
               cout << b.val() << endl; // 10
    ----------------------------------------------------------*/
    modint operator++(int) {
        modint result = *this;
        ++*this;
        return result;
    }

    /*----------------------------------------------------------
     - 機能  : 前置形の--演算子のオーバーロード
     - 使用例: modint<5> a(0);
               modint<5> b = --a;
               cout << a.val() << endl; // 4
               cout << b.val() << endl; // 4
    ----------------------------------------------------------*/
    modint& operator--() {
        if(_v == 0) _v = umod();
        _v--;
        return *this;
    }

    /*----------------------------------------------------------
     - 機能  : 後置形の--演算子のオーバーロード
     - 備考  : 引数はダミー
     - 使用例: modint<5> a(0);
               modint<5> b = a--;
               cout << a.val() << endl; // 4
               cout << b.val() << endl; // 0
    ----------------------------------------------------------*/
    modint operator--(int) {
        modint result = *this;
        --*this;
        return result;
    }

    /*----------------------------------------------------------
     - 機能  : 加算(+)のオーバーロード
     - 備考  : lhs(左辺)とrhs(右辺)の少なくとも一方がmodintであればよい
     - 使用例: int a = 10;
               modint<7> b = 8;
               modint<7> c = a + b; // 内部で行われるのは 3 + 1
               -----------------------
               int a = 8;
               int b = 9;
               modint<7> c = 10;
               modint<7> d = a + b + c; // modint(17) + modint(10) になることに注意
    ----------------------------------------------------------*/
    friend constexpr modint operator+(const modint& lhs, const modint& rhs) {
        return modint(lhs) += rhs;
    }

    /*----------------------------------------------------------
     - 機能  : 減算(-)のオーバーロード
     - 備考  : lhs(左辺)とrhs(右辺)の少なくとも一方がmodintであればよい
     - 使用例: const int MOD = INT32_MAX; // 2147483647
               modint<MOD> a = 0;
               modint<MOD> b = MOD - 1;   // modintがとりうる最大値
               modint<MOD> c = a - b;     // c.val() = 1
               -----------------------
               const int MOD = INT32_MAX; // 2147483647
               modint<MOD> a = 0;
               modint<MOD> b = 1;
               modint<MOD> c = a - b;     // c.val() = 2147483646
    ----------------------------------------------------------*/
    friend modint operator-(const modint& lhs, const modint& rhs) {
        return modint(lhs) -= rhs;
    }

    /*----------------------------------------------------------
     - 機能  : 乗算(*)のオーバーロード
     - 備考  : lhs(左辺)とrhs(右辺)の少なくとも一方がmodintであればよい
     - 使用例: const int MOD = INT32_MAX;
               modint<MOD> a = MOD - 1; // modintがとりうる最大値
               modint<MOD> b = MOD - 1;
               modint<MOD> c = a * b;   // c.val() = 1
    ----------------------------------------------------------*/
    friend modint operator*(const modint& lhs, const modint& rhs) {
        return modint(lhs) *= rhs;
    }

    /*----------------------------------------------------------
     - 機能  : 除算(/)のオーバーロード
     - 備考  : lhs(左辺)とrhs(右辺)の少なくとも一方がmodintであればよい
               内部で逆元の乗算を行う
     - 使用例: modint<10> x(7);
               modint<10> y = x / 3;    // 1/3 = -3 = 7 (mod 10)
               cout << y.val() << endl; // 9
    ----------------------------------------------------------*/
    friend modint operator/(const modint& lhs, const modint& rhs) {
        return modint(lhs) /= rhs;
    }

    /*----------------------------------------------------------
     - 機能  : 等価演算子(==)のオーバーロード
     - 使用例: string s = modint<11>(5) == modint<11>(-6) ? "Yes" : "No";
               cout << s << endl; // Yes
    ----------------------------------------------------------*/
    friend bool operator==(const modint& lhs, const modint& rhs) {
        return lhs._v == rhs._v;
    }

    /*----------------------------------------------------------
     - 機能  : 非等価演算子(!=)のオーバーロード
     - 使用例: string s = modint<7>(5) != modint<7>(12) ? "Yes" : "No";
               cout << s << endl; // No
    ----------------------------------------------------------*/
    friend bool operator!=(const modint& lhs, const modint& rhs) {
        return lhs._v != rhs._v;
    }
    
    /*----------------------------------------------------------
     - 機能  : 加算代入演算子(+=)のオーバーロード     
     - 使用例: modint<7> a(5);
               a += 3;
               cout << a.val() << endl; // 1
    ----------------------------------------------------------*/
    constexpr modint& operator += (const modint& rhs) noexcept {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }

    /*----------------------------------------------------------
     - 機能  : 減算代入演算子(-=)のオーバーロード     
     - 使用例: modint<7> a(2);
               a -= 3;
               cout << a.val() << endl; // 6
    ----------------------------------------------------------*/
    constexpr modint& operator -= (const modint& rhs) noexcept {
        int z = _v;
        z -= rhs._v;
        if (z < 0) z += umod();
        _v = (unsigned int)(z % mod());
        return *this;
    }

    /*----------------------------------------------------------
     - 機能  : 乗算代入演算子(*=)のオーバーロード     
     - 使用例: modint<INT32_MAX> a(INT32_MAX - 2);
               a *= (INT32_MAX - 3);
               cout << a.val() << endl; // 6
    ----------------------------------------------------------*/
    constexpr modint& operator *= (const modint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }

    /*----------------------------------------------------------
     - 機能  : 除算代入演算子(/=)のオーバーロード    
     - 備考  : モジュラ逆数を乗算する(inv関数を参照)
     - 使用例: modint<10> x(7);
               x /= 3; // 1/3 = -3 = 7 (mod 10)
               cout << x.val() << endl; // 9
    ----------------------------------------------------------*/
    constexpr modint& operator /= (const modint& rhs) { 
        return *this = *this * rhs.inv(); 
    }

    /*----------------------------------------------------------
     - 機能  : 正符号のオーバーロード
    ----------------------------------------------------------*/
    modint operator+() const { return *this; }

    /*----------------------------------------------------------
     - 機能  : 負号のオーバーロード
     - 使用例: modint<11> b(3);
               if(-b == modint<11>(8)) cout << "ok" << endl;
               else cout << "ng" << endl;
    ----------------------------------------------------------*/
    modint operator-() const { return modint() - *this; }

    /*----------------------------------------------------------
     - 機能  : モジュラ逆数を求める
     - 条件  : MOD と _v が互いに素でなければならない
     - 備考  : 非再帰拡張 Euclid の互除法により計算
     - 使用例: modint<10> x(7);
               modint<10> y = x / 3;    // 1/3 = -3 = 7 (mod 10)
               cout << y.val() << endl; // 9
               -----------------------
               modint<13> x(10);
               modint<13> y = x / 13;   // 逆元は存在しない
               cout << y.val() << endl; // 0
     - 参考  : https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
    ----------------------------------------------------------*/
    modint inv() const {
        long long gcd = _v; // Euclid の互除法を適用した後にgcdになる
        long long b = umod(), u = 1, v = 0; 

        // 非再帰拡張 Euclid の互除法
        while (b != 0) {
            long long t = gcd / b;
            gcd -= t * b; swap(gcd, b);
            u -= t * v;   swap(u, v);
        }

        // 逆元の存在条件を満たさないなら、メッセージを出して0を返す
        if(gcd != 1) {
            std::cout << "[modint] Error: modular multiplicative inverse does not exist." << std::endl;
            return modint(0);
        }

        u %= umod(); 
        if (u < 0) u += umod();
        unsigned int inv = (unsigned int)(u);
        modint ret(inv);
        return ret;
    }

    /*----------------------------------------------------------
     - 機能  : val の n 乗を求める
     - 備考  : 繰り返し二乗法により計算
     - 使用例: modint<6> x(11);
               modint<6> y = x.pow(1001001002);
               cout << y.val() << endl; // 1
     - 参考  : https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
    ----------------------------------------------------------*/
    modint pow(long long n) const {
        modint p = *this, r = 1;
        if(n < 0) {
            std::cout << "[modint] Error: exponent part must be 0 or positive." << std::endl;
            return r;
        }
        
        // 繰り返し二乗法
        while (n > 0) {
            if ((n & 1) != 0) r *= p;
            p *= p;
            n >>= 1;
        }
        return r;
    }

    private:
    unsigned int _v;
    static constexpr unsigned int umod() { return MOD; }
};
using modint998244353  = modint<998244353>;
using modint1000000007 = modint<1000000007>;