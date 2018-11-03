#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2005;
int mp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool jdg(const int x1,const int y1,const int x2,const int y2){
	if(mp[x1][y1]!=mp[x2][y2]) return 0;
	const int ddl=mp[x1][y1];
	for(int i=std::min(x1,x2);i<=std::max(x1,x2);++i){
		if(mp[i][y1]<ddl) return 0;
	}
	for(int i=std::min(y1,y2);i<=std::max(y1,y2);++i){
		if(mp[x2][i]<ddl) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	nxi(),nxi();
	for(int q=nxi();q--;){
		const int op=nxi(),x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
		if(op==1){
			for(int i=x1;i<=x2;++i){
				for(int j=y1;j<=y2;++j) ++mp[i][j];
			}
		}
		else if(op==2){
			for(int i=x1;i<=x2;++i){
				for(int j=y1;j<=y2;++j) --mp[i][j];
			}
		}
		else puts(jdg(x1,y1,x2,y2)?"Yes":"No");
	}
	return 0;
}
