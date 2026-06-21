#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Store {
protected:
    int* itemID;
    string* itemName;
    string* category;
    float* price;
    int catalogSize;
    string storeName;
    string storeLocation;

public:
    Store() {
        storeName = "Unnamed";
        storeLocation = "Unknown";
        catalogSize = 0;
        itemID = nullptr;
        itemName = nullptr;
        category = nullptr;
        price = nullptr;
    }

    Store(string name, string location, int size,
          int* ids, string* names, string* cats, float* prices) {
        storeName = name;
        storeLocation = location;
        catalogSize = size;

        itemID   = new int[catalogSize];
        itemName = new string[catalogSize];
        category = new string[catalogSize];
        price    = new float[catalogSize];

        for (int i = 0; i < catalogSize; ++i) {
            itemID[i]   = ids[i];
            itemName[i] = names[i];
            category[i] = cats[i];
            price[i]    = prices[i];
        }
    }

    Store(const Store& other) {
        storeName     = other.storeName;
        storeLocation = other.storeLocation;
        catalogSize   = other.catalogSize;

        if (catalogSize > 0) {
            itemID   = new int[catalogSize];
            itemName = new string[catalogSize];
            category = new string[catalogSize];
            price    = new float[catalogSize];

            for (int i = 0; i < catalogSize; ++i) {
                itemID[i]   = other.itemID[i];
                itemName[i] = other.itemName[i];
                category[i] = other.category[i];
                price[i]    = other.price[i];
            }
        } else {
            itemID   = nullptr;
            itemName = nullptr;
            category = nullptr;
            price    = nullptr;
        }
    }

    string getStoreName() const { 
        return storeName; 
        }

    string getStoreLocation() const { 
        return storeLocation; 
        }

    void displayBranchInfo() const {
        cout << "\n========================================\n";
        cout << "   " << storeName << " - " << storeLocation << "\n";
        cout << "========================================\n";
    }

    virtual ~Store() {
        delete[] itemID;
        delete[] itemName;
        delete[] category;
        delete[] price;
    }
};

class Clothing : public Store {
public:
    Clothing() : Store() {}

    Clothing(string name, string location, int size,
             int* ids, string* names, string* cats, float* prices)
        : Store(name, location, size, ids, names, cats, prices) {}

    Clothing(const Clothing& other) : Store(other) {}

    int getCatalogSize() const {
        return catalogSize; 
        }

    int getItemID(int i) const {
        return itemID[i]; 
        }

    string getItemName(int i) const {
        return itemName[i]; 
        }

    string getCategory(int i) const {
        return category[i]; 
        }

    float getItemPrice(int i) const {
        return price[i]; 
        }

    int findIndexByID(int id) const {
        for (int i = 0; i < catalogSize; ++i)
            if (itemID[i] == id) return i;
        return -1;
    }

    void displayCatalog() const {
        cout << "\n===== " << storeName << " Catalog =====\n";
        for (int i = 0; i < catalogSize; ++i) {
            cout << "ID: " << itemID[i]
                 << " | " << setw(15) << left << itemName[i]
                 << " | " << setw(11) << left << category[i]
                 << " | RM" << fixed << setprecision(2) << price[i] << "\n";
        }
    }
};

class Cart : public Store {
private:
    int* cartItemID;
    int* quantity;
    int cartCap, cartCount;

public:
    Cart() : Store() {
        cartCap = 10;
        cartCount = 0;
        cartItemID = new int[cartCap]{0};
        quantity   = new int[cartCap]{0};
    }

    Cart(int cap) : Store() {
        cartCap = cap;
        cartCount = 0;
        cartItemID = new int[cartCap]{0};
        quantity   = new int[cartCap]{0};
    }

    Cart(const Cart& other) : Store() {
        cartCap   = other.cartCap;
        cartCount = other.cartCount;
        cartItemID = new int[cartCap];
        quantity   = new int[cartCap];
        for (int i = 0; i < cartCap; ++i) {
            cartItemID[i] = other.cartItemID[i];
            quantity[i]   = other.quantity[i];
        }
    }

    ~Cart() {
        delete[] cartItemID;
        delete[] quantity;
    }

    int getCartCount() const {
        return cartCount; 
        }

    int getCartItemID(int index) const {
        return cartItemID[index]; 
        }

    int getCartQuantity(int index) const {
        if (index < 0 || index >= cartCount) return 0;
        return quantity[index];
        }

