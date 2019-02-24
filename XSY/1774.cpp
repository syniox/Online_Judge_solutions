#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long lint;
const int N=1.1e6+5;
const int mod=1e9+7;
const lint INF=4e18;
int n,q;
char ch[N];
bool type;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	const double ALP=0.7;
	int rt,*rebuild_pt,cnt_seq,seq[N];
	lint lim_l,lim_r;

	class node{
		public:
			int ls,rs,sz;
			lint val;
	}tr[N];

	inline void init(){
		tr[N-1].val=INF>>1;
	}

	inline bool cmp_small(const int a,const int b){
		if(ch[a]==ch[b]) return tr[a-1].val<tr[b-1].val;
		return ch[a]<ch[b];
	}

	inline bool balanced(const int k){
		const int limit=tr[k].sz*ALP;
		return tr[tr[k].ls].sz<=limit&&tr[tr[k].rs].sz<=limit;
	}

	inline void upd(const int k){
		tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
	}

	void _ins(int &k,int x,lint lim_l,lint lim_r){
		if(!k){
			k=x;
			tr[x].val=(lim_l+lim_r)>>1;
			return;
		}
		if(cmp_small(x,k)){
			_ins(tr[k].ls,x,lim_l,tr[k].val);
		}
		else{
			_ins(tr[k].rs,x,tr[k].val,lim_r);
		}
		upd(k);
		if(!balanced(k)){
			rebuild_pt=&k;
			T::lim_l=lim_l,T::lim_r=lim_r;
		}
	}

	void dfs_seq(const int k){
		if(tr[k].ls) dfs_seq(tr[k].ls);
		seq[++cnt_seq]=k;
		if(tr[k].rs) dfs_seq(tr[k].rs);
	}

	void dfs_build(int &k,int seq_l,int seq_r,lint lim_l,lint lim_r){
		const int mid=(seq_l+seq_r)>>1;
		k=seq[mid];
		tr[k].val=(lim_l+lim_r)>>1;
		tr[k].ls=tr[k].rs=0;
		if(seq_l<mid) dfs_build(tr[k].ls,seq_l,mid-1,lim_l,tr[k].val);
		if(seq_r>mid) dfs_build(tr[k].rs,mid+1,seq_r,tr[k].val,lim_r);
		upd(k);
	}

	void rebuild(int &k){
		//puts("rebuilded.");
		cnt_seq=0;
		dfs_seq(k);
		dfs_build(k,1,cnt_seq,lim_l,lim_r);
	}

	inline void ins(const int k){
		rebuild_pt=0;
		_ins(rt,k,0,INF);
		if(rebuild_pt){
			rebuild(*rebuild_pt);
		}
	}
}

inline int solve(const int x,const int y){
	return T::tr[x].val<T::tr[y].val?x:y;
}

int main(){
	scanf("%s",ch+1);
	T::init();
	q=nxi(),type=nxi();
	n=strlen(ch+1);
	std::reverse(ch+1,ch+n+1);
	for(int i=1; i<=n; ++i){
		T::tr[i]=(T::node){0,0,1,0};
		T::ins(i);
	}
	int ans=0;
	for(int res=0; q; --q){
		char c;
		while((c=getchar())!='Q'&&c!='I');
		if(c=='I'){
			while((c=getchar())>'z'||c<'a');
			ch[++n]=c;
			T::tr[n]=(T::node){0,0,1,0};
			T::ins(n);
		}
		else{
			int x=nxi(),y=nxi();
			if(type) x=(x^res)%n+1,y=(y^res)%n+1;
			ans=((lint)ans*23+(res=solve(x,y)))%mod;
		}
	}
	printf("%d\n",ans);
//	fprintf(stderr,"rebuild cnt: %d\n",T::reb_cnt);
	return 0;
}
