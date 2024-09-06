// more random.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// The base class for a hardware item
class HardwareItem {
public:
    string name;
    double price;
    int quantity;
    // Constructor initializes item name, price and quantity
    HardwareItem(string name, double price) {
        this->name = name;
        this->price = price;
        this->quantity = 0;
    }
};
// The order class which holds a list of hardware items and details about the order
class HardwareOrder {
public:
    vector<HardwareItem> items;
    double  total;
    double payment;
    double change;
    double DeliveryEXP=5.99;
   double DeliveryStan=2.99;
   int deliverychoice{};
   // Constructor initializes total, payment, change and delivery fees
    HardwareOrder() {
        total = 0.00;
        payment = 0.00;
        change = 0.00;
        DeliveryEXP = 5.99;
        DeliveryStan = 2.99;
    }
    // Method to add an item to the order
    void addItem(HardwareItem item, int qty) {
        item.quantity += qty;
        total += item.price * qty;
        items.push_back(item);
    }
    // Method to display the order summary
    void displayOrder() {
        cout << "Order summary:" << endl;
        for (HardwareItem item : items) {
            cout << item.name << " x" << item.quantity << " ($" << item.price << " each)" << endl;
        }
        cout << "Total: $" << total << endl; 
        system("pause");

        // Write the order summary to a file
        ofstream outFile;
        outFile.open("Your_Order_Summary.txt");
        outFile << "Order summary:" << endl;
        for (HardwareItem item : items) {
            outFile << item.name << " x" << item.quantity << " ($" << item.price << " each)" << endl;
        }
        outFile << "******DELIVERY INc******" << total << endl;
        outFile << "Total: $" << total << endl;
        outFile.close();
       
    }
    // Method to process payment and calculate change
    void PAY() {

        cout << "" << endl;
        cout << "Please now pay!" << endl;
        cout << "" << endl;
        cout << "PRESS ANY BUTTON TO CONTINUE !" << endl;
        system("pause");
        //  the  delivery option
        cout << "               Please select your delivery choice " << endl;
        cout << "---_____________________________________________________________---" << endl;
        cout << "[1]Standard Delivery :$2.99           [2]Express Delivery :$5.99 " << endl;
        cout << "" << endl;
        cout << " Enter Your Choice :" ;
        cin >> deliverychoice;
        // Apply the selected delivery fee to the total
        if (deliverychoice==1)
        {
            cout << "" << endl;
            cout << "YOU'VE SELECTED STANDARD DELIVERY " << endl;
            cout << "" << endl;
            DeliveryStan += total;
        
        }
        if (deliverychoice==2)
        {    
            cout << "" << endl;
            cout << "YOU'VE SELECTED EXPRESS DELIVERY " << endl;
            cout << "" << endl;
           
            DeliveryEXP += total;
        }
        system("pause");
        // Display the total amount to be paid and
        cout << "Total to be paid: $" << total << endl;

        do {
            cout << "\nPAYMENT:";
            cin >> payment;
            if (payment < total)
             cout << "Payment has to be higher or equal to the total amount!" << endl;
            else
            {
                change = payment - total;
                cout << "Here's your change : $" << change << endl;
                system("pause");
                system("cls");
                cout << "" << endl;
                cout << "Thankyou for shopping ... GOODBYE!!!!" << endl;
                cout << "" << endl;
                break;

            }
        } while (payment < total);


    }





};
// Header file for defining the HardwareOrderBuilder class

class HardwareOrderBuilder {
private:
    HardwareOrder order;

public:
    // Method to add an item and its quantity to the order
    void addItem(HardwareItem item, int qty) {
        order.addItem(item, qty);
    }

    // to return the final order objec
    HardwareOrder buildOrder() {
        return order;
    }
};

class HardwareStore {
private:
    // Vector of  the items available in the store

    vector<HardwareItem> items;

public:
    HardwareStore() {
        // Adding main items to the store
        items.push_back(HardwareItem("Main Items   |Hammer", 12.25));
        items.push_back(HardwareItem("Main Items   |Saw", 19.56));
        items.push_back(HardwareItem("Main Items   |Screwdriver", 5.18));
        // Adding accessories to the store
        items.push_back(HardwareItem("Accessories  |Brush ", 2.99));
        items.push_back(HardwareItem("Accessories  |Roller", 4.99));
        items.push_back(HardwareItem("Accessories  |Tape", 1.99));
    }

    void displayItems() {
        //  to display the available items in the store
        cout << "Welcome to our hardware store!" << endl;
        cout << "Here are the available main items and prices:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i].name << ": $" << items[i].price << endl;
        }
    }

    HardwareItem getItem(int index) {
        return items[index];
    }
};


