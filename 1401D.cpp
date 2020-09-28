
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

int mod = 1e9+7;
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


VVI G;
VPII E;
VI primes,in,np;

int n;
int m;

void dfs(int s,int par){
    in[s] = 1;
    for(int c : G[s]){
        if(c == par )continue;
        dfs(c,s);
        in[s] += in[c];
    }
}



void __Solve__(){

    
    cin >> n;
    G = vector<vector<int>>(n+1);
    E.clear();
    primes.clear();
    in = VI(n+1,0);

    forn(i,n-1){
        int u,v;
        cin >> u >> v;
        G[u].PB(v);G[v].PB(u);
        E.PB({u,v});
    }
    int m;
    cin >> m;
    forn(i,m){
        int p;
        cin >> p;
        primes.push_back(p);
    }
    sort(ALL(primes));
    reverse(ALL(primes));

    np =VI();
    if(m<=n-1){
        np =primes;
    }else{
        int beg = 1;
        int diff = m - n+2;
        for(int i=0;i<diff;i++){
            beg*=primes[i];
            beg%=mod;
        }
        np.push_back(beg);
        for(int i=diff;i<m;i++){
            np.push_back(primes[i]);
        }
    }
    
    

    dfs(1,0);

    VI prods;

    forn(i,n-1){
        int x = E[i].first;
        int y = E[i].second;
        if(in[x] > in[y]) swap(x,y);
        prods.PB(in[x] * (n-in[x]));
    }
    sort(ALL(prods));
    reverse(ALL(prods));

    int fans =0 ;
    forn(i,n-1){
        int x = (i>=np.size() ? 1 : np[i]);
        int y = prods[i] %mod;
        fans += (x*y %mod);
        fans%=mod;
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
    cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}