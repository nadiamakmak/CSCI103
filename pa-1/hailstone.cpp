#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int number;
  int counter = 0;
  cout << "Enter a number: ";
  cin >> number;

  while(number!=1){
    counter++;
    if (number%2==0){
      number/=2;
    }
    else {
      number*=3;
      number+=1;
    }
    cout << number << " ";
  }
  cout << endl << "Length: " << counter << endl;
}