    void addItem(int id, int qty) {
        if (qty <= 0) return;
        for (int i = 0; i < cartCount; ++i) {
            if (cartItemID[i] == id) { quantity[i] += qty; return; }
        }
        if (cartCount < cartCap) {
            cartItemID[cartCount] = id;
            quantity[cartCount]   = qty;
            cartCount++;
        } else {
            cout << "\nCart is full!\n";
        }
    }

    void editItem(int index, int newQty) {
        if (index < 0 || index >= cartCount || newQty < 0) return;
        quantity[index] = newQty;
        if (quantity[index] == 0) removeItem(index);
    }

    void removeItem(int index) {
        if (index < 0 || index >= cartCount) return;
        for (int i = index; i < cartCount - 1; ++i) {
            cartItemID[i] = cartItemID[i + 1];
            quantity[i]   = quantity[i + 1];
        }
        cartCount--;
        cartItemID[cartCount] = 0;
        quantity[cartCount]   = 0;
    }

    void viewCart(Clothing* branches, int branchCount) const {
        if (cartCount == 0) { cout << "\nYour cart is empty.\n"; return; }

        cout << "\n===== Your Cart =====\n";
        cout << left << setw(6)  << "No."
             << setw(12) << "Item ID"
             << setw(18) << "Item Name"
             << setw(10) << "Qty"
             << setw(16) << "Branch"
             << "Price\n";
        cout << string(70, '-') << "\n";

        float total = 0.0f;
        for (int i = 0; i < cartCount; ++i) {
            for (int b = 0; b < branchCount; ++b) {
                int idx = branches[b].findIndexByID(cartItemID[i]);
                if (idx != -1) {
                    float subtotal = branches[b].getItemPrice(idx) * quantity[i];
                    total += subtotal;
                    cout << left << setw(6)  << (i + 1)
                         << setw(12) << cartItemID[i]
                         << setw(18) << branches[b].getItemName(idx)
                         << setw(10) << quantity[i]
                         << setw(16) << branches[b].getStoreName()
                         << "RM" << fixed << setprecision(2) << subtotal << "\n";
                    break;
                }
            }
        }
        cout << string(70, '-') << "\n";
        cout << "Total: RM" << fixed << setprecision(2) << total << "\n";
    }

    friend float calculateTotalBill(const Cart& C, Clothing* branches, int branchCount);
};

float calculateTotalBill(const Cart& C, Clothing* branches, int branchCount) {
    float total = 0.0f;
    for (int i = 0; i < C.cartCount; ++i) {
        for (int b = 0; b < branchCount; ++b) {
            int idx = branches[b].findIndexByID(C.cartItemID[i]);
            if (idx != -1) {
                total += branches[b].getItemPrice(idx) * C.quantity[i];
                break;
            }
        }
    }
    return total;
}

