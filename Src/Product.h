using namespace std;

struct Product_Element {
    string id;
    string name;
    string category;
    string brand;
    double price;
    string unit;
    int stock;
    Product_Element* next;
    Product_Element* previous;
};

struct Product_List {
    int size; 
    Product_Element* head;
    Product_Element* tail;
};

