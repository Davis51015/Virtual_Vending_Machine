//Davis Smith
//CPSC 246
/*This program simulates the operation of a vending machine. Inventory is read
    in from a text file. Users can navigate the options with a keypad. Input must 
    meet constraints set by the program.*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <limits>
#include "Register.h"
#include "Inventory.h"
using namespace std;

//Function prototypes
void inputUserMoney(Register& machine);
void userSelection(Register& machine, Inventory& product, int count);

int main() {
    const int FIVE_NUM = 0;
    const int ONE_NUM = 0;
    const int QTR_NUM = 40;
    const int DIME_NUM = 50;
    const int NICK_NUM = 40;
    const int MAX_ITEMS = 15;
    ifstream inFS;
    ifstream inString;
    ofstream outFS;
    string fileName = "";
    string tempString, tempDouble, tempInt, testString;  //Temp variables to hold extracted items from file
    double totalMoneyStart = 0;
    double newDouble; //To pass into setter function
    int userInput;
    int checkComma = 0;
    int i = 0;      //Loop variable
    int count = 0;  //Count number of items in external file
    int newInt;		//To pass into setter function
    bool checkVal = true;
    
    //Objects
    Register machine(FIVE_NUM, ONE_NUM, QTR_NUM, DIME_NUM, NICK_NUM);
    Inventory product;
    
    totalMoneyStart = machine.GetTotalMoney(); //Keep track of how much money is in machine at start
    
    system ("tput clear");
    cout << "Type the filename for data extraction...\n";
    cin >> fileName;
    cout << endl;
    
    //Read in data from file and perform basic conditional tests for valid input file
    inFS.open(fileName);
    if (inFS.is_open()) {
        while (!inFS.eof()) {
            //Comma as delimiter
            getline(inFS, tempString, ',');
            if(tempString != ""){
                product.SetInventoryNames(tempString);
            }
            else{
                cout << "Error reading file...\n" << endl;
                return 1;
            }
            
            getline(inFS, tempDouble, ',');
            newDouble = atof(tempDouble.c_str());   //Convert string to double
            if(newDouble > 0 && newDouble < 10){
                product.SetInventoryCosts(newDouble);
            }
            else{
                cout << "Error reading file...\n" << endl;
                return 1;
            }
            
            getline(inFS, tempInt, '\n');           //Delimited by newline
            newInt = atoi(tempInt.c_str());			//Convert string to int
            if(newInt > 0 && newInt < 75){
                product.SetInventoryQuantity(newInt);
            }
            else{
                cout << "Error reading file...\n" << endl;
                return 1;
            }
            count++;  //Count the number of items read in
        }
    }
    else {
        cout << "Error reading file...\n" << endl;
        return 1;
    }
    inFS.close();
    
    
    //Check strings for delimiting commas
    inString.open(fileName);
    for(i = 0; i < count - 1; i++){
        getline(inString, testString);
        for(i = 0; i < testString.size(); i++){
            if(testString.at(i) == ','){
                checkComma++;
            }
        }
        //Only read in lines with 2 delimiting commas
        if(checkComma < 2){
            cout << "Error reading file...\n" << endl;
            return 1;
        }
    }
    inString.close();
       
        
    //Only allows a max of 10 items in vending machine
    if(count > MAX_ITEMS){
        cout << "Error reading file...\n" << endl;
        return 1;
    }
    
        
    userInput = 0;
    //Build user interface
    while (userInput != 4) {
        checkVal = true;
        cout << "-----VIRTUAL VENDING MACHINE-----\n\n";
        
        //Print menu
        for (i = 0; i < count; i++) {
            cout << "      " << product.GetItemNames(i);
            cout << " ---> $" << fixed << setprecision(2) << product.GetItemCosts(i) << endl;
        }
        
        //User menu with input
        cout << "\nMAKE ENTRY USING KEYPAD\n" << "1. Enter money\n" << "2. Choose item to vend\n"
        << "3. Return money\n" << "4. Quit\n" << "\nCurrent Amt: $" << machine.GetActivePurchaseAmt() << endl << endl;
        cin >> userInput;
        
        //Only inputs 1-4 accepted
        if (userInput < 1 || userInput > 4) {
            cout << "\nInvalid user input. Please try again.\n\n";
            cin.ignore();
            cout << "\nPress any key to continue...\n";
            cin.get();
            system ("tput clear");
            checkVal = false;
        }
        
        if (checkVal == true) {
            checkVal = false;
            switch (userInput) {
                case 1: {
                    inputUserMoney(machine);  //Function to input money in machine
                    system ("tput clear");
                    break;
                }
                case 2: {
                    userSelection(machine, product, count);  //Select item from choices
                    cout << "\nPress any key to continue...\n";
                    cin.get();
                    system ("tput clear");
                    break;
                }
                case 3: {
                    cout << "\nRETURNING CHANGE: $" << machine.GetActivePurchaseAmt() << endl << endl;
                    machine.CalculateChange(machine.GetActivePurchaseAmt(), 0.0, false);
                    machine.ClearMoney();
                    cin.ignore();
                    cout << "\nPress any key to continue...\n";
                    cin.get();
                    system ("tput clear");
                    break;
                }
            }
        }
    }
    
    //Print out machine and inventory stats
    cout << "-----VENDING MACHINE REPORT-----\n\n";
    cout << "Total in Machine: $" << fixed << setprecision(2) << machine.GetTotalMoney();
    cout << endl << "Revenue: $" << fixed << setprecision(2) << machine.GetTotalMoney() - totalMoneyStart;
    cout << "\n\nINVENTORY:";
    for(i = 0; i < count; i++){
        cout << endl << "Quantity " << product.GetItemNames(i) << ": " << product.GetItemQuantities(i);
    }
    cout << "\n\nDENOMINATIONS:";
    cout << endl << "Quantity nickels: " << machine.GetDenomQuantities(0);
    cout << endl << "Quantity dimes: " << machine.GetDenomQuantities(1);
    cout << endl << "Quantity quarters: " << machine.GetDenomQuantities(2);
    cout << endl << "Quantity ones: " << machine.GetDenomQuantities(3);
    cout << endl << "Quantity fives: " << machine.GetDenomQuantities(4);
    
    //Write machine and inventory stats to Report file
    cout << "\n\nWriting 'Report.txt'...\n\n";
    
    outFS.open("Report.txt");
    outFS << "-----VENDING MACHINE REPORT-----\n\n";
    outFS << "Total in Machine: $" << fixed << setprecision(2) << machine.GetTotalMoney();
    outFS << endl << "Revenue: $" << fixed << setprecision(2) << machine.GetTotalMoney() - totalMoneyStart;
    outFS << "\n\nINVENTORY:";
    for(i = 0; i < count; i++){
        outFS << endl << "Quantity " << product.GetItemNames(i) << ": " << product.GetItemQuantities(i);
    }
    outFS << "\n\nDENOMINATIONS:";
    outFS << endl << "Quantity nickels: " << machine.GetDenomQuantities(0);
    outFS << endl << "Quantity dimes: " << machine.GetDenomQuantities(1);
    outFS << endl << "Quantity quarters: " << machine.GetDenomQuantities(2);
    outFS << endl << "Quantity ones: " << machine.GetDenomQuantities(3);
    outFS << endl << "Quantity fives: " << machine.GetDenomQuantities(4);
    outFS.close();
    
    return 0;
}

/*==================================================================================*/

