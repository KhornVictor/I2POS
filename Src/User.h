using namespace std;

struct User_Element{
    string name;
    char gender;
    int age;
    string role;
    string email;
    string password;
    string phone;
    User_Element *next;
    User_Element *previous;
};

struct User_List{
    int size;
    User_Element* head;
    User_Element* tail;
};

