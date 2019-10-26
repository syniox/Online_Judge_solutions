#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
const int S=1800;
int n,q,cq,ans[N],val[N];
struct opt{
	int x,v,qid;
}op[N];
struct data{
	int id,v;
	friend bool operator < (const data &a,const data &b){
		return a.v<b.v;
	}
};

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool cmp_val(const int a,const int b){
	return val[a]<val[b];
}

namespace D{
	int cnt,val[N*2];
	inline void insert(const int v){
		val[++cnt]=v;
	}
	inline void build(){
		std::sort(val+1,val+cnt+1);
		cnt=std::unique(val+1,val+cnt+1)-val-1;
	}
	inline int ask(const int x){
		return std::lower_bound(val+1,val+cnt+1,x)-val;
	}
}

namespace B{
	int cnt,tr[N];
	inline void reset(const int len){
		cnt=len;
		memset(tr+1,0,len*sizeof(tr[0]));
	}
	inline void add(int x){
		assert(x);
		for(; x<=cnt; x+=x&-x) ++tr[x];
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

void upd_ans(const int p,data *dt,const int *idx,const int cnt){
	static int mp[N],to[N*2];
	const int st=(p-1)*S+1,ed=std::min(n,p*S),tot=ed-st+1;
	std::sort(dt+1,dt+cnt+1);
	int d=0;
	for(int i=1; i<=tot; ++i){
		if(!i||val[idx[i]]!=val[idx[i-1]]) {
			to[val[idx[i]]]=++d;
			mp[d]=val[idx[i]];
		}
	}
	B::reset(d);
	for(int i=cnt,j=tot; i; --i){
		for(; j&&val[idx[j]]>=dt[i].v; --j){
			if(idx[j]!=st) 
				B::add(to[val[idx[j]-1]]);
		}
		ans[dt[i].id]+=B::ask(std::lower_bound(mp+1,mp+d+1,dt[i].v)-mp-1);
	}
}

void sol_blk(const int p,const opt *op,const int tot){
	static data dt[N];
	static int idx[N];
	const int st=(p-1)*S+1,ed=std::min(n,p*S),sz=ed-st+1;
	for(int i=1; i<=sz; ++i){
		idx[i]=st+i-1;
	}
	std::sort(idx+1,idx+sz+1,cmp_val);
	int cnt=0;
	for(int i=1; i<=tot; ++i){
		if(op[i].qid==0){
			if(cnt) upd_ans(p,dt,idx,cnt),cnt=0;
			val[op[i].x]=op[i].v;
			int p=1;
			while(idx[p]!=op[i].x) ++p;
			for(; p>1&&val[idx[p]]<val[idx[p-1]]; --p){
				std::swap(idx[p],idx[p-1]);
			}
			for(; p<sz&&val[idx[p]]>val[idx[p+1]]; ++p){
				std::swap(idx[p],idx[p+1]);
			}
		}
		else{
			dt[++cnt]=(data){op[i].qid,op[i].v};
		}
	}
	if(cnt) upd_ans(p,dt,idx,cnt);
}

void ansqry(){
	static int tval[N];
	static opt op_b[N];
	memcpy(tval+1,val+1,n*sizeof(tval[0]));
	for(int i=1; i<=q; ++i){
		int type=nxi();
		if(type==1){
			int v=nxi();
			D::insert(v);
			op[i]=(opt){0,v,++cq};
			for(int i=0; i<n; i+=S){
				ans[cq]+=tval[i]<v&&tval[i+1]>=v;
			}
		}
		else{
			int p=nxi(),v=nxi();
			D::insert(v);
			op[i]=(opt){p,v,0};
			tval[p]=v;
		}
	}
	D::build();
	for(int i=1; i<=n; ++i){
		val[i]=D::ask(val[i]);
	}
	for(int i=1; i<=q; ++i){
		op[i].v=D::ask(op[i].v);
	}
	for(int i=1; (i-1)*S<n; ++i){
		int st=(i-1)*S+1,ed=std::min(n,i*S);
		int cnt=0;
		for(int j=1; j<=q; ++j){
			if(op[j].x==0){
				op_b[++cnt]=op[j];
			}
			else if(op[j].x>=st&&op[j].x<=ed){
				op_b[++cnt]=op[j];
			}
		}
		sol_blk(i,op_b,cnt);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::insert(val[i]);
	}
	ansqry();
	for(int i=1; i<=cq; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
