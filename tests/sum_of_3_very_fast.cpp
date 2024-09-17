#include <iostream>
#include <algorithm>
using namespace std;
struct p {
    int x,y;
};
// PBR is faster than PBV
bool c(p &a, p&b) {return a.x<b.x;}
// cool buffering
int read(){
    char r;
    int ret=0;
    r=getchar();
    if((r-'0'<0 || r-'0'>9)) r=getchar();
    while(!(r-'0'<0 || r-'0'>9)){
        ret= (ret<<1) + (ret<<3) + (r-'0');
        r=getchar();
    }
    return ret;
}
// this is actually very cool
void print(int x){
    if(x>9)print(x/10);
    putchar('0'+x%10);
}
int main() {
    int n = read(), x = read();
    p v[5000];
    for (int i = 0; i<n;++i) {
        v[i].x=read();
        v[i].y=i;}
    sort(v,v+n,c);
    // i iterates up to maximum endpoint and also ensures that
    // we are never processing unnecessarily large numbers which
    // will have no chance of constructing valid
    for (int i = 0; i<n-2 && v[i].x<=x/3; ++i) {
    	// s = target sum, r = maximum elem
        int s = x - v[i].x, l = i + 1, r = n - 1,z;
        // if we can't reach target skip
        if(v[r-1].x+v[r].x < s) continue;
        // converge upper and lower bounds to find best
        // checks that lower and upper are bounded properly
        // while also target sum not match sum
        while (l < r && (z=v[l].x+v[r].x)!=s) {
        	// greedily pick the side to move
            if (z<s)l++;
            else r--;
        }
        	// print out if we found one
            if (r != l) {
                print(v[l].y+1);
                putchar(' ');
                print(v[r].y+1);
                putchar(' ');
                print(v[i].y+1);
                return 0;
            }
            else if (v[l].x+v[r].x > s) r--;
            else l++;
 
    }
    cout << "IMPOSSIBLE";
}
