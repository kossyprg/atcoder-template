/*----------------------------------------------------------
 - 関数名: div_floor
 - 機能  : floor(a / b) を返す
 - 引数  : a: 被除数
 -         b: 除数 (0でない)
 - 戻り値: floor(a / b)
 - 備考  : c++では被除数が負のときの割り算は切り上げになる
 - 使用例: div_floor(4,3) // 1
           div_floor(-4,3) // -2
           div_floor(-4,-3) // 1
 - 参考  : ABC239-B
----------------------------------------------------------*/
template <typename T>
inline T div_floor(T a, T b) {
    if (b == 0) {
        std::cerr << "[div_floor] Error: Division by zero." << std::endl;
        return 0;
    }

    if (b < 0) {
        a = -a;
        b = -b;
    }
    return a / b - (a % b < 0);
}

/*----------------------------------------------------------
 - 関数名: div_ceil
 - 機能  : ceil(a / b) を返す
 - 引数  : a: 被除数
 -         b: 除数 (0でない)
 - 戻り値: ceil(a / b)
 - 備考  : c++では被除数が負のときの割り算は切り上げになる
 - 使用例: div_ceil(4,3) // 2
           div_ceil(-4,3) // -1
           div_ceil(-4,-3) // 2
----------------------------------------------------------*/
template <typename T>
inline T div_ceil(T a, T b) {
    if (b == 0) {
        std::cerr << "[div_ceil] Error: Division by zero." << std::endl;
        return 0;
    }

    if (b < 0) {
        a = -a;
        b = -b;
    }
    return (a >= 0) ? ((a + b - 1) / b) : (a / b);
}

/*----------------------------------------------------------
 - 関数名: safe_mod
 - 機能  : x を m で割った余りを0以上の値で返す
 - 引数  : x: 被除数
 -         m: mod演算の除数 (m > 0)
 - 戻り値: 0 <= (x % m) < m
 - 備考  : -4 % 3 // -1 
           safe_mod(-4, 3) // 2
----------------------------------------------------------*/
long long safe_mod(long long x, long long m) {
    if (m == 0) {
        std::cerr << "[safe_mod] Error: Division by zero." << std::endl;
        return 0;
    }

    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

/*----------------------------------------------------------
 - 関数名: Power
 - 機能  : a の b 乗を m で割った余りを返す
 - 引数  : a: 底
 -         b: 指数部
 -         m: mod演算の除数
 - 戻り値: (a ^ b) % m
----------------------------------------------------------*/
long long Power(long long a, long long b, long long m)
{
    long long p = a, ans = 1;
    while (b > 0) {
        if((b & 1) != 0) ans = (ans * p) % m;
        b >>= 1;
        p = (p * p) % m;
    }
    return ans;
}

/*----------------------------------------------------------
 - 関数名: ModInv
 - 機能  : モジュラ逆数を求める
 - 条件  : a と m は互いに素でなければならない
 - 引数  : long long a: 逆元を求める値
           long long m: mod演算の除数で素数
 - 戻り値: (1 / a) % m 
 - 備考  : 非再帰拡張 Euclid の互除法により計算
 - 計算量: O(log(a)) // Euclidの互除法
 - 使用例: ModInv(3, 7) // 5
 - 参考  : https://qiita.com/drken/items/3b4fdf0a78e7a138cd9a
----------------------------------------------------------*/
long long ModInv(long long a, long long m) {
    // a < 0 でも計算できるようにしている
    a %= m;
    if (a < 0) a += m;

    long long gcd = a; // Euclid の互除法を適用した後にgcdになる
    long long b = m, u = 1, v = 0;

    // 非再帰拡張 Euclid の互除法
    while (b != 0) {
        long long t = gcd / b;
        gcd -= t * b; std::swap(gcd, b);
        u -= t * v;   std::swap(u, v);
    }

    // a と m は互いに素でなければならない
    if(gcd != 1) {
        std::cout << "[ModInv] Error: modular multiplicative inverse does not exist. a and m must be relatively prime." << std::endl;
        std::cout << "(a, m) = (" << a << ", " << m << ")" << std::endl;
        return 0;
    }

    u %= m; 
    if (u < 0) u += m;
    return u;
}

/*----------------------------------------------------------
 - 関数名: Division
 - 機能  : a / b を m で割った余りを返す
 - 条件  : b と m は互いに素でなければならない(ModInvを参照)
 - 引数  : a: 被除数
 -         b: 除数
 -         m: mod演算の除数
 - 戻り値: (a / b) % m
 - 備考: モジュラ逆数を乗算することで割り算を実行する
----------------------------------------------------------*/
long long Division(long long a, long long b, long long m)
{
    return (a * ModInv(b, m)) % m;
}

/*----------------------------------------------------------
 - 関数名: Combination
 - 機能  : nCr を m で割った余りを返す
 - 引数  : n, r: 整数(n >= r >= 0)
 -         m: mod演算の除数で素数
 - 戻り値: nCr % m
 - 計算量: O(n + logx)
 - 備考: モジュラ逆数を乗算することで割り算を実行する
----------------------------------------------------------*/
long long Combination(long long n, long long r, long long m)
{
    if (r > n - r) r = n - r; // r <= n/2 とする

    long long numerator = 1;
    for (int i = n; i >= n - r + 1; i--) {
        numerator = (numerator * i) % m;
    }

    long long denominator = 1;
    for (int i = r; i >= 1; i--) {
        denominator = (denominator * i) % m;
    }

    long long ans = Division(numerator, denominator, m);
    return ans;
}