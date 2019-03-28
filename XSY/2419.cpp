#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include <sys/mman.h>
typedef long long lint;
const int N=2e5+5;
int n,q,chn[N],val[N][2],pos[N];
class _pair{
	public:
		int x,y;
		friend bool operator < (const _pair &a,const _pair &b){
			return a.x<b.x;
		}
}crd[N],chp[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

namespace D{
	int tot,buk[N<<1],*pt=buk;
	inline void insert(const int x){
		*pt++=x;
	}
	inline void build(){
		std::sort(buk,pt);
		pt=std::unique(buk,pt);
		tot=pt-buk;
	}
	inline int ask(const int v){
		return std::lower_bound(buk,pt,v)-buk+1;
	}
}

namespace BX{//max
	int tr[N<<1];
	inline void mod(int x,const int v){
		for(; x<=D::tot; x+=x&-x) apx(tr[x],v);
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

namespace BS{//sum&1
	bool tr[N<<1];
	inline void flip(int x){
		for(; x<=D::tot; x+=x&-x) tr[x]^=1;
	}
	inline bool ask(int x){
		bool ans=0;
		for(; x; x-=x&-x) ans^=tr[x];
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i][0]=nxi(),val[i][1]=nxi();
		D::insert(val[i][0]);
		D::insert(val[i][1]);
	}
	D::insert(1e9+5);
	D::build();
	for(int i=1; i<=q; ++i){
		chn[i]=std::upper_bound(D::buk,D::pt,nxi())-D::buk;
		if(!chn[i]) --i,--q;
		else chp[i]=(_pair){chn[i],i};
	}
	for(int i=1; i<=n; ++i){
		val[i][0]=D::ask(val[i][0]);
		val[i][1]=D::ask(val[i][1]);
		crd[i]=(_pair){std::max(val[i][0],val[i][1]),i};
	}
	std::sort(crd+1,crd+n+1);
	std::sort(chp+1,chp+q+1);
	for(int i=1,j=1; i<=n; ++i){
		for(; j<=q&&chp[j].x<crd[i].x; ++j){
			BX::mod(D::tot-chp[j].x+1,chp[j].y);
		}
		int tmp=std::min(val[crd[i].y][0],val[crd[i].y][1]);
		pos[crd[i].y]=BX::ask(D::tot-tmp+1);
	}
	for(int i=1; i<=n; ++i){
		crd[i]=(_pair){pos[i],i};
	}
	for(int i=1; i<=q; ++i){
		chp[i]=(_pair){i,chn[i]};
	}
	std::sort(crd+1,crd+n+1);
	std::sort(chp+1,chp+q+1);
	lint ans=0;
	for(int i=n,j=q; i; --i){
		for(; j&&chp[j].x>crd[i].x; --j){
			BS::flip(D::tot-chp[j].y+1);
		}
		int x=crd[i].y;
		int mn=std::min(val[x][0],val[x][1]);
		int mx=std::max(val[x][0],val[x][1]);
		assert(mn&&mx);
		bool res=BS::ask(D::tot-mx+1);
		if(!pos[x]) ans+=D::buk[val[x][res]-1];
		else ans+=D::buk[res?mn-1:mx-1];
	}
	printf("%lld\n",ans);
	return 0;
}
