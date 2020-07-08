#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
typedef long long lint;
using namespace std;
const int N=1005,V=5e4+5;
int n,pr[N],pc[N],pa[N],pb[N],pv[N];
lint dis[V][2];
bool vis[V][2];

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

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

struct stat{
	int x;
	bool f;
	friend stat operator*(stat a,stat b){
		if(a.f==b.f) return (stat){gcd(a.x,b.x),a.f};
		if(a.f) swap(a,b);
		int g=gcd(a.x,2*b.x);
		return (stat){std::min(g,b.x),g>b.x};
	}
	bool canto(const int a,const int b){
		if(a%x||b%x) return 0;
		return !f||(a/x&1)==(b/x&1);
	}
};
struct data{
	stat st;
	lint v;
	friend bool operator < (const data &a,const data &b){
		return a.v>b.v;
	}
};
std::priority_queue <data> pq;

inline stat getst(int a,int b){
	int x=gcd(a,b);
	return (stat){x,(a%(x*2))&&(b%(x*2))};
}

namespace D{
	int cnt,v[N*N*3];
	inline void insert(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+cnt+1,x)-v;
	}
}

int main(){
	memset(dis,10,sizeof(dis));
	n=nxi();
	for(int i=1; i<=n; ++i){
		pr[i]=nxi(),pc[i]=nxi();
		pa[i]=nxi(),pb[i]=nxi();
		pv[i]=nxi();
		for(int j=1; j<=3.5e4; ++j){
			if(pa[i]%j==0){
				D::insert(j);
				D::insert(pa[i]/j);
			}
			if(pb[i]%j==0){
				D::insert(j);
				D::insert(pb[i]/j);
			}
		}
	}
	if(pr[1]==0&&pc[1]==0){
		return puts("0"),0;
	}
	D::build();
	for(int i=1; i<=n; ++i){
		if(pr[i]!=pr[1]||pc[i]!=pc[1]) continue;
		stat tmp=getst(pa[i],pb[i]);
		pq.push((data){tmp,pv[i]});
		dis[D::ask(tmp.x)][tmp.f]=pv[i];
	}
	lint ans=1e14;
	while(!pq.empty()){
		data dt=pq.top();
		pq.pop();
		int x=D::ask(dt.st.x);
		if(vis[x][dt.st.f]) continue;
		vis[x][dt.st.f]=1;
		if(dt.st.canto(pr[1],pc[1])){
			apn(ans,dt.v);
		}
		for(int i=1; i<=n; ++i){
			if(!dt.st.canto(pr[1]-pr[i],pc[1]-pc[i])) continue;
			stat nst=dt.st*getst(pa[i],pb[i]);
			int y=D::ask(nst.x);
			if(dis[y][nst.f]>dt.v+pv[i]){
				dis[y][nst.f]=dt.v+pv[i];
				pq.push((data){nst,dt.v+pv[i]});
			}
		}
	}
	printf("%lld\n",ans==1e14?-1:ans);
	return 0;
}
