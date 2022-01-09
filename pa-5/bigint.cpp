#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
  base = setbase;
  if(input<0){
    isPositive = false;
  }
  else{
    isPositive = true;
  }
  
  int temp = abs(input)/base;
  int rem = abs(input)%base;
  
  while(temp!=0){
    //cout<<rem;
    vec.push_back(rem);
    rem = temp%base;
    temp = temp/base;
  }
  vec.push_back(rem);
  //for(unsigned int i=0; i<vec.size();i++){
  //  cout<<vec[i];
  //}
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
  base = setbase;
  
  if(s[0]== '-'){ 
    isPositive = false;
    for(int i=s.length()-1; i>0; i--){
      if(s[i]>64){ //If it is a capital letter, it will become a number
        vec.push_back(((int)(s[i]))-55); 
      }
      else{
        vec.push_back((int)(s[i]-48));
      }
    }
  }
  
  else{
    isPositive = true;
    for(int i=s.length()-1; i>-1; i--){
      if(s[i]>64){ //If it is a capital letter, it will become a number
        vec.push_back(((int)(s[i]))-55); 
      }
      else{
        vec.push_back((int)(s[i]-48));
      }
    }
  }
  
  /*for(int i=0; i<vec.size();i++){
    cout<<vec[i];
  }*/
  
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
  vec = b.vec;
  base = b.base;
  isPositive = b.isPositive;

}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
  vec = b.vec;
  base = b.base;
  isPositive = b.isPositive;

  return *this;
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
  vector<int> temp = this->vec;
  
  bool isZero = true;
  while(isZero && temp.size()>1){
    if(temp[temp.size()-1]!=0){
      isZero = false;
      break;
    }
    temp.pop_back();
  }
  
  string s = "";
  if(isPositive==false && this->to_int()!=0){
    s += '-';
  }
  
  for (int i=temp.size()-1; i>-1; i--){
    if(temp[i]>9){
      s += (char)(temp[i]+55);
    }
    else{
      s += (char)(temp[i]+48);
    }
  }
  return s;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/
  long long number = 0;
  int exp = 0;
  
  for(unsigned int i=0; i<vec.size(); i++){
    number += vec[i]*pow(base, exp);
    //cout << vec[i] << " times " << base << " to the power of " << exp << " = " << number <<endl;
    exp++;
    if (isPositive && number>2147483647){
      return INT_MAX;
    }
    else if(!isPositive && number<-2147483648){
      return INT_MIN;
    }
    //cout << number<<endl;
  }
  //cout<<number<<endl;
  
  if(isPositive==false){
    number = number*-1;
  }
  
  if (isPositive && number>2147483647){
    return INT_MAX;
  }
  else if(!isPositive && number<-2147483648){
    return INT_MIN;
  }
  
  return (int)number;//for now
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

  /*for(unsigned int i=0; i<this->vec.size();i++){
    cout<<this->vec[i] << " ";
  }
  cout <<endl;
  for(unsigned int i=0; i<b.vec.size();i++){
    cout<<b.vec[i] << " ";
  }
  cout <<endl;*/
  
    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?
  if(isPositive!=b.isPositive){
    if(isPositive){
      return 1;
    }
    else{
      return -1;
    }
  }
    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
  if(isPositive){
    if(vec.size()>b.vec.size()){
      return 1;
    }
    else if(vec.size()<b.vec.size()){
      return -1;
    }
  }
  else{
    if(vec.size()>b.vec.size()){
      return -1;
    }
    else if(vec.size()<b.vec.size()){
      return 1;
    }
  }
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
  if(isPositive){
    for(int i=vec.size()-1;i>-1;i--){
      //cout<<vec[i] << " >= " <<b.vec[i] << " ? " << endl;
      if(vec[i]==b.vec[i]){
        continue;
      }
      else if(vec[i]>b.vec[i]){
        return 1;
      }
      else{
        return -1;
      }
    }
  }
  else{
    for(int i=vec.size()-1;i>-1;i--){
      if(vec[i]==b.vec[i]){
        continue;
      }
      else if(vec[i]>b.vec[i]){
        return -1;
      }
      else{
        return 1;
      }
    }
  }
  
    //If ALL digits are the same, then they MUST be equal!!
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if(a.compare(b)==0){
    return true;
  }  
  return false;//for now
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if(a.compare(b)!=0){
    return true;
  }  
  return false;//for now
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if(a.compare(b)==-1 || a.compare(b)==0){
    return true;
  } 
  return false;//for now
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if(a.compare(b)==1 || a.compare(b)==0){
    return true;
  }   
  return false;//for now
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
 if(a.compare(b)==1){
    return true;
  }  
  return false;//for now
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
 if(a.compare(b)==-1){
    return true;
  }  
  return false;//for now
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt copy(a);
  copy += b;
  return copy;//for now
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  /*for(unsigned int i=0; i<this->vec.size();i++){
    cout<<this->vec[i] << " ";
  }
  cout <<endl;
  for(unsigned int i=0; i<b.vec.size();i++){
    cout<<b.vec[i] << " ";
  }
  cout <<endl;*/
  
  if(this->isPositive!=b.isPositive){
    BigInt top = this->isPositive ? *this : b;
    BigInt bottom = b.isPositive ? *this : b;
    bottom.isPositive = true;
    *this = top - bottom;
    //if(!b.isPositive){
    //  this->isPositive = !this->isPositive;   
    //}
    return *this;
  }
  
  unsigned int len = max(this->vec.size(), b.vec.size());
  int aVal = 0;
  int bVal = 0;
  int carry = 0;
  int sum = 0;

  
  for(unsigned int i=0;i<len;i++){
    if (i<this->vec.size()){
      aVal = this->vec[i];
    }
    else{
      aVal = 0;
    }
    if (i<b.vec.size()){
      bVal = b.vec[i];
    }
    else{
      bVal = 0;
    }
    
    if( (this->isPositive == true) && (b.isPositive == true)){
      sum = aVal + bVal + carry;
    }
    else if( (this->isPositive == false) && (b.isPositive == false)){
      sum = aVal + bVal + carry;
    }
    
    //cout << sum;
    carry=0;
    
    if(i>=this->vec.size()){
      //cout << "in " << i << " " << len << endl;
      //cout << sum << endl;
      if(i==len-1 && sum>=base){
        this->vec.push_back(sum%base);
        this->vec.push_back(1);
        break;
      }
      this->vec.push_back(sum%base);
      carry = sum/base;
      continue;
    }
    else if(sum<base){
      this->vec[i] = sum;
      continue;
    }
    else{
      //cout << "in " << i << endl;
      carry = sum/base;
      if(i==(len-1)){
        this->vec.push_back(carry);
      }
      this->vec[i] = sum%base;  
    }
    
  }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt copy(a);
  copy -= b;
  return copy;//for now
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  unsigned int len = max(this->vec.size(), b.vec.size());
  int topVal = 0;
  int botVal = 0;
  int borrow = 0;
  int diff = 0;
  
  bool amIlarger = this->compare(b)==1;
  if(!this->isPositive && !b.isPositive) {
    amIlarger = !amIlarger;
  }
  BigInt top = amIlarger ? *this : b;
  BigInt bottom = amIlarger ? b : *this;
  
  if(this->isPositive!=b.isPositive){
    top = this->isPositive ? *this : b;
    bottom = b.isPositive ? *this : b;
    top.isPositive = false;
    *this = top + bottom;
    if(!b.isPositive){
      this->isPositive = !this->isPositive;   
    }
    return *this;
  }
  
 
  for(unsigned int i=0;i<len;i++){    
    topVal = top.vec[i];
    if(i>=bottom.vec.size()){
      botVal = 0;
    }
    else{
      botVal = bottom.vec[i];
    }
    diff = (topVal-botVal)+borrow;
    borrow = 0;
    
    if(diff<0){
      diff += base;
      borrow = -1;
      top.vec[i] = diff;
    }
    else{
      top.vec[i] = diff;
    }
  
  }
  
  *this = top;
  //cout << top.isPositive << " " << amIlarger;
  if(top.isPositive && !amIlarger){
    this->isPositive = false;
  }
  else if(!top.isPositive && amIlarger){
    this->isPositive = false;
  }
  else if(!top.isPositive && !amIlarger){
    this->isPositive = true;
  }
  
  bool isZero = true;
  while(isZero && this->vec.size()>1){
    if(this->vec[this->vec.size()-1]!=0){
      isZero = false;
      break;
    }
    this->vec.pop_back();
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt copy(a);
  copy *= b;
  return copy;//for now
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  BigInt zero("0", this->base);
  BigInt one("1", this->base);
  BigInt negOne("-1", this->base);
  
  /*for(unsigned int i=0; i<this->vec.size();i++){
    cout<<this->vec[i] << " ";
  }
  cout <<endl;
  for(unsigned int i=0; i<b.vec.size();i++){
    cout<<b.vec[i] << " ";
  }
  cout <<endl;*/
  
  if(*this==zero){
    return *this;
  }
  else if(b==zero){
    *this = b;
    return *this;
  }
  if(*this==one){
    *this = b;
    return *this;
  }
  else if(b==one){
    return *this;
  }
  if(*this==negOne){
    *this = b;
    this->isPositive = !this->isPositive;
    return *this;
  }
  else if(b==negOne){
    this->isPositive = !this->isPositive;
    return *this;
  }
    
  BigInt total(0, this->base);
  int carry = 0;
  int product = 0;
  for(unsigned int i = 0; i<b.vec.size(); i++){
    BigInt temp(this->base);
    for(unsigned int x=0; x<i; x++){ temp.vec.push_back(0); }
    for(unsigned int j=0; j<this->vec.size(); j++){
      product = (b.vec[i]*this->vec[j])+carry;
      carry = product/base;
      //cout << product << " " << carry << endl;
      product = product%base;
      temp.vec.push_back(product);
    }
    //cout << i << " " << b.vec.size() <<endl;   
    temp.vec.push_back(carry);
    carry=0;
    total = total + temp;
    //cout << total.to_int() << endl;
  }
  
  if( (this->isPositive == true) && (b.isPositive == true)){
    total.isPositive = true;
  }
  else if( (this->isPositive == false) && (b.isPositive == false)){
    total.isPositive = true;
  }
  else{
    total.isPositive = false;
  }
  
  bool isZero = true;
  while(isZero && this->vec.size()>1){
    if(this->vec[this->vec.size()-1]!=0){
      isZero = false;
      break;
    }
    this->vec.pop_back();
  }
  
  *this = total;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt copy(a);
  copy /= b;
  return copy;//for now
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/

  BigInt q(this->base);
  BigInt r(this->base);
  divisionMain(b, q, r);
  
  *this = q;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
  BigInt copy(a);
  copy %= b;
  return copy;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/
  BigInt q(this->base);
  BigInt r(this->base);
  divisionMain(b, q, r);
  
  r.isPositive = this->isPositive;
  *this = r;
  return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
  //STEP 1
  //cout<< "STEP 1" <<endl;
  bool sameSign;
  if( (this->isPositive == true) && (b.isPositive == true)){
    sameSign = true;
  }
  else if( (this->isPositive == false) && (b.isPositive == false)){
    sameSign = true;
  }
  else{
    sameSign = false;
  }
  BigInt dividend(*this);
  BigInt divisor(b);
  dividend.isPositive = true;
  divisor.isPositive = true;
  
  //STEP 2
  //cout<< "STEP 2" <<endl;
  if(dividend.to_int()==1 && divisor.to_int()!=1){
    quotient.vec.push_back(0);
    remainder.vec.push_back(1);
    if(sameSign){
      quotient.isPositive = true;
    }
    else{
      quotient.isPositive = false;
    }
    return;
  }
  else if(divisor.to_int()==1){
    quotient = dividend;
    remainder.vec.push_back(0);
    if(sameSign){
      quotient.isPositive = true;
    }
    else{
      quotient.isPositive = false;
    }
    return;
  }
  //cout << dividend.to_string() << " < " << divisor.to_string() << " here ";
  if((dividend < divisor) || (dividend.to_int() < divisor.to_int())){
    //cout << dividend.to_string() << " < " << divisor.to_string() << " here ";
    quotient.vec.push_back(0);
    remainder = dividend;
    if(sameSign){
      quotient.isPositive = true;
    }
    else{
      quotient.isPositive = false;
    }
    return;
  }

  //STEP 3
  //cout<< "STEP 3" <<endl;
  int pos = dividend.vec.size()-1;
  BigInt dividend_seq(dividend.vec[pos], this->base);
  //dividend_seq.vec.push_back(dividend.vec[pos]);
  //cout << "step 3 before: " << dividend_seq.to_string() << " < " << divisor.to_string() << endl;
  //cout << "before: " << dividend_seq.to_string() << " - " << divisor.to_string() << endl;
  while(dividend_seq < divisor){
    //cout << "pos: " << pos << "; dividend = " << dividend_seq.to_string() << endl;
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), dividend.vec[pos]);
  }
  
  
  //STEP 9 (loop?)
  //cout<< "about to enter loop" <<endl;
  while(pos>-1){
    //STEP 4
    /*cout<< "STEP 4 @ pos " << pos <<endl;
    cout << "before: " << dividend_seq.to_string() << " / " << divisor.to_string() << endl;
    cout << "before: " << dividend_seq.to_string() << " - " << divisor.to_string() << endl;*/
    
    int count = 0;
    while(dividend_seq >= divisor){
      
      /*cout << boolalpha << (dividend_seq >= divisor) << endl;
      cout << "vec dividend = " ;
      for(unsigned int i=0; i<dividend_seq.vec.size();i++){
        cout<<dividend_seq.vec[i] << " ";
      }
      cout << endl;*/
      //cout << dividend_seq.to_string() << " - " << divisor.to_string() << " = ";
      
      dividend_seq = dividend_seq - divisor;
      //cout << dividend_seq.to_string() <<endl;
      //cout << " = " << dividend_seq.to_string() <<endl;
      count++;
    }
    //STEP 5
    quotient.vec.insert(quotient.vec.begin(), count);
    //cout << "adding " << count <<" to quotient"<< endl;

    //STEP 6
    if(dividend_seq.to_int()==0){
      dividend_seq.vec.clear();
    }
    //STEP 7
    if(pos>0){
      //cout << "in here: " << dividend.vec[pos-1] << " ; ";
      dividend_seq.vec.insert(dividend_seq.vec.begin(), dividend.vec[pos-1]);
      //cout << dividend_seq.to_int() <<endl;
      dividend_seq.isPositive=true;
    }

    //STEP 8
    pos--;
    
    if(pos==-1 && b.to_int()!=2){
      if(dividend_seq.vec.size()!=0){
    //cout << dividend_seq.to_string();
        remainder = dividend_seq;
      }
      else{
        remainder.vec.push_back(0);
      }
    }
    
  }
  
  //cout << dividend_seq.to_string();
  //AFTER STEP 9
  //for some reason doesn't get here?
  if(dividend_seq.vec.size()!=0){
    //cout << dividend_seq.to_string();
    remainder = dividend_seq;
  }
  else{
    remainder.vec.push_back(0);
  }
  if(sameSign){
    quotient.isPositive = true;
  }
  else{
    quotient.isPositive = false;
  }

}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt copy(a);
  copy.exponentiation(b);
  return copy;//for now
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
  BigInt exp(b);
  BigInt outer("1", this->base);
  
  BigInt zero("0", this->base);
  BigInt one("1", this->base);
  BigInt two("2", this->base);
  
  if(exp==zero){
    this->vec.clear();
    this->vec.push_back(1);
    if(*this>zero){
      this->isPositive = true;
    }
    else if(*this<zero){
      this->isPositive = true;
    }
    return *this;
  }
  else if(exp==one){
    return *this;
  }
  
  while(exp!=one){// exp>1
    if(exp%two==zero){
      *this = *this * *this;
      exp /= two;
    } 
    else{
      outer = outer * *this;
      *this *= *this;
      exp = (exp-one)/two;
    }
    
    // remove leading zeros if needed
    bool isZero = true;
    while(isZero && this->vec.size()>1){
      if(this->vec[this->vec.size()-1]!=0){
        isZero = false;
        break;
      }
      this->vec.pop_back();
    }
    
  }
  *this = *this * outer;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
  BigInt copy(a);
  copy.modulusExp(b, m);
  return copy;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
  BigInt exp(b);
  BigInt mod(m);
  BigInt zero("0", this->base);
  BigInt one("1", this->base);
  BigInt two("2", this->base);
  BigInt outer("1", this->base);
  
  if(exp==zero){
    this->vec.clear();
    this->vec.push_back(1);
    if(*this>zero){
      this->isPositive = true;
    }
    else if(*this<zero){
      this->isPositive = true;
    }
    return *this;
  }
  else if(exp==one){
    *this %= mod;
    return *this;
  }
  
  //cout << "(" << this->to_string() << " ^ " <<exp.to_string() << ") % " << mod.to_string() << endl;
  while(exp!=one){// exp>1
    if(exp%two==zero){
      *this = (*this * *this);
      //cout << this->to_string() << endl;
      //
      //remove leading zeros if needed
      bool isZero = true;
      while(isZero && this->vec.size()>1){
        if(this->vec[this->vec.size()-1]!=0){
          isZero = false;
          break;
        }
      this->vec.pop_back();
      }
      
      *this %= mod;
      exp /= two;
      //cout << "even: " << this->to_string() << " " << exp.to_string() << endl << endl;
    } 
    else{
      //cout << outer.to_string() << " * " << this->to_string() << " = ";
      outer = (outer*(*this));
      
      //remove leading zeros if needed
      bool isZero2 = true;
      while(isZero2 && outer.vec.size()>1){
        if(outer.vec[outer.vec.size()-1]!=0){
          isZero2 = false;
          break;
        }
      outer.vec.pop_back();
      }
      
      outer %= mod;
      //cout << outer.to_string() <<endl;
      *this = (*this * *this);
      
      //remove leading zeros if needed
      bool isZero = true;
      while(isZero && this->vec.size()>1){
        if(this->vec[this->vec.size()-1]!=0){
          isZero = false;
          break;
        }
      this->vec.pop_back();
      }
      //cout << this->to_string() << " % " << mod.to_string() << " = ";
      *this %= mod;
      //cout << this->to_string() <<endl;
      exp = (exp-one)/two;
      //cout << "odd: " << this->to_string() << " " << exp.to_string() << endl <<endl;
    }
    
    //remove leading zeros if needed
    bool isZero = true;
    while(isZero && this->vec.size()>1){
      if(this->vec[this->vec.size()-1]!=0){
        isZero = false;
        break;
      }
      this->vec.pop_back();
    }
    
  }
  //cout << this->to_string() << " " << outer.to_string() << endl;
  *this = (*this * outer);
  
  //remove leading zeros if needed
  bool isZero = true;
  while(isZero && this->vec.size()>1){
    if(this->vec[this->vec.size()-1]!=0){
      isZero = false;
      break;
    }
    this->vec.pop_back();
  }
  *this %= mod; 
  return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************