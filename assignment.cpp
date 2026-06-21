#include <iostream>
#include <iomanip>
using namespace std;

class Store{
    protected : 
        int* itemID;
        string* itemName;
        string* category;
        float* price;
        int catalogSize;


    public :
        Store(){
            catalogSize = 10;

            itemID = new int[catalogSize]{101,102,103,201,202,203,301,302,303,304};

            itemName = new string[catalogSize]
            {
                "T-Shirt","Hoodie","Turtleneck",
                "Jeans","Shorts","Joggers",
                "Scarf","Belt","Tie","Beanie"
            };

            category = new string[catalogSize]
            {
                "Shirt","Shirt","Shirt",
                "Pants","Pants","Pants",
                "Accessories","Accessories","Accessories","Accessories"
            };

            price = new float[catalogSize]
            {
                12.00, 13.00, 14.80,
                21.90, 16.50, 15.80,
                10.90, 20.00, 31.00, 15.70
            };

        }
        
        virtual ~Store() {
            delete[] itemID;
            delete[] itemName;
            delete[] category;
            delete[] price;        
        }

}S;

class Clothing : public Store{
    public :
        Clothing() : Store() {}

        int getCatalogSize(){
            return catalogSize; 
            }

        int getItemID(int i){
            return itemID[i]; 
            }

        string getItemName(int i){
            return itemName[i]; 
            }

        float getItemPrice(int i){
            return price[i]; 
        }

};

class Cart : public Store{
    private : 
        int* cartItemID;
        int* quantity;
        int cartCap, cartCount;

    public :
        Cart() : Store(){
            cartCap = 10;
            cartCount = 0;
            cartItemID = new int[cartCap]{0};
            quantity = new int[cartCap]{0};
        }

        ~Cart() {
        delete[] cartItemID;
        delete[] quantity;
        }

        int getCartCount(){
            return cartCount;
        }

        int getCartItemID(int index){
            return cartItemID[index]; 
        }

        int getCartQuantity(int index){
            return quantity[index]; 
        }
    
        void setCartCount(int count){
            cartCount = count;
        }

        void setCartItemID(int index, int id){
            cartItemID[index] = id;
        }

        void setCartQuantity(int index, int qty){ 
            quantity[index] = qty; 
        }

    // Friend function declaration
    friend float calculateTotalBill(const Cart& C, const Clothing& Shop);
};

int main()
{
    Clothing item;
    Cart userCart;
    int choice;

    while (choice != 6) {
        cout<<"\n=== CLOTHING RETAIL SHOPPING SYSTEM ===\n";
        cout<<"1. Add to Cart\n";
        cout<<"2. View Cart\n";
        cout<<"3. Edit Cart\n";
        cout<<"4. Remove from Cart\n";
        cout<<"5. Checkout\n";
        cout<<"Enter Choice: ";
        cin>>choice;
    }

    switch (choice)
    {
    case 1:
        cout << "\n===== Store Catalog =====\n";
            for (int i = 0; i < item.getCatalogSize(); ++i) {
                std::cout << "ID: " << item.getItemID(i) << " | " 
                          << item.getItemName(i) << " - $" << item.getItemPrice(i) << "\n";
            }
        break;
    
    case 2:
        /* code */
        break;
    
    case 3:
        /* code */
        break;
    
    case 4:
        /* code */
        break;

    case 5:
        /* code */
        break;
    
    default:
        break;
    }


    return 0;

}