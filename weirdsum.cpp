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


const int N = 6e5;

int F[N][2];

void add(int i,int x,int c){
    i++;
    for(;i<N;i+=(i&-i)){
        F[i][c] += x;
    }
}

int get(int i,int c){
    i++;
    int ans = 0;
    while(i>0){
        ans += F[i][c];
        i-=(i&-i);
    }
    return ans;
}


void __Solve__(){
    int n;
    cin >> n;
    int arr[n];
    forn(i,n) cin >> arr[i];
    vector<int> cnt(n+1,0);
    forn(i,n) cnt[arr[i]]++;
    vector<pair<int,int>> v;
    for(int i =1;i<=n;i++){
        if(cnt[i] > 0){
            v.emplace_back(cnt[i],i);
        }
    }
    sort(v.begin(),v.end());
    vector<int> fans(n+1,0);

    vector<int> left(n+1,0);
    vector<int> right(n+1,0);


    int m = v.size();
    for(auto x : v){
        trace(x);
    }
    for(int i = 0;i<m;i++){
        int curr = v[i].second;
        left[curr] = get(curr,0);
        add(curr,1,0);
    }
    for(int i = m-1;~i;i--){
        int curr = v[i].second;
        right[curr] = get(curr,1);
        add(curr,1,1);
    }
    
    vector<int> lcounts(n+1,0);
    for(int i = 0;i<m;i++){
        int max_cnt = v[i].first;
        int ele = v[i].second;

        int tans = 0;

        int rtotal = m-i+1;
        int rsmall = right[ele];
        int rbig = rtotal-rsmall;

        int ltotal = i;
        int lsmall = left[ele];
        int lbig = ltotal-lsmall;
    

        for(int j = 1;j<=max_cnt;j++){
            int tans1 =  calc1(j,rbig,rsmall);
            int tans2 = ?

            tans += tans1*tans2;

        }

        //calc left;

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
    // cin >> test_case;
    while(test_case--){
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}