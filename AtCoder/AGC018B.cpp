#include<iostream>
#include<cstdio>
#include<cstring>
const int N=302;
int n,m,ans,pt[N],buk[N],mp[N][N];
bool vis[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void upd_ans(){
	int tp=0;
	for(int j=1;j<=m;++j){
		apx(tp,buk[j]);
	}
	apn(ans,tp);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	ans=(int)1e8;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			mp[i][j]=nxi();
		}
	}
	for(int i=1;i<=n;++i){
		pt[i]=1;
		++buk[mp[i][1]];
	}
	for(int i=1;i<m;++i){
		upd_ans();
		int xbuk=0,idx;
		for(int j=1;j<=m;++j){
			if(buk[j]>xbuk){
				xbuk=buk[j];
				idx=j;
			}
		}
		vis[idx]=1;
		for(int i=1;i<=n;++i){
			for(;pt[i]<=m&&vis[mp[i][pt[i]]];++pt[i]){
				--buk[mp[i][pt[i]]];
				++buk[mp[i][pt[i]+1]];
			}
		}
	}
	upd_ans();
	printf("%d\n",ans);
	return 0;
}
