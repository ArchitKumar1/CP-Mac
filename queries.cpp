
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

#define ALL(value) value.begin(),value.end()
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
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}
////////////////////////////////////////////////////

struct seg_tree{
    int s,lz,right_count,left_count;
    int ss2,lazy1,lazy2;
    int child1,child2;
};


const int N = 100001;
int n,q,S_val,timer=0;
VI arr(N),brr(N),crr(N),parent(N);


seg_tree Tree[50*N];

class dsu {
    public:
    vector<int> par;
    int n;
    dsu(int _n) : n(_n) {
        par.resize(n);
        iota(par.begin(), par.end(), 0);
    } 
    inline int get(int x) {
        return (x == par[x] ? x : (par[x] = get(par[x])));
    }
    inline bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            par[x] = y;
            return true;
        }
        return false;
    }
};

dsu DS(N);


void aggregate(int index,int parent,int type){
    if(type==1){ 
        ++timer;
        int RC = Tree[parent].right_count;
        Tree[timer]=Tree[RC];
        Tree[parent].right_count=timer; 
    }
    else {
        ++timer;
        int LC = Tree[parent].left_count;
        Tree[timer]=Tree[LC];
        Tree[parent].left_count=timer; 
    }
}

void update(int index,int S,int E,int l,int r,int value)
{
    if(l==S && r==E){ Tree[index].lz+=value;  return; }
    else{  
        int mid=(S+E)/2;
        if(l>mid){
            aggregate(Tree[index].right_count,index,1);
            update(Tree[index].right_count,mid+1,E,l,r,value);
        }
        else if(r<=mid){
            aggregate(Tree[index].left_count,index,0);
            update(Tree[index].left_count,S,mid,l,r,value);
        }
        else {
            aggregate(Tree[index].right_count,index,1);
            aggregate(Tree[index].left_count,index,0);
            update(Tree[index].right_count,mid+1,E,mid+1,r,value);
            update(Tree[index].left_count,S,mid,l,mid,value);
        }
        Tree[index].s=max(Tree[Tree[index].right_count].s+Tree[Tree[index].right_count].lz,Tree[Tree[index].left_count].s+Tree[Tree[index].left_count].lz);
   }
}

int get_pos_val(int index,int S,int E,int l,int r){   
    if(index == 0) return 0;
    if(S==l && E==r) return Tree[index].s+Tree[index].lz;
    else{  
        int mid=(S+E)/2;
        if(l>mid){
             int V = get_pos_val(Tree[index].right_count,mid+1,E,l,r);
             return V +Tree[index].lz;
        }else if(r<=mid){
             int V =get_pos_val(Tree[index].left_count,S,mid,l,r);
             return V +Tree[index].lz;
        }else{
            int LC = get_pos_val(Tree[index].right_count,mid+1,E,mid+1,r)+Tree[index].lz;
            int RC = get_pos_val(Tree[index].left_count,S,mid,l,mid)+Tree[index].lz;
            return max(LC,RC); 
        }
    }
}
signed main(){
 #ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif    
    
    cin >> n >> q >> S_val;
    rep(i,n){
        cin >> arr[i];
    }
    //
    rep(i,n){
        crr[i] = arr[i];
    }
    dsu ds1(n);
    forn(i,n){
        if(i+2<n)
            ds1.merge(i,i+2);
    }
    //merged odd nodes spaced 2;

    int child;
    arr[0] = N;
    rep(i,n){  
        child = i-1;
        while(arr[child]<arr[i]){
            child=parent[child];
        }
        parent[i]=child;
    }
    rep(i,n){
        crr[i] = arr[i];
    }
    dsu ds2(n);
    forn(i,n){
        if(i+4<n)
            ds2.merge(i,i+4);
    }
    //merging even nodes spaced 4;

    rep(i,n){
        timer = timer + 1;
        brr[i]=timer;
        Tree[brr[i]]=Tree[brr[i-1]];
        update(brr[i],1,n,parent[i]+1,i,1);
    }
    
    dsu ds3(n);
    forn(i,n){
        if(i+8<n)
            ds3.merge(i,i+8);
    }
    

    int prev=0;
    forn(i,q){
        int value,position;
        cin >> value >> position;
        
        if(S_val!=0){
            value = (value+prev-1) %n +1;
            position = (position+prev-1) %n +1;
        }

        if(value > position){
            swap(value,position);
        }
        prev =  get_pos_val(brr[position],1,n,value,position);
        cout<< prev << endl;
    }
    
        
    #ifdef LOCAL
	cerr<<"Time elapsed: "<<(double)(clock()-clk)/CLOCKS_PER_SEC<<"  seconds" << "\n";
    #endif
}
