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
int LCA(int a,int b){
    if(depth[a] < depth[b]) swap(a,b);
    for(int i = LOGN-1;~i;i--){
        if(depth[anc[a][i]] >= depth[b]) a = anc[a][i];
    }
    if(a == b) return a;
    for(int i = LOGN-1;~i;i--){
        if(anc[a][i] != anc[b][i]) a = anc[a][i],b=anc[b][i];
    }
    return anc[a][0];
}
///////////////////////////////////////////////////////////////////////////////////

vector<int> val;
vector<int> total;
vector<int> depth;
vector<vector<int>> G;
vector<vector<int>> anc;
vector<vector<int>> dp;

void dfs(int s,int par){
    dp[s][val[s]]++;
    for(int c : G[s]){
        if(c == par) continue;

        anc[c][0] = s;
        depth[c] = depth[s] + 1;

        for(int i =1;i<=100;i++){
            dp[c][i] = dp[s][i];
        }
        dfs(c,s);        
    }
}


int LCA(int a,int b){
    if(depth[a] < depth[b]) swap(a,b);
    for(int i = LOGN-1;~i;i--){
        if(depth[anc[a][i]] >= depth[b]) a = anc[a][i];
    }
    if(a == b) return a;
    for(int i = LOGN-1;~i;i--){
        if(anc[a][i] != anc[b][i]) a = anc[a][i],b=anc[b][i];
    }
    return anc[a][0];
}

int query(int x,int y){
    int lca =LCA(x,y);
    int ans = INT_MAX ;
    // trace(lca,x,y);
    int total = 0;

    
    for(int i = 1;i<=100;i++){
        total += dp[x][i] + dp[y][i] - 2*dp[lca][i];
    }
    total += 1;
    if(total <= 100){
        vector<int> cnt(101,0);
        cnt[val[lca]]++;

        vector<int> diff;
        for(int i =1 ;i<=100;i++){
            cnt[i] += dp[x][i] + dp[y][i] - 2*dp[lca][i];
            // trace(i,dp[lca][i] ,dp[x][i] , dp[y][i],cnt[i]);
            if(cnt[i] > 1) return 0;
            if(cnt[i]) diff.push_back(i);
        }
        for(int i =0 ;i+1<diff.size();i++){
            ans = min(ans,diff[i+1]- diff[i]);
        }
        return ans;
    }else{
        return 0;
    }  
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

       
    TC{
        int n,q;
        cin >> n >> q;
        val.assign(n+1,0);
        total.assign(n+1,0);
        depth.assign(n+1,0);
        anc.assign(n+1,vector<int>(LOGN,1));
        dp.assign(n+1,vector<int>(101,0));
        G.assign(n+1,vector<int>());

        forn(i,n) cin >> val[i+1];
        forn(i,n-1) {
            int x,y;
            cin >>x >> y;
            G[x].PB(y);G[y].PB(x);
        }
        dfs(1,0);
        for(int i = 1;i<LOGN;i++){
            for(int j =1;j<=n;j++){
                anc[j][i] = anc[anc[j][i-1]][i-1];
            }
        }
        forn(i,q){
            int x,y;
            cin >> x>> y;
            cout << query(x,y) << endl;
        }

    }
    
#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}