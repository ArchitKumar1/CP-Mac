#pragma GCC optimize("O3")
#pragma comment(linker, "/stack:200000000")
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
int a,b,c;
int d,e,f;


int ans  = 3;


pair<int,int> multi2(int u,int v,int w,int x){
    pair<int,int> p = {0,0};
    if(w == 0 || x == 0) {
        return p;
    }
    if(u == 0 && v == 0) {
         p.first = 1,p.second = 0 ;
         return p;
    }

    int r1 = u%w;
    int r2 = v%x;

    if(r1 == 0 && r2 == 0){
        int q1 = u/w;
        int q2 = v/x;
        trace(u,v,w,x,r1,r2,q1,q2);
        if(q1 == q2){
            
            p.first = 1;
            p.second = q1;
        }else{
            return p;
        }
    }
    return p;
}

pair<int,int> add2(int u,int v,int w,int x){
    pair<int,int> ans;
    ans.first = ((u-w) == (v-x));
    ans.second = u-w;
    return ans;
}

pair<int,int> multi1(int u,int v){
    pair<int,int> ans = {0,0};
    if(v == 0) return ans;
    if(u%v != 0){
        ans.first = 1;
        ans.second = u/v;
    }
    return ans;
}

int collinear(int x1, int y1, int x2,  
               int y2, int x3, int y3) 
{ 
    int a = x1 * (y2 - y3) +  
            x2 * (y3 - y1) +  
            x3 * (y1 - y2); 
  
    return a == 0;
} 

void solve(){
    
    cin >> a >> b >> c;
    vector<int> A = {a,b,c};
    
    cin >> d >> e >> f;
    vector<int> D = {d,e,f};

    vector<pair<int,int>> BASE;
    for(int i = 0;i<3;i++){
        BASE.push_back({A[i],D[i]});
    }

    int diff[3] = {0};
    for(int i=0;i<3;i++){
        diff[i] = D[i] - A[i];
    }

    //pure addition
    set<int> diffs;
    for(int i=0;i<3;i++){
        if(diff[i]!=0)diffs.insert(diff[i]);
    }
   
    trace((int)diffs.size());
    ans = min(ans,(int)diffs.size());
    

    //pure multiplication
    set<int> mults;
    int safe = 1;
    int extra = 0;
    for(int i=0;i<3;i++){
        if(A[i] == 0) extra++;
        else{
            if(D[i]%A[i] != 0) safe = 0;
            if(D[i]!= A[i])
                mults.insert(D[i]/A[i]);
        }
    }
    if(safe){
        trace(extra + (int)mults.size());
        ans = min(ans,extra + (int)mults.size());
    }

    vector<pair<int,int>> curr = BASE;
    sort(ALL(curr));

    do{
        trace(curr[0],curr[1],curr[2]);
        int A = curr[0].first;
        int D = curr[0].second;

        int B = curr[1].first;
        int E = curr[1].second;

        int C = curr[2].first;
        int F = curr[2].second;

        //// 2 multi 2 add 1 common 
        int diffy = D-A;
        int nE = E - diffy;
        pair<int,int> p1 = multi2(nE,F,B,C);
        if(p1.first == 1){
            trace("2 multi 2 add 1 common " , p1);
            ans = min(ans,2LL);
        }
        ////

        //// 2 add 2 mutli 1 common 

        p1 = multi2(D,E,A,B);
        trace(D,E,A,B);
        if(p1.first == 1){
            
            nE = E/p1.second;
            if(add2(nE,F,B,C).first == 1){
                trace("2 add 2 multi 1 common " , p1);
                ans = min(ans,2LL);
            }
        }
        /////

        //3 multi 2 add
         p1 = multi1(D,A);
        if(p1.first == 1){
            int nB = B*p1.second;
            int nC = C*p1.second;
            if(add2(E,F,nB,nC).first == 1){
                trace("3 multi 2 add " , p1);
                ans = min(ans,2LL);
            }
        }
        //

        // 3 add 2 multi
        diffy = D-A;
        int nB= B +  diffy;
        int nC = C + diffy;
        p1 = multi2(E,F,nB,nC);
        if(p1.first == 1){
            trace(p1,"3 add 2,multi");
            ans = min(ans,2LL);
        }
        //

        // 2 multi 3 add
        
        diffy = D-A;
        nE = E - diffy;
        int nF = F - diffy;
        if(multi2(nE,nF,B,C).first == 1){
            trace("2 multi 3,add");
            ans = min(ans,2LL);
        }
        //

        //2 add 3 multi

        p1 = multi1(D,A);
        if(p1.first == 1 && p1.second != 0){
            int nE = E /p1.second;
            int nF = F /p1.second;
            if(add2(nE,nF,B,C).first == 1){
                trace("2 add 3,multi");
                ans = min(ans,2LL);
            }
        }
        //

        // 3multi 3 add


        //3 add 3 multi


    }while(next_permutation(ALL(curr)));

    cout << ans << endl;

    // 1 7 10  *5 -6

    // -1 29 44
    //          *-5 +6

    // 1 -29 -44
    

    
}

int32_t main()
{
    FASTIO
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 #endif 
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());
	// cout<<fixed<<setprecision(12);

   
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    
#ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
#endif
    
}