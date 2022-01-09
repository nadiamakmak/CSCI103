/********************************************************
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 ********************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;
  /*====================*/
  /* Start of your code */
  
  cin >> n;
  
  if (n < 0){
    n = n*-1;
    cout << "-";
  }
  
  long long temp = n;
  long long last = 0;
  long long sub = 0;
  long long commaSpot = n;
  int length = 1;
  int lastCount = 0;
  
  bool commatime = false;
  

  
  while (commaSpot>=10){
    commaSpot = commaSpot/10;
    length++; 
  }
  
  while (temp%10!=temp){
    while (temp>=10){
      temp = temp/10;
      last++;
    }
    
    if (length%3==1){
      commatime = true;
    }    
    
    if (lastCount-last>1){
      for (int i=1; i<(lastCount-last); i++){
        
        if (length%3==1){
          commatime = true;
        }
        
        if (commatime){
          cout << ",";
          commatime = false;
        }        
        
        cout << "0";        
        length--;

      }
      lastCount = last;
      cout<<temp;
      sub = sub + (temp*(long long)pow(10, last));
      temp=n-sub;
      last = 0;
      length--;
      continue;
    }
    lastCount = last;
    cout<<temp;
    sub = sub + (temp*(long long)pow(10, last));
    temp=n-sub;
    last = 0;
     
    if (length%3==1){
      commatime = true;
    }
    if (commatime){
       cout << ",";
       commatime = false;
    }
    
    length--;
  }
  
  if (lastCount-last>1){
      for (int i=1; i<(lastCount-last); i++){
        
        cout << "0";      

        
        if (length%3==1){
          commatime = true;
        }
        if (commatime){
          cout << ",";
          commatime = false;
        }
        length--;        
      }
  }

  cout << temp << endl;    //PRINTS OUT LAST NUMBER
  
  /* End of your code */
  /*==================*/
  
  return 0;
}
