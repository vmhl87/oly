#include <iostream>
#include <string>
using namespace std;

int ltr[26],*word,len=0,mlen=0;
bool *endp;

void setup_ends(){
	string end_ids;
	getline(cin,end_ids);
	getline(cin,end_ids);
	int buf=0;
	for(char c:end_ids){
		if(c==' '){
			if(buf<mlen+1&&buf>0)endp[buf-1]=1;
			buf=0;
		}else buf=10*buf+c-'0';
	}
	if(buf>0)endp[buf-1]=1;
	else endp[mlen-1]=1;
}

bool is_vowel(int id){
	char idc=id+'a';
	if(idc=='a')return 1;
	if(idc=='e')return 1;
	if(idc=='i')return 1;
	if(idc=='o')return 1;
	if(idc=='u')return 1;
	if(idc=='y')return 1;
	return 0;
}

void iterate(){
	if(len>3&&!is_vowel(word[len-1])&&!is_vowel(word[len-2]))
		if(!is_vowel(word[len-3])&&!is_vowel(word[len-4]))return;
	if(endp[len-1]){
		for(int i=0;i<len;i++)cout<<(char)('a'+word[i]);
		cout<<'\n';
	}
	if(len==mlen)return;
	for(int i=0;i<26;i++)if(ltr[i]>0){
		word[len]=i;
		len++;
		ltr[i]--;
		iterate();
		len--;
		ltr[i]++;
	}
}

int main(){
	for(int i=0;i<26;i++)ltr[i]=0;
	string letters;
	cin>>letters;
	for(char c:letters)ltr[c-'a']++;
	mlen=letters.length();
	word=new int[mlen];
	endp=new bool[mlen];
	setup_ends();
	iterate();
	delete[] word;
	delete[] endp;
}