int main()
{
    int    ids1[]    = {101, 102, 103, 201, 202};
    string names1[]  = {"T-Shirt", "Hoodie", "Turtleneck", "Jeans", "Shorts"};
    string cats1[]   = {"Shirt", "Shirt", "Shirt", "Pants", "Pants"};
    float  prices1[] = {15.00, 31.00, 37.80, 21.90, 16.50};

    int    ids2[]    = {301, 302, 303, 401, 402};
    string names2[]  = {"Blazer", "Dress Shirt", "Slacks", "Tie", "Belt"};
    string cats2[]   = {"Formal", "Formal", "Formal", "Accessories", "Accessories"};
    float  prices2[] = {89.90, 45.00, 55.00, 62.00, 95.00};

    int    ids3[]    = {501, 502, 503, 601, 602};
    string names3[]  = {"Joggers", "Bomber Jacket", "Cargo Pants", "Snapback", "Beanie"};
    string cats3[]   = {"Pants", "Jacket", "Pants", "Accessories", "Accessories"};
    float  prices3[] = {35.00, 120.00, 75.00, 25.00, 15.70};

    const int MAX_BRANCHES = 3;
    Clothing branches[MAX_BRANCHES] = {
        Clothing("KL Branch",     "Kuala Lumpur", 5, ids1, names1, cats1, prices1),
        Clothing("Penang Branch", "Penang",        5, ids2, names2, cats2, prices2),
        Clothing("JB Branch",     "Johor Bahru",   5, ids3, names3, cats3, prices3)
    };

    cout << "\n=== CLOTHING RETAIL SHOPPING SYSTEM ===\n";
    cout << "\nSelect a branch:\n";
    for (int i = 0; i < MAX_BRANCHES; ++i)
        cout << i + 1 << ". " << branches[i].getStoreName()
             << " (" << branches[i].getStoreLocation() << ")\n";

    int branchChoice;
    cout << "\nEnter choice: ";
    cin >> branchChoice;

    if (branchChoice < 1 || branchChoice > MAX_BRANCHES) {
        cout << "Invalid choice. Defaulting to KL Branch.\n";
        branchChoice = 1;
    }

    Clothing* branch = &branches[branchChoice - 1];
    branch->displayBranchInfo();

    Cart userCart;
    int choice = 0;

    do {
        cout << "\n=== " << branch->getStoreName() << " ===\n";
        cout << "1. Add to Cart\n";
        cout << "2. View Cart\n";
        cout << "3. Edit Cart\n";
        cout << "4. Remove from Cart\n";
        cout << "5. Switch Branch\n";
        cout << "6. Checkout\n\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: {
                branch->displayCatalog();
                int id, qty;
                cout << "\nEnter the Item ID: ";
                cin >> id;
                cout << "Enter Quantity: ";
                cin >> qty;

                if (branch->findIndexByID(id) != -1) {
                    userCart.addItem(id, qty);
                    cout << "Item added to cart successfully.\n";
                } else {
                    cout << "Invalid item ID.\n";
                }
                break;
            }

            case 2: {
                userCart.viewCart(branches, MAX_BRANCHES);
                break;
            }

            case 3: {
                userCart.viewCart(branches, MAX_BRANCHES);
                if (userCart.getCartCount() == 0) break;

                int index, qty;
                cout << "\nEnter cart item number to edit: ";
                cin >> index;
                if (index <= 0 || index > userCart.getCartCount()) {
                    cout << "Invalid number.\n";
                } else {
                    cout << "Enter new quantity: ";
                    cin >> qty;
                    userCart.editItem(index - 1, qty);
                    cout << "Cart updated.\n";
                }
                break;
            }

            case 4: {
                userCart.viewCart(branches, MAX_BRANCHES);
                if (userCart.getCartCount() == 0) break;

                int index;
                cout << "\nEnter cart item number to remove: ";
                cin >> index;
                if (index <= 0 || index > userCart.getCartCount()) {
                    cout << "Invalid number.\n";
                } else {
                    userCart.removeItem(index - 1);
                    cout << "Item removed from cart.\n";
                }
                break;
            }

            case 5: {
                cout << "\nSelect new branch:\n";
                for (int i = 0; i < MAX_BRANCHES; ++i)
                    cout << i + 1 << ". " << branches[i].getStoreName()
                         << " (" << branches[i].getStoreLocation() << ")\n";
                cout << "Enter choice: ";
                cin >> branchChoice;

                if (branchChoice < 1 || branchChoice > MAX_BRANCHES) {
                    cout << "Invalid choice.\n";
                } else {
                    branch = &branches[branchChoice - 1];
                    branch->displayBranchInfo();
                    cout << "Note: items from other branches remain in your cart.\n";
                }
                break;
            }

            case 6: {
                if (userCart.getCartCount() == 0) {
                    cout << "\nCart is empty, nothing to checkout.\n";
                    break;
                }
                cout << "\n===== Receipt =====\n";
                cout << "Branch: " << branch->getStoreName() << "\n";
                cout << "-------------------\n";

                float grandTotal = 0.0f;
                for (int i = 0; i < userCart.getCartCount(); ++i) {
                    int cartID = userCart.getCartItemID(i);
                    for (int b = 0; b < MAX_BRANCHES; ++b) {
                        int idx = branches[b].findIndexByID(cartID);
                        if (idx != -1) {
                            float subtotal = branches[b].getItemPrice(idx) * userCart.getCartQuantity(i);
                            grandTotal += subtotal;
                            cout << "[" << branches[b].getStoreName() << "] "
                                 << branches[b].getItemName(idx)
                                 << " x" << userCart.getCartQuantity(i)
                                 << " = RM" << fixed << setprecision(2) << subtotal << "\n";
                            break;
                        }
                    }
                }
                cout << "-------------------\n";
                cout << "TOTAL: RM" << fixed << setprecision(2)
                     << calculateTotalBill(userCart, branches, MAX_BRANCHES) << "\n";
                cout << "Thank you for shopping!\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}