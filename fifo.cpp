#include<iostream>
#include<fstream>
using namespace std;

class lilmem{
	public:
	
	int pageNo;
	int priNo;
	static int currPri;
	static int size;
	
	lilmem(){
		pageNo = -1;
		priNo = -1;
		}	
};

int lilmem::currPri = 0;
int lilmem::size = 0;

int main(){

	int size,i=0, page = -1,flag = 0,minPri= 100,minPriI= 0;
	std::fstream myfile("inpu.txt",std::ios_base::in);
	myfile>>size;
	lilmem::size = size;
	lilmem* lil[size];
	
	for(;i<size;i++)
		lil[i] = new lilmem();
	
	while(myfile>>page){
	
		for(i=0; i<size; i++)
			if(page == lil[i]->pageNo){

				flag = 1;
				break;
				}

		if(flag == 0){
		
			for(i=0; i<size; i++)
				if(lil[i]->priNo < minPri){
					minPri = lil[i]->priNo; 
					minPriI = i;
					}
					
			lilmem::currPri++;
			lil[minPriI]->pageNo = page;
			lil[minPriI]->priNo = lilmem::currPri;		
			
			for(i=0; i<size; i++)
				cout<<lil[i]->pageNo<<"  ";
			cout<<endl;
			minPri= 100;
		}
		flag = 0;
	}	
}		
		
		
		
		
		
		
