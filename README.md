Inventory Management System

What is this?

This is a simple, command-line program to help you manage an inventory of products. Think of it as a digital stock-keeping notebook for a small shop, a hobby, or a personal collection.

It lets you add your products, track how many you have, record sales, and see your sales history. Best of all, it automatically saves your work, so your product list and sales log are always there when you restart the program.

What can it do? (Features)

When you run the program, you'll see a main menu with 10 options. Here's what they all do in plain English:

Add Product: Add a new item to your inventory. You'll give it a unique ID, a name, the quantity you have in stock, and its price.

Display All Products: Shows you a clean list of every item you have, including its ID, name, quantity, and price.

Save Data to CSV: Manually save your current inventory list. (Note: The program also saves automatically after you sell, edit, or delete a product, so your data is almost always safe!)

Delete Product: Remove a product from your inventory. You can find it by typing its ID or its name.

Edit Product: Change the details of a product. You'll find the product by its ID, and then you can update its quantity or price.

Sell Product: Record a sale. You'll enter the product's ID, the quantity being sold, and the buyer's name. This automatically:

Reduces the quantity you have in stock.

Calculates the revenue.

Adds a new line to your "transactions.csv" sales log.

Check Low Stock: Get an automatic warning for any product that has fewer than 20 items left in stock, helping you know when to reorder.

View Transaction History: Shows you a complete list of all the sales you've ever recorded.

Clear Transaction History: Wipes the sales log clean. (Use this with caution! It cannot be undone.)

Exit: Safely closes the program.

How to Use It

When you run the program, just type the number of the action you want to perform (e.g., type 1 and press Enter to add a new product) and follow the simple on-screen prompts.

Files This Program Creates

This program automatically creates and manages two files in the same-folder to store your data:

inventory.csv: This is your main product list. The program saves your items here so you don't lose your work when you close it.

transactions.csv: This is your sales log. Every time you use the "Sell Product" option, a new line is added here.