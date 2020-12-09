
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
using namespace __gnu_pbds;
template<class T> 
using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os, unordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator << (ostream& os, multiset<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
//template<class T> ostream& operator<<(ostream &os, ordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}


#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__,__VA_ARGS__)
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	cout<<name<<" : "<<arg1<<endl;
}
template<typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
		const char* comma=strchr(names+1,',');cout.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...) 1
#endif

//reading vectors
template <class T> void RV(vector<T> &v){for(auto &c : v) cin >> c;}
template <class T> void RV(vector<vector<T>> &v){for(auto &c : v) RV(c);}


//defines and typedefs
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i = 1;i<=n;i++)

#define ALL(x) x.begin(),x.end()
#define int long long int
// #define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"

typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;

auto clk=clock();

//constants
int mod = 1e9+7;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 20;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////

const int N= 3e5+1;
const int K = 26;
int n,q;
int arr[N];

int tin[N],tout[N];
int BIT[N][K];

void add(int i,int val,int k){
    for(;i<N;i+=(i&-i)){
        BIT[i][k] += val;
    }
}
int sum(int i,int k){
    int fans = 0;
    for(;i>0;i-=(i&-i)){
        fans += BIT[i][k];
    }
    return fans;
}

vector<vector<int>> G(N);
vector<int> depth(N,0);
vector<vector<int>> p(N,vector<int>(LOGN,1));
 
int timer = 1;
void dfs(int s,int par){
    
    depth[s] = depth[par] + 1;
    tin[s] = timer;
    timer+=1;
    p[s][0] = par; 
    for(int c : G[s]){    
        if(c == par) continue;
        dfs(c,s);
    }
    
    tout[s] = timer;
}
int lca(int u,int v) {
	if (depth[u]>depth[v]) swap(u,v);
	for(int i = LOGN-1;i>=0;i--) if (depth[p[v][i]]>=depth[u]) v=p[v][i];
	if (u==v) return u;
	for(int i = LOGN-1;i>=0;i--) if (p[v][i]!=p[u][i]) u=p[u][i],v=p[v][i];
	return p[u][0];
}

int kth(int u,int k) {
    int nd = depth[u] - k;
    if(nd <= 1)return 1;
	for(int i = LOGN-1;i>=0;i--) if (depth[p[u][i]]>=nd) u=p[u][i];
	return u;
}


void __Solve__(){
    cin >> n >> q;
    rep(i,n) cin >> arr[i];
    
    forn(i,n-1){
        int u,v;
        cin >> u >> v;
        G[u].PB(v),G[v].PB(u);
    }
    dfs(1,0);
    for(int j =1;j<LOGN;j++){
        for(int i = 1;i<=n;i++){
            p[i][j] = p[p[i][j-1]][j-1];
        }
    }
    // for(int i = 1;i<=n;i++){
    //     trace(tin[i],tout[i]);
    // }
    rep(i,n){
        add(tin[i],1,arr[i]);
        add(tout[i],-1,arr[i]);
    }
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int v,x;
            cin >> v >> x;
            //trace(tin[v],arr[v]);
            add(tin[v],-1,arr[v]);
            add(tout[v],1,arr[v]);
            arr[v] = x;
            add(tin[v],1,arr[v]);

            add(tout[v],-1,arr[v]);

            // add(tin[v],-1,arr[v]);
            // arr[v] = x;
            // add(tin[v],1,arr[v]);

            //add(tout[v]+1,-1,arr[v]);

        }else{
            int v,k;
            cin >> v >> k;
             int u = kth(v,k);
            int fans = 0;
            //trace(v,k,u);
            for(int i = 0;i<K;i++){
                int s1 = sum(tin[v],i) - sum(tin[u]-1,i);
                if(s1) trace(s1,i,v,k,u,s1%2 ==0 );
                if(s1 %2 == 1){
                    fans += i;
                }
            }
            cout << fans << endl;
            
        }
    }
    trace(kth(8,0));
}

signed main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(2);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    int test_case = 1;
    //cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}