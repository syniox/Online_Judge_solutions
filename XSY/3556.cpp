#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
typedef long long lint;
const int N=1e5+5;
int n,q,ans,npos;
bool ol,used[N];
struct seg{
	int p,l,r;
	friend bool operator < (const seg &a,const seg &b){
		return a.p<b.p;
	}
};
std::set <int> conc[N];
std::set <seg> sg;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace U{
	int fa[N];
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace T{
	int x,v,tr[N];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=std::max(tr[idx(l,mid)],tr[idx(mid+1,r)]);
	}

	void init(const int l,const int r){
		tr[idx(l,r)]=n+1;
		if(l==r) return;
		const int mid=(l+r)>>1;
		init(l,mid);
		init(mid+1,r);
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	int qpos(const int l,const int r,const int p){
		//最小的nxt>p的数
		if(l==r) return tr[idx(l,r)]>p?l:l+1;
		const int mid=(l+r)>>1;
		if(tr[idx(l,mid)]>p) return qpos(l,mid,p);
		return qpos(mid+1,r,p);
	}

	inline void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(1,n);
	}

	inline int val(const int x){
		return tr[idx(x,x)];
	}
}

void link(const int x,const int y){
	std::set <seg> ::iterator st2,st=sg.lower_bound((seg){x,0,0});
	T::mod(x,y);
	if(st==sg.end()||st->p!=x) return;
	int ql=st->l,qr=st->r;
	for(int i=ql,j; i<=qr; i=j+1){
		int p=T::qpos(1,n,i);
		j=std::min(qr,T::val(p)-1);
		if(p==st->p){
			sg.erase(st);
			sg.insert((seg){p,i,j});
			st=sg.lower_bound((seg){x,0,0});
			continue;
		}
		if(i==ql&&st!=sg.begin()){
			if(p==(--st)->p){
				seg tmp=*st;
				sg.erase(st++);
				sg.insert((seg){tmp.p,tmp.l,j});
				continue;
			}
			else ++st;
		}
		if(j==qr){
			if((st2=sg.lower_bound((seg){p,0,0}))!=sg.end()&&st2->p==p){
				seg tmp=*st2;
				sg.erase(st2--);
				sg.insert((seg){tmp.p,i,tmp.r});
				if(j>=npos){
					apn(ans,std::max(i,npos)-tmp.p+1);
				}
				continue;
			}
		}
		sg.insert((seg){p,i,j});
		if(j>=npos){
			apn(ans,std::max(i,npos)-p+1);
		}
	}
}

void merge(int x,int y){
	x=U::find_rt(x),y=U::find_rt(y);
	if(x==y) return;
	used[std::max(x,y)]=1;
	while(used[npos]) --npos;
	if(conc[x].size()>conc[y].size()) std::swap(x,y);
	U::fa[x]=y;
	for(std::set <int> ::iterator it=conc[x].begin(); it!=conc[x].end(); ++it){
		std::set <int> ::iterator des=conc[y].lower_bound(*it);
		assert(*it!=*des);
		if(des!=conc[y].end()){
			link(*it,*des);
		}
		if(des!=conc[y].begin()){
			--des;
			link(*des,*it);
		}
		conc[y].insert(*it);
		//conc[y].insert(des,*it);
	}
	conc[x].clear();
}

int main(){
	n=nxi(),q=nxi(),ol=nxi();
	T::init(1,n);
	sg.insert((seg){1,1,n});
	for(int i=1; i<=n; ++i){
		conc[i].insert(i);
	}
	ans=npos=n;
	for(int i=1,lst=0; i<=q; lst*=ol,++i){
		int a=(nxi()+lst-1)%n+1,b=(nxi()+lst-1)%n+1;
		merge(a,b);
		printf("%d\n",lst=ans);
	}
	return 0;
}
