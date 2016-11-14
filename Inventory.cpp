#include "Inventory.h"
#include <string>
#include <iostream>
using namespace std;

Inventory::Inventory() {
	vector<string> itemName(10);
	vector<double> itemCost(10);
	vector<int> itemQuantity(10);
	return;
}

void Inventory::SetInventoryNames(string newString) {
	//Set inventory name with string from file.
	itemName.push_back(newString);
	return;
}

void Inventory::SetInventoryCosts(double newDouble) {
	//Set the costs of each item from text file.
	itemCost.push_back(newDouble);
	return;
}

void Inventory::SetInventoryQuantity(int newInt) {
	//Set quantity of each item in inventory
	itemQuantity.push_back(newInt);
	return;
}

void Inventory::UpdateInventory(int itemChoice, int count) {
	/*The user's choice is passed as a parameter in order to decrement inventory. Decrease 
	purchased item (itemQuantity) from inventory if condition is met and item is dispensed.*/
	int i = 0;

	for (i = 0; i < count; i++) {
		if (itemChoice == i) {
			itemQuantity.at(i)--;
		}
	}

	return;
}

string Inventory::GetItemNames(int i) const {
	return itemName.at(i);
}

double Inventory::GetItemCosts(int i) const {
	return itemCost.at(i);
}

int Inventory::GetItemQuantities(int i) const {
	return itemQuantity.at(i);
}
