// technically i could use bits/stdc++.h but that only works on some compilers
#include <iostream>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

int dirs[8][2] = {
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1},
        {-1, 0},
        {-1, 1}
};

//  stores a path - x,y coordinates of its endpoint and \
    its length and direction and if it has turned       \
    i think the proper way to declare a c++ struct is   \
    different but this works and is pretty clean so idk
typedef struct{
    int x;
    int y;
    int len = 1;
    int dir = -1; // default value
    bool turned = false;
} path;

bool in_bounds(path p, int d, int r, int c) {
    if(p.x+dirs[d][0]<0 || p.y+dirs[d][1]<0) return false;
    if(p.x+dirs[d][0]>=r || p.y+dirs[d][1]>=c) return false;
    return true;
}

//  checks if two directions are either the same or turned 90 deg \
    (cleaner than the abs(abs()) mess)
bool dirs_correct(int a, int b) {
    if(a==b) return true;
    int offset = a-b;
    if(offset==2) return true;
    if(offset==-2) return true;
    if(offset==6) return true;
    if(offset==-6) return true;
    return false;
}

//  helper function to calculate the next endpoint of a path \
    so that it can be appended to the queue (bfs)
path move(path p, int d) {
    path tmp;
    tmp.x = p.x + dirs[d][0];
    tmp.y = p.y + dirs[d][1];
    //  we make sure that the next direction is either the same \
        or 90 degrees rotated in another part of the algorithm, \
        so we don't need to worry about it here
    if(p.dir>=0 && p.dir != d) tmp.turned = true;
    tmp.dir = d;
    tmp.len = p.len + 1;
    return tmp;
}

int main(){
    // inputs
    string s;
    cin >> s;
    int r, c;
    cin >> r >> c;

    int ret = 0;

    // more inputs
    char a[r][c];
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            cin >> a[i][j];
    
    // queue for bfs
    queue<path> paths;
    
    // find starting locations
    for(int i=0; i<r; i++) {
        for(int j=0; j<r; j++) {
            if(a[i][j] == s[0]) {
                //  because path is a struct and not a class,  \
                    it has no constructor, so we have to do it \
                    here
                path tmp;
                tmp.x = i;
                tmp.y = j;
                paths.push(tmp);
            }
        }
    }

    // do the bfs stuff
    while(!paths.empty()) {
        // get current path
        path p = paths.front();
        paths.pop();
        //  if path is at end, add to ret \
            also somehow c++ does not like comparing int and string length
        if(p.len == (int)s.length()) {
            ret++;
            continue;
        }
        // loop through possible directions
        for(int d=0; d<8; d++) {
            //  if we aren't moving out of bounds, and the cell is the correct char, \
                and the direction is either 90 degrees turned or the same, append
            if(in_bounds(p,d,r,c) && a[p.x+dirs[d][0]][p.y+dirs[d][1]]==s[p.len] &&
            (p.dir<0 || (!p.turned && dirs_correct(p.dir, d)))) {
                // adds updated path to paths (move returns a path)
                paths.push(move(p,d));
            }
        }
    }

    //  apparently '\n' is fasther than endl because of some input/output stuff \
        however in practice there is no difference
    cout << ret << '\n';
}
