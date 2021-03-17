#include <iostream>
using namespace std;
typedef enum{st0,st500,st1000,stopen,stkembali} state_t;
state_t presentState;
state_t nextState;
int datain;
int C500,C1000=0;
void ceksensor(void);
void dropCandy();
void dropKoin();
int main() {
	presentState=st0;
	cout<<"vending machine 1.1"<<endl;
	while(1)
	{
		switch (presentState) {
		case st0:
			ceksensor();
			cout<<"st0: ";
			if(C500) {
				nextState=st500;
			} else if (C1000){
				nextState=st1000;
			}
			break;
		case st500:
			cout<<"st500: ";
			ceksensor();
			if(C500) {
				nextState=st1000;
			} else if (C1000){
				nextState=stopen;
			}
			break;
		case st1000:
			cout<<"st1000: ";
			ceksensor();
			if(C500) {
				nextState=stopen;
			} else if (C1000){
				nextState=stkembali;
			}
			break;
		case stkembali:
			dropKoin();
			nextState=stopen;
			break;
		case stopen:
			cout<<"stopen: ";
			nextState=st0;
			dropCandy();
			break;
		}
		presentState=nextState;
	}
	return 0;
}

void ceksensor(void){
	cout<<"masukkan koin";
	cin>>datain;
	if(datain==500) {
		C500=1;
		C1000=0;
	} else if (datain==1000) {
		C500=0;
		C1000=1;
	} else {
		C500=0;
		C1000=0;
	}
}
void dropCandy(){
	cout <<"permen keluar"<<endl;
}
void dropKoin(){
	cout <<"kembali 500"<<endl;
}
