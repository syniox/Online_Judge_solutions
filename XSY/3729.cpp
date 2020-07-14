#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=105,L=1e3+5;
const int mod=1e9+7;
int n,va[N],vb[N],res[N],cta[N][L],ctb[N][L];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace D{
	int cnt,v[L];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

void getzyz(int x){
	for(int i=2; i<=3.5e4; ++i){
		if(x%i) continue;
		D::add(i);
		while(x%i==0) x/=i;
	}
	if(x>1) D::add(x);
}
int qcnt(int t,const int z){
	int ans=0;
	assert(t);
	for(; t%z==0; t/=z,++ans);
	return ans;
}

int qans(const int p,const int tot){
	static int tgt[L];
	for(int i=1; i<=D::cnt; ++i){
		tgt[i]=qcnt(va[p],D::v[i])+qcnt(vb[p],D::v[i])*tot;
	}
	for(int i=1; i<=n; ++i){
		int cc=-1;
		for(int j=1; j<=D::cnt; ++j){
			int wa=qcnt(va[i],D::v[j]),wb=qcnt(vb[i],D::v[j]);
			if(!wb){
				if(wa!=tgt[j]) return -1;
				continue;
			}
			int curt=tgt[j]-wa;
			if(curt<0||curt%wb) return -1;
			curt/=wb;
			if(cc==-1) cc=curt;
			else if(cc!=curt) return -1;
		}
	}
	int ans=1;
	for(int i=1; i<=D::cnt; ++i){
		while(tgt[i]--) ans=(lint)ans*D::v[i]%mod;
	}
	return ans;
}

bool san0(){
	for(int i=1; i<=D::cnt; ++i){
		for(int j=1; j<=n; ++j){
			if(vb[j]%D::v[i]==0) continue;
			int tgt=qcnt(va[j],D::v[i]),p=1;
			for(; p<=n&&vb[p]%D::v[i]; ++p);
			if(p>n){
				for(int k=2; k<=n; ++k){
					if(qcnt(va[k],D::v[i])!=qcnt(va[1],D::v[i]))
						return puts("-1"),0;
				}
				for(int k=i+1; k<=D::cnt; ++k){
					D::v[k-1]=D::v[k];
				}
				--D::cnt,--i;
				break;
			}
			int tot=tgt-qcnt(va[p],D::v[i]);
			if(tot%qcnt(vb[p],D::v[i])) return puts("-1"),0;
			tot/=qcnt(vb[p],D::v[i]);
			return printf("%d\n",qans(p,tot)),0;
		}
	}
	return 1;
}

bool sanmulp(){
	using namespace D;
	for(int i=2; i<=cnt; ++i){
		for(int j=2; j<=n; ++j){
			if(ctb[1][i]*ctb[j][1]==ctb[1][1]*ctb[j][i]){
				int tmp1=cta[1][i]*ctb[1][1]-ctb[1][i]*cta[1][1];
				int tmp2=cta[j][i]*ctb[1][1]-ctb[1][i]*cta[j][1];
				if(tmp1!=tmp2) return puts("-1"),0;
			}else{
				int numj=cta[1][i]*ctb[1][1]-cta[1][1]*ctb[1][i];
				numj-=cta[j][i]*ctb[1][1]-cta[j][1]*ctb[1][i];
				int denomj=ctb[j][i]*ctb[1][1]-ctb[j][1]*ctb[1][i];
				if(numj%denomj||numj/denomj<0) return puts("-1"),0;
				return qans(j,numj/denomj),0;
			}
		}
	}
	return 1;
}

int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
int exgcd(int x,int y,int &a,int &b,const int c){
	if(!y){
		a=c/x,b=0;
		return x;
	}
	int res=exgcd(y,x%y,a,b,c),tmp=a-(x/y)*b;
	a=b,b=tmp;
	return res;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		va[i]=nxi(),vb[i]=nxi();
		getzyz(va[i]),getzyz(vb[i]);
	}
	D::build();
	if(!san0()) return 0;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=D::cnt; ++j){
			cta[i][j]=qcnt(va[i],D::v[j]);
			ctb[i][j]=qcnt(vb[i],D::v[j]);
		}
	}
	if(!sanmulp()) return 0;
	{
		lint st=1,rs=0;
		for(int i=1; i<=n; ++i){
			int si=ctb[i][1],ri=cta[i][1]%si,a,b;
			if((rs-ri)%gcd(st,si)) return puts("-1"),0;
			exgcd(st,-si,a,b,ri-rs);
			st=st/gcd(st,si)*si;
			rs=((lint)b*si+ri)%st;
		}
		for(int i=1; i<=n; ++i){
			rs+=max(0ll,(cta[i][1]-rs+st-1)/st)*st;
		}
		assert((rs-cta[1][1])%ctb[1][1]==0);
		printf("%d\n",qans(1,(rs-cta[1][1])/ctb[1][1]));
	}
	return 0;
}
