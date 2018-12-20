#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
const int N=1e5+5;
const int mod=1e9+7;
int n,cnt_mp,mp[128];
char ch[N];
struct state{
	int x[53];
	bool operator < (const state &b) const {
		for(int i=1; i<=cnt_mp; ++i){
			if(x[i]!=b.x[i]) return x[i]<b.x[i];
		}
		return 0;
	}
};
std::map <state,int> h_map;

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=1; i<=n; ++i){
		if(!mp[(int)ch[i]]) mp[(int)ch[i]]=++cnt_mp;
	}
}

inline int solve(){
	static state buk;
	++h_map[buk];
	int ans=0;
	for(int i=1; i<=n; ++i){
		int x=mp[(int)ch[i]];
		if(x>1) ++buk.x[x];
		if(x<cnt_mp) --buk.x[x+1];
		twk(ans+=h_map[buk]);
		++h_map[buk];
	}
	return ans;
}

int main(){
	n=nxi();
	scanf("%s",ch+1);
	init();
	printf("%d\n",solve());
	return 0;
}
