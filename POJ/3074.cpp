#include <iostream>
#include <cstdio>
#include <cstring>
const int N=9;
const int S=3;
int cbit[1<<N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=1; i<1<<9; ++i){
		cbit[i]=cbit[i>>1]+(i&1);
	}
}

namespace G{
	int mp[N][N],bel[N][N];
	int vld_row[N],vld_col[N],vld_sqr[N];
	//actually used

	inline int get_sqr(int x,int y){
		return x/S*S+y/S;
	}

	inline void clear(){
		memset(mp,0,sizeof(mp));
		memset(vld_row,0,sizeof(vld_row));
		memset(vld_col,0,sizeof(vld_col));
		memset(vld_sqr,0,sizeof(vld_sqr));
	}

	inline void init(){
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				bel[i][j]=get_sqr(i,j);
			}
		}
	}

	inline int get_vld(const int x,const int y){
		return vld_row[x]|vld_col[y]|vld_sqr[bel[x][y]];
	}

	inline void fill(int x,int y,int v){
		if(v==0) return;
		mp[x][y]^=v;
		vld_row[x]^=1<<(v-1);
		vld_col[y]^=1<<(v-1);
		vld_sqr[bel[x][y]]^=1<<(v-1);
	}

	bool dfs(){
		int bx=0,by=0,st=0;
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				if(mp[i][j]) continue;
				int tmp=get_vld(i,j);
				if(cbit[st]<cbit[tmp]){
					bx=i,by=j,st=tmp;
				}
			}
		}
		if(mp[bx][by]){
			for(int i=0; i<N; ++i){
				for(int j=0; j<N; ++j){
					printf("%d",mp[i][j]);
				}
			}
			puts("");
			return 1;
		}
		for(int i=1; i<=9; ++i){
			if(!((st>>(i-1))&1)){
				fill(bx,by,i);
				if(dfs()) return 1;
				fill(bx,by,i);
			}
		}
		return 0;
	}
}

int main(){
	static char ch[N*N];
	init();
	G::init();
	for(;;){
		scanf("%s",ch);
		if(ch[0]=='e') break;
		G::clear();
		for(int i=0,cnt=0; i<N; ++i){
			using namespace G;
			for(int j=0; j<N; ++j,++cnt){
				if(ch[cnt]!='.') fill(i,j,ch[cnt]-'0');
			}
		}
		G::dfs();
	}
	return 0;
}
