#include "Register.h"
#include <iostream>
using namespace std;

Register::Register() {
	fiveVal = 5.00;
	oneVal = 1.00;
	quarterVal = 0.25;
	dimeVal = 0.10;
	nickelVal = 0.05;
	fiveQuantity = 0;
	oneQuantity = 0;
	quarterQuantity = 0;
	dimeQuantity = 0;
	nickelQuantity = 0;
	purchaseAmount = 0;
	totalAmount = 0;
	change = 0;
    numDenom = 0;

	return;
}

Register::Register(int five, int one, int quarter, int dime, int nickel) {
	fiveVal = 5.00;
	oneVal = 1.00;
	quarterVal = 0.25;
	dimeVal = 0.10;
	nickelVal = 0.05;
	fiveQuantity = five;
	oneQuantity = one;
	quarterQuantity = quarter;
	dimeQuantity = dime;
	nickelQuantity = nickel;
	purchaseAmount = 0;
	totalAmount = ((fiveQuantity * fiveVal) + (oneQuantity * oneVal) + (quarterQuantity * quarterVal) + (dimeQuantity * dimeVal) + (nickelQuantity * nickelVal));
	change = 0;
    numDenom = 0;

	return;
}

void Register::SetActiveUserAmt(int userMoney) {
	/*Set the purchase amount to what user gives the machine. Every time the user inputs money,
	call this method and add to purchaseAmount */
	if (userMoney == 1) {
		purchaseAmount += nickelVal;
	}
	else if (userMoney == 2) {
		purchaseAmount += dimeVal;
	}
	else if (userMoney == 3) {
		purchaseAmount += quarterVal;
	}
	else if (userMoney == 4) {
		purchaseAmount += oneVal;
	}
	else if (userMoney == 5) {
		purchaseAmount += fiveVal;
	}
	return;
}

void Register::UpdateTotalMoney(double productPrice) {
    //Adds to total amount if the product has been dispensed
	totalAmount += productPrice;
	return;
}

void Register::CalculateChange(double userAmount, double productPrice, bool purchaseCheck) {
	/*By using the price of the item purchased, calculate the change by subtracting the cost of 
	the item from purchaseAmount(user's entered money). If purchaseCheck is false, then no item
    was purchased, so just refund money in coins(Can't return bills)*/
    int i = 0;
    int count = 0;
    double tempChange = 0;
    
    //Check if machine is returning change after purchase or for refund. Depends on bool val.
    if(purchaseCheck == true){
        change = userAmount - productPrice;
        tempChange = change;
    }
    else{
        change = userAmount;
        tempChange = change;
    }
    
    //Need to calculate denomination in return
    numDenom = tempChange / quarterVal;
    for(i = 0; i < numDenom; i++){
        if(quarterQuantity > 0){
            quarterQuantity--;
            count++;
        }
    }
    
    //Subtract amount of change possible made by quarters
    tempChange -= count * quarterVal;
    if(tempChange == 0)
        return;
    
    count = 0;
    numDenom = tempChange / dimeVal;
    for(i = 0; i < numDenom; i++){
        if(dimeQuantity > 0){
            dimeQuantity--;
            count++;
        }
    }
    
    tempChange -= count * dimeVal;
    if(tempChange == 0)
        return;
    
    numDenom = tempChange / nickelVal;
    for(i = 0; i < numDenom; i++){
        if(nickelQuantity > 0){
            nickelQuantity--;
        }
    }
    
	return;
}

void Register::UpdateDenomination(int userMoney){
    /*Update the quanity and amount of each coin/bill. Use else-if statement to check value of userMoney,
     and then update the quantity of given type (five, one, quarter, dime, nickel) */
    if (userMoney == 1) {
        nickelQuantity++;
    }
    else if (userMoney == 2) {
        dimeQuantity++;
    }
    else if (userMoney == 3) {
        quarterQuantity++;
    }
    else if (userMoney == 4) {
        oneQuantity++;
    }
    else if (userMoney == 5) {
        fiveQuantity++;
    }
    return;
}

void Register::ClearMoney(){
	purchaseAmount = 0;
	return;
}

double Register::GetActivePurchaseAmt() const {
	return purchaseAmount;
}

double Register::GetTotalMoney() const {
	return totalAmount;
}

double Register::GetChange() const {
	return change;
}

int Register::GetDenomQuantities(int i) const {
    if (i == 0) {
        return nickelQuantity;
    }
    else if (i == 1) {
        return dimeQuantity;
    }
    else if (i == 2) {
        return quarterQuantity;
    }
    else if (i == 3) {
        return oneQuantity;
    }
    else if (i == 4) {
        return fiveQuantity;
    }
    else
        return -1;
}

