#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
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

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)

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

int mod = pow(10,9) +7;
const long long inf = 2e18;
const double eps = 1e-6;
const int  LOGN = 25;

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
/////////////////////////////////////////
//reading
// template <class T>
// void RV(vector<T> v){
//     for(T &c : v) cin >> c;
// }
// template <class T>
// void RV(vector<vector<T>> v){
//     int n = v.size();
//     vector<vector<T>> v(n,vector<T>(m));
//     for(vector<T> &c : v) RV(c);
// }
// //getting
// template <class T>
// vector<T> GV(int n,T value = 0){
//     vector<T> v(n,value);
//     return v;
// }
// template <class T>
// vector<vector<T>> GV(int n,int m,T value = 0){
//     vector<vector<T>> v(n,vector<T>(m,value));
//     return v;
// }
///////////////////////////////////////////////////////////////////////////////////

const int N  = 2.1e5;

vector<int> G[N];

int dp[N],parent[N];
int in[N];

int n,m;


void dfs(int s,int par){
    
    if(dp[par] + 1 > dp[s]){
        dp[s] = dp[par] + 1;
        parent[s] = par;
    }
    if(in[s] == 0){
        for(int c : G[s]){
            in[c]--;
            dfs(c,s);
        }
    }
    
}
signed main()
{
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	// cout<<fixed<<setprecision(12);

    cin >> n >> m;
    forn(i,m){
        int a,b;
        cin >> a >> b;
        G[a].PB(b);
        in[b]++;
    }

    dfs(1,0);

    cout << dp[n] << endl;
    vector<int> ans;
    for(int x = n;x != 1;x = parent[x]){
        ans.push_back(x);
    }
    cout << "1 ";
    reverse(ALL(ans));
    for(int c : ans ) cout << c  << " ";
    cout << endl;

    
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}