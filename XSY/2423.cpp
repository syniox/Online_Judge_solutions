#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <set>
typedef long long lint;
const int S=260;
const int N=1e5+5;
struct data{
	int t,p;
};
data dt[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

class mset{
	protected:
		int rt;
		static int cnt;
		static struct node{
			int w,ls,rs,sz;
			lint v;
			node(){w=rand();}
		}tr[N];

		inline void upd(const int k){
			tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
		}

		void merge(int &k,const int r1,const int r2){
			if(!r1||!r2){
				k=r1+r2;
				return;
			}
			if(tr[r1].w<tr[r2].w){
				k=r1;
				merge(tr[k].rs,tr[k].rs,r2);
			}
			else{
				k=r2;
				merge(tr[k].ls,r1,tr[k].ls);
			}
			upd(k);
		}

		void split(const int k,int &r1,int &r2,const lint v){
			if(!k){
				r1=r2=0;
				return;
			}
			if(tr[k].v<=v){
				r1=k;
				split(tr[k].rs,tr[k].rs,r2,v);
			}
			else{
				r2=k;
				split(tr[k].ls,r1,tr[k].ls,v);
			}
			if(r1) upd(r1);
			if(r2) upd(r2);
		}

		int rnk_t(const int k,const int v){
			if(!k) return 0;
			if(tr[k].v>v) return rnk_t(tr[k].ls,v);
			return tr[tr[k].ls].sz+1+rnk_t(tr[k].rs,v);
		}
	public:
		inline void insert(const lint v){
			int r1,r2;
			split(rt,r1,r2,v);
			tr[++cnt].v=v;
			tr[cnt].sz=1;
			merge(r1,r1,cnt);
			merge(rt,r1,r2);
		}

		inline int rnk(const lint k){
			return rnk_t(rt,k);
		}
}tbuk[S];
int mset::cnt;
mset::node mset::tr[N];

int main(){
	for(int cdt=0,cjmp=0,q=nxi(); q; --q){
		const int op=nxi();
		if(op==1){
			const int x=nxi(),t=nxi();
			if(t>=S) dt[++cdt]=(data){t,x};
			else tbuk[t].insert(x-(lint)t*cjmp);
		}
		else if(op==2){
			++cjmp;
			int cnt=0;
			for(int i=1; i<=cdt; ++i){
				dt[i].p+=dt[i].t;
				if(dt[i].p<=(int)1e5) dt[++cnt]=dt[i];
			}
			cdt=cnt;
		}
		else if(op==3){
			const int l=nxi(),r=nxi();
			int ans=0;
			for(int i=1; i<=cdt; ++i){
				ans+=dt[i].p>=l&&dt[i].p<=r;
			}
			for(int i=1; i<S; ++i){
				ans+=tbuk[i].rnk(r-(lint)cjmp*i)-tbuk[i].rnk(l-1-(lint)cjmp*i);
			}
			printf("%d\n",ans);
		}
		else assert(0);
	}
	return 0;
}
