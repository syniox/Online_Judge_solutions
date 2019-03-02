#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
const int Q=100;
const int S=10;
int n,q,status[Q],lg2[1<<S],universal[Q];
char ch[Q][30];
std::bitset <32768> bs[S][1<<S];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=0; i<10; ++i){
		lg2[1<<i]=i;
	}
}

inline void get_bs(const int p){
	static std::bitset <32768> tp_st[10];
	const int all=(1<<(n>>1))-1;
	for(int i=0; i<S; ++i){
		const int cur=i+p*S;
		tp_st[i].reset();
		for(int j=0; j<1<<(n>>1); ++j){
			if((j^(status[cur]&all))&(all^(universal[cur]&all))) continue;
			tp_st[i][j]=1;
		}
	}
	for(int i=1; i<1<<S; ++i){
		int lbit=i&-i;
		bs[p][i]=bs[p][i^lbit]|tp_st[lg2[lbit]];
	}
}

inline int ask_bs(const int st){
	static std::bitset <32768> res;
	const int cnt_s=q/S;
	const int all=(1<<(n>>1))-1;
	res.reset();
	for(int i=0; i<cnt_s; ++i){
		int able=0;
		for(int j=i*S; j<(i+1)*S; ++j){
			if((st^(status[j]>>(n>>1)))&(all^(universal[j]>>(n>>1)))) continue;
			able|=1<<(j-i*S);
		}
		res|=bs[i][able];
	}
	return res.count();
}

int main(){
	init();
	n=nxi(),q=nxi();
	for(int i=0; i<q; ++i){
		scanf("%s",ch[i]);
		for(int j=0; j<n; ++j){
			status[i]|=(ch[i][j]=='1')<<j;
			universal[i]|=(ch[i][j]=='?')<<j;
		}
	}
	n+=n&1;//changing status is unnecessary
	for(; q%10; ++q){
		status[q]=status[0];
		universal[q]=universal[0];
	}
	for(int i=0; i<q/S; ++i){
		get_bs(i);
	}
	int ans=0;
	for(int i=0; i<1<<(n>>1); ++i){
		ans+=ask_bs(i);
	}
	printf("%d\n",ans);
	return 0;
}
