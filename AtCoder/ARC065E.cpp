#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,dis,qa,qb;
bool vld[N];
std::vector <int> bukx[N<<1],buky[N<<1]; 
struct _pair{
	int x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.y<b.y;
	}
}pnt[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	template <class T> inline T cabs(const T x){
		return x<0?-x:x;
	}
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

template <class T,size_t S>
class _Disc{
	public:
		T buk[S],*pt;
		int tot;
		_Disc(){pt=buk;}

		inline void ins(const T &v){
			*++pt=v;
		}
		inline void build(){
			std::sort(buk+1,pt+1);
			pt=std::unique(buk+1,pt+1)-1;
			tot=pt-buk;
		}
		inline int ask(const T &v){
			return std::lower_bound(buk+1,pt+1,v)-buk;
		}
};
_Disc <int,N<<1> D;

void get_vld(){
	static std::set <_pair> inqx[N<<1],inqy[N<<1];//{id,val}
	static _pair que[N];
	int hd=0,tl=0;
	que[tl++]=pnt[qa];
	que[tl++]=pnt[qb];
	vld[qa]=vld[qb]=1;
	for(int i=1; i<=n; ++i){
		if(i==qa||i==qb) continue;
		inqx[pnt[i].x].insert((_pair){i,D.buk[pnt[i].y]});
		inqy[pnt[i].y].insert((_pair){i,D.buk[pnt[i].x]});
	}
	while(hd!=tl){
		_pair p=que[hd++];
		for(int i=-1; i<=1; i+=2){
			const lint qx=(lint)i*dis+D.buk[p.x];
			if(qx<-2e9||qx>2e9) continue;
			int posx=D.ask(qx);
			if(D.buk[posx]!=qx) continue;
			_pair tmp=(_pair){0,D.buk[p.y]-dis};
			std::set <_pair> ::iterator it=inqx[posx].lower_bound(tmp);
			while(it!=inqx[posx].end()&&it->y<=(lint)D.buk[p.y]+dis){
				que[tl++]=pnt[it->x];
				vld[it->x]=1;
				/*{
					int org_y=D.ask(it->y);
					std::set <_pair> ::iterator rm_it;
					rm_it=inqy[org_y].find((_pair){it->x,(int)qx});
					assert(rm_it!=inqy[org_y].end());
					inqy[org_y].erase(rm_it);
				}*/
				inqy[D.ask(it->y)].erase((_pair){it->x,(int)qx});
				inqx[posx].erase(it++);
			}
		}
		for(int i=-1; i<=1; i+=2){
			const lint qy=(lint)i*dis+D.buk[p.y];
			if(qy<-2e9||qy>2e9) continue;
			int posy=D.ask(qy);
			if(D.buk[posy]!=qy) continue;
			_pair tmp=(_pair){0,D.buk[p.x]-dis};
			std::set <_pair> ::iterator it=inqy[posy].lower_bound(tmp);
			while(it!=inqy[posy].end()&&it->y<=(lint)D.buk[p.x]+dis){
				que[tl++]=pnt[it->x];
				vld[it->x]=1;
				/*{
					int org_x=D.ask(it->y);
					std::set <_pair> ::iterator rm_it;
					rm_it=inqx[org_x].find((_pair){it->x,(int)qy});
					assert(rm_it!=inqx[org_x].end());
					inqx[org_x].erase(rm_it);
				}*/
				inqx[D.ask(it->y)].erase((_pair){it->x,(int)qy});
				inqy[posy].erase(it++);
			}
		}
	}
}

int qry_cnt(const std::vector <int> &vt,int l,int r){
	if(l>r||vt.empty()||r<*vt.begin()) return 0;
	int it_l=std::lower_bound(vt.begin(),vt.end(),l)-vt.begin();
	int it_r=std::upper_bound(vt.begin(),vt.end(),r)-vt.begin()-1;
	return it_r-it_l+1;
}

int main(){
	n=nxi(),qa=nxi(),qb=nxi();
	for(int i=1; i<=n; ++i){
		const int x=nxi(),y=nxi();
		pnt[i].x=x+y,pnt[i].y=y-x;
		D.ins(pnt[i].x);
		D.ins(pnt[i].y);
	}
	dis=std::max(cabs(pnt[qa].x-pnt[qb].x),cabs(pnt[qa].y-pnt[qb].y));
	D.build();
	for(int i=1; i<=n; ++i){
		pnt[i].x=D.ask(pnt[i].x);
		pnt[i].y=D.ask(pnt[i].y);
		//assert(pnt[i].x&&pnt[i].y);
		bukx[pnt[i].x].push_back(D.buk[pnt[i].y]);
		buky[pnt[i].y].push_back(D.buk[pnt[i].x]);
	}
	for(int i=1; i<=D.tot; ++i){
		if(!bukx[i].empty()){
			std::sort(bukx[i].begin(),bukx[i].end());
		}
		if(!buky[i].empty()){
			std::sort(buky[i].begin(),buky[i].end());
		}
	}
	get_vld();
	lint ans=0;
	for(int i=1; i<=n; ++i){
		if(!vld[i]) continue;
		for(int j=-1; j<=1; j+=2){
			const lint qx=(lint)j*dis+D.buk[pnt[i].x];
			if(qx<-2e9||qx>2e9) continue;
			const int posx=D.ask(qx);
			if(D.buk[posx]!=qx) continue;
			const int r_y=D.buk[pnt[i].y];
			int lim_l=std::max((lint)-2e9,(lint)r_y-dis);
			int lim_r=std::min((lint)2e9,(lint)r_y+dis);
			ans+=qry_cnt(bukx[posx],lim_l,lim_r);
		}
		for(int j=-1; j<=1; j+=2){
			const lint qy=(lint)j*dis+D.buk[pnt[i].y];
			if(qy<-2e9||qy>2e9) continue;
			const int posy=D.ask(qy);
			if(D.buk[posy]!=qy) continue;
			const int r_x=D.buk[pnt[i].x];
			int lim_l=std::max((lint)-2e9,(lint)r_x-dis);
			int lim_r=std::min((lint)2e9,(lint)r_x+dis);
			ans+=qry_cnt(buky[posy],lim_l+1,lim_r-1);
		}
	}
	assert((ans&1)==0);
	printf("%lld\n",ans>>1);
	return 0;
}
