#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cstring>
static const int N=150;
static const std::string mp[4]={"010","101","011","111"};

std::string alice(int n,const std::vector <int> &p,long long x){
	static bool invld[N];
	memset(invld,0,sizeof(invld));
	for(int i=0; i<(int)p.size(); ++i){
		invld[p[i]]=1;
	}
	std::string str="";
	for(int pos=0; x&&pos<150; pos+=3){
		int vld_cnt=(1-invld[pos])+(1-invld[pos+1])+(1-invld[pos+2]);
		if(vld_cnt<2){
			str+="000";
		}else if(vld_cnt==2&&(invld[pos]==0||x&1)){
			str+=x&1?(invld[pos+2]?"110":"001"):"100";
			x>>=1;
		}else{
			str+=mp[x&3];
			x>>=2;
		}
	}
	str.resize(n,'0');
	return str;
}

long long bob(const std::string &str){
	static std::string ch="000";
	long long ans=0;
	for(int i=0,cnt=0; i<150; i+=3){
		for(int j=0; j<3; ++j) ch[j]=str[i+j];
		if(ch=="000") continue;
		if(ch=="110"||ch=="100"||ch=="001"){
			if(ch!="100") ans|=1ll<<cnt;
			cnt+=1;
		}
		else{
			for(int i=0; i<4; ++i){
				if(ch==mp[i]){
					ans|=(long long)i<<cnt;
					break;
				}
			}
			cnt+=2;
		}
	}
	return ans;
}
