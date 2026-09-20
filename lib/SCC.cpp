/*----------------------------------------------------------
 - クラス名  : SCC (Strongly connected component)
 - 機能      : 互いに行き来可能な頂点集合（強連結成分）に分解する
----------------------------------------------------------*/
class SCC {
    public:

    /*----------------------------------------------------------
     - 関数名: SCC
     - 引数  : int N : 頂点の数
    ----------------------------------------------------------*/
    SCC(int N) {
        _n = N;
        G.resize(N);
        rG.resize(N);
    }

    /*----------------------------------------------------------
     - 関数名: add_edge
     - 機能  : from -> to の有向辺を追加する
     - 引数  : int from, to
     - 戻り値: なし
    ----------------------------------------------------------*/
    void add_edge(int from, int to) {
        if (from < 0 || from >= _n || to < 0 || to >= _n) {
            printf("[SCC] Error: argument of add_edge function is inappropriate.\n");
            printf("(from, to) : (%d,%d)", from, to);
            return;
        }
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    /*----------------------------------------------------------
     - 関数名: scc
     - 機能  : 強連結成分ごとに分解した頂点のリストを返す
     - 引数  : なし
     - 戻り値: 強連結成分ごとにまとめたグラフのリスト
     - 計算量: 辺の本数を M として O(N + M)
    ----------------------------------------------------------*/
    std::vector<std::vector<int>> scc() {
        std::vector<std::vector<int>> scc;
        std::vector<int> vs;
        std::vector<bool> visited(_n, false);

        auto dfs = [&](auto self, int v) -> void {
            visited[v] = true;
            for (auto e : G[v]) {
                if (!visited[e]) self(self, e);
            }
            vs.push_back(v);
        };

        for (int i = 0; i < _n; i++) {
            if (!visited[i]) dfs(dfs, i);
        }

        std::vector<int> rvs;
        visited.assign(_n, false);

        auto rdfs = [&](auto self, int v) -> void {
            visited[v] = true;
            for (auto e : rG[v]) {
                if (!visited[e]) self(self, e);
            }
            rvs.push_back(v);
        };

        for (int i = _n - 1; i >= 0; i--) {
            if (visited[vs[i]]) continue;
            rvs.clear();
            rdfs(rdfs, vs[i]);
            scc.push_back(rvs);
        }

        return scc;
    }

    private:
    int _n;
    std::vector<std::vector<int>> G;
    std::vector<std::vector<int>> rG;
};