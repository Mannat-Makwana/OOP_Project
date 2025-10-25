#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Product {
private:  
    int id;
    string name;
    int quantity;
    double price;

public:
    Product(int id, string name, int quantity, double price)
        : id(id), name(name), quantity(quantity), price(price) {
    }


    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }


    string toCSV() const {
        return to_string(id) + "," + name + "," + to_string(quantity) + "," + to_string(price);
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price << endl;
    }
};


class Inventory {
private:
    vector<Product> products;

public:
    void addProduct() {
        int id, quantity;
        string name;
        double price;

        cout << "\nEnter Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;

        Product newProduct(id, name, quantity, price);
        products.push_back(newProduct);

        cout << "\nProduct added successfully!\n";
    }

    void displayAll() {
        if (products.empty()) {
            cout << "\n  No products in inventory.\n";
            return;
        }

        cout << "\n---------------------- INVENTORY LIST ----------------------\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price" << endl;
        cout << "-----------------------------------------------------------\n";

        for (const auto& p : products)
            p.display();

        cout << "-----------------------------------------------------------\n";
        
        cout << "Total Products: " << products.size() << endl;
    }

    void saveToCSV(const string& filename = "inventory.csv") {
        ofstream file(filename);

        if (!file) {
            cerr << "\n Error opening file for writing.\n";
            return;
        }

        file << "ID,Name,Quantity,Price\n";
        for (const auto& p : products)
            file << p.toCSV() << "\n";

        file.close();
        cout << "\nData saved to " << filename << " successfully!\n";
    }

    void loadFromCSV(const string& filename = "inventory.csv") {
        ifstream file(filename);
        if (!file) {
            cout << "\nWarning: File " << filename << " not found. Starting with empty inventory.\n";
            return;
        }

        string line;
        getline(file, line); // skip header

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string idStr, name, quantityStr, priceStr;

            if (!getline(ss, idStr, ',')) continue;
            if (!getline(ss, name, ',')) continue;
            if (!getline(ss, quantityStr, ',')) continue;
            if (!getline(ss, priceStr, ',')) continue;

            int id = stoi(idStr);
            int quantity = stoi(quantityStr);
            double price = stod(priceStr);

            Product p(id, name, quantity, price);
            products.push_back(p);
        }
        file.close();
    }

    void deleteProduct() {
        if (products.empty()) {
            cout << "\nNo products to delete.\n";
            return;
        }

        cout << "\nDelete product by:\n1. ID\n2. Name\nEnter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        bool found = false;
        if (choice == 1) {
            int delId;
            cout << "Enter Product ID to delete: ";
            cin >> delId;
            for (auto it = products.begin(); it != products.end(); ++it) {
                if (it->getId() == delId) {
                    products.erase(it);
                    cout << "Product with ID " << delId << " deleted successfully.\n";
                    found = true;
                    break;
                }
            }
        } else if (choice == 2) {
            string delName;
            cout << "Enter Product Name to delete: ";
            getline(cin, delName);
            for (auto it = products.begin(); it != products.end(); ++it) {
                if (it->getName() == delName) {
                    products.erase(it);
                    cout << "Product with Name \"" << delName << "\" deleted successfully.\n";
                    found = true;
                    break;
                }
            }
        } else {
            cout << "Invalid choice.\n";
            return;
        }

        if (!found) {
            cout << "Product not found.\n";
        }
    }
};

int main() {
    Inventory inventory;
    inventory.loadFromCSV();
    int choice;

    do {
        cout << "\n========= INVENTORY MANAGEMENT SYSTEM =========";
        cout << "\n1. Add Product";
        cout << "\n2. Display All Products";
        cout << "\n3. Save Data to CSV";
        cout << "\n4. Delete Product";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            inventory.addProduct();
            break;
        case 2:
            inventory.displayAll();
            break;
        case 3:
            inventory.saveToCSV();
            break;
        case 4:
            inventory.deleteProduct();
            break;
        case 5:
            cout << "\nExiting... Goodbye!\n";
            break;
        default:
            cout << "\n Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}