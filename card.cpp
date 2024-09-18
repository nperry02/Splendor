/*
 * card.cpp
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: Implement the methods for the Card class
 *
 */

#include "card.h"

//Card Constructor
//takes in the prestige, discount and cost of each gem
//iniltilizes everything
Card::Card(int prestige, string discount, int w, int r, int p, int b, int g){
    //initlize prestige
    this->prestige = prestige;

    //discounted gem
    this->discount = discount;

    //puts coast of each gem in array
    this->cost[0]=w;
    this->cost[1]=r;
    this->cost[2]=p;
    this->cost[3]=b;
    this->cost[4]=g;
}

Card::~Card() {
  //  delete cards;
}

// discounted gemcolor getter
//no input
//returns the name of the discounted gem
string Card::getGemColor(){
    return discount;
}

//getDiscountIndex
//no input
//returns the index of the discounted gem
int Card::getDiscountIndex(){
    if(discount == "white"){
        return 0;
    }
    else if (discount == "red"){
        return 1;
    }
    else if (discount == "pink"){
        return 2;
    }
    else if (discount == "blue"){
        return 3;
    }
    else{
        return 4;
    }
}

// prestige getter
//no input
// returns the amount of prestuge the card has
int Card::getPrestige(){
    return prestige;
}

//price getter
//takes in the index of the gem 
//returns the cost of that gem color
int Card::getPrice(int g){
    return cost[g];
}



 