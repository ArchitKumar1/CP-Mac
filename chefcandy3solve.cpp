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


////////////////////////////////////////////////////

void pset(set<int> &s){
    for(auto x : s){
        cout << x << " ";
    }
    cout << endl;
}
const int BASE_3 = 20;
const int SUM_SQUARES_3 = BASE_3 *(BASE_3+1)/2;
const int SUM_CUBES_3 = SUM_SQUARES_3*SUM_SQUARES_3;
int min_brute3 = INT_MAX;

unordered_map<int,pair<int,int>> m3_all;
unordered_map<int,pair<int,int>> vals3;
vector<int> range_3(SUM_CUBES_3,0);

vector<int> max_brute_vals(10,INT_MAX);
unordered_map<int,pair<int,int>> m3_all_brute;
unordered_map<int,pair<int,int>> brute_vals_3;
bool prep3 = 0;

int sA,sB;

void calc3(int v ,int a ,int b,int mv){
    if(v == mv+1){
        int val = abs(a-b);
        range_3[val] = 1;
    m3_all[val] = make_pair(sA,sB);
        vals3[val] = {a,b};
    }else{
        sA ^= (1 << (v-1));
        int newA = a+v*v*v;
        int newB = b;
        calc3(v+1,newA,newB,mv);
        sA ^= (1 << (v-1));

        sB ^= (1 << (v-1));
        newA = a;
        newB = b+ v*v*v;
        calc3(v+1,newA,newB,mv);
        sB ^= (1 << (v-1));
    }  
}
void calc3_brute(int v ,int a ,int b,int mv){
    if(v == mv+1){
        int val = abs(a-b);
        if(val < min_brute3){
            m3_all_brute[mv] = {sA,sB};
            min_brute3 =  val;
            brute_vals_3[mv] = {a,b};
        }
    }else{
        sA ^= (1 << (v-1));
        int newA = a+v*v*v;
        int newB = b;
        calc3_brute(v+1,newA,newB,mv);
        sA ^= (1 << (v-1));

        sB ^= (1 << (v-1));
        newA = a;
        newB = b+ v*v*v;
        calc3_brute(v+1,newA,newB,mv);
        sB ^= (1 << (v-1));
    }  
}
void __Solve__(){
    
    int k;
    cin >> k;

    TC{
        int n;
        cin >> n;
        string fans(n,'0');
        
        //preparation
        if(prep3 == 0){
            prep3 = 1;
            sA = 0;
            sB = 0;
            calc3(1,0,0,BASE_3);
            for(int i = 1;i<=BASE_3;i++){
                sA = 0;
                sB = 0;
                min_brute3 = 1e18;
                calc3_brute(1,0,0,i);
                //trace(m3_all_brute[i]);
                //trace(brute_vals_3[i].first - brute_vals_3[i].second);
            }
        }
        if(n>BASE_3){
        
            int sa=0,sb=0;
            for(int i =n;i>BASE_3;i--){
                if(sa > sb){
                    sb += i*i*i;
                }else{
                    sa += i*i*i;
                    fans[i-1] = '1';
                }
                int mini =min(sa,sb);
                sa -= mini;
                sb -= mini;
                
            }
            int diff = abs(sa-sb);
            if(range_3[diff] == 0){
                diff += 1;
            }
            int cx = 0;
            int cy = 0;
            int Sx =m3_all[diff].first;
            int Sy =m3_all[diff].second;   

            if(sa < sb && vals3[diff].first < vals3[diff].second){
                swap(Sx,Sy);
            }
            if(sa > sb && vals3[diff].first > vals3[diff].second){
                swap(Sx,Sy);
            }
            for(int i = 1;i<=BASE_3;i++){
                if(Sx&(1 << (i-1))){
                    fans[i-1] = '1';
                    cx += i*i*i;
                }else{
                    cy += i*i*i;
                }
            }  
            for(int i = BASE_3+1;i<=n;i++){
                if(fans[i-1] == '1'){
                    cx += i*i*i;
                }else{
                    cy += i*i*i;
                }
                int mini = min(cx,cy);
                cx-=mini,cy-=mini;
            }
        // trace(cx,cy,abs(cx-cy),diff);
            cout << abs(cx-cy) << endl;
            cout <<fans << endl;
        }else{
            int cx = 0;
            int cy = 0;

            int Sx = m3_all_brute[n].first;
            int Sy = m3_all_brute[n].second;   

            int sa = brute_vals_3[n].first;
            int sb = brute_vals_3[n].second;
            
            //trace(to_bin(Sx),to_bin(Sy),Sx,Sy,sa,sb);

            for(int i = 1;i<=n;i++){
                if(Sx&(1 << (i-1))){
                    fans[i-1] = '1';
                    cx += i*i*i;
                }else{
                    cy += i*i*i;
                }
            }  
        // trace(cx,cy,abs(cx-cy),abs(sa-sb));
            cout << abs(cx-cy) << endl;
            cout <<fans << endl;
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