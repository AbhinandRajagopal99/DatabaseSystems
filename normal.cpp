#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

struct attribute{
	char Attribute;
	int check;
}n[10];

struct closure{
	char p[10];
	int cl;
}clo[20];

int f;
char close[100];
int s=0;
char noprimetemp[10];

class normal{
	private:
		char R[10];	//Relation
		char fdep[10][10];	//Set of FDs
		int fno;	//no. of FDs
		//int pos[10]; //position of - for each FD
		int LAtcount[10];	//no. of attributes in LHS for each FD
		int RAtcount[10];	//no. of attributes in RHS for each FD
		char LAt[10][10];	//LHS Attributes in FD
		char RAt[10][10];	//RHS Attributes in FD
		char prime[10];		//Prime Attributes
		char noprime[10];
		int k;		//No. of prime attributes

	public:
		void Read();
		void candidate();
		int Closure();
		int NF2();
		int NF3();
		int BCNF();
};

void normal::Read(){
	cout<<"Enter the Attributes of Relation R: ";
	cin>>R;
	
	for(int i=0; i<strlen(R); i++){
		n[i].Attribute=R[i];
		
	}
	
	cout<<"Enter number of FD's: ";
	cin>>fno;
	cout<<"(put space instead of ->)"<<endl;
	
	for(int i=0; i<fno; i++){
		cout<<"FD"<<i+1<<" is : ";
		cin>>LAt[i]>>RAt[i];
	}
	
	for(int j=0; j<fno; j++){
		LAtcount[j]=strlen(LAt[j]);
		RAtcount[j]=strlen(RAt[j]);
	}
	 /*
	for(int i=0; i<fno; i++){
		cout<<"FD"<<i+1<<" is : ";
		cout<<LAtcount[i]<<"  "<<RAtcount[i]<<"  ";
		cout<<"  "<<LAt[i]<<"   ~~~~~  "<<RAt[i]<<endl;
	}
	cout<<endl;
	*/
	for(int i=0; i<strlen(R); i++){
			n[i].check=0;
		
	}
	
	candidate();
}

