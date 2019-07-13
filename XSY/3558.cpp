#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <set>
typedef long long lint;
const int mod=1e9+7;
int n,m;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace S1{
	const int C=14;
	int cnt;
	struct prm{
		int v[C];
		friend bool operator < (const prm &a,const prm &b){
			for(int i=0; i<C; ++i){
				if(a.v[i]!=b.v[i]) return a.v[i]<b.v[i];
			}
			return 0;
		}
		friend bool operator == (const prm &a,const prm &b){
			for(int i=0; i<C; ++i){
				if(a.v[i]!=b.v[i]) return 0;
			}
			return 1;
		}
		friend bool operator != (const prm &a,const prm &b){
			return !(a==b);
		}
		friend prm operator + (const prm &a,const prm &b){
			prm c;
			for(int i=0; i<C; ++i){
				c.v[i]=b.v[a.v[i]];
			}
			return c;
		}
	}buk[1000];
	std::set <prm> bprm;

	int solve(const prm &p){
		static bool vis[C];
		memset(vis,0,sizeof(vis));
		int ans=1;
		for(int i=0; i<6; ++i){
			if(vis[i]) continue;
			ans=(lint)ans*n%mod;
			for(int j=i; !vis[j]; vis[j]=1,j=p.v[j]){
				assert(j<6);
			}
		}
		for(int i=6; i<14; ++i){
			if(vis[i]) continue;
			ans=(lint)ans*m%mod;
			for(int j=i; !vis[j]; vis[j]=1,j=p.v[j]){
				assert(j>5);
			}
		}
		return ans;
	}

	int main(){
		//下，上，前，右，后，左
		//三角形：先下后上，正面左棱开始
		buk[++cnt]=(prm){0,1,2,3,4,5,6,7,8,9,10,11,12,13};
		buk[++cnt]=(prm){0,1,3,4,5,2,8,9,10,11,12,13,6,7};
		buk[++cnt]=(prm){2,4,1,3,0,5,7,13,9,11,8,10,6,12};
		buk[++cnt]=(prm){3,5,2,1,4,0,8,6,9,7,11,13,10,12};
		for(int i=1; i<=cnt; ++i){
			bprm.insert(buk[i]);
		}
		int ans=0;
		for(int i=1; i<=cnt; ++i){
			for(int j=1; j<=i; ++j){
				prm res=buk[i]+buk[j];
				if(bprm.find(res)==bprm.end()){
					buk[++cnt]=res;
					bprm.insert(res);
				}
			}
			ans=(ans+solve(buk[i]))%mod;
		}
		return (lint)ans*fpow(cnt,mod-2)%mod;
	}
}

int main(){
	n=nxi(),m=nxi();
	if(n==1&&m==1){
		puts("1");
		return 0;
	}
	//if(m==1) printf("%d\n",S1::main(n));
	printf("%d\n",S1::main());
	return 0;
}
