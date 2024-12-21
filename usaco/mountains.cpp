// not my code; helping debug vector issue

#include <set>
#include <cmath>
#include <iostream>

using namespace std;

vector<int> lis;

bool cmp(int cur, int fir, int sec) {
    int a = abs(cur-fir);
    int b = abs(cur-sec);
    int c = lis[cur]-lis[fir];
    int d = lis[cur]-lis[sec];
    return (long long)a * (long long)d >= (long long)b * (long long)c;
}

set<int> nums[2001];

signed main()  {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("mountains.in", "r", stdin);
    int n;
    cin >> n;
    lis.resize(n);
    for (int i= 0; i < n; i++)  {
        cin >> lis[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++)   {
            if (nums[i].empty())    {
                nums[i].insert(j);
                ans += 1;
            } else  {
                if (cmp(i, j, *nums[i].rbegin()))   {
                    nums[i].insert(j);
                    ans += 1;
                }
            }
        }
    }
    int q;
    cin >> q;
    //cout << ans << '\n';
    for (int k = 0; k < q; k++) {
        int x, y;
        cin >> x >> y;
        x -= 1;
        lis[x] += y;
        for (int i = 0; i < x; i++) {
            auto cur = lower_bound(nums[i].begin(), nums[i].end(), x);
            bool done = false;
            if ((*cur) == x)  {
                cur++;
                done = true;
            } else  {
                cur--;
                if (cmp(i, x, (*cur)))    {
                    //cout <<"ADAD " <<  i << ' ' << x << '\n';
                    ans += 1;
                    nums[i].insert(x);
                    cur++;
                    cur++;
                    done = true;
                }
            }
            if (done)   {
                while (cur != nums[i].end() && nums[i].empty() == false && !cmp(i, (*cur), x))    {
                    cur = nums[i].erase(cur);
                    ans -= 1;
                }
            }
        }
        ans -= nums[x].size();
        nums[x].clear();
        for (int i = x+1; i < n; i++)   {
            if (nums[x].empty() == true)   {
                nums[x].insert(i);
                ans += 1;
            } else  {
                if (cmp(x, i, *nums[x].rbegin()))   {
                    nums[x].insert(i);
                    ans += 1;
                }
            }
        }
        cout << ans << '\n';
    }
}
