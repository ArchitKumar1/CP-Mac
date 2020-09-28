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
    return binary;
}
////////////////////////////////////////////////////

void pset(set<int> &s){
    for(auto x : s){
        cout << x << " ";
    }
    cout << endl;
}
const int BASE_2 = 10;
const int SUM_SQUARES_2 = BASE_2 *(BASE_2+1) * (2*BASE_2+1)/6 + 5;

map<int,pair<set<int>,set<int>>> m2_all;
int min_brute2 = INT_MAX;
pair<set<int>,set<int>> brutepair;
pair<int,int> bruteval;

map<int,pair<int,int>> vals;
vector<int> range(SUM_SQUARES_2,0);
int p = 2;


void calc2(int v ,set<int> sa,set<int> sb,int a ,int b,int mv){
    if(v == mv+1){
        int val = abs(a-b);
        range[val] = 1;
        m2_all[val] = make_pair(sa,sb);
        vals[val] = {a,b};
    }else{
        sa.insert(pow(v,p));
        calc2(v+1,sa,sb,a+pow(v,p),b,mv);
        sa.erase(pow(v,p));

        sb.insert(pow(v,p));
        calc2(v+1,sa,sb,a,b+pow(v,p),mv);
        sb.erase(pow(v,p));
    }  
}


void calc2brute(int v ,set<int> sa,set<int> sb,int a ,int b,int mv){
    if(v == mv+1){
        int val = abs(a-b);
        if(val < min_brute2){
            brutepair.first = sa;
            brutepair.second = sb;
            min_brute2 =  val;
        }
        m2_all[val] = make_pair(sa,sb);
        vals[val] = {a,b};
    }else{
        sa.insert(pow(v,p));
        calc2brute(v+1,sa,sb,a+pow(v,p),b,mv);
        sa.erase(pow(v,p));

        sb.insert(pow(v,p));
        calc2brute(v+1,sa,sb,a,b+pow(v,p),mv);
        sb.erase(pow(v,p));
    }  
}

void __Solve__(){
    
    int n;
    cin >> n;
    string fans(n,'0');
    
    
    if(n>10){
        set<int> x,y;
        calc2(1,x,y,0,0,10);
        int sa=0,sb=0;
        for(int i =n;i>10;i--){
            if(sa > sb){
                sb += i*i;
            }else{
                sa += i*i;
                fans[i-1] = '1';
            }
            int mini =min(sa,sb);
            sa -= mini;
            sb -= mini;
            
        }
        int diff = abs(sa-sb);
        if(range[diff] == 0){
            diff += 1;
        }
        int cx = 0;
        int cy = 0;
        set<int> Sx = m2_all[diff].first;
        set<int> Sy = m2_all[diff].second;

        if(sa < sb && vals[diff].first < vals[diff].second){
            swap(Sx,Sy);
        }
        if(sa > sb && vals[diff].first > vals[diff].second){
            swap(Sx,Sy);
        }
        for(int i = 1;i<=10;i++){
            
            if(Sx.find(i*i)!=Sx.end()){
                fans[i-1] = '1';
                cx += i*i;
            }else{
                cy += i*i;
            }
        }  
        for(int i = 11;i<=n;i++){
            if(fans[i-1] == '1'){
                cx += i*i;
            }else{
                cy += i*i;
            }
        }
        //trace(cx,cy,abs(cx-cy),sa,sb,diff);
        cout << abs(cx-cy) << endl;
        cout <<fans << endl;
        // pset(Sx);
        // pset(Sy);
    }else{
        set<int> x,y;
        calc2brute(1,x,y,0,0,n);
        min_brute2 = INT_MAX;

        set<int> Sx = brutepair.first;
        set<int> Sy = brutepair.second;
        int cx = 0;
        int cy = 0;

        for(int i = 1;i<=n;i++){
            
            if(Sx.find(i*i)!=Sx.end()){
                fans[i-1] = '1';
                cx += i*i;
            }else{
                cy += i*i;
            }
        }  
        for(int i = 11;i<=n;i++){
            if(fans[i-1] == '1'){
                cx += i*i;
            }else{
                cy += i*i;
            }
        }
        //trace(cx,cy,abs(cx-cy));
        cout << abs(cx-cy) << endl;
        cout <<fans << endl;
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