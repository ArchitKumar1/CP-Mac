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
const long long inf = 1e9;
const long long linf = 2e18;
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
int to_int(string s){
    reverse(s.begin(), s.end());
    int pos = 0;
    int ans = 0;
    for(char c : s){
        ans += (c == '1' ? pow(2,pos) : 0);
        pos ++;
    }
    return ans;
}
///////////////////////////////////////////////////////////////////////////////////

int MODDY = 212072634227239451;
int n,m;
const int N = 1004;
int arr[N][N];

vector<int> bande ={ 107,1361, 10000019};
int M = 4;
int forbi = 1 << M;

int dp[N][N][3][3][2];


void pop(int &val,int &x,int &y,int &z){
    int ans = 0;
    x += (val%107 == 0);
    x += (val%(107*107) == 0);
    y += (val%1361 == 0);
    y += (val%(1361*1361) == 0);
    z += (val%10000019 == 0);
    if(x > 2) x = 2;
    if(y > 2) y = 2;
    if(z > 1) z = 1;
}

bool safe(int &x,int &y,int &z){
    return !(x>=2 && y>=2 && z>=1) ;
}
int solve(int i,int j,int x,int y,int z){
    if(i == n || j == m){
        return  0;
    }
    pop(arr[i][j],x,y,z);
    if(!safe(x,y,z)) return 0;
    if(i == n-1 && j == m-1){
        if(safe(x,y,z)){
            return dp[i][j][x][y][z] = 1;
        }else{
            return dp[i][j][x][y][z] = 0;
        }
    }
    
    if(dp[i][j][x][y][z] != -1){
        return dp[i][j][x][y][z];
    }
    return dp[i][j][x][y][z] = (solve(i+1,j,x,y,z) + solve(i,j+1,x,y,z))%mod;
}
signed main()
{
    FASTIO
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(12);

    
        cin >> n >> m;   
      forn(i,n)forn(j,m) cin >> arr[i][j];

        memset(dp,-1,sizeof(dp));
      cout << solve(0,0,0,0,0)%mod;
    
       
          
    
#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}