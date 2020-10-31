



#pragma GCC optimize("O3")
//#pragma comment(linker, "/stack:200000000")
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

VI ans;

void dfs(int s,int par,int val){
    ans[s] = val;
    for(int c :G[s]){
        if(c == par) continue;
        dfs(c,s,val ==1 ? 2 : 1);
    }
}
  
void __Solve__(){
     
    
     
    int d;
    cin >> d;

    if(d == 0){
        cout << 1 << endl;
        cout << "1" << endl;
        return;
    }
    if(d == 1){
        cout << 2 << endl;
        cout << "3 2" << endl;
        return;
    }
    vector<int> ans;

    int X= 3e4;
    int q = d/X;
    int r = d%X;

    forn(i,q){
        ans.push_back(2*X);
        ans.push_back(3*X);
        ans.push_back(1);
    }
    if(r > 0){
        ans.push_back(2*r);
        ans.push_back(3*r);
        ans.push_back(1);
    }


    if(ans.size() <=1e5){
        cout << ans.size() << endl;
        for(int c : ans){
            cout <<c << " ";
        }
         cout << endl;
    }
    else{
        vector<int> newans;
        newans.push_back(2*X);
        newans.push_back(3*X);
        newans.push_back(2*X);
        newans.push_back(1);
        for(int i = 9;i<(int)ans.size();i++){
            newans.push_back(ans[i]);
        }
        cout << newans.size() << endl;
        for(int c : newans){
            cout <<c << " ";
        }
        cout << endl;
    
    }
    
    
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
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}