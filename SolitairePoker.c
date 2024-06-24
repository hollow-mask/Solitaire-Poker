/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//do not remove
#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card){

    int rankcard = card % 13;
    if(rankcard == 0 ){
        return ACE;
    }

    if(rankcard == 1 ) return TWO;

    if(rankcard == 2 ) return THREE;

    if(rankcard == 3 ) return FOUR;

    if(rankcard == 4 ) return FIVE;

    if(rankcard == 5 ) return SIX;

    if(rankcard == 6 ) return SEVEN;

    if(rankcard == 7 ) return EIGHT;

    if(rankcard == 8 ) return NINE;

    if(rankcard == 9 ) return TEN;

    if(rankcard == 10 ) return JACK;

    if(rankcard == 11 ) return QUEEN;

    if(rankcard == 12 ) return KING;

}

// Function to get the suit of a card
enum suits getsuit(int card){
    if(card >=0 && card <=12) return CLUB;

    if(card >=13 && card <=25) return DIAMOND;

    if(card >=26 && card <=38) return HEART;

    if(card >=39 && card <=51) return SPADE;
    
}
// Function to evaluate the poker hand
/*enum hands eval(int cards[]){
    if(royalflush(cards)==1){
        return 10;
    } 
    else if(straightflush(cards)==1){
        return 9;
    }
    else if(fourofkind(cards)==1){
        return 8;
    }
    else if(fullhouse(cards)==1){
        return 7;
    }
    else if(flush(cards)==1){
        return 6;
    }
    else if(straight(cards)==1){
        return 5;
    }
    else if(threekind(cards)==1){
        return 4;
    }
    else if(twopair(cards)==1){
        return 3;
    }
    else if(pair(cards)==1){
        return 2;
    }
    else {
        return 1;
    }
}*/


// Function to check for a royal flush
int countclub=0;
int countheart=0;
int countspade=0;
int countdiamond=0;

int countAce=0;
int countKing=0;
int countQueen=0;
int countJack=0;
int count10 = 0;
int royalranks=0;// checks if one of each rank for royal flush
int hasroyalflush=0;//checks if royalflush fumcgtion is true

