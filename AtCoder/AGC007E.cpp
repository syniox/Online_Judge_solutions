#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=131080;
int n;
class pair{
	public:
		lint x,y;
		friend bool operator < (const pair &a,const pair &b);
};

bool operator < (const pair &a,const pair &b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int x_bound(std::vector <pair> &vt,const lint _lim){
	int l=0,r=vt.size()-1,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(vt[mid].x>_lim) r=mid-1;
		else l=mid;
	}
	return l;
}

inline int y_bound(std::vector <pair> &vt,const lint _lim){
	int l=0,r=vt.size()-1,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(vt[mid].y>_lim) l=mid+1;
		else r=mid;
	}
	return l;
}

inline void sanitize_seq(std::vector <pair> &vt){
	const int sz=vt.size();
	int p1=1,p2=1;
	for(; p1<sz; ++p1){
		if(vt[p1].x!=vt[p1-1].x) vt[p2++]=vt[p1];
	}
	while((int)vt.size()>p2) vt.pop_back();
}

namespace G{
	int cnt,nxt[N][2],wt[N][2];
	lint lim_w;
	std::vector <pair> vt[N];

	inline void add(const int a,const int b,const int v){
		bool f=nxt[a][0]>0;
		nxt[a][f]=b,wt[a][f]=v;
	}

	void dfs(const int x){
		if(!nxt[x][0]){
			vt[x].push_back((pair){0,0});
			return;
		}
		dfs(nxt[x][0]);
		dfs(nxt[x][1]);
		if(vt[nxt[x][0]].size()>vt[nxt[x][1]].size()){
			std::swap(nxt[x][0],nxt[x][1]);
			std::swap(wt[x][0],wt[x][1]);
		}

		const int c0=nxt[x][0],c1=nxt[x][1];
		const lint v0=wt[x][0],v1=wt[x][1];
		const int lim_l=vt[c0].size();

		for(int i=0,j,lst_j=-1; i<lim_l; ++i){
			const lint _lim=lim_w-vt[c0][i].y-v0-v1;
			j=x_bound(vt[c1],_lim);
			if(vt[c1][j].x>_lim) continue;
			if(j!=lst_j){
				lst_j=j;
				vt[x].push_back((pair){vt[c0][i].x+v0,vt[c1][j].y+v1});
			}
		}
		for(int i=lim_l-1,j,lst_j=-1; i>=0; --i){
			const lint _lim=lim_w-vt[c0][i].x-v0-v1;
			j=y_bound(vt[c1],_lim);
			if(vt[c1][j].y>_lim) continue;
			if(j!=lst_j){
				lst_j=j;
				vt[x].push_back((pair){vt[c1][j].x+v1,vt[c0][i].y+v0});
			}
		}
		std::sort(vt[x].begin(),vt[x].end());
		sanitize_seq(vt[x]);
	}

	bool jdg(const lint tgt){
		lim_w=tgt;
		for(int i=1; i<=n; ++i){
			vt[i].clear();
		}
		dfs(1);
		return !vt[1].empty();
	}
}

inline lint solve(){
	lint l=0,r=2e10,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(G::jdg(mid)) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i){
		int fr=nxi();
		G::add(fr,i,nxi());
	}
	printf("%lld\n",solve());
	return 0;
}
