#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5;
int n,w,q,val[N];
bool type;
vector <int> vbuk[N];
vector <int> rbuk[N<<1],rval[N<<1];
struct mdf_s{
	int l,r,v;
	friend bool operator<(const mdf_s &a,const mdf_s &b){
		return a.l<b.l;
	}
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

namespace T{
#define mid ((l+r)>>1)
	int cnt,x,y,v;
	struct node{
		int ls,rs,v;
	}tr[N*18*32];

	void addv_t(int &k,const int l,const int r){
		tr[++cnt]=tr[k];
		k=cnt;
		if(l>=x&&r<=y){
			tr[k].v+=v;
			return;
		}
		if(x<=mid) addv_t(tr[k].ls,l,mid);
		if(y>mid) addv_t(tr[k].rs,mid+1,r);
	}
	int qsum_t(const int k,const int l,const int r){
		if(!k||(l==x&&r==x)) return tr[k].v;
		if(x<=mid) return qsum_t(tr[k].ls,l,mid)+tr[k].v;
		return qsum_t(tr[k].rs,mid+1,r)+tr[k].v;
	}

	void addv(int &r,const int x,const int y,const int v){
		T::x=x,T::y=y,T::v=v;
		addv_t(r,1,n);
	}
	int qsum(int r,const int x){
		T::x=x;
		return qsum_t(r,1,n);
	}
#undef mid
}

void prebuild(const int k,const int l,const int r){
	static vector<mdf_s> mbuk;
	const int mid=(l+r)>>1;
	mbuk.clear();
	for(int i=l; i<=mid; ++i){
		for(int j=0; j<(int)vbuk[i].size(); ++j){
			const int cur=vbuk[i][j];
			if(j>=w){
				int p=j==w?1:vbuk[i][j-w-1]+1;
				mbuk.push_back((mdf_s){p,cur,-w});
				mbuk.push_back((mdf_s){vbuk[i][j-w]+1,cur,w+1});
			}else{
				mbuk.push_back((mdf_s){1,cur,1});
			}
			mbuk.push_back((mdf_s){cur+1,cur,-1});
		}
	}
	sort(mbuk.begin(),mbuk.end());
	int rt=0;
	for(int i=0; i<(int)mbuk.size(); ++i){
		T::addv(rt,mbuk[i].r,n,mbuk[i].v);
		if((i+1==(int)mbuk.size())||mbuk[i].l!=mbuk[i+1].l){
			rbuk[k].push_back(rt);
			rval[k].push_back(mbuk[i].l);
		}
	}
	if(l<mid) prebuild(k<<1,l,mid);
	if(r>mid+1) prebuild(k<<1|1,mid+1,r);
}

int qkth(const int k,const int l,const int r,const int x,const int y,const int rk){
	if(l==r) return l;
	const int rpos=upper_bound(rval[k].begin(),rval[k].end(),x)-rval[k].begin()-1;
	const int rt=rpos<0?0:rbuk[k][rpos];
	const int res=T::qsum(rt,y),mid=(l+r)>>1;
	if(res>=rk) return qkth(k<<1,l,mid,x,y,rk);
	return qkth(k<<1|1,mid+1,r,x,y,rk-res);
}

int main(){
	n=nxi(),w=nxi(),q=nxi(),type=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		vbuk[val[i]].push_back(i);
	}
	prebuild(1,0,n);
	for(int ans=0; q--; ans*=type){
		const int l=nxi()^ans,r=nxi()^ans,k=nxi()^ans;
		printf("%d\n",ans=qkth(1,0,n,l,r,k));
	}
	return 0;
}
