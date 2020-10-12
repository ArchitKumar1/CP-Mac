
#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;

// #include "ext/pb_ds/assoc_container.hpp"
// #include "ext/pb_ds/tree_policy.hpp"
// using namespace __gnu_pbds;
// template<class T> 
// using ordered_set = tree<T, null_type,less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
// template<class key, class value, class cmp = std::less<key>>
// using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

template<class T> ostream& operator<<(ostream &os, set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os, unordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class T> ostream& operator << (ostream& os, multiset<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
//template<class T> ostream& operator<<(ostream &os, ordered_set<T> S){os << "{ ";for(auto s:S) os<<s<<" ";return os<<"}";}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {return os << "(" << P.first << "," << P.second << ")";}
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {os << "{ ";for(auto m:M) os<<"("<<m.first<<":"<<m.second<<") ";return os<<"}";}
template<class T> ostream& operator<<(ostream &os,vector<T> V){os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";}


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

//reading vectors
template <class T> void RV(vector<T> &v){for(auto &c : v) cin >> c;}
template <class T> void RV(vector<vector<T>> &v){for(auto &c : v) RV(c);}


//defines and typedefs
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define TC int testcase; cin >> testcase;while(testcase--)
#define forn(i,n) for(int i=0;i<n;i++)
#define rep(i,n) for(int i = 1;i<=n;i++)

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

//constants
int mod = 1e9+7;
const long long inf = 1e17;
const double eps = 1e-6;
const int  LOGN = 25;

// maths stuff
template <class T,class U>T pow_mod(T a,T b,int m= mod){long long  res = 1;while(b){ if(b&1) res =((long long)res*a)%m; a = ((long long)a*a)%m;b >>=1;}return res;}
template <typename T> T inv(T a){return pow_mod(a,mod-2,mod);}
template <typename T> T gcd(T a,T b){if(b == 0) return a;return gcd(b,a%b);}
template <typename T> T lcm(T a,T b){ return a*b /gcd(a,b);}
template <typename T> string to_bin(T num,int pad = 32){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());binary = string(pad-binary.size(),'0')+binary;return binary;}
////////////////////////////////////////////////////
VI arr;

int get_highest_bit(int x){
    for(int i = 30;~i;i--){
        if(x&(1<<i)){
            return (1<<i);
        }
    }
    return 0;
}

int ghb(int x){
    for(int i = 30;~i;i--){
        if(x&(1<<i)){
            return i;
        }
    }
}
map<multiset<int>,int> m1;
map<multiset<int>,int> m2;

int solve(multiset<int> vals){
    //trace(vals);
    if(vals.size() == 1){
        //trace(*vals.begin());
        return *vals.begin();
    }
    if(m2[vals] != 0){
        return m1[vals];
    }
    int ans = INT_MAX;
    vector<int> vvals(ALL(vals));
    int sz= vals.size();
    for(int i =0 ;i<sz;i++){
        for(int j = i+1;j<sz;j++){
            vals.erase(vals.find(vvals[i]));
            vals.erase(vals.find(vvals[j]));
            int Xor = get_highest_bit(vvals[i] ^ vvals[j]);
            vals.insert(Xor);
            
            ans = min(ans,solve(vals));

            vals.insert(vvals[i]);
            vals.insert(vvals[j]);
            vals.erase(vals.find(Xor));
        }
    }
    m2[vals] = 1;
    return m1[vals] = ans;

}


int solve2(int i,int j){
    if(i == j) return arr[i];
    int tans = 0;
    int mb = 0;
    int vis = 0;
    for(int k= i;k<=j;k++){
        vis |=vis;
        tans ^= arr[k];
        mb = ghb(arr[k]);
    }
    return tans&(1<<mb);
    // for(int i = 31;~i;i--){
    //     if(vis&(1<<i)){
    //         if(tans&(1<<i)){
    //             return 1<<i;
    //         }
    //     }else{
            
    //     }
    // }
}
void __Solve__(){
    
    int n;
    cin >> n;
    arr = VI(n);
    RV(arr);
    int fans = 0;
    int fans2 = 0;

    forn(i,n){
        multiset<int> ms;
        forn(j,n){
            if(j>=i){
                ms.insert(arr[j]);
                m1.clear();
                m2.clear();
                
                int x = solve(ms);
                int y = solve2(i,j);
                fans += x;
                fans2 += y;
                for(auto p: ms){
                     trace(to_bin(p,7),p);
                }
                trace(x,y);
            }
        }
    }
    
    cout << fans << endl;
    cout << fans2 << endl;

}

signed main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	cout<<fixed<<setprecision(12);
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    int test_case = 1;
   // cin >> test_case;
    forn(i,test_case){
        //cout << "Case #" << i+1<<": ";
        __Solve__();
    }
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
}