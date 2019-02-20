#include <iostream>
#include <cstdio>
#include <cstring>
const int N=9;
const int S=3;
int cbit[1<<N],fpos[1<<N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=1; i<1<<N; ++i){
		cbit[i]=cbit[i>>1]+(i&1);
	}
	for(int i=0; i<N; ++i){
		fpos[((1<<N)-1)^(1<<i)]=i;
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

	inline void reset(int bak_mp[N][N],int bak_row[N],int bak_col[N],int bak_sqr[N]){
		memcpy(mp,bak_mp,sizeof(mp));
		memcpy(vld_row,bak_row,sizeof(vld_row));
		memcpy(vld_col,bak_col,sizeof(vld_col));
		memcpy(vld_sqr,bak_sqr,sizeof(vld_sqr));
	}

	inline bool sanitize_rc(){
		int st[N];
		for(int i=0; i<N; ++i){
			memset(st,0,sizeof(st));
			for(int j=0; j<N; ++j){
				if(mp[i][j]) continue;
				int tmp=((1<<N)-1)^get_vld(i,j);
				for(int k=0; k<N; ++k){
					if(tmp>>k&1) st[k]|=1<<j;
				}
			}
			for(int j=0; j<N; ++j){
				if(vld_row[i]>>j&1) continue;
				if(cbit[st[j]]==0) return 0;
				if(cbit[st[j]]==1){
					int pos=fpos[((1<<N)-1)^st[j]];
					fill(i,pos,j+1);
				}
			}
		}

		for(int i=0; i<N; ++i){
			memset(st,0,sizeof(st));
			for(int j=0; j<N; ++j){
				if(mp[j][i]) continue;
				int tmp=((1<<N)-1)^get_vld(j,i);
				for(int k=0; k<N; ++k){
					if(tmp>>k&1) st[k]|=1<<j;
				}
			}
			for(int j=0; j<N; ++j){
				if(vld_col[i]>>j&1) continue;
				if(cbit[st[j]]==0) return 0;
				if(cbit[st[j]]==1){
					int pos=fpos[((1<<N)-1)^st[j]];
					fill(pos,i,j+1);
				}
			}
		}
		return 1;
	}

	bool dfs(){
		int bak_mp[N][N],bak_row[N],bak_col[N],bak_sqr[N];
		memcpy(bak_mp,mp,sizeof(bak_mp));
		memcpy(bak_row,vld_row,sizeof(bak_row));
		memcpy(bak_col,vld_col,sizeof(bak_col));
		memcpy(bak_sqr,vld_sqr,sizeof(bak_sqr));

		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				if(mp[i][j]) continue;
				int tmp=get_vld(i,j);
				if(cbit[tmp]!=N-1) continue;
				fill(i,j,fpos[tmp]+1);
			}
		}

		if(!sanitize_rc()){
			reset(bak_mp,bak_row,bak_col,bak_sqr);
			return 0;
		}

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
		for(int i=1; i<=N; ++i){
			if(!((st>>(i-1))&1)){
				fill(bx,by,i);
				if(dfs()) return 1;
				fill(bx,by,i);
			}
		}
		reset(bak_mp,bak_row,bak_col,bak_sqr);
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
