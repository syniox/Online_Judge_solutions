#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
typedef long long lint;
const int N=505;
int n,val[N];
lint ans;
struct _Lim{
	//x>=y
	int x,y;
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],cur[N],dep[N];
	struct edge{
		int to,wi,nx;
	}eg[(int)4e5];

	inline void init(int len){
		cnt=1;
		memset(fir,0,(len+1)*sizeof(int));
		fir[N-1]=0;
	}

	inline void add(const int a,const int b,const int v){
		//printf("add: %d %d v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(int len){
		static int que[N];
		memset(dep,0,(len+1)*sizeof(int));
		dep[N-1]=0;
		int hd=0,tl=1;
		dep[0]=1;
		que[0]=0;
		while(hd!=tl){
			int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!dep[y]&&eg[i].wi){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return dep[N-1];
	}

	int dfs(int x,int t){
		if(x==N-1) return t;
		int tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				tt-=tp;
				if(!tt) break;
			}
		}
		return t-tt;
	}
}
int mp[N];
bool bel[N];

void solve(std::vector <int> &nd_sol,std::vector <_Lim> &eg_buk,int l,int r){
	if(l==r){
		for(std::vector <int> ::iterator it=nd_sol.begin(); it!=nd_sol.end(); ++it){
			ans+=abs(val[*it]-l);
			//printf("ans%d: %d\n",*it,l);
		}
		return;
	}
	const int sz_qry=nd_sol.size();
	const int mid=(l+r)>>1;
	std::vector <int> sol_l,sol_r;
	std::vector <_Lim> lim_l,lim_r;
	G::init(sz_qry);
	for(int i=0; i<sz_qry; ++i){
		mp[nd_sol[i]]=i;
		if(val[nd_sol[i]]<=mid) G::add(0,i+1,1);
		else G::add(i+1,N-1,1);
	}
	for(std::vector <_Lim> ::iterator it=eg_buk.begin(); it!=eg_buk.end(); ++it){
		G::add(mp[it->x]+1,mp[it->y]+1,N);
	}
	while(G::bfs(sz_qry)) G::dfs(0,N);
	for(int i=0; i<sz_qry; ++i){
		if((bel[i]=(G::dep[i+1]>0))) sol_l.push_back(nd_sol[i]);
		else sol_r.push_back(nd_sol[i]);
	}
	for(std::vector <_Lim> ::iterator it=eg_buk.begin(); it!=eg_buk.end(); ++it){
		if(bel[mp[it->x]]!=bel[mp[it->y]]) continue;
		else{
			if(bel[mp[it->x]]==1) lim_l.push_back(*it);
			else lim_r.push_back(*it);
		}
	}
	nd_sol.clear();
	std::vector <int> ().swap(nd_sol);
	eg_buk.clear();
	std::vector <_Lim> ().swap(eg_buk);
	if(!sol_l.empty()) solve(sol_l,lim_l,l,mid);
	if(!sol_r.empty()) solve(sol_r,lim_r,mid+1,r);
}

int main(){
	std::vector <int> nd_sol;
	std::vector <_Lim> eg_buk;
	n=nxi();
	int m1=nxi(),m2=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		nd_sol.push_back(i);
	}
	for(int i=1; i<=m1; ++i){
		int x=nxi(),y=nxi();
		eg_buk.push_back((_Lim){x,y});
		eg_buk.push_back((_Lim){y,x});
	}
	for(int i=1; i<=m2; ++i){
		int x=nxi(),y=nxi();
		eg_buk.push_back((_Lim){y,x});
	}
	solve(nd_sol,eg_buk,1,1e9);
	//solve(nd_sol,eg_buk,1,10);
	printf("%lld\n",ans);
	return 0;
}
