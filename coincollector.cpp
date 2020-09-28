
#include<bits/stdc++.h>

using namespace std;

template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){return os<<"("<<P.first<<","<<P.second<<")";}

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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,a,b) for(int i = a;i<=b;i++)

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

int mod = 7340033;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 25;


template <class T>
void RV(vector<T> v){
    for(T &c : v) cin >> c;
}
template <class T>
void RV(vector<vector<T>> v){
    int n = v.size();
    for(vector<T> &c : v) RV(c);
}
template <class T>
vector<T> V(int n,T value = 0){
    vector<T> v(n,value);
    return v;
}
template <class T>
vector<vector<T>> V(int n,int m,T value = 0){
    vector<vector<T>> v(n,vector<T>(m,value));
    return v;
}

int pow_mod(int a,int b,int m= mod){
    long long  res = 1;
    while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}
    return res;
}
template <typename T> 
T gcd(T a,T b){
    if(b == 0) return a;return gcd(b,a%b);
}
template <typename T> 
T lcm(T a,T b){ 
    return a*b /gcd(a,b);
}
template <typename T,typename U>
T add(T a, U b){
    a = (long long)a+b;a = (a+mod)%mod;return a;
}
template <typename T,typename U>
T mul(T a, U b){
    a = ((long long)a*b)%mod;return a;
}
template <typename T>
T add(vector<T> v){
    long long sum=0; for(T x : v) sum = (sum + x)%mod;return (T)sum;
}
template <typename T> 
T mul(vector<T> v){ 
    long long  sum = 1LL;for(T x : v)sum = (sum * x)%mod;return (T)sum;
}
template <typename T>
string to_bin(T num){
    string binary = "";
    while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}
    reverse(binary.begin(), binary.end());
    return binary;
}
////////////////////////////////////////////////////


const int N = 1e5 + 5;

VI G[N],IG[N],G3[N],vis,who(N,0),x(N,0),y(N,0),dp(N,0),comp;
stack<int> st;
int n,m;

void dfs1(int s){
    vis[s] = 1;
    for(int c : G[s]){
        if(!vis[c]){
            dfs1(c);
        }
    }
    st.push(s);
}

void dfs2(int s,int w){
    vis[s] = 1;
    who[s] = w;
    comp.PB(s);
    for(int c : IG[s]){
        if(!vis[c]){
            dfs2(c,w);
        }
    }
    y[who[s]] += x[s];
}

void dfs3(int s){
    vis[s] = 1;
    dp[s] = 0;
    for(int  c: G3[s]){
        if(!vis[c]){
            dfs3(c);
        }
        dp[s] = max(dp[s],dp[c]);
    }
    dp[s] += y[s];
}

void __Solve__(){
    cin >> n >> m;
    rep(i,1,n) cin >> x[i];

    forn(i,m){
        int a,b;
        cin >> a >>b;
        G[a].PB(b);IG[b].PB(a);
    }
    vis = VI(n+1,0);
    rep(i,1,n){
        if(!vis[i]){
            dfs1(i);
        }
    }
    vis = VI(n+1,0);
    while(st.size()){
        int s = st.top();st.pop();
        if(!vis[s]){
            dfs2(s,s);
            comp.clear();
        }
    }
    rep(i,1,n){
        for(int c : G[i]){
            if(who[i] != who[c]){
                G3[who[i]].PB(who[c]);
            }
        }
    }
    int fans = 0;
    vis = VI(n+1,0);

    rep(i,1,n){
        if(!vis[i] && who[i] == i){
            dfs3(i);
            fans = max(dp[i],fans);
        }
    }
    cout << fans << endl;




}

signed main()
{
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	// cout<<fixed<<setprecision(12);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    int test_case = 1;
    // cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}