//Function allows user to input money into machine
void inputUserMoney(Register& machine) {
    int userMoney = 0;
    int numFives = 0;  //Only allow two fives to be inserted at time
    int numOnes = 0;   //Only allow five ones to be inserted at time
    bool checkVal = true;
    
    
    while (userMoney != 6) {
        checkVal = true;
        system ("tput clear");
        cout << "-----ENTER COIN OR BILL USING KEYPAD-----\n\n" << "1. Nickel\n" << "2. Dime\n"
        << "3. Quarter\n" << "4. One\n" << "5. Five\n" << "6. Return to main menu\n\n"
        << "Current Amt: $" << machine.GetActivePurchaseAmt() << endl;
        cin >> userMoney;
        cout << endl;
        
        if (userMoney < 1 || userMoney > 6) {
            cout << "\nInvalid user input. Please try again.\n\n";
            cout << "\nPress any key to continue...\n";
            cin.ignore();
            cin.get();
            system ("tput clear");
            checkVal = false;
        }
        
        if (checkVal == true) {
            switch (userMoney) {
                case 1: {
                    machine.SetActiveUserAmt(userMoney);
                    machine.UpdateDenomination(userMoney);
                    break;
                }
                case 2: {
                    machine.SetActiveUserAmt(userMoney);
                    machine.UpdateDenomination(userMoney);
                    break;
                }
                case 3: {
                    machine.SetActiveUserAmt(userMoney);
                    machine.UpdateDenomination(userMoney);
                    break;
                }
                case 4: {
                    if(numOnes < 5){   //Only allow two fives to be inserted at time
                        machine.SetActiveUserAmt(userMoney);
                        machine.UpdateDenomination(userMoney);
                        numOnes++;
                    }
                    else{
                        cout << "\nMAX LIMIT OF DOLLAR BILLS REACHED...\n";
                        cout << "\nPress any key to continue...\n";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
                case 5: {
                    if(numFives < 2){   //Only allow five ones to be inserted at time
                        machine.SetActiveUserAmt(userMoney);
                        machine.UpdateDenomination(userMoney);
                        numFives++;
                    }
                    else{
                        cout << "\nMAX LIMIT OF FIVES REACHED...\n";
                        cout << "\nPress any key to continue...\n";
                        cin.ignore();
                        cin.get();
                    }
                    break;
                }
            }
        }
    }
    return;
}

/*==================================================================================*/

/*Allows user to make product selection, then tests to see if enough funds are available.
	If funds are sufficient, decrement and dispense product, calculate change, and give change.*/
void userSelection(Register& machine, Inventory& product, int count) {
    double costCheck = 0;  //To hold selected item's cost for conditionals
    int userChoice = 0;
    int i = 0;    //Loop variable
    bool checkVal = true;
    bool checkStock = true;
    
    while (userChoice != (count + 1)) {
        checkVal = true;
        checkStock = true;
        system ("tput clear");
        cout << "\n-----ENTER SELECTION USING KEYPAD-----\n\n";
        
        //Print items to choose from
        for (i = 0; i < count; i++) {
            cout << (i + 1) << ". " << product.GetItemNames(i) << " ---> $ " << product.GetItemCosts(i) << endl;
        }
        cout << (count + 1) << ". Return to home screen\n";
        cout << "\nCurrent Amt: $" << machine.GetActivePurchaseAmt() << "\n\n";
        cin >> userChoice;
        
        //Only choices 1 through total # of items can be pressed
        if (userChoice < 1 || userChoice > (count + 1)) {
            cout << "\nInvalid user input...\n\n";
            cout << "\nPress any key to continue...\n";
            cin.ignore();
            cin.get();
            checkVal = false;
        }
        
        if(checkVal == true) {
            for (i = 1; i < count + 1; i++) {
                if (userChoice == i) {
                    costCheck = product.GetItemCosts(i - 1);
                    if (costCheck > machine.GetActivePurchaseAmt() || machine.GetActivePurchaseAmt() == 0) {
                        cout << "\nINSUFFICIENT FUNDS...\n\n";
                        cout << "\nPress any key to continue...\n";
                        cin.ignore();
                        cin.get();
                    }
                    else if (product.GetItemQuantities(i - 1) == 0) {
                        checkStock = false;
                        cout << "\nOUT OF STOCK...\n\n";
                        cout << "\nPress any key to continue...\n";
                        cin.ignore();
                        cin.get();
                    }
                    else if (machine.GetActivePurchaseAmt() >= costCheck && machine.GetActivePurchaseAmt() > 0 && checkStock == true) {
                        product.UpdateInventory(i - 1, count);
                        machine.UpdateTotalMoney(product.GetItemCosts(i - 1));
                        machine.CalculateChange(machine.GetActivePurchaseAmt(), product.GetItemCosts(i - 1), true);
                        
                        
                        cout << "\nDispensing " << product.GetItemNames(i - 1) << "...\nCHANGE: $" << machine.GetChange() << endl << endl;
                        machine.ClearMoney();
                        cin.get();
                        return;
                    }
                }
            }
        }
    }
}
