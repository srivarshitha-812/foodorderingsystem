#include<iostream>
#include<string>
#include<sstream>

struct MenuItem {
    std::string name;
    double price;
};

struct Order {
    MenuItem* items;
    int itemCount;
    int capacity;

    Order() {
        itemCount = 0;
        capacity = 10;
        items = new MenuItem[capacity];
    }

    ~Order() {
        delete[] items;
    }

    void addItem(MenuItem item) {
        if(itemCount == capacity) {
            capacity *= 2;
            MenuItem* newItems = new MenuItem[capacity];
            for(int i = 0; i < itemCount; i++) {
                newItems[i] = items[i];
            }
            delete[] items;
            items = newItems;
        }
        items[itemCount] = item;
        itemCount++;
    }
};

double getTotal(Order order) {
    double total = 0;
    for(int i = 0; i < order.itemCount; i++) {
        total += order.items[i].price;
    }
    return total;
}

bool processPayment(double amount) {
    // In a real-world application, this is where you would interface with a payment gateway.
    // For this example, we'll just simulate a successful payment.
    return true;
}

int main() {
    MenuItem menu[3] = {{"Pizza", 10.99}, {"Burger", 7.99}, {"Pasta", 8.99}};
    
    Order order;
    
    int choice;
    std::string input;
    while(true) {
        std::cout << "Menu:\n";
        for(int i = 0; i < 3; i++) {
            std::cout << i+1 << ". " << menu[i].name << " - $" << menu[i].price << "\n";
        }
        std::cout << "Enter the number of the item you want to order, or 0 to finish your order: ";
        std::getline(std::cin, input);
        
        std::stringstream ss(input);
        if(!(ss >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        
        if(choice == 0) break;
        
        if(choice < 1 || choice > 3) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }
        
        order.addItem(menu[choice-1]);
    }
    
    double total = getTotal(order);
    
    std::cout << "Your total is: $" << total << "\n";
    
    if(processPayment(total)) {
        std::cout << "Payment successful!\n";
    } else {
        std::cout << "Payment failed. Please try a different payment method.\n";
    }
    
    return 0;
}