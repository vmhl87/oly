#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<string, pair<int, int> > ship;
map<string, int> shipind;

int *root;
int *totcrew;
int *totsize;
set<string> stin;

int findroot(int x){
    while(x != root[x]){
        root[x] = root[root[x]];
        x = root[x];
    }
    return x;
}

int unitebutnot(int x, int y){
    // totcrew[root[findroot(x)]] += totcrew[root[findroot(y)]];
    // totsize[root[findroot(x)]] += totsize[root[findroot(y)]];
    // cout << findroot(x) << " " << findroot(y) << endl;
    // cout << root[findroot(x)] << " " << root[findroot(y)] << endl;
    // cout << totcrew[root[findroot(x)]] << " " << totcrew[root[findroot(y)]] << endl;
    // cout << totsize[root[findroot(x)]] << " " << totsize[root[findroot(y)]] << endl;
    totcrew[root[findroot(y)]] += totcrew[root[findroot(x)]];
    totsize[root[findroot(y)]] += totsize[root[findroot(x)]];
    root[findroot(x)] = root[findroot(y)];
    // cout << "hi" << endl;
}

void rem(string s){
    totcrew[root[findroot(shipind[s])]] -= ship[s].first;
    totsize[root[findroot(shipind[s])]] -= ship[s].second;
    stin.erase(s);
}

int main(){
    int n;
    cin >> n;

	root = new int[n+1];
	totcrew = new int[n+1];
	totsize = new int[n+1];

    for(int i = 0; i < n; i++){
        root[i] = i;
    }
    
    // cout << totcrew[0] << endl;

    for(int t = 0; t < n; t++){
        char c;
        cin >> c;
        if(c == 'u'){
            string s1, s2;
            cin >> s1 >> s2;
			if(shipind.find(s1)==shipind.end()) cout<<"uh oh!\n";
            unitebutnot(shipind[s1], shipind[s2]);
        }
        else if(c == 'a'){
            string s1, s2;
            cin >> s1 >> s2;
            if(findroot(shipind[s1]) == findroot(shipind[s2])){
                cout << "Aye" << endl;
            }
            else{
                cout << "Nay" << endl;
            }
        }
        else if(c == 'j'){
            string s;
            cin >> s;
            int i, k;
            cin >> i >> k;

            ship[s] = make_pair(i, k);
            shipind[s] = ship.size()-1;

            totcrew[root[findroot(shipind[s])]] = i;
            totsize[root[findroot(shipind[s])]] = k;

            stin.insert(s);
        }
        else if(c == 's'){
            string s;
            cin >> s;
            cout << totcrew[root[findroot(shipind[s])]] << endl;
        }
        else if(c == 'w'){
            for(string s: stin){
                cout << s << endl;
            }
        }
        else if(c == 'r'){
            string s1, s2;
            cin >> s1 >> s2;
            if(findroot(shipind[s1]) == findroot(shipind[s2])){
                cout << "Ye be a daft one! They be sailin’ under the same flag!" << endl;
            }
            else{
                if(totcrew[root[findroot(shipind[s1])]] > totcrew[root[findroot(shipind[s2])]]){
                    cout << s1 << endl;
                    rem(s2);
                }
                else if(totcrew[root[findroot(shipind[s1])]] < totcrew[root[findroot(shipind[s2])]]){
                    cout << s2 << endl;
                    rem(s1);
                }
                else{
                    if(totsize[root[findroot(shipind[s1])]] > totsize[root[findroot(shipind[s2])]]){
                        cout << s1 << endl;
                        rem(s2);
                    }
                    else if(totsize[root[findroot(shipind[s1])]] < totsize[root[findroot(shipind[s2])]]){
                        cout << s2 << endl;
                        rem(s1);
                    }
                    else{
                        cout << "Arrr, both of them pirate crews be walkin’ the plank!" << endl;
                        rem(s1);
                        rem(s2);
                    }
                }
            }
        }
    }
}