////////////////////////////////////////////////////////////////////////////
//the display of each store 
///////////////////////////////////////////////////////////////////////////////



//  class for defining a branch

class Branch
{
public:
    virtual void displayBranch() = 0;
};

//  virtual method to display the name of the branch

class TreforestB : public  Branch {
public:
    void displayBranch() {

        cout << " Welcome To Treforest Store " << endl;
    }
};

class CardiffB : public  Branch {
public:
    void displayBranch() {

        cout << " Welcome To Cardiff Store" << endl;
    }
};

class PontypriddB : public  Branch {
public:
    void displayBranch() {

        cout << " Welcome To Pontypridd Store" << endl;
    }
};
class BranchFactory {
public:
    virtual  Branch* createBranch() = 0;

};
//returing the details 
class Treforest : public BranchFactory {
public:
    Branch* createBranch() {
        return new TreforestB();
    }
};

class Cardiff : public BranchFactory {
public:
    Branch* createBranch() {
        return new CardiffB();
    }
};

class Pontypridd : public BranchFactory {
public:
    Branch* createBranch() {
        return new PontypriddB();
    }
};



// the start of the program that the user will first see 
//this will allow the user to pick their chosen branch 

class Thestart {

    int choice{};

public:

    string store;

    void gogo() {


        BranchFactory* treforest = new Treforest();
        BranchFactory* pontypriddf = new Pontypridd();
        BranchFactory* cardiff = new Cardiff();

        Branch* MyBranch;


        cout << "__________________________________________________________________________________________________________" << endl;
        cout << "                                      SELECT YOUR CHOSEN BRANCH                                            " << endl;
        cout << "__________________________________________________________________________________________________________" << endl;
        cout << "  " << endl;
        cout << "       " << "1.Treforest Store" << setw(10) << "                  " << "2.Pontypridd Store" << "                  " << "3.Cardiff Store" << endl;
        cout << "" << endl;
        cout << "                                           0.Exit Program  " << endl;
        cout << "  " << endl;
        cout << " Select Your Choice:  ";
        cin >> choice;

        if (choice == 1) {
            //  store = " Treforest ";


            cout << " you picked Treforest, now redirecting..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << " " << endl;

            system("cls");
            MyBranch = treforest->createBranch();
            MyBranch->displayBranch();
        }

        else if (choice == 2) {
            // store = " Pontypridd ";

            cout << " you picked Pontypridd, now redirecting..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << " " << endl;
            system("cls");
            MyBranch = pontypriddf->createBranch();
            MyBranch->displayBranch();


        }

        else if (choice == 3) {
            //  store = " Cardiff";

            cout << " you picked Cardiff, now redirecting..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            cout << " " << endl;
            system("cls");
            MyBranch = cardiff->createBranch();
            MyBranch->displayBranch();


        }
        else if (choice == 0) {
            system("cls");
            cout << "GOODBYE" << endl;
            exit(0);
        }

        else  if (choice > 0 || 3 < choice) {



            cout << "invalid input.TRY AGAIN!" << endl;


            return gogo();
        }


    }


};






int main() {
    //the links to the classes 
    Thestart the;
    the.gogo();

    HardwareStore store;
    HardwareOrderBuilder builder;


    // the main user interface 

    int choice;
    do {
       
        cout << "_______________________________________________________________________" << endl;
        cout << "     Please browse our store and order your chosen item" << endl;
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "1. Display available items" << endl;
        cout << "2. Add item to order" << endl;
        cout << "3. Display order" << endl;
        cout << "4. Confirm order" << endl;
        cout << "5. Cancel order" << endl;
        cout << "Select Your Choice:";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            store.displayItems();
            break;

        case 2: {
            int itemChoice;
            int qty;
            cout << "Which item would you like to add to your order? (enter item number 1-6): ";
            cin >> itemChoice;
            cout << "Please select your quantity? ";
            cin >> qty;
            HardwareItem item = store.getItem(itemChoice - 1);
            builder.addItem(item, qty);
            cout << "Added " << qty << " " << item.name << "(s) to your order." << endl;
            break;
        }

        case 3:
            builder.buildOrder().displayOrder();
            break;

        case 4:
            cout << "___________________________________ " << endl;
            cout << "Thankyou for shopping at our store!" << endl;
            cout << "ORDER CONFIRMED-------> REDIRECTING TO PAYMMENT SYSTEM..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            system("cls");
            builder.buildOrder().PAY();

            return 0;

        case 5:
            cout << "Your order has been cancelled." << endl;
            system("cls");
            cout << "GOODBYE ,I HOPE WE COULD BE BETTER HELP NEXT TIME! " << endl;
            return 0;


        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
        cout << endl;
    } while (true);

    return 0;
}