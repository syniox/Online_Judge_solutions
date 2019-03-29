#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=31;
const int mod=998244353;
int qm,m,n,fir[N<<1][N<<1][N],nxt[N<<1][N<<1][N],alw[N<<1][N<<1][N];
int fir_ext[N<<1][N<<1],invld_x[N],invld_y[N];
bool invld[N<<1][N<<1];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

template <class T> inline T abs(const T x){
	return x<0?-x:x;
}

inline void mul(const int len,int *a,const int *b,int *c=NULL){
	static lint Lim=1e18*8;
	if(c==NULL) c=a;
	for(int i=len-1; ~i; --i){
		lint tmp=0;
		for(int j=i; ~j; --j){
			tmp+=(lint)a[j]*b[i-j];
			tmp<Lim?0:tmp%=mod;
		}
		c[i]=tmp%mod;
	}
}

void work_cyc(int tmp1[N<<1][N<<1],int tmp2[N<<1][N<<1],
		const int lim,const int fx=N,const int fy=N){
	for(int i=-lim; i<=lim; ++i){
		const int len=lim-abs(i);
		for(int j=-len; j<=len; ++j){
			const int cur=tmp1[i+fx][j+fy];
			if(!cur) continue;
			twk(tmp2[i+fx+0][j+fy-1]+=cur);
			twk(tmp2[i+fx-1][j+fy+0]+=cur);
			twk(tmp2[i+fx+0][j+fy+1]+=cur);
			twk(tmp2[i+fx+1][j+fy+0]+=cur);
		}
	}
	for(int i=1; i<=m; ++i){
		tmp2[invld_x[i]][invld_y[i]]=0;
	}
}

inline void build(const int x,const int y){
	static int tmp1[N<<1][N<<1],tmp2[N<<1][N<<1];
	memset(tmp2,0,sizeof(tmp2));
	tmp2[N][N]=1;
	int fir_ext=-1;
	fir[x][y][0]=tmp2[x][y];
	if(fir[x][y][0]) fir_ext=0;
	for(int step=1; (x!=N||y!=N)&&step<=qm; ++step){
		memcpy(tmp1,tmp2,sizeof(tmp1));
		memset(tmp2,0,sizeof(tmp2));
		work_cyc(tmp1,tmp2,step);
		fir[x][y][step]=tmp2[x][y];
		if(fir[x][y][step]&&fir_ext==-1) fir_ext=step;
		tmp2[x][y]=0;
	}
	::fir_ext[x][y]=fir_ext;
	if(fir_ext==-1) return;
	memset(tmp2,0,sizeof(tmp2));
	tmp2[x][y]=1;
	for(int step=1; step<=qm-fir_ext; ++step){
		memcpy(tmp1,tmp2,sizeof(tmp1));
		memset(tmp2,0,sizeof(tmp2));
		work_cyc(tmp1,tmp2,step,x,y);
		nxt[x][y][step]=tmp2[x][y];
		tmp2[x][y]=0;
	}
	memset(tmp2,0,sizeof(tmp2));
	tmp2[x][y]=1;
	alw[x][y][0]=1;
	for(int step=1; step<=qm-fir_ext; ++step){
		memcpy(tmp1,tmp2,sizeof(tmp1));
		memset(tmp2,0,sizeof(tmp2));
		work_cyc(tmp1,tmp2,step,x,y);
		for(int i=-step; i<=step; ++i){
			const int len=step-abs(i);
			for(int j=-len; j<=len; ++j){
				twk(alw[x][y][step]+=tmp2[i+x][j+y]);
			}
		}
	}
}

int get_ans(const int* flw,const int* nxt,const int* alw){
	static int res[N];
	memcpy(res,flw,(qm+1)*sizeof(int));
	for(int i=1; i<n; ++i){
		mul(qm+1,res,nxt);
	}
	mul(qm+1,res,alw);
	assert(res[qm]<mod);
	return res[qm];
}

int main(){
	qm=nxi(),m=nxi(),n=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		invld[a+N][b+N]=1;
		invld_x[i]=a+N,invld_y[i]=b+N;
	}
	for(int i=-qm; i<=qm; ++i){
		const int len=qm-abs(i);
		for(int j=-len; j<=len; ++j){
			if(!invld[i+N][j+N]) build(i+N,j+N);
		}
	}
	int ans=0;
	for(int i=-qm; i<=qm; ++i){
		const int len=qm-abs(i);
		for(int j=-len; j<=len; ++j){
			if(invld[i+N][j+N]||fir_ext[i+N][j+N]==-1) continue;
			twk(ans+=get_ans(fir[i+N][j+N],nxt[i+N][j+N],alw[i+N][j+N]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
