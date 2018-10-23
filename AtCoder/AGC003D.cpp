#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
typedef long long lint;
const int N=1e5+5,S=2200;
int n,ans,cnp,prm[S];
lint f3[S];
bool npr[S];
std::map <lint,int> mp;

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=2;i<S;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<S;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
	for(int i=1;i<=cnp;++i){
		f3[i]=(lint)prm[i]*prm[i]*prm[i];
	}
}

inline void san(lint &x){
	for(int i=1;i<=cnp;++i){
		while(x%f3[i]==0) x/=f3[i];
	}
}

inline lint get_link(lint x){
	lint res=1;
	for(int i=1;i<=cnp;++i){
		int cnt=0;
		while(x%prm[i]==0){
			x/=prm[i],++cnt;
		}
		cnt%=3;
		if(cnt) res*=cnt==1?prm[i]*prm[i]:prm[i];
	}
	const lint tp=sqrt(x);
	if(tp*tp==x) res*=tp;
	else res*=x*x;
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	init();
	n=nxi<int>();
	for(int i=1;i<=n;++i){
		lint hx=nxi<lint>();
		san(hx);
		++mp[hx];
	}
	std::map <lint,int> ::iterator it;
	for(it=mp.begin();it!=mp.end();mp.erase(it++)){
		const lint y=get_link(it->first);
		if(mp.find(y)==mp.end()) ans+=it->second;
		else if(y==it->first) ++ans;
		else{
			ans+=std::max(it->second,mp[y]);
			mp.erase(y);
		}
	}
	printf("%d\n",ans);
	return 0;
}
