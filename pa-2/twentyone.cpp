/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  int j;
  int temp;
  
  for (int i=NUM_CARDS-1; i>0; i--){
    j = rand()%(i+1);
    temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
  
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  if (id<=12){
    if(id==9){
      cout << type[9] << "-" << suit[0];
    }
    else if (id==10){
      cout << type[10] << "-" << suit[0];
    }
    else if (id==11){
      cout << type[11] << "-" << suit[0];
    }
    else if (id==12){
      cout << type[12] << "-" << suit[0];
    }
    else{
      cout << id+2 << "-" << suit[0];      
    }
  }

  else if (id<=25){
    if(id==22){
      cout << type[9] << "-" << suit[1];
    }
    else if (id==23){
      cout << type[10] << "-" << suit[1];
    }
    else if (id==24){
      cout << type[11] << "-" << suit[1];
    }
    else if (id==25){
      cout << type[12] << "-" << suit[1];
    }
    else{
      cout << id-11 << "-" << suit[1];      
    }
  }
  
  else if (id<=38){
    if(id==35){
      cout << type[9] << "-" << suit[2];
    }
    else if (id==36){
      cout << type[10] << "-" << suit[2];
    }
    else if (id==37){
      cout << type[11] << "-" << suit[2];
    }
    else if (id==38){
      cout << type[12] << "-" << suit[2];
    }
    else{
      cout << id-24 << "-" << suit[2];     
    }
  }
  
  else if (id<=51){
    if(id==48){
      cout << type[9] << "-" << suit[3];
    }
    else if (id==49){
      cout << type[10] << "-" << suit[3];
    }
    else if (id==50){
      cout << type[11] << "-" << suit[3];
    }
    else if (id==51){
      cout << type[12] << "-" << suit[3];
    }
    else{
      cout << id-37 << "-" << suit[3];     
    }
  }
  
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int val = 0;
  
  if (id<=12){
    val = value[id];
  }
  else if (id<=25){
    val = value[id-13];
  }
  else if (id<=38){
    val = value[id-26];
  }
  else if (id<=51){
    val = value[id-39];
  }
  
  return val;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i=0; i<numCards; i++){
    printCard(hand[i]);
    cout << setw(3);
  }
  cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum = 0;
  int val = 0;
  int aces = 0;
  
  
  for(int i=0; i<numCards; i++){
    val = cardValue(hand[i]);
    if(val==11){
      aces++;
      if(sum+11>21){
        sum=sum+1;
      }
      else{
        sum = sum + val;
      }
    }
    else{
      sum = sum + val;
    }  
  }

  if(sum>21){
    if(aces>0){
      sum = 0;
      for(int p=0; p<numCards; p++){
        val = cardValue(hand[p]);
        if(val==11){
          sum=sum+1;
        }
        else{
          sum = sum + val;
        }  
      }
    }
  }
  
  
  return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  bool done = false;
  int nextCard = 0;
  char hitStay;
 
  
  while(done==false){
    
    for (int x=0; x<NUM_CARDS; x++){
      cards[x] = x;
    }

    shuffle(cards);
    
    for (int k=0; k<8; k++){
      phand[k]=k;
      dhand[k]=k;
    }
    
    nextCard = 0;
    
    //-----------------------------------
    //for (int u=0; u<NUM_CARDS; u++){ //printing for testing purposes
    //  cout << cards[u] << setw(4);
    //}
    //cout << endl << endl;
    //-----------------------------------
    
    
    
    int phandLength = 2;
    int dhandLength = 2;
    
    for (int i = 0; i < 2; i++){
      phand[i]=cards[nextCard];
      nextCard++;
      dhand[i]=cards[nextCard];
      nextCard++;
    }
    
    cout << "Dealer: " << '?' << setw(2);
    //printHand(dhand, dhandLength); //TEST
    printCard(dhand[1]);
    cout << endl << "Player: ";
    printHand(phand, phandLength);

    if(getBestScore(phand, phandLength)==21){
      
    }

    else if(getBestScore(phand, phandLength)<21){

      while(getBestScore(phand, phandLength)<21){
        
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        cin >> hitStay;

        if(hitStay=='h'){  
          phand[phandLength]=cards[nextCard];
          nextCard++;
          phandLength++;
          cout << "Player: ";
          printHand(phand, phandLength);
        }
        else{
          break;
        }
      }      

    }

    

    
    if(getBestScore(phand, phandLength)>21){      //player busts
      cout << "Player busts" << endl << "Lose ";
      cout << getBestScore(phand, phandLength);
      cout << " ";
      cout << getBestScore(dhand, dhandLength);
      cout << endl;
    }

    else if(getBestScore(phand, phandLength)<=21){ //if player didn't bust
      while(getBestScore(dhand, dhandLength)<17){  //dealer plays (if he has less than 17)
        dhand[dhandLength]=cards[nextCard];
        nextCard++;
        dhandLength++; 
      }

      if(getBestScore(dhand, dhandLength)>21){     //dealer busts
        cout << "Dealer: ";
        printHand(dhand, dhandLength);
        cout << "Dealer busts" << endl << "Win ";
        cout << getBestScore(phand, phandLength);
        cout << " ";
        cout << getBestScore(dhand, dhandLength);
        cout << endl;
      }
      else{  //dealer did not bust
        if(getBestScore(dhand, dhandLength)>getBestScore(phand, phandLength)){ //dealer is closer to 21 than player
          cout << "Dealer: ";
          printHand(dhand, dhandLength); 
          cout << "Lose ";
          cout << getBestScore(phand, phandLength);
          cout << " ";
          cout << getBestScore(dhand, dhandLength);
          cout << endl;
        }
        else if(getBestScore(dhand, dhandLength)<getBestScore(phand, phandLength)){ //player is closer to 21 than dealer
          cout << "Dealer: ";
          printHand(dhand, dhandLength);
          cout << "Win ";
          cout << getBestScore(phand, phandLength);
          cout << " ";
          cout << getBestScore(dhand, dhandLength);
          cout << endl;
        }
        else{ //both have equal
          cout << "Dealer: ";
          printHand(dhand, dhandLength);
          cout << "Tie ";
          cout << getBestScore(phand, phandLength);
          cout << " ";
          cout << getBestScore(dhand, dhandLength);
          cout << endl;
        }
      }
    }
    
    cout << endl << "Play again? [y/n]" << endl;
    cin >> hitStay;
    if (hitStay=='y'){
      done = false;
    }
    else{
      done = true;
      break;
    }
    
  }
  
  return 0;
}


