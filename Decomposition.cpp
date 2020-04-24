#include<iostream>
#include<string.h>

using namespace std;


struct Alpha{
	char Attribute;
	int check[10];
}n[10];



class FD{
	private:
		char R[10];	//Relation
		char decR[10];	//decomposed Relationships
		char fdep[10][10];	//Set of FDs
		int no;	//no. of decompositions
		int fno;	//no. of FDs
		int pos[10]; //position of - for each FD
		int LAtcount[10];	//no. of attributes in LHS for each FD
		int RAtcount[10];	//no. of attributes in RHS for each FD
	public:
		void Read();
		void Functional();
		void Check();

};

void FD::Read(){

	cout<<"Enter the Attributes of Relation R: ";
	cin>>R;
	
	cout<<"Enter Number to Decomposed Relations: ";
	cin>>no;
	
	for(int i=0; i<strlen(R); i++){
		n[i].Attribute=R[i];
		
	}
	for(int i=0; i<no; i++){
		cout<<"Enter Attributes for R"<<i+1<<" : ";
		cin>> decR;
		for(int k=0; k<strlen(R); k++){
			for(int j=0; j<strlen(decR); j++){
				if(n[k].Attribute==decR[j]){
					n[k].check[i]=1;
					break;
				}
				else
					n[k].check[i]=0;
			}
		}
	}
	
	for(int i=0; i<strlen(R); i++){
		cout<<n[i].Attribute<<" : ";
		for(int j=0; j<no; j++){
			cout<<n[i].check[j]<<"   ";
		}
		cout<<endl;
	}
	
	Functional();

}
	
void FD::Functional(){ 
	
	cout<<"Enter number of FD's: ";
	cin>>fno;
	cout<<"(put - instead of ->)"<<endl;
	
	for(int i=0; i<fno; i++){
		cout<<"FD"<<i+1<<" is : ";
		cin>>fdep[i];
	}
	/*
	for(int i=0; i<fno; i++)
		cout<<fdep[i]<<"   ";
	cout<<endl;
	*/
	for(int i=0; i<strlen(R); i++){
		for(int j=0; j<fno; j++){
			for(int k=0; k<strlen(fdep[j]); k++){
				if(fdep[j][k]=='-'){
					pos[j]=k;
					break;
				}			
			}
			LAtcount[j]=pos[j];
			RAtcount[j]=strlen(fdep[j])-pos[j]-1;
		}
	}
	/*
	for(int i=0; i<fno; i++){
		cout<<"FD"<<i+1<<" is : ";
		cout<<fdep[i]<<"   "<<LAtcount[i]<<"  "<<RAtcount[i]<<endl;
	}
	cout<<endl;
	*/
	Check();
	
}
	
void FD::Check(){
	int alpcount[fno];
	int flag[fno];

	for(int j=0; j<fno; j++){
		alpcount[j]=0;
		for(int i=0; i<strlen(R); i++){
			
			for(int k=0; k<LAtcount[j]; k++){
				
				if(fdep[j][k]==n[i].Attribute){
					for(int l=0; l<no; l++){
						alpcount[j]+=n[i].check[l];
					}
				//cout<<alpcount[j]<<endl;
				}
				if(alpcount[j]/LAtcount[j]==no){
					flag[j]=1;
					break;
				}
				else{
					flag[j]=0;
				}
			}

		}
		
		for(int i=0; i<strlen(R); i++){
			for(int p=LAtcount[j]; p<strlen(fdep[j]); p++){
				if(fdep[j][p]==n[i].Attribute){
					//cout<<"----bbdhs--";
					for(int l=0; l<no; l++){
						//cout<<"--------aaaa-";
						n[i].check[l]=1;
					}
				}
			}
		}
	}
	
	for(int i=0; i<strlen(R); i++){
		cout<<n[i].Attribute<<" : ";
		for(int j=0; j<no; j++){
			cout<<n[i].check[j]<<"   ";
		}
		cout<<endl;
	}
	
	int countr;
	int fl=0;
	for(int j=0; j<fno; j++){
		countr=0;
		for(int i=0; i<strlen(R); i++){
			countr+=n[i].check[j];
		}
		if(countr==strlen(R)){
			fl=1;
			break;
		}
		
	}
	if(fl==0)
		cout<<"Lossy Decomposition"<<endl;
	else
		cout<<"Lossless Decomposition"<<endl;

}

int main(){
	FD obj;
	obj.Read();

	return 0;
}
