template<typename T>
void printArray(const std::vector<T>& arr) {
    for (const auto& element : arr) {
        std::cerr << element << " ";
    }
    std::cerr << '\n';
}

template<typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix, bool useDelimiter = true, const char delimiter = ' ') {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cerr << element;
            if (useDelimiter) std::cerr << delimiter;
        }
        std::cerr << '\n';
    }
}