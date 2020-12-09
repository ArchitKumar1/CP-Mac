
#include<bits/stdc++.h>
using namespace std;


#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i = 1;i<=n;i++)

#define ll long 
#define PB push_back


const int  LOGN = 20;

const int N = 500010;
#define mod (1LL << 32)

ll  left_order[N], s_order[N], fans[N],l[N], r[N];
ll  scalar_val[N], scalar_val1[N],right_order[N];
int  indexy1[2*N], hirberto[N];
bool visited[N];
vector<int> G[N];
int n, Q;
int timer, v1[N], depth[N], parent[20][N];

///Hilbert order  taken from codeforces blog https://codeforces.com/blog/entry/61203

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}
///Hilbert order  taken from codeforces blog https://codeforces.com/blog/entry/61203

struct query {
    int id, r,l, lca_value;
    int64_t ord;

    inline void findAns() {
        ord = hilbertOrder(l, r, 21, 0);
    }
    
};

query queries[N];

inline bool operator<(const query&a,const query &b){
    return a.ord < b.ord;
}

void dfs1(int u, int par, int h) {
    l[u] = ++timer;
    indexy1[timer] = u;
    depth[u] = h;
    for (int i = 1; i < LOGN; i++) parent[i][u] = parent[i - 1][parent[i - 1][u]];
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == par) continue;
        parent[0][v] = u;
        dfs1(v, u, h + 1);
    }
    r[u] = ++timer;
    indexy1[timer] = u;
}

inline int LCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--){
        if (depth[v] - (1 << i) >= depth[u]) 
        v = parent[i][v];
    }
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (parent[i][u] != parent[i][v]) {
            u = parent[i][u];
            v = parent[i][v];
        }
    }
    return parent[0][u];
}

inline void validate(long x, long &res) {
    if ((visited[x])) {
        if (hirberto[depth[x]] == 2) {
            res -= left_order[depth[x]];res += mod; res %= mod;
            s_order[depth[x]] -= v1[x]; s_order[depth[x]] += mod;s_order[depth[x]] %= mod;
            right_order[depth[x]] -= (v1[x] * s_order[depth[x]]);right_order[depth[x]] += mod;right_order[depth[x]] %= mod;
        } else if (hirberto[depth[x]] == 3) {
            s_order[depth[x]] -= v1[x];s_order[depth[x]] += mod;s_order[depth[x]] %= mod;
            right_order[depth[x]] -= (v1[x] * s_order[depth[x]]);right_order[depth[x]] += mod;right_order[depth[x]] %= mod;
            res += right_order[depth[x]];res %= mod;left_order[depth[x]] = right_order[depth[x]];
        } else {
            s_order[depth[x]] -= v1[x];s_order[depth[x]] += mod;s_order[depth[x]] %= mod;
            right_order[depth[x]] -= (v1[x] * s_order[depth[x]]);right_order[depth[x]] += mod;right_order[depth[x]] %= mod;
        }
        hirberto[depth[x]]--;
    } else {
        if (hirberto[depth[x]] == 1) {
            right_order[depth[x]] += (v1[x] * s_order[depth[x]]);right_order[depth[x]] %= mod;
            res += right_order[depth[x]];res %= mod;
            s_order[depth[x]] += v1[x];s_order[depth[x]] %= mod;
            left_order[depth[x]] = right_order[depth[x]];
        } else if (hirberto[depth[x]] == 2) {
            right_order[depth[x]] += (v1[x] * s_order[depth[x]]);right_order[depth[x]] %= mod;
            s_order[depth[x]] += v1[x];s_order[depth[x]] %= mod;
            res -= left_order[depth[x]];res += mod;res %= mod;
        } else {
            right_order[depth[x]] += (v1[x] * s_order[depth[x]]);right_order[depth[x]] %= mod;
            s_order[depth[x]] += v1[x]; s_order[depth[x]] %= mod;
        }
        hirberto[depth[x]]++;
    }
    visited[x] ^= 1;
}

void dfs2(int v, int p) {
    for (auto i: G[v]) {
        if (i != p) {
            scalar_val[i] = (scalar_val[v] + (v1[i] * v1[i]) % mod) % mod;
            dfs2(i, v);
        }
    }
}

void dfs3(int v, int p) {
    return;
    for (auto i: G[v]) {
        if (i != p) {
            scalar_val1[i] = (v1[i]);
            dfs3(i, v);
        }
    }
}
int main() {

#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 

    while (scanf("%d %d", &n, &Q) != EOF) {
        rep(i,n) scanf("%d", &v1[i]);
        forn(i,n-1) {
            int u,v; scanf("%d %d", &u, &v);
            G[u].push_back(v); G[v].push_back(u);
        }
        parent[0][1] = 1;
        dfs1(1, -1, 1);
        scalar_val[1] = v1[1] * v1[1];
        scalar_val[1] %= mod;

        dfs2(1, 0);
        dfs3(1,0);
        forn(i,Q)  {
            int u,v; scanf("%d %d", &u, &v);
            queries[i].lca_value = LCA(u, v);
            if (l[u] > l[v]){
                swap(u, v);
            }
            if (queries[i].lca_value == u){
                queries[i].l = l[u];
                queries[i].r = l[v];
            }
            else{
                queries[i].l = r[u];
                queries[i].r = l[v];
            }
            queries[i].id = i;
            queries[i].findAns();
        }

        sort(queries, queries + Q);
        ll lefty = queries[0].l, righty = queries[0].l - 1, res = 0;

        //dfs3(1,0);
        forn(i,Q) {

            while (lefty < queries[i].l) validate(indexy1[lefty++], res);
            while (lefty > queries[i].l) validate(indexy1[--lefty], res);
            while (righty < queries[i].r) validate(indexy1[++righty], res);
            while (righty > queries[i].r) validate(indexy1[righty--], res);

            int u = indexy1[lefty], v = indexy1[righty];

            if (queries[i].lca_value != u and queries[i].lca_value != v){
                validate(queries[i].lca_value, res);
            }

            fans[queries[i].id] = (res + scalar_val[queries[i].lca_value]) % mod;

            if (queries[i].lca_value != u and queries[i].lca_value != v){
                validate(queries[i].lca_value, res);
            }
        }

        forn(i,Q){
            printf("%ld\n", fans[i]);
        }
    }

}

