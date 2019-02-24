#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
typedef long long lint;
const int N=1e5+5;
const lint INF=4e18;
int n,bel[N];
std::vector <int> buk[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	const double D=0.65;
	int cnt,cur_p,idx,rt,*pt,cnt_seq,seq[N];
	lint lim_l,lim_r;

	class node{
		public:
			int lf,rf,sz,sum,ls,rs;
			lint val;

			friend bool operator == (const node &a,const node &b);
			friend bool operator < (const node &a,const node &b);
	}tr[N];

	bool operator == (const node &a,const node &b){
		return a.lf==b.lf&&a.rf==b.rf;
	}

	bool operator < (const node &a,const node &b){
		if(tr[a.lf].val==tr[b.lf].val){
			return tr[a.rf].val<tr[b.rf].val;
		}
		return tr[a.lf].val<tr[b.lf].val;
	}

	inline void init(){
		rt=1;
		tr[++cnt]=(node){1,1,2,1,0,2,INF>>1};
		buk[1].push_back(0);
		bel[0]=cnt;
		tr[++cnt]=(node){2,2,1,1,0,0,(INF+(INF>>1))>>1};
		buk[2].push_back(n+1);
		bel[n+1]=cnt;
	}

	inline bool balance(const int k){
		return tr[k].sz*D>tr[tr[k].ls].sz&&tr[k].sz*D>tr[tr[k].rs].sz;
	}

	inline void upd(const int k){
		tr[k].sum=buk[k].size()+tr[tr[k].ls].sum+tr[tr[k].rs].sum;
		tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
	}

	bool _ins(int &k,const lint lim_l,const lint lim_r){
		if(!k){
			tr[k=idx].val=(lim_l+lim_r)>>1;
			tr[k].sz=tr[k].sum=1;
			bel[cur_p]=k;
			buk[k].push_back(cur_p);
			return 1;
		}
		if(tr[k]==tr[idx]){
			bel[cur_p]=k;
			buk[k].push_back(cur_p);
			++tr[k].sum;
			return 0;
		}
		bool f;
		if(tr[k]<tr[idx]){
			f=_ins(tr[k].rs,tr[k].val,lim_r);
		}
		else{
			f=_ins(tr[k].ls,lim_l,tr[k].val);
		}
		upd(k);
		if(!f) return 0;
		if(!balance(k)){
			pt=&k;
			T::lim_l=lim_l;
			T::lim_r=lim_r;
		}
		return 1;
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
		if(seq_l<mid){
			dfs_build(tr[k].ls,seq_l,mid-1,lim_l,tr[k].val);
		}
		if(seq_r>mid){
			dfs_build(tr[k].rs,mid+1,seq_r,tr[k].val,lim_r);
		}
		upd(k);
	}

	inline void rebuild(int &k){
		cnt_seq=0;
		dfs_seq(k);
		dfs_build(k,1,cnt_seq,lim_l,lim_r);
	}

	inline bool ins(int k){
		T::idx=k;
		pt=0;
		if(!_ins(rt,0,INF)) return 0;
		if(pt) rebuild(*pt);
		return 1;
	}

	inline int qry(int k,int q){
		int sum=0;
		if(tr[k].val>tr[q].val) return qry(tr[k].ls,q);
		sum=tr[tr[k].ls].sum+buk[k].size();
		if(tr[k].val==tr[q].val) return sum;
		return qry(tr[k].rs,q)+sum;
	}
}

int main(){
	n=nxi();
	T::init();
	for(int i=1; i<=n; ++i){
		const int l=nxi(),r=nxi();
		T::cur_p=i;
		T::tr[++T::cnt]=(T::node){bel[l],bel[r],1,0,0,0};
		if(!T::ins(T::cnt)) --T::cnt;
		printf("%d\n",T::qry(T::rt,bel[i]));
	}
	return 0;
}
