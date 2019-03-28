#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
const int N=12;
const double Pi=acos(-1);
const double eps=1e-12;
int n,q;
double rq,sinq,cosq,tanq,ans;
bool vis[1<<N][1<<N],exist[1<<N][1<<N];
//编号大的在上面

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void oput_mtrx(){
	for(int i=(1<<n)-1; i; --i){
		for(int j=1; j<1<<n; ++j){
			putchar(exist[i][j]?'*':' ');
		}
		puts("");
	}
}

inline void get_mtrx(){
	exist[1][1]=1;
	for(int i=2; i<=n; ++i){
		int sz=(1<<(i-1))-1;
		for(int j=1; j<=sz; ++j){
			memcpy(exist[j]+sz+2,exist[j]+1,sz*sizeof(bool));
		}
		for(int j=1; j<=sz; ++j){
			for(int k=1; k<=sz; ++k){
				exist[sz+1+k][sz+1-j]=exist[j][k]^1;
				exist[sz*2+2-k][sz+1+j]=exist[j][k]^1;
			}
		}
		for(int j=1; j<=sz*2+1; ++j){
			exist[sz+1][j]=1;
		}
		for(int j=1; j<=sz; ++j){
			exist[sz+1+j][sz+1]=1;
		}
	}
}

inline double calc(double h){
	if(q==0) return h;
	int type=(h>=sinq)+(h>=cosq);
	if(type==0){
		return h*h;
	}
	else if(type==1){
		if(cosq<sinq) return cosq*(h*2-cosq);
		else return sinq*(h*2-sinq);
	}
	else{
		double len=sinq+cosq-h;
		return sinq*cosq*2-(len*len);
	}
}

inline bool valid(const int x,const int y){
	return x>0&&x<1<<n&&y>0&&y<1<<n&&exist[x][y]&&!vis[x][y];
}

double dfs(const int x,const int y,const double h){
	if(vis[x][y]==1){
		fprintf(stderr,"visited %d %d.\n",x,y);
		return 0;
	}
	ans+=calc(h);
	//printf("%d %d %lf\n",x,y,ans);
	vis[x][y]=1;
	if(valid(x-1,y)){
		double newh=std::min(cosq+sinq,h+cosq);
		dfs(x-1,y,newh);
	}
	if(valid(x+1,y)){
		double newh=h-cosq;
		if(newh>eps) dfs(x+1,y,newh);
	}
	if(valid(x,y-1)){
		double newh=std::min(cosq+sinq,h+sinq);
		dfs(x,y-1,newh);
	}
	if(valid(x,y+1)){
		double newh=h-sinq;
		if(newh>eps) dfs(x,y+1,newh);
	}
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	rq=Pi/180*q;
	sinq=sin(rq),cosq=cos(rq),tanq=tan(rq);
	get_mtrx();
	//oput_mtrx();
	int sz=(1<<n)-1;
	for(int i=1; i<=sz; ++i){
		if(exist[sz][i]) dfs(sz,i,cosq);
	}
	printf("%lf\n",q?ans/sinq/cosq/2:ans);
	return 0;
}
