#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    int a[200001];
    set<int> s[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i]--;
        s[a[i]].insert(i);
    }

    int k = 0;
    vector<pair<int, pair<int, int> > > res;
    for(int i = 0; i < n; i++){
        if(s[i].size() > 1){
            if(s[i].find(i) != s[i].end()){
                for(int j: s[i]){
                    if(j != i){
                        a[j] = -1;
                        res.push_back(make_pair(2, make_pair(i, j)));
                        k++;
                    }
                }
				s[i].clear();
				s[i].insert(i);
            }
            else{
                int l = -1;
                for(int j: s[i]){
                    // cout << j << endl;
                    if(s[j].size() >= 1){
                        l = j;
                    }
                }
                if(l == -1){
                    for(int j: s[i]){
                        l = j;
                        break;
                    }
                }
                for(int j: s[i]){
                    if(j != l){
                        a[j] = -1;
                        res.push_back(make_pair(2, make_pair(l, j)));
                        k++;
                    }
                }
				s[i].clear();
				s[i].insert(l);
            }
        }
    }

    // for(int i = 0; i < n; i++){
    //     cout << a[i] << " ";
    // }
    // cout << endl;

	for(int i=0; i<n; ++i)
		if(s[i].size())
			if((*s[i].begin()) != i){
				int b = *s[i].begin();
				res.push_back(make_pair(1, make_pair(i, b)));
				s[a[i]].clear();
				s[a[i]].insert(b);
				a[b] = a[i];
			}

    cout << res.size() << endl;
    for(pair<int, pair<int, int> > p: res){
        cout << p.first << " " << p.second.first + 1 << " " << p.second.second + 1 << endl;
    }
    // for(int i = 0; i < n; i++){
    //     cout << a[i] << " ";
    // }
    // cout << endl;
}
