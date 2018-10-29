#include<iostream>
#include<cstdio>
#include<cstring>
int n,ans;
char ch[22];
struct data{
	//idx:3456789{10}JQKA2wW
	short cnt[15];
}dt;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int calc(const data &dt){
	int cnt[5]={0};
	cnt[1]+=dt.cnt[13]^dt.cnt[14];
	for(int i=0;i<13;++i){
		++cnt[dt.cnt[i]];
	}
	int f1=(cnt[4]<<1)+cnt[3];
	if(cnt[1]-f1<2) return 100;
	for(int i=0;i<15;++i){
		if(dt.cnt[i]==1){
			if(--f1==-2) return i;
		}
	}
	return 0;
}

void dfs(data dt){
	apx(ans,calc(dt));
	for(int i=5;i<=11;++i){
		for(int j=0;j<=11-i+1;++j){
			bool f=1;
			for(int k=0;k<i;++k){
				if(!dt.cnt[j+k]){
					f=0;break;
				}
			}
			if(f){
				for(int k=0;k<i;++k){
					--dt.cnt[j+k];
				}
				dfs(dt);
				for(int k=0;k<i;++k){
					++dt.cnt[j+k];
				}
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	scanf("%s",ch+1);
	data dt;
	memset(&dt,0,sizeof(dt));
	for(int i=1;i<=n;++i){
		switch(ch[i]){
			case 'T': ++dt.cnt[7];break;
			case 'J': ++dt.cnt[8];break;
			case 'Q': ++dt.cnt[9];break;
			case 'K': ++dt.cnt[10];break;
			case 'A': ++dt.cnt[11];break;
			case '2': ++dt.cnt[12];break;
			case 'w': ++dt.cnt[13];break;
			case 'W': ++dt.cnt[14];break;
			default: ++dt.cnt[ch[i]-'3'];
		}
	}
	dfs(dt);
	switch(ans){
		case 7: puts("10");break;
		case 8: puts("J");break;
		case 9: puts("Q");break;
		case 10: puts("K");break;
		case 11: puts("A");break;
		case 12: puts("2");break;
		case 13: puts("w");break;
		case 14: puts("W");break;
		case 100: puts("-1");break;
		default: putchar(ans+'3'),putchar('\n');
	}
	return 0;
}
