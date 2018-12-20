#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
typedef long long lint;
const int mod=1e9+7;
lint n;

template <class T> inline T twk(T &x){
	return x>=mod?x-=mod:x;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int prm_pt,pcnt[7],pcal[1<<6];
	std::map <lint,int> mp,nmp;

	inline int get_id(int x,int y){
		if(x>y) std::swap(x,y);
		return x*prm_pt+y;
	}

	inline bool jdg(const lint fr,const int to){
		for(int i=1; i<=prm_pt; ++i){
			if(!(to>>(i-1)&1)) continue;
			for(int j=i+1; j<=prm_pt; ++j){
				if(!(to>>(j-1)&1)) continue;
				if(fr>>get_id(i,j)&1) return 0;
			}
		}
		return 1;
	}

	inline void init(lint n){
		const int SQ=sqrt(n)+1;
		for(int i=2; i<=SQ; ++i){
			if(n%i) continue;
			++prm_pt;
			for(lint y=n/i; n-y*i==0; n=y,y=n/i){
				++pcnt[prm_pt];
			}
		}
		if(n>1) ++pcnt[++prm_pt];
		pcal[0]=1;
		for(int i=1; i<=prm_pt; ++i){
			pcal[1<<(i-1)]=pcnt[i];
		}
		for(int i=1; i<1<<prm_pt; ++i){
			int fr=i&-i;
			pcal[i]=(lint)pcal[i^fr]*pcal[fr]%mod;
		}
	}

	inline int solve(){
		int ans=0;
		mp[0]=1;
		while(!mp.empty()){
			for(std::map <lint,int> ::iterator it=mp.begin(); it!=mp.end(); ++it){
				const lint fr=it->first;
				twk(ans+=it->second);
				int able=0;
				for(int i=1; i<=prm_pt; ++i){
					if(!(fr>>get_id(i,i)&1)) able|=1<<(i-1);
				}
				for(int to=able; to; to=(to-1)&able){
					if(!jdg(fr,to)) continue;
					lint cur=fr|to;
					for(int i=1; i<=prm_pt; ++i){
						if(!(fr>>(i-1)&1)) continue;
						for(int j=1; j<=prm_pt; ++j){
							if((to>>(j-1)&1)) cur|=1ll<<get_id(i,j);
						}
					}
					nmp[cur]=(nmp[cur]+(lint)(it->second)*pcal[to])%mod;
				}
			}
			mp=nmp;
			nmp.clear();
		}
		return twk(ans+=mod-1);
	}
}

int main(){
	n=nxi<lint>();
	S::init(n);
	printf("%d\n",S::solve());
	return 0;
}
