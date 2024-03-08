/*----------------------------------------------------------
 - 関数名: printArray
 - 機能  : 1次元配列の中身を標準出力に表示する
 - 引数  : arr: 1次元配列
 - 戻り値: なし
----------------------------------------------------------*/
template<typename T>
void printArray(const std::vector<T>& arr) {
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

/*----------------------------------------------------------
 - 関数名: printMatrix
 - 機能  : 2次元配列の中身を標準出力に表示する
 - 引数  : matrix: 2次元配列
 - 戻り値: なし
----------------------------------------------------------*/
template<typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}