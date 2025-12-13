#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Struct to store item details
struct Item{
    string name;
    int price;
};

// Used by greedy algorithm to sort by price
bool comparePrices(Item a,Item b){
    return a.price<b.price;
}

// Dynamic Programming approach to maximize item count
void solveDynamicProgramming(int totalBudget,vector<Item> items){
    int numItems=items.size();

    // DP table: items vs budget
    vector<vector<int>> countTable(numItems+1,vector<int>(totalBudget+1));

    for(int i=0;i<=numItems;i++){
        for(int capacity=0;capacity<=totalBudget;capacity++){
            if(i==0||capacity==0){
                countTable[i][capacity]=0;
            }
            else if(items[i-1].price<=capacity){
                int buyItem=1+countTable[i-1][capacity-items[i-1].price];
                int skipItem =countTable[i-1][capacity];
                countTable[i][capacity]=max(buyItem,skipItem);
            }
            else{
                countTable[i][capacity]=countTable[i-1][capacity];
            }
        }
    }

    cout<<"\nDynamic Programming results:"<<endl;
    cout<<"Maximum items found: "<<countTable[numItems][totalBudget]<<endl;
    cout<<"Shopping list:"<<endl;

    int remainingBudget=totalBudget;
    int currentResult =countTable[numItems][totalBudget];

    // Backtrack to print chosen items
    for(int i=numItems;i>0 && currentResult>0;i--){
        if(countTable[i][remainingBudget]!=countTable[i-1][remainingBudget]){
            cout<<"  - "<<items[i-1].name<<" ($"<<items[i-1].price<<")"<<endl;
            remainingBudget-=items[i-1].price;
            currentResult--;
        }
    }
}

// Greedy approach: buy cheapest items first
void solveGreedy(int totalBudget,vector<Item> items){
    sort(items.begin(),items.end(),comparePrices);

    cout<<"\nGreedy Algorithm results:"<<endl;

    int itemsCount=0;
    int moneySpent =0;

    cout<<"Shopping list:"<<endl;

    for(int i=0;i<items.size();i++){
        if(moneySpent+items[i].price<=totalBudget){
            moneySpent+=items[i].price;
            itemsCount++;
            cout<<"  - "<<items[i].name<<" ($"<<items[i].price<<")"<<endl;
        }
    }

    cout<<"Maximum items found: "<<itemsCount<<endl;
}

int main(){
    int userBudget;
    int numberOfItems;

    cout<<"Enter your total shopping budget: ";
    cin>>userBudget;

    cout<<"How many items are in the store? ";
    cin>>numberOfItems;

    vector<Item> storeInventory(numberOfItems);

    // Read item input
    for(int i=0;i<numberOfItems;i++){
        cout<<"\nItem "<<i+1<<":"<<endl;
        cout<<"  Name: ";
        cin>>storeInventory[i].name;
        cout<<"  Price: ";
        cin>>storeInventory[i].price;
    }

    // Run both algorithms
    solveDynamicProgramming(userBudget,storeInventory);
    solveGreedy(userBudget,storeInventory);

    return 0;
}
