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
    binary = string(32-(binary.size()),'0') + binary;
    return binary;
}
////////////////////////////////////////////////////


  
void __Solve__(){
    int n,q;
    cin >> n;
    int arr[n];
    forn(i,n) cin >> arr[i],trace(to_bin(arr[i]));
    
    cin >> q;

    int dp[n+1][32];
    memset(dp,0,sizeof(dp));


    
    for(int i = 0;i<n;i++){
        for(int j = 0;j<32;j++){
            dp[i+1][j] = dp[i][j];
            if((1LL<<j)&arr[i]){
                dp[i+1][j] += 1; 
            }
        }
    }
    int cnts[n+1][32];
    memset(cnts,0,sizeof(cnts));

    for(int j = 0;j<n;j++){
        for(int i = 31;i>=0;i--){

            int k = i+1;
            int cnt = 0;
            if(((1<<i)&arr[j]) == 0){
                while(k>=0 && ((1<<k)&arr[i]) >=1){
                    cnt += 1;
                    k++;
                }
                 cnts[j+1][i] = (1LL<<(i-cnt));
            }else{
                cnts[j+1][i] = 0;
            }
            
        }
    }
    // for(int i = 1;i<=n;i++){
    //     for(int j = 0;j<32;j++){
    //         cout << cnts[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<32;j++){
            cnts[i][j] += cnts[i-1][j] ; 
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<32;j++){
            cout << cnts[i][j] << " ";
        }
        cout << endl;
    }

    while(q--){
        int l,r;
        cin >> l >> r;
        vector<int> cntsq(32,0);
        bool ok = 0;
        for(int j = 0;j<32;j++){
            cntsq[j] = dp[r][j] - dp[l-1][j];
            ok|=(cntsq[j]==(r-l+1));
        }
        //trace(cntsq);
        if(ok){
            cout << 0 << endl;
        }else{
            int ans = 1e18;
            for(int j = 0;j<32;j++){
                int cost = cnts[r][j] - cnts[l-1][j];
                ans = min(ans,cost);
            }
            cout << ans << endl;
        }
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
    //  cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}