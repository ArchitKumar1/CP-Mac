
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// using namespace __gnu_pbds;
// template<class T> 
// using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
// template<class key, class value, class cmp = std::less<key>>
// using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

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
const int  LOGN = 25;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////


const int N = 1.1e5;

VVI G1(N),G2(N),G3(N),comps(N);
VI vis(N),who(N),in(N),fans,seq;

stack<int> st;

void dfs1(int s){
    if(vis[s] == 1) return;
    vis[s] = 1;
    for(int c : G1[s]){
        if(!vis[c])
            dfs1(c);
    }
    st.push(s);
}

void dfs2(int s,int w){
    if(vis[s] == 1) return;
    vis[s] = 1;
    who[s] = w;
    comps[w].push_back(s);
    for(int c : G2[s]){
        if(!vis[c])
            dfs2(c,w);
    }
}

void dfs3(int s){
    if(vis[s] == 1) return;
    vis[s] = 1;
    seq.PB(s);
    for(int c : G3[s]){
        if(!vis[c])
            dfs3(c);
    }
}


void __Solve__(){
    
    int n,m,k;
    cin >> n >> m >> k;
    vis = VI(N);

    forn(i,m){
        int x,y; cin >> x >> y;
        G1[x].PB(y);G2[y].PB(x);
    }
    vis = VI(N);
    rep(i,n){
        if(!vis[i]) dfs1(i);
    }

    vis = VI(N);
    while(st.size()){
        int u = st.top(); st.pop();
        if(!vis[u]) dfs2(u,u);
    }

    rep(i,n){
        for(int c : G1[i]){
            if(who[i] !=  who[c] ){
                G3[who[i]].push_back(who[c]);
                in[c]++;
            }
        }
    }
    VI zcnt;
    rep(i,n) if(in[i] == 0){
        zcnt.PB(i);
    }
    sort(ALL(zcnt));
    vis = VI(N);
    for(int x : zcnt){
        if(!vis[x]){
            seq.clear();
            dfs3(x);
            sort(ALL(seq));
            for(int c : seq){
                fans.PB(c);
            }
        }
    }
    if(zcnt.size() >k+1){
        cout << -1 << endl;
        return;
    }
    for(int c : fans){
        cout << c << " ";
    }
    cout << endl;


    
}

signed main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(12);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    int test_case = 1;
   // cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}