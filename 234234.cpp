#include<bits/stdc++.h>
using namespace std;
template<class T> ostream& operator<<(ostream &os,vector<T> V){
    os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
    return os<<"("<<P.first<<","<<P.second<<")";
}

#define ALL(x) x.begin(),x.end()
#define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"
#define l() cout << endl;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TC int t; cin >> t;while(t--)
#define forn(i,n) for(int i=0;i<n;i++)

const int mod = pow(10,9)+7;
const int inf = 2e9;
const LL linf = 2e18;
const double eps = 1e-9;


////////////////////////////

const int N = 1250;
int rail[N][N],road[N][N];
int u,v;
vector<vector<pair<int,int>>> G1(N),G2(N);
int n;
vector<int> dij(int s,vector<vector<pair<int,int>>>&G){
    vector<int> vis(n,0);
    vector<int> dist(n,inf);
    set<pair<int,int>> ss;
    dist[s] = 0;
    ss.insert({0,s});
    while(ss.size()){
        pair<int,int> top = *ss.begin();ss.erase(*ss.begin());
        if(vis[top.second]) continue;
        vis[top.second] = 1;
        for(pair<int,int> c : G[top.second]){
            if(dist[c.first] > dist[top.second] + c.second){
                ss.insert({dist[c.first]=dist[top.second] + c.second,c.first});
            }
        }
    }
    return dist;
}

void solve(){
    cin >> n;
    forn(i,n)forn(j,n) cin >> rail[i][j];
    forn(i,n)forn(j,n) cin >> road[i][j];
    forn(i,n)forn(j,n){
        if(i!=j){
            G1[i].PB({j,rail[i][j]});
        }
    }
    forn(i,n)forn(j,n){
        if(i!=j){
            G2[j].PB({i,road[i][j]});
        }
    }
    cin >> u >> v;
    u--;v--;
    vector<int> v1 = dij(u,G1);
    vector<int> v2 = dij(v,G2);
    int fans = INT_MAX;
    for(int i=0;i<n;i++){
        if(i!= u && i!= v)
        fans = min(fans,v1[i] + v2[i]);
    }

    forn(i,n){
        G1[i].clear();
        G2[i].clear();
    }
    forn(i,n)forn(j,n){
        if(i!=j){
            G1[i].PB({j,road[i][j]});
        }
    }
    forn(i,n)forn(j,n){
        if(i!=j){
            G2[j].PB({i,rail[i][j]});
        }
    
     v1 = dij(u,G1);
    v2  = dij(v,G2);

    for(int i=0;i<n;i++){
        if(i!= u && i!= v)
        fans = min(fans,v1[i] + v2[i]);
    }
    cout << fans << endl;
}

int main(){
FASTIO
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
    
    int t =1;
    //cin >> t;
    for(int i=1;i<=t;i++){
        solve();
    }
    return 0;

}