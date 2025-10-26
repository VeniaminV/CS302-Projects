//Veniamin Velikoretskikh  veniamin@pdx.edu
//Karla Fant CS302 fall 2025

// Main menu interface for Festival program
/*
#include "List.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void display_menu()
{
    cout << "\n=== Festival Menu ===\n";
    cout << "1. Add Trinket Vendor\n";
    cout << "2. Add Cuisine Vendor\n";
    cout << "3. Add Entertainer\n";
    cout << "4. Display All Vendors\n";
    cout << "5. Retrieve Cuisine Vendor\n";
    cout << "6. Retrieve Entertainer Vendor\n";
    cout << "7. Remove Cuisine Vendor\n";
    cout << "8. Remove Entertainer Vendor\n";
    cout << "10. Take Cuisine Order\n";
    cout << "11. Recommend Cuisine Item\n";
    cout << "12. Reschedule Entertainer\n";
//    cout << "13. Rename Vendor\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Festival fest;
    int choice;

    do {
        display_menu();
        cin >> choice;
        cin.ignore(100, '\n'); // clear input buffer

        switch (choice) {
            case 1: {  // Add Trinket Vendor
                string name, signature;
                cout << "Enter Trinket Vendor name: ";
                getline(cin, name);
                cout << "Enter signature item: ";
                getline(cin, signature);
                fest.add_trinket_vendor(TrinketVendor(name.c_str(), signature.c_str()));
                break;
            }

            case 2: {  // Add Cuisine Vendor
                string name;
                cout << "Enter Cuisine Vendor name: ";
                getline(cin, name);

                char addMore;
                vector<string> menuItems;
                do {
                    string item;
                    cout << "Enter menu item: ";
                    getline(cin, item);
                    menuItems.push_back(item);

                    cout << "Add another menu item? (y/n): ";
                    cin >> addMore;
                    cin.ignore(100, '\n');
                } while (addMore == 'y' || addMore == 'Y');

                fest.add_cuisine_vendor(CuisineVendor(name.c_str(), menuItems));
                break;
            }

            case 3: {  // Add Entertainer
                string name, group, stage;
                int duration;
                cout << "Enter Entertainer name: ";
                getline(cin, name);
                cout << "Enter group name: ";
                getline(cin, group);
                cout << "Enter duration (minutes): ";
                cin >> duration;
                cin.ignore(100, '\n');
                cout << "Enter stage time: ";
                getline(cin, stage);

                fest.add_entertainer(EntertainerVendor(name.c_str(), group, duration, stage));
                break;
            }

            case 4:  // Display all vendors
                if (!fest.display_all())
                    cout << "No vendors to display.\n";
                break;

            case 5: {  // Retrieve Cuisine Vendor
                string name;
                cout << "Enter the Cuisine Vendor name to retrieve: ";
                getline(cin, name);
                const CuisineVendor *cv = fest.retrieve_cuisine(name.c_str());
                if (!cv || !cv->show_menu())
                    cout << "Cuisine vendor not found.\n";
                break;
            }

            case 6: {  // Retrieve Entertainer Vendor
                string name;
                cout << "Enter the Entertainer name to retrieve: ";
                getline(cin, name);
                const EntertainerVendor *ev = fest.retrieve_entertainer(name.c_str());
                if (!ev || !ev->announce())
                    cout << "Entertainer not found.\n";
                break;
            }

            case 7: {  // Remove Cuisine Vendor
                string name;
                cout << "Enter the Cuisine Vendor name to remove: ";
                getline(cin, name);
                if (fest.remove_cuisine(name.c_str()))
                    cout << "Cuisine vendor removed.\n";
                else
                    cout << "Cuisine vendor not found.\n";
                break;
            }

            case 8: {  // Remove Entertainer Vendor
                string name;
                cout << "Enter the Entertainer name to remove: ";
                getline(cin, name);
                if (fest.remove_entertainer(name.c_str()))
                    cout << "Entertainer removed.\n";
                else
                    cout << "Entertainer not found.\n";
                break;
            }

            case 10: {  // Take Cuisine Order
                string vendorName, food;
                cout << "Enter Cuisine Vendor name: ";
                getline(cin, vendorName);
                cout << "Enter food to order: ";
                getline(cin, food);

                const CuisineVendor *cv = fest.retrieve_cuisine(vendorName.c_str());
                if (cv)
                    cv->take_order(food);
                else
                    cout << "Cuisine vendor not found.\n";
                break;
            }

            case 11: {  // Recommend Cuisine Item
                string vendorName;
                cout << "Enter Cuisine Vendor name: ";
                getline(cin, vendorName);

                const CuisineVendor *cv = fest.retrieve_cuisine(vendorName.c_str());
                if (cv)
                    cv->recommend_item();
                else
                    cout << "Cuisine vendor not found.\n";
                break;
            }

            case 12: {  // Reschedule Entertainer
                string vendorName, newTime;
                cout << "Enter Entertainer name: ";
                getline(cin, vendorName);
                cout << "Enter new stage time: ";
                getline(cin, newTime);

                EntertainerVendor *ev = const_cast<EntertainerVendor*>(fest.retrieve_entertainer(vendorName.c_str()));
                if (ev)
                    ev->reschedule(newTime);
                else
                    cout << "Entertainer not found.\n";
                break;
            }

            case 13: {  // Rename Vendor
                string oldName, newName;
                cout << "Enter current Vendor name: ";
                getline(cin, oldName);
                cout << "Enter new Vendor name: ";
                getline(cin, newName);

                // Implement rename_vendor in Festival if needed
                if (!fest.rename_vendor(oldName.c_str(), newName.c_str()))
                    cout << "Vendor not found.\n";
                break;
            /

            case 0:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
*/
// Veniamin Velikoretskikh  veniamin@pdx.edu
// Karla Fant  CS302 Fall 2025
// Main menu interface for Festival program

