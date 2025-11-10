#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define int long long

int MOD = 1000000007;

int pow(int x, int y) {
    if(x == 0) return 0;
    if(y == 0) return 1;
    if(y % 2 == 0) {
        return (pow(x, y/2) % MOD * pow(x, y/2) % MOD) % MOD;
    }
    return x * pow(x, y-1) % MOD;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
while(t--) {
    int n, m;
    cin >> n >> m;
    string bag;
    cin >> bag;
    map<int, int> basicFries;
    map<int, int> basicPortals;
    int depth = 0;
    //get the basic fry info and allat
    for(int i = 0; i < n; ++i) {
        if(bag[i] == '(') depth++;
        else if(bag[i] == ')') depth--;
        else if(bag[i] == '|') {
            if(depth > m) continue;
            basicFries[depth] ++;
            basicFries[depth] %= MOD;
        }
        else if(bag[i] == 'O') {
            if(depth > m) continue;
            basicPortals[depth]++;
            basicPortals[depth] %= MOD;
        }
    }
    int bigans = 0;
    //loop over every starter fry, every starter portal
    for(auto fry = basicFries.begin(); fry != basicFries.end(); ++fry) {
        int fd = (*fry).first % MOD;
        int fv = (*fry).second % MOD;
        bigans += fv % MOD;
        bigans %= MOD;
        //cout << "TEST" << bigans << endl;
        for(auto port = basicPortals.begin(); port != basicPortals.end(); ++port) {
            // (*fry).first is our depth
            // (*port).first is our depth incrementer
            
            int pd = (*port).first % MOD;
            int pv = (*port).second % MOD;
            if(pv == 1) {
                int en = (m-fd)/pd % MOD;
                bigans += en*fv % MOD;
                bigans %= MOD;
            }
            else {
                //for n such that fd + n*pd <= m
                // n = (m-fd)/pd, we want n+1
                int en = ((m-fd)/pd+1) % MOD;
                //now just plug into equation
                bigans += ((fv*((pow(pv, en)-1)))% MOD /(pv-1))-fv % MOD;
                bigans %= MOD;
            }
        }
    }

    cout << bigans << '\n';
}
}