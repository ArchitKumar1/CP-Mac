#include<bits/stdc++.h>
using namespace std;
template<class T> ostream& operator<<(ostream &os,vector<T> V){
    os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
template<class L,class R> ostream& operator<<(ostream &os,pair<L,R> P){
    return os<<"("<<P.first<<","<<P.second<<")";
}
#define TRACE
#ifdef TRACE
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

const int mod = pow(10,9)+7;
const int inf = 2e9;
const LL linf = 2e18;
const double eps = 1e-9;


////////////////////////////



void solve(){
    
    LL n,k;
    cin >>n >> k;
    LL arr[n];
    forn(i,n) cin >> arr[i];
    sort(arr,arr+n);
    LL dp[n+1];
    dp[0] = 0;

    for(LL i=1;i<=n;i++){
        dp[i] = dp[i-1] + arr[i-1];
    }

    LL fans = (LL)2e18;
    for(LL i=1;i<=n;i++){
        if(i-k>=0){
            LL diff = (LL)arr[i-1]*k - ((LL)dp[i] - dp[i-k]);
            fans = min(fans,diff);
        }
    }
    cout <<fans << endl;
}

int main(){

#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif    
    
    int t =1;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case " << "#" << i <<": ";
        solve();
    }
    return 0;

}