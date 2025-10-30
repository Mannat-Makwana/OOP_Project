#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Product {
private:  
    int id;
    string name;
    int quantity;
    double price;

public:
    Product(int i, string n, int q, double p){
        id = i;
        name = n;
        quantity = q;
        price = p;
    } 
    

    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    string toCSV() const {
        return to_string(id) + "," + name + "," + to_string(quantity) + "," + to_string(price);
    }

    void display() const {
        cout << id << "\t" << name << "\t" << quantity << "\t" << price << endl;
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

        for (const auto &p : products) {
            if (p.getId() == id) {
                cout << "\nError: Product ID already exists. Please use a unique ID.\n";
                return;
            }
        }

        cout << "Enter Product Name: ";
        getline(cin, name);
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;

        products.push_back(Product(id, name, quantity, price));
        cout << "\nProduct added successfully!\n";
    }

    void displayAll() {
        if (products.empty()) {
            cout << "\nNo products in inventory.\n";
            return;
        }

        cout << "\nInventory List:\n";
        cout << "ID\tName\tQuantity\tPrice\n";
        cout << "----------------------------------------\n";
        for (const Product& p : products)
            p.display();
            cout<<endl;

        cout << "Total Products: " << products.size() << endl;
    }

    void saveToCSV(const string& filename = "inventory.csv") {
        ofstream file(filename);
        if (!file) {
            cout << "\nError opening file for writing.\n";
            return;
        }

        file << "ID,Name,Quantity,Price\n";
        for (const Product& p : products)
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
        getline(file, line); 

        while (getline(file, line)) {
            if (line.empty()) continue;

            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            int id = stoi(line.substr(0, pos1));
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            double price = stod(line.substr(pos3 + 1));

            products.push_back(Product(id, name, quantity, price));
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
                    saveToCSV();
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
                    saveToCSV();
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

    void editProduct() {
        if (products.empty()) {
            cout << "\nNo products available to edit.\n";
            return;
        }

        int id;
        cout << "\nEnter Product ID to edit: ";
        cin >> id;
        cin.ignore();

        for (auto &p : products) {
            if (p.getId() == id) {
                cout << "\nEditing Product: " << p.getName() << " (Current Quantity: " << p.getQuantity() << ", Price: " << p.getPrice() << ")\n";
                
                int newQty;
                double newPrice;
                
                cout << "Enter new quantity (or -1 to keep unchanged): ";
                cin >> newQty;
                cout << "Enter new price (or -1 to keep unchanged): ";
                cin >> newPrice;

                if (newQty >= 0)
                    p = Product(p.getId(), p.getName(), newQty, (newPrice >= 0 ? newPrice : p.getPrice()));
                else if (newPrice >= 0)
                    p = Product(p.getId(), p.getName(), p.getQuantity(), newPrice);

                saveToCSV();
                cout << "\nProduct details updated successfully!\n";
                return;
            }
        }

        cout << "\nProduct not found.\n";
    }

    void sellProduct() {
        if (products.empty()) {
            cout << "\nNo products available for sale.\n";
            return;
        }

        int id, qtyToSell;
        string buyer;
        cout << "\nEnter Product ID to sell: ";
        cin >> id;
        cout << "Enter Quantity to sell: ";
        cin >> qtyToSell;
        cin.ignore();
        cout << "Enter Buyer Name: ";
        getline(cin, buyer);

        bool found = false;
        for (auto &p : products) {
            if (p.getId() == id) {
                found = true;
                if (p.getQuantity() < qtyToSell) {
                    cout << "\nQuantity too low. Cannot process sale.\n";
                    return;
                }

                double revenue = p.getPrice() * qtyToSell;
                int newQty = p.getQuantity() - qtyToSell;
                p = Product(p.getId(), p.getName(), newQty, p.getPrice());

                saveToCSV();

                ofstream file("transactions.csv", ios::app);
                if (file.tellp() == 0)
                    file << "ID,Product_Name,Quantity_Sold,Sold_To,Revenue,Date_of_Selling\n";

                time_t now = time(0);
                string date = ctime(&now);
                date.pop_back();

                file << p.getId() << "," << p.getName() << "," << qtyToSell << "," << buyer << "," << revenue << "," << date << "\n";
                file.close();

                cout << "\nSale recorded successfully!\n";
                return;
            }
        }

        if (!found) cout << "\nProduct not found.\n";
    }

    void checkLowStock() {
        bool alert = false;
        for (const auto &p : products) {
            if (p.getQuantity() < 20) {
                cout << "⚠️ Low stock alert: " << p.getName() << " (ID: " << p.getId() << ") has only " << p.getQuantity() << " left. Please restock.\n";
                alert = true;
            }
        }
        if (!alert) cout << "\nAll products are sufficiently stocked.\n";
    }

    void displayTransactions() {
        ifstream file("transactions.csv");
        if (!file) {
            cout << "\nNo transaction records found.\n";
            return;
        }

        string line;
        getline(file, line); // skip header
        if (file.peek() == EOF) {
            cout << "\nNo transactions to display.\n";
            return;
        }

        cout << "\nTransaction History:\n";
        cout << "ID\tProduct Name\tQty Sold\tSold To\tRevenue\tDate of Selling\n";
        cout << "---------------------------------------------------------------\n";

        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            size_t pos5 = line.find(',', pos4 + 1);

            string id = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string qty = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string buyer = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string revenue = line.substr(pos4 + 1, pos5 - pos4 - 1);
            string date = line.substr(pos5 + 1);

            cout << id << "\t" << name << "\t" << qty << "\t" << buyer << "\t" << revenue << "\t" << date << "\n";
        }

        file.close();
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
        cout << "\n5. Edit Product";
        cout << "\n6. Sell Product";
        cout << "\n7. Check Low Stock";
        cout << "\n8. Exit";
        cout << "\n9. View Transaction History";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inventory.addProduct(); break;
            case 2: inventory.displayAll(); break;
            case 3: inventory.saveToCSV(); break;
            case 4: inventory.deleteProduct(); break;
            case 5: inventory.editProduct(); break;
            case 6: inventory.sellProduct(); break;
            case 7: inventory.checkLowStock(); break;
            case 8: cout << "\nExiting... Goodbye!\n"; break;
            case 9: inventory.displayTransactions(); break;
            default: cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}