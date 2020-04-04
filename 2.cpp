#include<bits/stdc++.h>
using namespace std;
template<class T> ostream& operator<<(ostream &os,vector<T> V){
    os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
    return os<<"("<<P.first<<","<<P.second<<")";
}

const int mod = pow(10,9)+7;
const int inf = 2e9;
const long long linf = 2e18;
const double eps = 1e-9;

#define ALL(x) x.begin(),x.end()
#define LL long long int
#define PB push_back
#define EB emplace_back
#define F first
#define S second
#define endl "\n"
#define l() cout << endl;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define TC int t; cin >> t;while(t--)
#define forn(i,n) for(int i=0;i<n;i++)

template<typename T,typename U>void mmul(T &a,U b){a =((long long int)(a*b)%mod);}
template<typename T,typename U>void madd(T &a,U b){a =((long long int)(a+b)%mod);}
template<typename T>T gcd(T a,T b){if(b == 0) return a;else return gcd(b,a%b);}


////////////////////////////


const int N  = 1234;
int milk[N];
int apples[N];
int dp[N][N];

int n;
map<pair<LL,int>,int> m1;

LL solve(LL energy,int pos,int total){
  //  cout << energy <<  " " << pos << " " << total << endl;
    if(m1[{energy,pos}] > 0) return m1[{energy,pos}]; 
    if(energy < 0) return 0;
    if(pos == n) return total;
    int& ans = m1[{energy,pos}];
    ans = max(solve(energy-1,pos+1,total+ apples[pos]),
                solve(energy+milk[pos],pos+1,total));
    return ans;
    
}
int main(){
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
   
    TC{
        cin >> n;
        LL p;
        cin >> p;

        forn(i,n){
            cin >> milk[i];
        }
        forn(i,n)  cin >> apples[i];

        cout << solve(p-1,0,0) << endl;
        m1.clear();
    }
    

    return 0;  
}
