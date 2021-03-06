#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>

using namespace std;

template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){return os<<"("<<P.first<<","<<P.second<<")";}

#ifndef AR
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
#define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"

typedef pair<int,int>PII;
typedef vector<PII> VPII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VLL;
typedef pair<LL,LL>PLL;
typedef vector<PLL> VPLL;
auto clk=clock();

int mod = pow(10,9) +7;
const int inf = 2e9;
const LL linf = 2e18;
const double eps = 1e-9;
const int  LOGN = 20;

int pow_mod(int a,int b,int m= mod){
    LL res = 1;
    while(b){ if(b&1) res =((LL)res*a)%m; a = ((LL)a*a)%m;b >>=1;}
    return res;
}
template <typename T> 
T gcd(T a,T b){
    if(b == 0) return a;return gcd(b,a%b);
}
template <typename T,typename U>
T add(T a, U b){
    a = (LL)a+b;a = (a+mod)%mod;return a;
}
template <typename T,typename U>
T mul(T a, U b){
    a = ((LL)a*b)%mod;return a;
}
template <typename T>
T add(vector<T> v){
    LL sum=0; for(T x : v) sum = (sum + x)%mod;return (T)sum;
}
template <typename T> 
T mul(vector<T> v){ 
    LL sum = 1LL;for(T x : v)sum = (sum * x)%mod;return (T)sum;
}
template <typename T>
string to_bin(T num){
    string binary = "";
    while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}
    reverse(binary.begin(), binary.end());
    return binary;
}
///////////////////////////////////////////////////////////////////////////////////

 
const int N = 10005;

vector<pair<LL,LL>> fact[N];
vector<LL> maxfact(N,0);



int main()
{
    FASTIO
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif
    
    for(int i = 1;i<N;i++){
        int y = i;
        for(int j = 2;j*j<=N;j++){
            int cnt =0 ;
            while(y%j == 0){
                cnt++;
                y/=j;
            }
            if(cnt)fact[i].emplace_back(j,cnt);
        }
        if(y!=1){
            fact[i].emplace_back(y,1);
        }
    }
    


    TC{
        maxfact.assign(N,0);
        int n;
        cin >> n;
        int m;
        cin >> m;
        int arr[n];
        forn(i,n) cin >> arr[i];

        LL maxans = 1;
        LL val = 1;
        for(int x : arr){
            for(auto y: fact[x]){
                maxfact[y.first]= max(maxfact[y.first],y.second);
            }
        }

        for(int i = 1;i<=m;i++){
            LL tans = 1;
            for(auto x: fact[i]){
                // trace(x,maxfact[x.first]);
                tans*= x.first*max(x.second - maxfact[x.first],0LL);
            }
            if(tans > maxans){
                maxans = tans;
                val = i;
            }
        }
        cout << val << endl;
    }

#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}