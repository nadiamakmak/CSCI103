#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int maxnum = 0;
  int minnum = 0;
  int max = 0;
  int min = 1000000000;
  int range1;
  int range2;
  int number;
  int counter = 0;
  
  cout << "Enter the range that you want to search: ";
  cin >> range1 >> range2;

  if (range1>range2){
    cout << "Invalid range" << endl;
  }
  
  else{
    while (range1<=range2){
      number = range1;
    
      while(number!=1){
        counter++;
        if (number%2==0){
          number/=2;
        }
        else {
          number*=3;
          number+=1;
        }
      }
      
      if (counter<min){
        min = counter;
        minnum = range1;
      }       
      if (counter>max){
        max = counter;
        maxnum = range1;
      }
 
      counter=0;
      range1++; 
    }
  cout << "Minimum length: " << min << endl;
  cout << "Achieved by: " << minnum << endl;
  cout << "Maximum length: " << max << endl;
  cout << "Achieved by: " << maxnum << endl;  
  }
}  