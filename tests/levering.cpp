#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define iter(i, n) for(int i = 0; i < n; i++)
#define rngIt(n, m, s) if(n>m){for(int i = n-1; i >= m-1; i-=s)}else{for(int i = n; i < m; i+=s)}
#define it(arr) for(ll i : arr) std::cerr << i << ' '; cerr << '\n';
#define printl(s) cout<<s<<endl;
#define printerr(s) cerr<<s<<endl;
#define endl "\n";
bool stress = true;
bool dbg = true;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
    uniform_int_distribution<> dist(a, b);
    return dist(rng);
}
int brute(int t, int c, set<int>&st, string s)
{
	return 0;
    string glyph = "LFR";
    int ans = 0;
    map<char,int>mp;
    mp['L']=-1;
    mp['F']=0;
    mp['R']=1;
    pair<int,char> bst;
    iter(i,c)
    {
        char cc = s[i];
        iter(j,3)
        {
            s[i]=glyph[j];
            int cur = 0;
            int ct = 0;
            set<int>vis;
            iter(k,c)
            {
                cur+=mp[s[k]];
                if(mp[s[k]]==0)
                {
                    if(vis.count(cur))continue;
                    if(!st.count(cur))continue;
                    vis.insert(cur);
                    ct++;
                }
            }
            if(ct>ans&&!stress)
            {
               bst = {i,glyph[j]};
            }
            ans = max(ct,ans);
        }
        s[i]=cc;
    }
    if(!stress)
    {
        printl(bst.first<<"->"<<bst.second)
    }
    return ans;
}
void test()
{
    string glyph = "LFR";
    int t,c; cin>>t>>c;
    if(stress)
    {
        t=rand(1,5);
        c=rand(1,10);
    }
    map<char,int>mp;
    mp['L']=-1;
    mp['F']=0;
    mp['R']=1;
    map<int,vector<int>>fR; //relative f
    vector<int>arr(t);
    set<int>st;
    set<int>set1;
    iter(i,t)
    {
        cin>>arr[i];
        if(stress)
        {
            int chk = rand(-c,c);
            while(set1.count(chk)) {
                chk = rand(-c, c);
            }
            set1.insert(chk);
            arr[i]=chk;
        }
        st.insert(arr[i]);
    }
    string s; cin>>s;
    if(dbg) {
        printl("brute says "<<brute(t,c,st,s))
    }
    if(stress)
    {
        s.clear();
        iter(i,c)
        {
            s.push_back(glyph[rand(0,2)]);
        }
    }
    int cur = 0;
    set<int>fs;
    vector<int>pfx(c+1);
    iter(i,c)
    {
        cur+=mp[s[i]];
        pfx[i+1]=cur;
        if(mp[s[i]]==0) {
            fR[cur].push_back(i);
            fs.insert(i);
        }
    }
    set<int>vis;
    map<int,int>cToI;
    int ans = 0;
    pair<int,char>bst;
    bst.second='P';
    vector<int>fq(5);
    cur = 0;
    map<int,int>pre;
    int hit=0;
    map<int,int>fInst;
    iter(i,c)
    {
        if(s[i]=='F')
        {
            if(st.count(cur)) {
                pre[cur]++;
                if(!vis.count(cur))
                {
                    vis.insert(cur);
                    hit++;
                    fInst[cur]=i;
                }
            }
        }
        cur+=mp[s[i]];
    }
    vis.clear();
    map<int,int>posToPhit;
    vector<int> pHit(5);
    iter(idx,c)
    {
        int i = c-idx-1;
        iter(j,3)
        {
            int diff = mp[glyph[j]]-mp[s[i]];
            //L to F and F to L
            int val = 0;
            if(s[i]!='F'&&glyph[j]=='F')
            {
                //in this case we add 1 as long as there exists not f at pfx[i+1]
                if(!vis.count(pfx[i]+diff)&&!pre[pfx[i]+diff]&&st.count(pfx[i]+diff))
                    val++;
            }
            if(s[i]=='F'&&glyph[j]!='F')
            {
                //ok last case, we subtract one if its a target, and pre[pfx[i]] is one (meaning this is the only one)
                if(vis.count(pfx[i]+diff)&&pre[pfx[i]+diff]==1&&st.count(pfx[i]+diff))
                    val--;
            }
            int tmp = fq[diff+2]-pHit[diff+2]+hit+val;
            if(i==1&&j==0&&dbg)
            {
                it(pfx)
                printerr(diff)
                printerr(hit)
                printerr(val)
                printerr(fq[diff+2])
                it(pHit)
                it(fq)
            }
            if(tmp>ans)
            {
                bst = {i,glyph[j]};
                if(dbg) {
                    printl(tmp << ": " << i << "->" << glyph[j])
                }
            }
            ans = max(tmp,ans);
        }
        //printl("hit at "<<i<<" "<<hit<<" ")
        //printl("phit at "<<i<<" "<<pHit<<" ")
        if(fs.count(i))
        {
            iter(j,5)
            {
                if(st.count(j-2+pfx[i+1])) {
                    if(pre[pfx[i+1]+j-2]>0) {
                        pHit[j]++;
                        //printl("Added to pHit with first instance "<<fInst[pfx[i+1]])
                        //now we need
                        posToPhit[fInst[pfx[i+1]]]=j;
                        pre[pfx[i+1]]--;
                        if(pre[pfx[i+1]]==0)
                            hit--;
                    }
                    if(vis.count(pfx[i+1]))continue;
                        fq[j]++;
                }
            }
            if(fInst[pfx[i+1]]==i)
                pHit[posToPhit[fInst[pfx[i+1]]]]--;
            vis.insert(pfx[i+1]);
        }
    }
    if(stress&&ans!=brute(t,c,st,s))
    {
        printl("")
        cerr<<"Mismatch E:"<<brute(t,c,st,s)<<" A:"<<ans<<endl;
        cerr<<"------------------------------------"<<endl;
        cerr<<t<<" "<<c<<endl;
        it(arr)
        cerr<<s<<endl;
        return;
    }
    if(!stress) {
        if(dbg) {
            printl("sol says " << bst.first << "->" << bst.second)
        }
        printl(ans)
    }
}
int main()
{
    //cin.tie(0)->sync_with_stdio(0);
    if(stress)
    {
        printl("Stress mode")
        cout<<flush;
        if(stress)dbg=false;
        int t; cin>>t;
        iter(i,t){test();}
        printl("No issues!")
        return 0;
    }
    else {
        test();
        return 0;
    }
    return 0;
}
