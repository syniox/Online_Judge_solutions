#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
const int N=1e5+5;
int n,tot,per[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace G{
	int cnt,fir[N],*buk[N];
	int cpos[N],mx_buk[N],cir_len[N],cir_sz[N],ccir,cur_len;
	bool on_cir[N],vis[N],tvis[N];
	std::vector <int> sz_list[N],len_list[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add_edge(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void init(){
		memset(fir+1,0,n*sizeof(int));
		memset(mx_buk+1,0,n*sizeof(int));
		memset(cir_sz+1,0,n*sizeof(int));
		memset(vis+1,0,n*sizeof(bool));
		memset(tvis+1,0,n*sizeof(bool));
		memset(on_cir+1,0,n*sizeof(bool));
		ccir=cnt=0;
		for(int i=1; i<=n; ++i){
			add_edge(per[i],i);
			sz_list[i].clear();
			len_list[i].clear();
			if(buk[i]!=NULL){
				delete[] buk[i];
				buk[i]=NULL;
			}
		}
	}

	inline void dfs_tr(const int x,const int dis){
		++buk[ccir][dis];
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) dfs_tr(y,(dis+1)%cur_len);
		}
	}

	inline void get_cir(const int p){
		int x=p;
		for(; !tvis[x]; x=per[x]) tvis[x]=1;
		int rt=x,len=1;
		on_cir[x]=1;
		for(int i=per[x]; i!=x; i=per[i]){
			++len;
			on_cir[i]=1;
			apn(rt,i);
		}
		cpos[++ccir]=rt;
		cir_len[ccir]=len;
		cur_len=len;
		buk[ccir]=new int[len];
		memset(buk[ccir],0,len*sizeof(int));
		dfs_tr(rt,0);
		for(int i=0; i<len; ++i){
			cir_sz[ccir]+=buk[ccir][i];
			apx(mx_buk[ccir],buk[ccir][i]);
		}
		sz_list[cir_sz[ccir]].push_back(ccir);
		len_list[cir_len[ccir]].push_back(ccir);
	}

	int get_xselfcyc(){
		int ans=0;
		for(int i=1; i<=ccir; ++i){
			if(cir_len[i]==1) apx(ans,cir_sz[i]);
		}
		return ans;
	}

	namespace S{
		int buk[N],cbuk[N],mx_buk;
		//buk为每种颜色的出现次数,cbuk为每种出现次数的出现次数

		inline void mod(const int x,const int delta){
			--cbuk[buk[x]];
			buk[x]+=delta;
			++cbuk[buk[x]];
			apx(mx_buk,buk[x]);
			while(!cbuk[mx_buk]) --mx_buk;
		}

		void dfs_buk(const int x,int *buk,int dis,int flag){
			mod(dis,flag);
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!on_cir[y]) dfs_buk(y,buk,(dis+1)%cur_len,flag);
			}
		}

		int sanitize(const int p,const int len){
			memset(buk,0,(std::min(len,cir_sz[p])+1)*sizeof(int));
			memset(cbuk,0,(cir_sz[p]+1)*sizeof(int));
			cbuk[0]=len;
			mx_buk=0;
			int ans=0,tag=0,x=cpos[p];
			cur_len=len;
			dfs_buk(x,buk,0,1);
			x=per[x];
			for(int i=(cir_len[p]-1)%len; x!=cpos[p]; i=(i-1+len)%len,x=per[x]){
				dfs_buk(x,buk,i,1);
			}
			ans=mx_buk;
			for(int step=(cir_len[p]-1)%len,i=per[x]; i!=x; i=per[i]){
				dfs_buk(i,buk,(step+tag)%len,-1);
				if(--tag<0) tag+=len;
				dfs_buk(i,buk,tag,1);
				apx(ans,mx_buk);
			}
			return ans;
		}
	}

	void solve_selfcyc(int *ans,int sz_cyc){
		int mx;
		for(mx=n; sz_list[mx].empty(); --mx);
		ans[0]=sz_cyc;
		for(int i=1,cnt=0; i<tot; ++cnt,++i){
			if(mx&&cnt+(sz_cyc==mx)==(int)sz_list[mx].size()){
				cnt=0;
				for(--mx; sz_list[mx].size()<=(mx==sz_cyc); --mx);
			}
			ans[i]=ans[i-1]+mx;
		}
	}

	void solve(int len,int *ans){
		static int sum[N];
		memset(sum,0,(n+1)*sizeof(int));
		int base=0;
		for(int i=0; i<(int)len_list[len].size(); ++i){
			if(mx_buk[len_list[len][i]]>mx_buk[base]){
				base=len_list[len][i];
			}
		}
		for(int i=1; i<=ccir; ++i){
			if(i==base) continue;
			if(cir_len[i]==len) ++sum[mx_buk[i]];
			else ++sum[S::sanitize(i,len)];
		}
		ans[0]=mx_buk[base];
		int top=0;
		for(int i=n; i; --i){
			while(sum[i]--){
				ans[top+1]=ans[top]+i;
				++top;
			}
		}
		for(; top<tot; ++top){
			ans[top+1]=ans[top];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	static int ans[N],tmpans[N];
	for(int T=nxi(); T; --T){
		bool self_cyc=0;
		n=nxi();
		for(int i=1; i<=n; ++i){
			per[i]=nxi();
			self_cyc|=i==per[i];
		}
		G::init();
		for(int i=1; i<=n; ++i){
			if(!G::vis[i]) G::get_cir(i);
		}
		tot=G::ccir-self_cyc;
		printf("%d\n",tot);
		G::solve_selfcyc(ans,G::get_xselfcyc());
		for(int i=2; i<=n; ++i){
			if(G::len_list[i].empty()) continue;
			G::solve(i,tmpans);
			for(int i=0; i<tot; ++i){
				apx(ans[i],tmpans[i]);
			}
		}
		ans[tot]=n;
		for(int i=0; i<=tot; ++i){
			printf("%d ",ans[i]);
		}
		puts("");
	}
	return 0;
}
