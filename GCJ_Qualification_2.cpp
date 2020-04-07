#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>

using namespace std;

template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){return os<<"("<<P.first<<","<<P.second<<")";}

#ifndef TRACE
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
#define TC int t; cin >> t;while(t--)
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
const int  LOGN = 20;

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
///////////////////////////////////////////////////////////////////////////////////


void solve(){
   
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    forn(i,n) cin >> v[i].F >> v[i].S;
    vector<pair<int,int>> all;
    map<pair<int,int>,pair<int,int>> m1;
    forn(i,n){
        all.emplace_back(v[i].F,1LL);
        all.emplace_back(v[i].S,-1LL);
        m1[{v[i].F,1LL}] = {v[i].S,-1LL};
    }
    sort(ALL(all));
    int curr =0 ;
    string per ="JC";
    PII x = {0,0};
    PII y = {0,0};
    string ans = "";
    for(PII p : all){

        if(x <= p){
            x = {0,0};
        }
        if(y <= p){
            y = {0,0};
        }
            
        if(p.S == 1){   
            curr +=1;
            // trace(p,curr,"d");
            if(curr>2){
                cout << "IMPOSSIBLE" <<endl;
                return ;   
            }
            if(curr == 2 || curr == 1){
                bool ok = 0;
                if(x == make_pair(0LL,0LL)){
                    x = m1[p];
                    ans += per[0];
                    continue;
                }

                if(y == make_pair(0LL,0LL)){
                   y = m1[p];
                    ans += per[1];
                }
            }
        }else{
            curr-=1;
            
            // trace(p,curr);
        }
        
    }
    cout << ans << endl;
}


signed main()
{
    FASTIO
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    cout.precision(6);cout << fixed;

   int tt = 1;
    cin >> tt;
    int pos = 1;
   while(tt--){
       cout << "Case #" << pos++ <<": ";
       solve();
   }
#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}