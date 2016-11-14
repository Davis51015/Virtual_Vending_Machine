#ifndef REGISTER_H
#define REGISTER_H
#include <string>
using namespace std;

class Register {
public:
	void SetActiveUserAmt(int userMoney);  //Call every time user inserts coin/bill. Set back to zero after change is returned.
	void UpdateTotalMoney(double productPrice); 
	void CalculateChange(double userAmount, double productPrice, bool purchaseCheck);  //Include changes to quantities of bills/coins and totalAmount.
    void UpdateDenomination(int userMoney);   //Updates quantities of coins/bills
	void ClearMoney();    //Sets purchaseAmount and totalAmount back to previous state
	double GetActivePurchaseAmt() const;
	double GetTotalMoney() const;
	double GetChange() const;
    int GetDenomQuantities(int i) const;
	Register();		//Constructor
	Register(int five, int one, int quarter, int dime, int nickel); //Sets quantities of coin/bills


private:
	double fiveVal;
	double oneVal;
	double quarterVal;
	double dimeVal;
	double nickelVal;
	int fiveQuantity;
	int oneQuantity;
	int quarterQuantity;
	int dimeQuantity;
	int nickelQuantity;
	double purchaseAmount;  //Equals purchaseAmount += 'new coin/bill inserted'.
	double totalAmount;   //Should equal the total of the quantity * value of each coin/bill.
	double change;
    int numDenom;

};


#endif 

