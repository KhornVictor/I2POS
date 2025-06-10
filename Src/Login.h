using namespace std;

struct Login_Element {
    string email;
    string time;
    Login_Element *next;
};

struct Login_List {
    int size;
    Login_Element *head;
    Login_Element *tail;
};