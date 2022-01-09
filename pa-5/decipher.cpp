#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/

  ifstream ifile;
  ifile.open(argv[1]);
  if(ifile.fail()){
    return 0;
  }
 
  int base;
  string PK, modNum, secretCode;
  BigInt privateKey, mod, code, result;
  
  try{
    ifile >> base >> PK >> modNum;
    privateKey = BigInt(PK, base);
    mod = BigInt(modNum, base);
  }
  catch(const exception &e){
    cout << e.what() << endl;
    return -1;
  }
  
  try{
    while(!ifile.fail()){
      ifile >> secretCode;
      code = BigInt(secretCode, base);
      result = BigInt(modPow(code, privateKey, mod));
      cout << (char)result.to_int();
    }
    cout << endl;
  }
  catch(const exception &e2){
    cout << e2.what() <<endl;
    return -1;
  }
  
	return 0;
}
