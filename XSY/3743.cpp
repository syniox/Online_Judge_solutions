#include "recover.h"
#include <vector>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <queue>
using namespace std;
static const int N=2005;

static int col[N];
static vector<int> g[N];

struct data{
	int x,dgr;
	friend bool operator<(const data &a,const data &b){
		return a.dgr>b.dgr;
	}
};

void getcol(const int n){
	static int dgr[N],buk[N];
	static bool vis[N];
	priority_queue <data> pq;
	memset(col+1,0,n*sizeof(col[0]));
	memset(vis+1,0,n*sizeof(vis[0]));
	for(int i=1; i<=n; ++i){
		dgr[i]=g[i].size();
		pq.push((data){i,dgr[i]});
	}
	int cnt=0;
	while(!pq.empty()){
		const int x=pq.top().x;
		pq.pop();
		if(vis[x]) continue;
		vis[x]=1;
		buk[++cnt]=x;
		for(vector<int>::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			pq.push((data){*it,--dgr[*it]});
		}
	}
	assert(cnt==n);
	memset(vis+1,0,n*sizeof(vis[0]));
	for(int i=cnt; i; --i){
		static bool used[N];
		const int x=buk[i];
		vis[x]=1;
		for(vector<int>::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(vis[*it]) used[col[*it]]=1;
		}
		for(col[x]=1; used[col[x]]; ++col[x]);
		for(vector<int>::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(vis[*it]) used[col[*it]]=0;
		}
	}
}

vector<pair<int,int> > recover(const int n){
	static vector<int> cbuk[N];
	vector<pair<int,int> > abuk;
	for(int i=2; i<=n; ++i){
		getcol(i-1);
		for(int j=1; j<i; ++j){
			cbuk[j].clear();
		}
		for(int j=1; j<i; ++j){
			cbuk[col[j]].push_back(j);
		}
		for(int j=1; j<i; ++j){
			if(cbuk[j].empty()) continue;
			cbuk[j].push_back(i);
			inplace_merge(cbuk[j].begin(),cbuk[j].end()-1,cbuk[j].end());
			for(;;){
				pair<int,int> res=query(cbuk[j]);
				if(res.first==-1) break;
				abuk.push_back(res);
				g[res.first].push_back(res.second);
				g[res.second].push_back(res.first);
				int lnk=res.first^res.second^i;
				cbuk[j].erase(lower_bound(cbuk[j].begin(),cbuk[j].end(),lnk));
			}
		}
	}
	return abuk;
}
