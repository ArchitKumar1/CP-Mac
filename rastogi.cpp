/* Author: Dhruv Rastogi */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(sdk) sdk.begin(),sdk.end()
#define mll map<int, int>
#define pb push_back
#define rep(i,a,b) for(int i=a;i<b;++i)
#define repd(i,a,b) for(int i=a;i>=b;--i)
#define mp make_pair
#define hell 1000000007
#define endl '\n'
#define vvll vector<vector<int> >
#define vll vector<int>
#define mint map<int,int> 
#define sz(x) (int)x.size()
#define sll set<int>
#define pll pair<int,int>
#define F first
#define S second
template <typename T> string to_bin(T num){string binary = "";while (num){binary += (num % 2 == 1 ? "1" : "0");num >>= 1;}reverse(binary.begin(), binary.end());return binary;}

const long double PI = acos(-1.0);

int a[1005];
void solve(){  
	int n,m;
	cin>>n>>m;
	rep(i,0,n) cin>>a[i];
	int cnt[52];
	memset(cnt,0,sizeof cnt);
	rep(i,0,n){
		rep(j,0,52){
			if((a[i]>>j)&1) cnt[j]++;
		}
	}	
	int ans=0; 
	rep(j,0,52){
		ans+=min(cnt[j],n-cnt[j])*(1LL<<j);
	}
	if(ans>m){
		cout<<-1<<endl;
		return;
	}
	int curans=0;
	int k=0; 
	repd(i,51,0){
		int diff=0;
		diff+=(1LL<<i)*(n-cnt[i]);
		repd(j,i-1,0){
			diff+=min(cnt[j],n-cnt[j])*(1LL<<j);
		}
		if(curans+diff<=m){
			k+=(1LL<<i);
			curans+=(1LL<<i)*(n-cnt[i]);
		}
		else{
			curans+=(1LL<<i)*cnt[i];
		}
	}
    cout << to_bin(k) << endl;
	cout<<k<<endl;
}

signed main(){
#ifdef LOCAL 
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#endif 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    rep(i,1,t+1){
    	cout<<"Case #"<<i<<": ";
        solve();
    }
    return 0;
}