void normal::candidate(){

	for(int j=0; j<fno; j++){
		for(int p=0; p<RAtcount[j]; p++){
			for(int i=0; i<strlen(R); i++){
				if(RAt[j][p]==n[i].Attribute){
					n[i].check=1;
					break;
				}
			}
		}
	}
	
	
	for(int i=0; i<strlen(R); i++){
		cout<<n[i].Attribute<<" : ";
		cout<<n[i].check<<"   "<<endl;
	}
	cout<<endl;
	
	k=0;
	for(int i=0; i<strlen(R); i++){
		if(n[i].check==0){
			prime[k]=n[i].Attribute;
			k++;
		}
	}
	cout<<"Intial prime attribute: ";
	for(int i=0; i<k; i++)
		cout<<prime[i];
	cout<<endl;
	
	strcpy(clo[0].p, prime);

	strcpy(close, clo[0].p);
	f=0;
	
	//------------------------------REMEMBER TO UPDATE K also
	
	int csize=Closure();
	char temp[20];
	int flag=0;
	if(csize==0){
		cout<<"true\n";
		clo[0].cl=0;
		strcpy(prime, clo[0].p);
		cout<<prime;
		k=strlen(prime);
		f=1;
		flag=1;
	}
	else{
		cout<<"false\n";
		
		int start = f;
		int end = strlen(R)-k;
		
		//Current non prime:
		strcpy(noprimetemp, R);
		for(int j=0; j<k; j++){
			for(int i=0; i<strlen(R); i++){
				if(prime[j]==n[i].Attribute)
					noprimetemp[i]='1';
			}
		}
		for(int i=0; i<strlen(R); i++)
			if(noprimetemp[i]!='1'){
				noprime[s]=noprimetemp[i];
				s++;
			}
		noprime[s]='\0';
		//int cheend=strlen(noprime);
		//cout<<cheend<<"~~~~"<<end;
		cout<<"Non Prime: "<<noprime<<endl;
		int b=0;
		
		for(int i=start; i<end; i++){
			strcpy(clo[i].p, prime);
			int g= strlen(clo[i].p);
			clo[i].p[g]=noprime[b];
			b++;
			g++;
			clo[i].p[g]='\0';
		}
		cout<<endl;
		for(int j=start; j<end; j++){
			cout<<clo[j].p<<"    ";
			sort(clo[j].p, clo[j].p+end);
			strcpy(close, clo[j].p);
			int psize=Closure();
			
			if(psize==0){
				cout<<"trueeee\n";
				clo[j].cl=0;
				strcpy(prime, clo[j].p);
				k=strlen(prime);
				flag=1;
				break;	
			}
			else
				clo[j].cl=-1;
			
		}
		/*
		int cou;
		strcpy(temp, prime);
		int q=k;
		for(int i=0; i<strlen(R); i++){
			cou=0;
			for(int j=0; j<k; j++){
				if(prime[j]!=n[i].Attribute){
					cou++;
				}
				
			}
			cout<<cou<<"-------------"<<endl;
		
			if(cou==strlen(R)-k){
				temp[q]=n[i].Attribute;
				strcpy(close,temp);
				int psize=Closure();
				
				if(psize==0){
					cout<<"true\n";
					prime[k]=n[i].Attribute;
					k++;
				}
				else
					cout<<"false\n";
			}
		}
		*/
	}
	
	/*
	//--------------NON PRIME ATTRIBUTES???
	for(int i=0; i<strlen(R); i++){
		for(int j=0; j<k; j++){
			if(prime[j]==n[i].Attribute)//-----
				
		}
	}
	
	*///-----------------
	if(flag==1){
	int nf2check=NF2();
	if(nf2check==1){
		int nf3check=NF3();
		if(nf3check==1){
			
			int bcnfcheck=BCNF();
				if(bcnfcheck==1)
					cout<<"HIGHEST NORMAL FORM: BCNF"<<endl;
				else
					cout<<"HIGHEST NORMAL FORM: 3NF"<<endl;
			//cout<<"~~~~~~~~~";
		}
		
		else
			cout<<"HIGHEST NORMAL FORM: 2NF"<<endl;
	
	}
	else
		cout<<"ASSUMED TO BE ATOMIC: HIGHEST NORMAL FORM: 1NF"<<endl;
	}
}

int isSubstring(char s1[], char s2[]){
	int M=strlen(s1);
	int N=strlen(s2);
	
	for(int i=0; i<=N-M; i++){
		int j;
		for(j=0; j<M; j++)
			if(s2[i+j] != s1[j])
				break;
			if(j==M)
				return i;
		
	}
	return -1;

}

int normal::Closure(){
	
	int check, index;
	//cout<<strlen(close);
	
	for(int i=0; i<fno; i++){
		
		
		check=isSubstring(LAt[i],close);
		cout<<check<<endl;
		if(check>=0)
		{
			for(int x=0; x<RAtcount[i]; x++){
				check=-1;
			
				for(int l=0; l<strlen(close); l++)
				{
					if(RAt[i][x]==close[l])
					{
						check=l;
						break;
					}	
				}
				
				if(check<0)
				{
					index=strlen(close);
					cout<<index<<endl;
					close[index]=RAt[i][x];
					close[index+1]='\0';
					//index+=2;
				}
			}
		
		}
	
	}
	
	cout<<close;
	cout<<endl;
	return strlen(close)-strlen(R);	
}

int normal::NF2(){
	int count2=0;
	int in2count=0;
	for(int i=0; i<fno; i++){
		for(int j=0; j<LAtcount[i]; j++){
			for(int m=0; m<k; m++){	
				if(LAt[i][j]==prime[m]){
					in2count++;
					break;
				}
			}
			//cout<<in2count;
			if(in2count==0 || in2count==k)
				count2++;
		}
		//cout<<"-----"<<count2;
	}
	
	if(count2==fno)
		return 1;
	else 
		return 0;
}

int normal::NF3(){
	int count3=0;
	int in3count=0;
	
	if(count3==fno)
		return 1;
	else
		return 0;

}

int normal::BCNF(){
  int countbc=0;
  int inbccount=0;
  
  if(countbc==fno)
    	return 1;
  else
    	return 0;
}

int main(){
	normal obj;
	obj.Read();
	int csize;
	
	return 0;
}
