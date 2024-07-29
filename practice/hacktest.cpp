#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vstr = vector<string>;
using vpll = vector<pll>; 
 
#define tcT template<class T
#define tcTU tcT, class U
 
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)

// loops
#define FOR(i,a,b) for (ll i = (a); i < (b); ++i)
#define ROF(i,a,b) for (ll i = (b)-1; i >= (a); --i)
#define trav(a,x) for (auto& a: x)

//min heap
template<class T> using pqg = priority_queue<T,vector<T>,greater<T>>;

 
const ll MOD = 1e9+7; // 998244353;
const ll MX = 1e6+5;
const ll INF = 1e18; // not too close to LLONG_MAX
const ld PI = acos((ld)-1);
const ll dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; // for every grid problem!!
map<pll,char> dirFromDiff = {{{1,0},'R'},{{0,1},'U'},{{-1,0},'L'} , {{0,-1},'D'}};
map<char,pll> diffFromDir = {{'R',{1,0}} , {'U',{0,1}}, {'L',{-1,0}},{'D',{0,-1}}};


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> 
using oset = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

tcTU> T fstTrue(T lo, T hi, U f) {hi ++; assert(lo <= hi); while (lo < hi) {T mid = lo+(hi-lo)/2;
  f(mid) ? hi = mid : lo = mid+1; } return lo;}
tcTU> T lstTrue(T lo, T hi, U f){lo --; assert(lo <= hi);while (lo < hi) {T mid = lo+(hi-lo+1)/2;
  f(mid) ? lo = mid : hi = mid-1;} return lo;}

ll binpow(ll x,ll n){if(n==0)return 1;ll temp = binpow(x,n/2);temp  =(temp*temp)%MOD;
  if(n&1) {temp = (temp*x)%MOD;}return temp;}

bool comp(pll& a, pll& b){
  if(a.first!=b.first) return a.first<b.first;
  return a.second>b.second;
}

ll func(vpll& a, vll& temp, ll x, unordered_map<ll,ll>& mp){
  if(mp.count(x) != 0){
    return mp[x];
  }
  ll curAns = 0;
  ll idx = upper_bound(temp.begin(),temp.end(),x) - temp.begin();
  --idx;
  if(idx<0){
    mp[x]=0;
    return 0;
  }
  ll steps = 1 + (x - a[idx].first)/a[idx].second;
  curAns += 2*steps;
  curAns += func(a,temp,x-steps*a[idx].second,mp);
  mp[x] = curAns;
  return curAns;
}

void solve(){
  ll n,m; cin>>n>>m;
  vpll a(n);
  vll temp(n);
  FOR(i,0,n) cin>>a[i].first;
  FOR(i,0,n) temp[i] = a[i].first;
  FOR(i,0,n) cin>>a[i].second;
  sort(a.begin(),a.end(), comp);
  sort(temp.begin(),temp.end());
  FOR(i,0,n){
    a[i].second = a[i].first-a[i].second;
    if(i>0){
      a[i].second = min(a[i].second,a[i-1].second);
    }
  }
  vll v(m);
  FOR(i,0,m){
    cin>>v[i];
  }
  sort(v.begin(),v.end());
  unordered_map<ll,ll> mp;

  ll ans = 0;
  FOR(i,0,m){
    if(mp.count(v[i])>0){
      ans += mp[v[i]];
      continue;
    }
    ans += func(a,temp,v[i],mp);
  }
  cout<<ans<<endl;
}

int main(){
  cin.sync_with_stdio(0);	cin.tie(0);	cout.tie(0);
  ll t=1;
  FOR(i,0,t){
    solve();
  }
}
