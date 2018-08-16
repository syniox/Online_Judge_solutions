#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
const int N=1e5+2;
int n,inv[2],flip[2],pos[N],map[3][N];
struct B_I_T{
	int tr[N];
	inline void init(){
		memset(tr,0,sizeof(tr));
	}
	inline void add(int x,int v){
		for(;x<=n;x+=x&-x){
			tr[x]+=v;
		}
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x){
			ans+=tr[x];
		}
		return ans;
	}
	inline void mod(const int x,const int y,const int v){
		if(x>y) return;
		add(x,v);
		add(y+1,-v);
	}
}ad;

inline int tri_max(const int a,const int b,const int c){
	if(a>b) return a>c?a:c;
	return b>c?b:c;
}
inline int tri_min(const int a,const int b,const int c){
	if(a<b) return a<c?a:c;
	return b<c?b:c;
}

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=0;i<3;++i){
		for(int j=1;j<=n;++j){
			map[i][j]=nxi();
		}
	}
	for(int i=1;i<=n;++i){
		int x=map[0][i],y=map[1][i],z=map[2][i],w=tri_max(x,y,z);
		if(w-tri_min(x,y,z)!=2||w%3){
			puts("No");
			return 0;
		}
		if((i-w/3)&1){
			puts("No");
			return 0;
		}
		if(z!=w) inv[i&1]^=1;
		pos[w/3]=i;
	}
	for(int i=1;i<=n;i+=2){
		int p=pos[i],add=ad.ask(p);
		flip[1]=(flip[1]+(abs(p+add-i)>>1))&1;
		ad.mod(1,p,2);
	}
	ad.init();
	for(int i=2;i<=n;i+=2){
		int p=pos[i],add=ad.ask(p);
		flip[0]=(flip[0]+(abs(p+add-i)>>1))&1;
		ad.mod(1,p,2);
	}
	if((flip[0]-inv[1])&1||(flip[1]-inv[0])&1) puts("No");
	else puts("Yes");
	return 0;
}