int royalflush(int cards[]){
 
    int suits[4]={0};
 
  int ranks[13]={0};
  int countsuits;
  for(int j =0;j<5;j++){
        if (getrank(cards[j]) < 9 && getrank(cards[j]) !=0 ){
            return 0;
        }
         ranks[getrank(cards[j])]++;
         suits[getsuit(cards[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(ranks[i] >1){
            return 0;
        }
    }
    for(int k =0;k<4;k++){
        if(suits[k]==5){
            return 1;
        }
    }

}
// Function to check for a straight flush
int straightflush(int hands[]){
    //checking suits
    int countsuits=0;
    int ranks[13]={0};
    int suits[4]={0};
    for(int j =0;j<5;j++){
         ranks[getrank(hands[j])]++;
         suits[getsuit(hands[j])]++;
    }
    for(int i =0;i<13;i++){
        if(ranks[i] >1){
            return 0;
        }

    }

    for(int p =0;p<4;p++){
        if(suits[p] ==5){
            countsuits=1;
        }
    }

    //int isconsec =0;
    int min=getrank(hands[0]);
    int max=getrank(hands[0]);
    if(countsuits == 1){
        for(int i=0;i<5;i++){
            if(getrank(hands[i]) < min){
                min = getrank(hands[i]);
            }
        }
        for(int j=0;j<5;j++){
            if(getrank(hands[j])>max){
                max = getrank(hands[j]);
            }
        }
        if(max - min == 4){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

// Function to check for four of a kind
int fourofkind(int hands[]){
    int countsuits;
    int ranks[13]={0};
    //int suits[4]={0};
    for(int j =0;j<5;j++){
         ranks[getrank(hands[j])]++;
    }
    /*for(int i =0;i<13;i++){
        if(ranks[i] >1){
            return 0;
        
        }
    }*/
    for(int j =0;j<13;j++){
        if(ranks[j] == 4){
            return 1;
        }
    }
    return 0;
 
}

// Function to check for a full house
int fullhouse(int cards[]){
    int onetrip[13] = {0};
    int three=0;
  for(int j =0;j<5;j++){
         onetrip[getrank(cards[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(onetrip[i]==3){
            three++;
        }
    }
    //
    //int onepair[13] = {0};
    int pair=0;
  int onepair[13]={0};
  for(int j =0;j<5;j++){
         onepair[getrank(cards[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(onepair[i]==2){
            pair++;
        }
    }
    if(three ==1 && pair==1){
        return 1;
    }
    else{
        return 0;
    }
}

// Function to check for a flush
int flush(int cards[]){
    int countsuits;
    int suits[4]={0};
    for(int j =0;j<5;j++){
         suits[getsuit(cards[j])]++;
    }
    for(int p =0;p<4;p++){
        if(suits[p] ==5){
            return 1;
        }
        
    }
    return 0;
}

// Function to check for a straight
int straight(int hands[]){
    int countsuits;
    int ranks[13]={0};
    
    for(int j =0;j<5;j++){
         ranks[getrank(hands[j])]++;
    }
    for(int i =0;i<13;i++){
        if(ranks[i] >1){
            return 0;
        }

    }

    //int isconsec =0;
    int min=getrank(hands[0]);
    int max=getrank(hands[0]);
    
        for(int i=0;i<5;i++){
            if(getrank(hands[i]) < min){
                min = getrank(hands[i]);
            }
        }
        for(int j=0;j<5;j++){
            if(getrank(hands[j])>max){
                max = getrank(hands[j]);
            }
        }
        if(max - min == 4){
            return 1;
        }
        else{
            return 0;
        }
}

// Function to check for three of a kind
int threekind(int hands[]){
    int onetrip[13] = {0};
    int three=0;
  int onepair[13]={0};
  for(int j =0;j<5;j++){
         onetrip[getrank(hands[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(onetrip[i]==3){
            three++;
        }
    }
    if(three ==1){
        return 1;
    }
    else{
        return 0;
    }
}

// Function to check for two pairs
int twopair(int hands[]){
    int pair=0;
  int twopair[13]={0};
  for(int j =0;j<5;j++){
         twopair[getrank(hands[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(twopair[i]==2){
            pair++;
        }
    }
    if(pair ==2){
        return 1;
    }
    else{
        return 0;
    }
}

// Function to check for a pair
int pair(int hands[]){
    //int onepair[13] = {0};
    int pair=0;
  int onepair[13]={0};
  for(int j =0;j<5;j++){
         onepair[getrank(hands[j])]++;  
    }
    for(int i =0;i<13;i++){
        if(onepair[i]==2){
            pair++;
        }
    }
    if(pair ==1){
        return 1;
    }
    else{
        return 0;
    }
}

enum hands eval(int cards[]){
    if(royalflush(cards)==1){
        return 10;
    } 
    else if(straightflush(cards)==1){
        return 9;
    }
    else if(fourofkind(cards)==1){
        return 8;
    }
    else if(fullhouse(cards)==1){
        return 7;
    }
    else if(flush(cards)==1){
        return 6;
    }
    else if(straight(cards)==1){
        return 5;
    }
    else if(threekind(cards)==1){
        return 4;
    }
    else if(twopair(cards)==1){
        return 3;
    }
    else if(pair(cards)==1){
        return 2;
    }
    else {
        return 1;
    }
}   




int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions

    //TODO:
        int prevhands[10][5]={0};
        int hand[5];
        int carddeal;
        char cardeals[10];//which cards they want to change
        int numcarddeals[4];
        int scores[10];
    for(int t=0;t<10;t++){
            shuffle();
            for(int i=0;i<5;i++){
                hand[i] = nextcard();
            }
        for(int j=0;j<5;j++){
            //getsuit(hand[j]);
            //getrank(hand[j]);
            printf("%s-", suitNames[getsuit(hand[j])]);
            printf("%s ", rankNames[getrank(hand[j])]);
            //printf("(%d) ", hand[j]);
        }
        printf("\n");
        printf("Select up to three cards to replace[1-5] and press enter\n");
        /*for(int v=0;v<5;v++){
            getsuit(hand[v]);
            getrank(hand[v]);
            printf("%s-", suitNames[getsuit(hand[v])]);
            printf("%s ", rankNames[getrank(hand[v])]);
        }*/
        //printf("\n");
        //for(int p=0;p<5;p++){
             //printf("###(%d) \n", hand[p]);
        //}
        strcpy(cardeals, "");
        fgets(cardeals, 10, stdin);
        cardeals[strlen(cardeals)-1]= '\0';
        //for(int u=0;u<5;u++){
             //printf("$$(%d) \n", hand[u]);
        //}
        if(cardeals[0] != '\n') {//how to put enter cardeals[0] != '\n'
            //for(int x=0;x<strlen(cardeals);x++){
                //numcarddeals[x]=atoi(cardeals[x]);
            //}
            //shuffle();
            for(int l=0;l<strlen(cardeals);l++){
                if(cardeals[l] == '1'){
                    printf("1 ");
                   hand[0] = nextcard(); 
                }
                if(cardeals[l] == '2'){
                    printf("2 ");
                   hand[1] = nextcard(); 
                }
                if(cardeals[l] == '3'){
                    printf("3 ");
                   hand[2] = nextcard(); 
                }
                if(cardeals[l] == '4'){
                    printf("4 ");
                   hand[3] = nextcard(); 
                }
                if(cardeals[l] == '5'){
                    printf("5 ");
                   hand[4] = nextcard(); 
                }
            }
            printf("\n");
        }
        for(int b=0;b<5;b++){
                //getsuit(hand[b]);
                //getrank(hand[b]);
                printf("%s-", suitNames[getsuit(hand[b])]);
                printf("%s ", rankNames[getrank(hand[b])]);
                //printf("(%d) ", hand[b]);
                prevhands[t][b]=hand[b];
            }
            printf("\n");

        //int scoresheet[10]={0};
        int score=0;
        if (eval(hand)==10){
            score = 50;
            scores[t]= 50;
        }
        else if (eval(hand)==9){
            score = 45;
            scores[t]=45;
        }
        else if (eval(hand)==8){
            score = 40;
            scores[t]=40;
        }
        else if (eval(hand)==7){
            score = 32;
            scores[t]=32;
        }
        else if (eval(hand)==6){
            score = 26;
            scores[t]=26;
        }
        else if (eval(hand)==5){
            score = 17;
            scores[t]=17;
        }
        else if (eval(hand)==4){
            score = 11;
            scores[t]=11;
        }
        else if (eval(hand)==3){
            score = 7;
            scores[t]=7;
        }
        else if (eval(hand)==2){
            score = 3;
            scores[t]=3;
        }
        else if (eval(hand)==1){
            score = 1;
            scores[t]=1;
        }
        printf("Hand %2d: Score: %5d %s\n", t+1, score, handNames[eval(hand)]);
        
            //SHOW DEALT HAND
            //DRAW UP TO 3 CARDS
            //SHOW FINAL HAND
            //EVAL REPPORT AND SAVE INFO FOR LATER
        //GENERATE SCORESHEET USING INFO
    }
printf("********************************************************************************\n");
printf("***                         S C O R E S H E E T                              ***\n");
printf("********************************************************************************\n");    

for(int i=0;i<10;i++){
    printf("Hand %2d: Score: %5d ", i+1, scores[i]);
    
    if(scores[i]== 50){
        printf("ROYALFLUSH     ");
    }
    else if(scores[i]==45){
        printf("STRAIGHTFLUSH  ");
    }
    else if(scores[i]==40){
        printf("QUADS          ");
    }
    else if(scores[i]==32){
        printf("FULLHOUSE      ");
    }
    else if(scores[i]==26){
        printf("FLUSH          ");
    }
    else if(scores[i]==17){
        printf("STRAIGHT       ");
    }
    else if(scores[i]==11){
        printf("TRIPS          ");
    }
    else if(scores[i]==7){
        printf("TWOPAIR        ");
    }
    else if(scores[i]==3){
        printf("PAIR           ");
    }
    else if(scores[i]==1){
        printf("HIGHCARD       ");
    }
    printf("[");

    for(int y=0;y<5;y++){
        fflush(stdout);
        // printf("%2d ", prevhands[i][y]);
        printf("%2d %7s-%-6s", prevhands[i][y], suitNames[getsuit(prevhands[i][y])], rankNames[getrank(prevhands[i][y])]);
    }

    printf("]\n");
}
int sum=0;
for(int s=0;s<10;s++){
    sum+=scores[s];
}
printf("==============================================================================\n");
printf("Total points: %7d\n", sum); 
printf("==============================================================================\n");
    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY

// Function to get the suit of a card
/*enum suits getsuit(int card){
    return 0;
}

// Function to get the rank of a card
enum ranks getrank(int card){
    return 0;
}
// Function to evaluate the poker hand
enum hands eval(int hand[]){
    return 0;
}

// Function to check for a royal flush
int royalflush(int hand[]){
    for (int i=0;i<5;i++){

        if(getsuit(cards[i]) == CLUB){
            countclub++;
        }
        if(getsuit(cards[i]) == HEART){
            countheart++;
        }
        if(getsuit(cards[i]) == DIAMOND){
            countclub++;
        }
        if(getsuit(cards[i]) == SPADE){
            countspade++;
        }
        if(getrank(cards[i]) == ACE){
            countAce++;
        }
        if(getrank(cards[i]) == KING){
            countKing++;
        }
        if(getrank(cards[i]) == QUEEN){
            countQueen++;
        }
        if(getrank(cards[i]) == JACK){
            countJack++;
        }
        if(getrank(cards[i]) == TEN){
            count10++;
        }
        if(count10 == 1 && countAce==1 && countKing==1 && countQueen==1 && countJack==1){
            royalranks = 0;
        }
        else {
            royalranks=1;
        }
        if(royalranks == 0){
            if(countclub==5){
                return 10;
            }
            else if(countdiamond==5){
                return 10;
            }
            else if(countspade==5){
                return 10;
            }
            else if(countheart==5){
                return 10;
            }
            else {
                hasroyalflush = 1;
                return 10;
            }
        }
    }
}

// Function to check for a straight flush
int straightflush(int hand[]){
    return 0;
}

// Function to check for a flush
int flush(int hand[]){
    return 0;
}

// Function to check for a straight
int straight(int hand[]){
    return 0;
}

// Function to check for four of a kind
int fourofkind(int hand[]){
    return 0;
}

// Function to check for a full house
int fullhouse(int hand[]){
    return 0;
}

// Function to check for three of a kind
int threekind(int hand[]){
    return 0;
}

// Function to check for two pairs
int twopair(int hand[]){
    return 0;
}

// Function to check for a pair
int pair(int hand[]){
    return 0;
}*/
