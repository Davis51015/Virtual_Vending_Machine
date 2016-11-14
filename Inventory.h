#ifndef INVENTORY_H
#define INVENTORY_H
#include <string>
#include <vector>
using namespace std;

class Inventory {
public:
	void SetInventoryNames(string newString);
	void SetInventoryCosts(double newDouble);
	void SetInventoryQuantity(int newInt);
	void UpdateInventory(int itemChoice, int count); 
	string GetItemNames(int i) const;
	double GetItemCosts(int i) const;
	int GetItemQuantities(int i) const;
	
	Inventory();    //Default constructor.

private:
	vector<string> itemName;
	vector<double> itemCost;
	vector<int> itemQuantity;
};


#endif 

