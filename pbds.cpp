#pragma GCC optimize("O3")
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



const int N = 4;
vector<int> fact(N,1);

void pre(){
    for(int i = 1;i<N;i++){
        fact[i] = i*fact[i-1]%mod;
    }
}

int inv(int x){
    return pow_mod(x,mod-2,mod);
}
int upd(int c,int num){
    int ans = pow_mod(c+1,num,mod)*inv(pow_mod(c,num,mod))%mod;
    return ans;
}

int ncr(int n,int r){
    fact[n] * inv(fact[n-r]) %mod * inv(fact[r]) %mod;
}
void __Solve__(){
    int n;
    cin >> n;
    int arr[n];
    forn(i,n) cin >> arr[i];
    vector<int> cnt(n+1,0);
    forn(i,n) cnt[arr[i]]++;
    vector<vector<int>> v(N);
    for(int i =1;i<=n;i++){
        for(int c = 1;c<=cnt[i];c++){
            v[c].push_back(i);
        }
    }
    for(int i = 0;i<N;i++){
        sort(v[i].begin(),v[i].end());
    }
    
    
    int back = 1;

    vector<int> fans(n+1,0);
    int backprep = 1;
    int forwardprep = 1;
    for(int i =1;i<N;i++){
        trace(i,v[i]);
         for(int j = 0;j<v[i].size();j++){
            int ele = v[i][j];
            int tcnt = cnt[ele];
            forwardprep*= ncr(tcnt,i) * inv(tcnt,i-1)%mod * (i+1) * inv(i) %mod;
        }
        for(int j = 0;j<v[i].size();j++){
            int ele = v[i][j];
            int tcnt = cnt[ele];

            forwardprep*= (inv(ncr(tcnt,i) * inv(i+1)) %mod;
              
            trace(rcnt,back,"BEFORE");
            int tans2 = pow_mod(i+1,rcnt,mod)*back%mod;
            trace(rcnt,back,tans2,"AFTER");

            
            fans[v[i][j]]+=tans2;
        }
 
    //    int x = upd(i,v[i].size());
    //    trace(x);
    //     back = back* x%mod;
    //     trace(back);


    }
    for(int  i=1;i<=n;i++){
        cout << fans[i] << " ";
    }
    cout << endl;

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
    pre();
    int test_case = 1;
    cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}