#include "List.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void display_menu()
{
    cout << "\n=== Festival Menu ===\n";
    cout << "1. Add Trinket Vendor\n";
    cout << "2. Add Cuisine Vendor\n";
    cout << "3. Add Entertainer\n";
    cout << "4. Display All Vendors\n";
    cout << "5. Retrieve Cuisine Vendor\n";
    cout << "6. Retrieve Entertainer Vendor\n";
    cout << "7. Remove Cuisine Vendor\n";
    cout << "8. Remove Entertainer Vendor\n";
    cout << "9. Sell Trinket Item\n";
    cout << "10. Take Cuisine Order\n";
    cout << "11. Recommend Cuisine Item\n";
    cout << "12. Reschedule Entertainer\n";
    cout << "13. Rename Vendor\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Festival fest;
    int choice = -1;

    do {
        display_menu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        cin.ignore(100, '\n'); // clear newline

        switch (choice) {

        case 1: { // Add Trinket Vendor
            string name, signature;
            cout << "Enter Trinket Vendor name: ";
            getline(cin, name);
            cout << "Enter signature item: ";
            getline(cin, signature);

            if (fest.add_trinket_vendor(TrinketVendor(name.c_str(), signature.c_str())))
                cout << "Trinket vendor added.\n";
            else
                cout << "Failed to add vendor.\n";
            break;
        }

        case 2: { // Add Cuisine Vendor
            string name;
            cout << "Enter Cuisine Vendor name: ";
            getline(cin, name);

            vector<string> menuItems;
            char addMore;
            do {
                string item;
                cout << "Enter menu item: ";
                getline(cin, item);
                menuItems.push_back(item);

                cout << "Add another item? (y/n): ";
                cin >> addMore;
                cin.ignore(100, '\n');
            } while (addMore == 'y' || addMore == 'Y');

            if (fest.add_cuisine_vendor(CuisineVendor(name.c_str(), menuItems)))
                cout << "Cuisine vendor added.\n";
            else
                cout << "Failed to add cuisine vendor.\n";
            break;
        }

        case 3: { // Add Entertainer
            string name, group, stage;
            int duration;
            cout << "Enter Entertainer name: ";
            getline(cin, name);
            cout << "Enter group name: ";
            getline(cin, group);
            cout << "Enter duration (minutes): ";
            cin >> duration;
            cin.ignore(100, '\n');
            cout << "Enter stage time: ";
            getline(cin, stage);

            if (fest.add_entertainer(EntertainerVendor(name.c_str(), group, duration, stage)))
                cout << "Entertainer added.\n";
            else
                cout << "Failed to add entertainer.\n";
            break;
        }

        case 4: { // Display all vendors
            int count = fest.display_all();
            if (count == 0)
                cout << "No vendors to display.\n";
            break;
        }

        case 5: { // Retrieve Cuisine Vendor
            string name;
            cout << "Enter Cuisine Vendor name to retrieve: ";
            getline(cin, name);

            const CuisineVendor *cv = fest.retrieve_cuisine(name.c_str());
            if (cv) cv->show_menu();
            else cout << "Cuisine vendor not found.\n";
            break;
        }

        case 6: { // Retrieve Entertainer Vendor
            string name;
            cout << "Enter Entertainer name to retrieve: ";
            getline(cin, name);

            EntertainerVendor *ev =
                const_cast<EntertainerVendor*>(fest.retrieve_entertainer(name.c_str()));

            if (ev) ev->announce();
            else cout << "Entertainer not found.\n";
            break;
        }

        case 7: { // Remove Cuisine Vendor
            string name;
            cout << "Enter Cuisine Vendor name to remove: ";
            getline(cin, name);

            if (fest.remove_cuisine(name.c_str()))
                cout << "Cuisine vendor removed.\n";
            else
                cout << "Cuisine vendor not found.\n";
            break;
        }

        case 8: { // Remove Entertainer Vendor
            string name;
            cout << "Enter Entertainer Vendor name to remove: ";
            getline(cin, name);

            if (fest.remove_entertainer(name.c_str()))
                cout << "Entertainer removed.\n";
            else
                cout << "Entertainer not found.\n";
            break;
        }
/*
        case 9: { // Sell Trinket Item
            string vendorName, item;
            cout << "Enter Trinket Vendor name: ";
            getline(cin, vendorName);
            cout << "Enter item to sell: ";
            getline(cin, item);

            TrinketVendor *tv = fest.retrieve_trinket(vendorName.c_str());
            if (tv) tv->sell_item(item);
            else cout << "Trinket vendor not found.\n";
            break;
        }
*/
        case 10: { // Take Cuisine Order
            string vendorName, food;
            cout << "Enter Cuisine Vendor name: ";
            getline(cin, vendorName);
            cout << "Enter food to order: ";
            getline(cin, food);

            CuisineVendor *cv = const_cast<CuisineVendor*>(fest.retrieve_cuisine(vendorName.c_str()));
            if (cv) cv->take_order(food);
            else cout << "Cuisine vendor not found.\n";
            break;
        }

        case 11: { // Recommend Cuisine Item
            string vendorName;
            cout << "Enter Cuisine Vendor name: ";
            getline(cin, vendorName);

            const CuisineVendor *cv = fest.retrieve_cuisine(vendorName.c_str());
            if (cv) cv->recommend_item();
            else cout << "Cuisine vendor not found.\n";
            break;
        }

        case 12: { // Reschedule Entertainer
            string vendorName, newTime;
            cout << "Enter Entertainer name: ";
            getline(cin, vendorName);
            cout << "Enter new stage time: ";
            getline(cin, newTime);

            EntertainerVendor *ev = fest.retrieve_entertainer(vendorName.c_str());
            if (ev) ev->reschedule(newTime);
            else cout << "Entertainer not found.\n";
            break;
        }

        case 13: { // Rename Vendor
            string oldName, newName;
            cout << "Enter current Vendor name: ";
            getline(cin, oldName);
            cout << "Enter new Vendor name: ";
            getline(cin, newName);

            if (fest.rename_vendor(oldName.c_str(), newName.c_str()))
                cout << "Vendor renamed.\n";
            else
                cout << "Vendor not found.\n";
            break;
        }

        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}

