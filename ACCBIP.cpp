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

int n,c,K;

vector<vector<int>> dp,values;
vector<int> ccost;

const int N = 3100;


int solve(int k,int i){
    if(k < 0) return -1e18;
    if(i == c){
        if(k>=0) return 0;
        else return -1e18;
    } 
    if(dp[k][i] != -1) return dp[k][i];
    int s = 0;
    int ans = -1e18;
    ans = max(ans,solve(k,i+1));
    for(int j = 0;j<values[i].size();j++){
        s+= values[i][j];
        ans = max(ans,s + solve(k-((j+1)*ccost[i]),i+1));
    }
    return dp[k][i] = ans;
}


void __Solve__(){
    cin >> n >> c >> K;
    map<int,int> m1[c];
    dp = vector<vector<int>>(N,vector<int>(N,-1));
    values = vector<vector<int>>(c);
    int totalcount = 0;
    
    for(int i =0;i<n;i++){
        int a,b,cc;
        cin >> a >> b >> cc;
        --cc;
        m1[cc][a]++;
    }
    ccost.assign(n,0);
    for(int i = 0;i<c;i++){
        cin >> ccost[i];
    }
    vector<int> all[c];
    for(int i = 0;i<c;i++){
        for(auto p : m1[i]){
            if(p.second > 0){
                all[i].push_back(p.second);
            }
        }
    }
    
    for(int i = 0;i<c;i++){
        int global_sum = 0;
        int global_sums = 0;
        for(int x : all[i]){
            global_sum += x;
            global_sums += x*x;
        }
        sort(all[i].begin(),all[i].end());
        // std::random_device rd;
        // std::mt19937 g(rd());
        // shuffle(all[i].begin(),all[i].end(),g);
        for(int j = 0;j+2<all[i].size();j++){
            global_sum -= all[i][j];
            global_sums -= (all[i][j]*all[i][j]);
            int tbr = (global_sum*global_sum - global_sums)/2; 
            for(int k = 0;k<all[i][j];k++){
                values[i].push_back(tbr);
            }
            totalcount += all[i][j]*tbr;                                                                                                                                                                                                                                                                                                                                                                                  
        }
        sort(values[i].begin(),values[i].end());
        reverse(values[i].begin(),values[i].end());      
    }
    // for(int i = 0;i<c;i++){
    //     for(auto x : all[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i = 0;i<c;i++){
    //     for(auto x : values[i]){
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }
    
    int ans = solve(K,0);
    // trace(totalcount,ans);
    
    cout << totalcount - ans << endl;
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