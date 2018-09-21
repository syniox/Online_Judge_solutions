#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e6+2;
int n,llen,rlen,lc[N],rc[N],lsq[N],rsq[N];
int dif[N],col[N],end_col_pos[N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void get(int cc[N],int sq[N],const bool fx){
	static int lk[N],buk[N],pos_c[N];
	memset(buk,0,sizeof(buk));
	int st=1,ed=n,sp=fx?-1:1;
	if(fx) std::swap(st,ed);
	st-=sp;
	for(int i=ed;i!=st;i-=sp){
		lk[i]=buk[col[i]];
		buk[col[i]]=i;
	}
	st+=sp;
	const int len=fx?rlen:llen;
	pos_c[0]=st-sp;
	ed+=sp;
	for(int i=1;i<=len;++i){
		pos_c[i]=buk[sq[i]];
		while(pos_c[i]&&((pos_c[i]<pos_c[i-1])^fx||pos_c[i]==pos_c[i-1])) pos_c[i]=lk[pos_c[i]];
	}
	for(int i=st-sp;i!=ed;i+=sp){
		pos_c[0]=i;
		for(int j=1;j<=len;++j){
			const int tp=pos_c[j];
			while(pos_c[j]&&((pos_c[j]<pos_c[j-1])^fx||pos_c[j]==pos_c[j-1])) pos_c[j]=lk[pos_c[j]];
			if(pos_c[j]==tp) break;
			if(!pos_c[j]) return;
		}
		cc[i]=pos_c[len];
	}
}

inline void oput(){
	static int buf[N];
	const int aim_col=lsq[llen];
	int cur=0,ans=0;
	for(int i=1;i<=n;++i){
		if((cur+=dif[i])>0&&col[i]==aim_col){
			buf[++ans]=i;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;++i){
		printf("%d ",buf[i]);
	}
	puts("");
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi(),nxi();
	for(int i=1;i<=n;++i){
		col[i]=nxi();
		end_col_pos[col[i]]=i;
	}
	llen=nxi(),rlen=nxi();
	for(int i=1;i<=llen;++i){
		lsq[i]=nxi();
	}
	for(int i=1;i<=rlen;++i){
		rsq[i]=nxi();
	}
	get(lc,lsq,0);
	get(rc,rsq,1);
	for(int i=1;i<=n;++i){
		const int st=lc[i],ed=rc[end_col_pos[col[i]]];
		if(st&&ed&&st<=ed) ++dif[st],--dif[ed+1];
	}
	oput();
	return 0;
}
