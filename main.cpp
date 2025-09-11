#include<iostream>
using namespace std; 

class Product{
    int p_id;
    string p_name;
    string p_category;
    string p_supplier;
    float p_price;
    int stock;
    static int count=0;

    public:
        void add(){
            cout<<"Enter the Product name: ";
            cin>>p_name;
            cout<<"Enter the Product ID: ";
            cin>>p_id;
            cout<<"Enter the Product Category: ";
            cin>>p_category;
            cout<<"Enter the Product Supplier: ";
            cin>>p_supplier;
            cout<<"Enter the Product Price: ";
            cin>>p_price;
            cout<<"Enter the Product stock: ";
            cin>>stock;

            count++;
        }

        void display(){
            cout<<"***********************PRODUCT DETAILS************************\n";
            cout<<"Product ID: "<<p_id;
            cout<<"Product Name: "<<p_name;
            cout<<"Product Category: "<<p_category;
            cout<<"Product Supplier: "<<p_supplier;
            cout<<"Product Price: "<<p_price;
            cout<<"Product Stock: "<<stock;
        }
        
        
};