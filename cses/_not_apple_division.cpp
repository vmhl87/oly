#include <bits/stdc++.h>
using namespace std;

/*  ex: 5, 3 2 7 4 1
vs = 7 4 3 2 1
ss = 1 3 6 10 17 ->
	 17 10 6 3 1

	ss[i] represents maximal sum of length n-i

recurse: d=0,o=0 [looking at vs:7, ss:10]
 check 0+7 >= 10: no
return min( r(d:7) , r(d:7) )

recurse: d=7,o=1 [vs:4, ss:6]
 
*/

// o == len?    also d always +
long md(vector<long> &vs, vector<long> &ss, long d, int o) {
	// if at end: return d (running sum?) - last elem of vs
  if (o == vs.size() - 1) return abs(d - vs[o]);
  // if d+this elem >= <a running sum>
  if (d + vs[o] >= ss[o + 1])
  // return smaller of (d+elem - running sum, recurse(d-elem))
    return min(d + vs[o] - ss[o + 1], md(vs, ss, abs(d - vs[o]), o + 1));
  // else return smaller of (recurse(d+elem), recurse(d-elem))
  return min(md(vs, ss, d + vs[o], o + 1), md(vs, ss, abs(d - vs[o]), o + 1));
}
 
int main() {
  long n, v;
  cin >> n;
  vector<long> vs, ss;
  // values
  for (int i = 0; i < n; i++) {
    cin >> v;
    vs.push_back(v);
  } // input values
  // sort in decreasing order?
  sort(vs.begin(), vs.end(), greater<long>());
  // loop: s = running sum, i iterates bkwrds
  for (long s = 0, i = vs.size(); i > 0; i--) {
  	// increment sum by current value (smallest??)
    s += vs[i - 1];
    // push running sum to ss
    ss.push_back(s);
  }
  // reverse ss (biggest sum to smallest)
  reverse(ss.begin(), ss.end());
  cout << md(vs, ss, 0, 0);
}
