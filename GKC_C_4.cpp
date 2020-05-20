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

double pi = 3.141592653589793238462643383279;


int n,q;
vector<int> arr,tree1,tree2;


void build1(int s,int e,int index){
    if(s == e){
        tree1[index] = arr[s];
        return;
    }
    int m = (s+e)/2;
    build1(s,m,2*index);
    build1(m+1,e,2*index+1);
    tree1[index] = tree1[2*index] + tree1[2*index+1];
}

void build2(int s,int e,int index){
    if(s == e){
        tree2[index] = (s+1)*arr[s];
        return;
    }
    int m = (s+e)/2;
    build2(s,m,2*index);
    build2(m+1,e,2*index+1);
    tree2[index] = tree2[2*index] + tree2[2*index+1];
}

int query1(int s,int e,int l,int r,int index){
    if(s > r || e < l) return 0;
    if( s >=l && e <= r) return tree1[index];

    int m = (s+e)/2;
    return query1(s,m,l,r,2*index) + query1(m+1,s,l,r,2*index+1);

}
int query2(int s,int e,int l,int r,int index){
    if(s > r || e < l) return 0;
    if( s >=l && e <= r) return tree2[index];

    int m = (s+e)/2;
    return query2(s,m,l,r,2*index) + query2(m+1,s,l,r,2*index+1);
}
void update(int s,int e,int pos,int val,int index){
    if(s > pos || e < pos) return;
    if(s == e){
        tree1[index] = val;
        tree2[index] = (s+1)*val;
        arr[pos] = val;
        return;
    }
    int m = (s+e)/2;
    tree1[index] = tree1[2*index] + tree1[2*index+1];
    tree2[index] = tree2[2*index] + tree2[2*index+1];
}
void __solve(){
    cin >> n >> q;
    arr.resize(n);
    forn(i,n) cin >> arr[i];
    tree1.assign(4*n,0);
    tree2.assign(4*n,0);
    int s = 0, e = 0, index= 0;

    build1(s,e,index);
    build2(s,e,index);

    while(q--){
        char c ;
        cin >> c;
        
        if(c == 'Q'){
            int l,r;
            cin >> l >> r;
            l--;r--;
            int val = query2(s,e,l,r,index) - l*query1(s,e,l,r,index);
            cout << val << endl;
        }else{
            int pos,val;
            cin >> pos >> val;
            pos--;
            update(s,e,pos,val,index);
        }
        
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
      
    int t;
    cin >> t;
    forn(tt,t){
        cout << "Case #"<<tt+1<<": "; 
        __solve();
    } 
#ifndef ONLINE_JUDGE
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}