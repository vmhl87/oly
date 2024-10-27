bool vis[16000001];

struct lm{
	int v;
	lm *next;
};

lm *head[16000001];
lm board[4001][4001];

void dfs(int i){
	vis[i] = 1;
	lm *p = head[i];
	while(p){
		if(!vis[p->v]) dfs(p->v);
		p = p->next;
	}
}

bool can_escape(int m, int n, std::vector<std::vector<int>> v){
	for(int i=1; i<=m; ++i)
		for(int j=1; j<=n; ++j){
			if(head[i*j])
				board[i][j].next = head[i*j];
			head[i*j] = &(board[i][j]);
			board[i][j].v = v[i][j];
		}

	dfs(1);

	return vis[m*n];
}
