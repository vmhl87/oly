/* actual solution code written by antares
 * modified by myself to use my pseudo-hashmap in order to test
 * speed - ends up ~2x faster than gp hash table */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;

using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ~9 * 10 ^ 18
const ll LL_MAX = 9'223'372'036'854'775'807;

// ~2 * 10 ^ 9
const int MAX = 2'147'483'647;
// const ll MOD = 1'000'000'000 + 7;
const ll MOD = 998'244'353;


ll splitmix64(ll i){
	uint64_t z = (i += (uint64_t) 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}


template <int S>
struct not_hashmap{
	ll k[1<<S] = {}, v[1<<S] = {};
	bool u[1<<S] = {}, d[1<<S];
	int s, c = 0;

	not_hashmap(){
		s = (1<<S) - 1;
	}

	inline int find(ll i){
		//int I = i & s;
		int I = splitmix64(i) & s;
		while(u[I] & k[I] != i)
			I = (I+1) & s;
		return I;
	}

	void set(ll i, ll j){
		int I = find(i);
		if(!u[I] || d[I]) ++c;
		u[I] = 1, d[I] = 0,
			k[I] = i, v[I] = j;
	}

	int get(ll i){
		int I = find(i);
		if(u[I] && !d[I] && k[I] == i)
			return v[I];
		else return 0;
	}

	bool has(int i){
		int I = find(i);
		return u[I] && !d[I] && k[I] == i;
	}

	void erase(int i){
		int I = find(i);
		if(u[I] && !d[I] && k[I] == i)
			--c, d[I] = 1;
	}

	int size(){
		return c;
	}
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];


    // [i][r] s.t. we fix i and iterate r
    ll cnt[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cnt[i][j] = 0;
    }

    for (int i = 0; i < n; i++) {
        //gp_hash_table<ll, ll> ma({}, {}, {}, {}, {1 << 13});
		not_hashmap<13> ma;
        ll target = -a[i];
        ll tot = 0;
        for (int j = i + 1; j < n; j++) {
            ll need = target - a[j];
            //tot += ma[need];
			tot += ma.get(need);
            //ma[a[j]]++;
			ma.set(a[j], ma.get(a[j])+1);

            cnt[i][j] = tot;

            // cout << i << " " << j << " " << tot << endl;
        }
    }

    for (int j = 0; j < n; j++) {
        ll curr = 0;
        for (int i = 0; i < n; i++) {
            curr += cnt[i][j];
            cnt[i][j] = curr;
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        ll ans = cnt[r][r];
        if (l > 0) ans -= cnt[l - 1][r];

        cout << ans << "\n";
    }
}

void multi_solve() {
    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        solve();
    }
}

int main() {


    /*
     * FAST IO
     * Remember to remove for interactive problems!!!
     * https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
     */

    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    // solve();
}
