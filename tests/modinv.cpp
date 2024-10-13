int inv(int x) { return x==1?1:mod-1ll*mod/x*inv(mod%x)%mod; }
