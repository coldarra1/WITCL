#include<bits/stdc++.h>
using namespace std;

void ac(){
	cout<<"AC"<<endl;
	exit(0);
}
void wa(string reason){
	cout<<"WA "<<reason<<endl;
	exit(0);
}

void readSpace(){
	while(true){
		char ch=getchar();
		if(!isspace((unsigned char)ch)){
			if(ch!=EOF){
				ungetc(ch,stdin);
			}
			break;
		}
	}
}

typedef pair<bool,int> Res;

Res parsePositiveNumber(string number,int min,int max){
	if(number.size()==0){
		return Res(false,1);
	}
	if(number[0]=='0'){
		return Res(false,1);
	}
	long long current=0;
	bool badRange=false;
	for(size_t i=0;i<number.size();i++){
		char ch=number[i];
		if(!isdigit(ch)){
			return Res(false,1);
		}
		int delta=ch^'0';
		current=current*10+delta;
		if(current>max){
			badRange=true;
			current=0;// prevent overflow
		}
	}
	if(current>max||current<min){
		badRange=true;
	}
	if(badRange){
		return Res(false,0);
	}
	return Res(true,(int)current);
}

Res parseNumber(string number,int min,int max){
	if(number.size()==0){
		return Res(false,1);
	}
	if(number=="0"){
		return Res(min<=0&&max>=0,0);
	}
	if(number[0]=='-'){
		Res res=parsePositiveNumber(number.substr(1),-max,-min);
		res.second*=-1;
		return res;
	}
	else{
		return parsePositiveNumber(number,min,max);
	}
}

int readInt(int min,int max,string name){
	string number;
	char ch;
	while(true){
		ch=getchar();
		if(!isspace(ch)&&ch!=EOF){
			number+=ch;
		}
		else{
			ungetc(ch,stdin);
			break;
		}
	}
	Res result=parseNumber(number,min,max);
	if(result.first){
		return result.second;
	}
	else{
		if(result.second){
			wa("format "+name);
		}
		else{
			wa("range "+name);
		}
	}
	return -1;// make `g++ -Wall` happy
}

typedef pair<int,int> Pos;

map<Pos,int> board;
int get(int x,int y){
	map<Pos,int>::iterator it=board.find(Pos(x,y));
	return it==board.end()?0:it->second;
}

bool canModify(int x,int y,int level){
	set<int> s;
	s.insert(get(x+1,y));
	s.insert(get(x-1,y));
	s.insert(get(x,y+1));
	s.insert(get(x,y-1));
	for(int i=max(level-4,1);i<=level-1;i++){
		if(!s.count(i)){
			return false;
		}
	}
	return true;
}

const int MIN_N=1;
const int MAX_N=100;

const int MIN_POS=-1e9;
const int MAX_POS=1e9;

const int MAX_STEPS=1e5;

int main(int argc,char *argv[]){
	assert(argc==2);
    
	FILE *inf=fopen(argv[1],"r");
	assert(inf);
	int n;
	int result=fscanf(inf,"%d",&n);
	fclose(inf);
	assert(result==1);

	assert(n>=MIN_N);
	assert(n<=MAX_N);

	int steps=0;
	readSpace();
	while(!feof(stdin)){
		int x=readInt(MIN_POS,MAX_POS,"x");
		readSpace();
		int y=readInt(MIN_POS,MAX_POS,"y");
		readSpace();
		int v=readInt(1,n,"v");
		if(canModify(x,y,v)){
			steps++;
			if(steps>MAX_STEPS){
				wa("too many steps");
			}
			board[Pos(x,y)]=v;
		}
		else{
			wa("cannot modify");
		}
		readSpace();
	}

	for(map<Pos,int>::iterator it=board.begin();it!=board.end();++it){
		if(it->second==n){
			ac();
		}
	}
	wa("no color n");
}