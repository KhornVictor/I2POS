
using namespace std;

User_List *create_new_user_list(){
    User_List *New_User = new User_List;
    New_User -> size = 0;
    New_User -> head = NULL;
    New_User -> tail = NULL;
    return New_User;
}

void insert_user_begin(User_List *list, string name, char gender, int age, string phone, string role, string email, string password){
    User_Element *newnode = new User_Element;
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;                                                                     
    newnode -> previous = NULL;                                                                   
    newnode -> next = list -> head;                                                            
    if(list -> size == 0) list -> tail = newnode;                                                  
    else list -> head -> previous = newnode;                                                        
    list -> head = newnode;                                                                      
    list -> size++;                                                                             
}

void insert_user_end(User_List *list, string name, char gender, int age, string phone, string role, string email, string password){
    User_Element *newnode = new User_Element; 
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;                                                                    
    newnode -> next = NULL;                                                                   
    newnode -> previous = list -> tail;                                                          
    if(list -> size == 0) list -> head = newnode;                                                  
    else list -> tail -> next = newnode;                                                        
    list -> tail = newnode;                                                                      
    list -> size++;                                                                             
}

void delete_end (User_List* list) {
    if (list -> size == 0) return;                                                         
    User_Element *temporary = list -> tail;                                                      
    list -> tail = list -> tail -> previous;                                              
    if (list -> tail != NULL) list -> tail -> next = NULL;                                 
    else list -> head = NULL;                                                                     
    delete temporary;                                                                        
    list -> size--;                                                                                  
}

void delete_begin (User_List* list) {
    if (list -> size == 0) return;                                                            
    User_Element *temporary = list -> head;                                                       
    list -> head = list -> head -> next;                                                     
    if (list->head != NULL) list -> head -> previous = NULL;                                   
    else list->tail = NULL;                                                                        
    delete temporary;                                                                   
    list->size--;                                                           
}

void delete_random_variablesx_by_index(User_List* list, int index_that_have_to_delete){
    if (list -> size == 0 || index_that_have_to_delete < 0) return;
    if (index_that_have_to_delete == list -> size) delete_end(list);
    else if (index_that_have_to_delete == 1) delete_begin(list);
    else {
        User_Element *temporary = list->head;
        for (int i = 0; i < index_that_have_to_delete - 1; i++) temporary = temporary->next;
        if (temporary->previous != NULL) temporary->previous->next = temporary->next;
        else list->head = temporary->next;
        if (temporary->next != NULL) temporary->next->previous = temporary->previous;
        else list->tail = temporary->previous;
        delete temporary;
        list->size--;
    }
}

void add_user_specific(User_List *list, int position, string name, char gender, int age, string phone, string role, string email, string password){
    User_Element* newnode = new User_Element;
    newnode -> name = name;
    newnode -> gender = gender;
    newnode -> age = age;
    newnode -> phone = phone;
    newnode -> role = role;
    newnode -> email = email;
    newnode -> password = password;
    if (position == 1 || list -> size == 0) insert_user_begin(list, name, gender, age, phone, role, email, password);
    else if (position == list -> size + 1) insert_user_end(list, name, gender, age, phone, role, email, password);
    else if(position < 0 || position > list -> size) cout << "Invalid Position" << endl;
    else {
        User_Element* temporary = list->head;
        for (int i = 1; i < position - 1; i++){temporary = temporary -> next;}
        newnode -> previous = temporary;
        newnode -> next = temporary -> next; 
        if (temporary -> next != NULL) temporary -> next -> previous = newnode;
        temporary -> next = newnode;
        list -> size++;
    }
}

void get_all_users_from_csv(User_List* s, string filename) {
    ifstream file;
    file.open(filename, ios::in);
    string line;
    if (!file.is_open()) cout << RED << "Cannot open the file!" << RESET << endl;
    else {
        while (getline(file, line)) {
            stringstream ss(line);
            string name, ageStr, genderStr, phone, role, email, password;
            getline(ss, name, ',');
            getline(ss, ageStr, ',');
            getline(ss, genderStr, ',');
            getline(ss, phone, ',');
            getline(ss, role, ',');
            getline(ss, email, ',');
            getline(ss, password);

            int age = stoi(ageStr);
            char gender = genderStr[0];

            insert_user_end(s, name, gender, age, phone, role, email, password);
        }
        file.close();
    }
}

void display_user_table(User_List* list, bool clear) {
    User_Element* temporary = list->head;
    int number = 1;
    cout << GREEN << "Here are all user in this system ..." << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;

    while (temporary != NULL) {
        if (temporary -> role == "admin") cout << GREEN;
        else if (temporary -> role == "customer") cout << YELLOW;
        else if (temporary -> role == "manager") cout << RED;
        else cout << BLUE;
        cout << left
             << setw(8)  << number
             << setw(20) << temporary -> name
             << setw(6)  << temporary -> age
             << setw(8)  << temporary -> gender
             << setw(15) << temporary -> phone
             << setw(12) << temporary -> role
             << endl;
        temporary = temporary -> next;
        number++;
        cout << RESET;
    }
    cout << endl
         << GREEN  << "GREEN"  << RESET << " : admin\t"
         << RED    << "RED"    << RESET << " : manager\t"
         << BLUE   << "BLUE"   << RESET << " : cashier\t"
         << YELLOW << "YELLOW" << RESET << " : customer\t"
         << endl;
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl;system("cls");}
}

void check_user_display_role_menu (User_List* list,string role){
    User_Element* temporary = list->head;
    int number = 1;
    int count = 0;
    cout << GREEN << "Here are " << role << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;
    while (temporary != NULL) {
        if (temporary -> role == role){
            cout << left
                 << setw(8)  << number
                 << setw(20) << temporary->name
                 << setw(6)  << temporary->age
                 << setw(8)  << temporary->gender
                 << setw(15) << temporary->phone
                 << setw(12) << temporary->role
                 << endl;
            temporary = temporary -> next;
            number++;
            count++;
        }
        else temporary = temporary -> next;
    }
    if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void check_user_display_age_menu (User_List* list){
    User_Element* temporary = list->head;
    int number = 1;
    int count = 0, maximum, minimum;
    cout << "Enter age to display" << endl;
    cout << "Min : "; cin >> minimum;
    cout << "Max : "; cin >> maximum;
    system("cls");
    cout << GREEN << "Here are user of ages between ... " << minimum << " and " << maximum << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;

    while (temporary != NULL) {
        if (temporary -> age >= minimum && temporary -> age <= maximum){
            cout << left
                 << setw(8)  << number
                 << setw(20) << temporary->name
                 << setw(6)  << temporary->age
                 << setw(8)  << temporary->gender
                 << setw(15) << temporary->phone
                 << setw(12) << temporary->role
                 << endl;
            temporary = temporary -> next;
            number++;
            count++;
        }
        else temporary = temporary -> next;
    }
    if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void check_user_display_gender_menu (User_List *list){
    User_Element* temporary = list -> head;
    int number = 1;
    int count = 0;
    char gender;
    cout << "Enter the gender (M/F) : " << YELLOW; cin >> gender; cout << RESET;
    gender = toupper(gender);
    system("cls");
    if (gender == 'M' || gender == 'F'){
        cout << GREEN << "Here are " << ((gender == 'M') ? "male" : "female") << " user ..." << endl << RESET << endl;
        cout << left
             << setw(8)  << "No"
             << setw(20) << "Name"
             << setw(6)  << "Age"
             << setw(8)  << "Gender"
             << setw(15) << "Phone"
             << setw(12) << "Role"
             << endl;
        cout << string(69, '-') << endl;
    
        while (temporary != NULL) {
            if (temporary -> gender == gender){
                cout << left
                     << setw(8)  << number
                     << setw(20) << temporary->name
                     << setw(6)  << temporary->age
                     << setw(8)  << temporary->gender
                     << setw(15) << temporary->phone
                     << setw(12) << temporary->role
                     << endl;
                temporary = temporary -> next;
                number++;
                count++;
            }
            else temporary = temporary -> next;
        }
        if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
        cout << endl << GRAY; system("pause"); cout << RESET << endl;
        system("cls");
    }
    else cout << RED << "Invalid Input!" << RESET << endl;
}

void display_user_email_password(User_List* list) {
    User_Element* temp = list -> head;
    int number = 1;
    cout << GREEN << "Here are email and password of all user ... " << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(30) << "Email"
         << setw(20) << "Password"
         << endl;
    cout << string(78, '-') << endl;

    while (temp != NULL) {
        cout << left
             << setw(8)  << number
             << setw(20) << temp->name
             << setw(30) << temp->email
             << setw(20) << temp->password
             << endl;
        temp = temp->next;
        number++;
    }
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void check_user_display_menu(User_List* list){
    system("cls");
    int option = 0;
    while(option != 9){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Display        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. All                          " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Age                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Gender                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Admin                        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Manager                      " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Customer                     " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Cashier                      " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 8. Email & Password             " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 9. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");display_user_table(list, true);break;
            case 2:system("cls");check_user_display_age_menu(list);break;
            case 3:system("cls");check_user_display_gender_menu(list);break;
            case 4:system("cls");check_user_display_role_menu(list, "admin");break;
            case 5:system("cls");check_user_display_role_menu(list, "manager");break;
            case 6:system("cls");check_user_display_role_menu(list, "customer");break;
            case 7:system("cls");check_user_display_role_menu(list, "cashier");break;
            case 8:system("cls");display_user_email_password(list);break;
            case 9:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void write_all_users_to_csv(User_List* list, const string& filename) {
    ofstream file(filename, ios::out);
    if (!file.is_open()) {cout << RED << "Cannot open the file for writing!" << RESET << endl; return;}
    User_Element* temporary = list -> head;
    while (temporary != NULL) {
        file << temporary -> name << ","
             << temporary -> age << ","
             << temporary -> gender << ","
             << temporary -> phone << ","
             << temporary -> role << ","
             << temporary -> email << ","
             << temporary -> password << endl;
        temporary = temporary ->next;
    }
    file.close();
}

void check_user_modify_change_information_add_to_list(User_List *list, int select, string name, char gender, int age, string phone, string role, string email, string password){
    delete_random_variablesx_by_index(list, select);
    add_user_specific(list, select, name, gender, age, phone, role, email, password);
}

string check_user_modify_change_information_name(int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Name modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new name: " << YELLOW; getline(cin >> ws, x); cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Name's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Name's added !\n" << RESET << endl;
        if (isAllAlphabets(x)) return x;
        else {system("cls");cout << RED << "Invlid name!" << RESET << endl;continue;}
    }
}

char check_user_modify_change_information_gender(int header_condition){
    char x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Gender modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Gender: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Gender's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Gender's added !\n" << RESET << endl;
        x = toupper(x);
        if (x == 'M' || x == 'F') return x;
        else {system("cls");cout << RED << "Invlid gender!" << RESET << endl; continue;}
    }
}

int check_user_modify_change_information_age(int header_condition){
    int x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Age modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Age: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Age's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Age's added !\n" << RESET << endl;
        if (x >= 0 && x <= 100) return x;
        else {system("cls");cout << RED << "Invlid age!" << RESET << endl; continue;}
    }
}

string check_user_modify_change_information_phone(int header_condition){
    while (true){
        string x;
        if (header_condition == 1) cout << CYAN << "Phone modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Phone: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Phone's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Phone's added !\n" << RESET << endl;
        if (isAllDigits(x) && x[0] == '0' && (x.size() == 9 || x.size() == 10)) return x;
        else {system("cls");cout << RED << "Invlid Phone!" << RESET << endl; continue;}
    }
}

string check_user_modify_change_information_role(int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Role modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Role: " << YELLOW; cin >> x; cout << RESET;
        x = change_string_to_lower(x);
        system("cls");
        if (header_condition == 1) cout << GREEN << "Role's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Role's added !\n" << RESET << endl;
        if (x == "admin"   || 
            x == "manager" || 
            x == "cashier" ||
            x == "customer"
        ) return x;
        else {system("cls");cout << RED << "Invlid Role!" << RESET << endl; continue;}
    }
}

string check_user_modify_change_information_email(User_List *list ,int header_condition){
    string x;
    while (true){
        if (header_condition == 1) cout << CYAN << "Email modification ... " << RESET << endl;
        else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
        cout << "Enter new Email: " << YELLOW; cin >> x; cout << RESET;
        system("cls");
        if (header_condition == 1) cout << GREEN << "Email's changed !" << RESET << endl;
        else if (header_condition == 2) cout << GREEN << "Email's added !\n" << RESET << endl;
        if (check_validation_of_email(list, x)) continue;
        if (x.size() >= 10 && x.substr(x.size() - 10) == "@gmail.com") return x;
        else {system("cls");cout << RED << "Invlid Email!" << RESET << endl; continue;}
    }
}

string check_user_modify_change_information_password(int header_condition){
    string x;
    if (header_condition == 1) cout << CYAN << "Password modification ... " << RESET << endl;
    else if (header_condition == 2) cout << CYAN << "Adding User ... " << RESET << endl;
    cout << "Enter new Password: " << YELLOW; cin >> x; cout << RESET;
    system("cls");
    if (header_condition == 1) cout << GREEN << "Password's changed !" << RESET << endl;
    else if (header_condition == 2) cout << GREEN << "Passowrd's added !\n" << RESET << endl;
    return x;
}

void check_user_modify_add_user(User_List *list){
    string email = check_user_modify_change_information_email(list, 2);
    string password = check_user_modify_change_information_password(2);
    string name = check_user_modify_change_information_name(2);
    int age = check_user_modify_change_information_age(2);
    char gender = check_user_modify_change_information_gender(2);
    string role = check_user_modify_change_information_role(2);
    string phone = check_user_modify_change_information_phone(2);
    system("cls");
    cout << CYAN << "New User ... " << RESET << endl
         << "Name :   " << YELLOW << name << RESET << endl
         << "Gender : " << YELLOW << gender << RESET << endl
         << "Age :    " << YELLOW << age << RESET << endl
         << "Role :   " << YELLOW << role << RESET << endl
         << "Phone :  " << YELLOW << phone << RESET << endl
         << "Email :  " << YELLOW << email << RESET << endl << endl;
    cout << GRAY; system("pause"); system("cls"); cout << RESET;
    cout << GREEN << "New User added ... " << RESET << endl;
    insert_user_end(list, name, gender, age, phone, role, email, password);
    write_all_users_to_csv(list, "Database/user.csv");

}

void check_user_modify_change_information(User_List *list){
    User_Element* temporary = new User_Element;
    int option = 0;
    int select;
    while(option != 8){
        int number = 1;
        temporary = list -> head; 
        cout << GREEN << "Modification Menu ..." << endl << RESET << endl;
        cout << left
            << setw(8)  << "No"
            << setw(20) << "Name"
            << setw(6)  << "Age"
            << setw(8)  << "Gender"
            << setw(15) << "Phone"
            << setw(12) << "Role"
            << endl;
        cout << string(69, '-') << endl;

        while (temporary != NULL) {
            if (temporary -> role == "admin") cout << GREEN;
            else if (temporary -> role == "customer") cout << YELLOW;
            else if (temporary -> role == "manager") cout << RED;
            else cout << BLUE;
            cout << left
                << setw(8)  << number
                << setw(20) << temporary -> name
                << setw(6)  << temporary -> age
                << setw(8)  << temporary -> gender
                << setw(15) << temporary -> phone
                << setw(12) << temporary -> role
                << endl;
            temporary = temporary -> next;
            number++;
            cout << RESET;
        }
        cout << endl
            << GREEN  << "GREEN"  << RESET << " : admin\t"
            << RED    << "RED"    << RESET << " : manager\t"
            << BLUE   << "BLUE"   << RESET << " : cashier\t"
            << YELLOW << "YELLOW" << RESET << " : customer\t"
            << endl << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify/Change Information " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter No of user to modify                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Number: " << YELLOW; cin >> select; cout << RESET;

        if (select <= 0 || select > list -> size ) {
            system("cls");
            cout << RED << "Invalid Input" << RESET << endl;        
            continue;
        }
        
        temporary = list -> head;
        for (int i = 0; i < select - 1; i++){temporary = temporary -> next;}
        system("cls");
        cout << GREEN;
        for (char i : temporary -> name){
            if (i == ' ') break;
            else cout << i;
        }
        cout << "'s Information" << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;
        cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
        cout << "Gender: " << YELLOW << temporary -> gender << RESET << endl;
        cout << "Age: " << YELLOW << temporary -> age << RESET << endl;
        cout << "Role: " << YELLOW << temporary -> role << RESET << endl;
        cout << "Email: " << YELLOW << temporary -> email << RESET << endl;
        cout << "Phone: " << YELLOW << temporary -> phone << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify/Change Information " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter the option to modify                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 1. Name                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Gender                                  " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Age                                     " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Role                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Email                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Phone                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Password                                " << RED << "||" << RESET << endl;  
        cout << RED  << "||" << RESET << " 8. Back                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Modification option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");temporary -> name = check_user_modify_change_information_name(1);break;
            case 2:system("cls");temporary -> gender = check_user_modify_change_information_gender(1);break;
            case 3:system("cls");temporary -> age = check_user_modify_change_information_age(1);break;
            case 4:system("cls");temporary -> role = check_user_modify_change_information_role(1);break;
            case 5:system("cls");temporary -> email = check_user_modify_change_information_email(list, 1);break;
            case 6:system("cls");temporary -> phone = check_user_modify_change_information_phone(1);break;
            case 7:system("cls");temporary -> password = check_user_modify_change_information_password(1);break;
            case 8:system("cls");break;
        }
        check_user_modify_change_information_add_to_list(list, select, temporary -> name, temporary -> gender, temporary -> age, temporary -> phone, temporary -> role, temporary -> email, temporary -> password);
        char check_if_want_to_write = 'A';
        while (check_if_want_to_write != 'N' && check_if_want_to_write != 'Y') {
            cout << "Do you want to modify something else? [Y(es)/N(o)] => "; cin >> check_if_want_to_write;
            check_if_want_to_write = toupper(check_if_want_to_write);
            switch (check_if_want_to_write){
                case 'Y':system("cls");cout << GREEN << "Information changed!!!" << RESET << endl << YELLOW << "Note: " << RESET << "It hasn't pushed to database yet." << endl;break;
                case 'N':system("cls");write_all_users_to_csv(list, "Database/user.csv");break;
                default :system("cls");cout << RED << "Invalid input" << RESET << endl;
            }
        }  
    }
}

void check_user_modify_menu(User_List *list){
    User_Element* temporary = list->head;
    int number = 1;
    int option = 0;
    while(option != 3){
        cout << CYAN << "Modification Menu ..." << endl << RESET << endl;
        cout << left
            << setw(8)  << "No"
            << setw(20) << "Name"
            << setw(6)  << "Age"
            << setw(8)  << "Gender"
            << setw(15) << "Phone"
            << setw(12) << "Role"
            << endl;
        cout << string(69, '-') << endl;

        while (temporary != NULL) {
            if (temporary -> role == "admin") cout << GREEN;
            else if (temporary -> role == "customer") cout << YELLOW;
            else if (temporary -> role == "manager") cout << RED;
            else cout << BLUE;
            cout << left
                << setw(8)  << number
                << setw(20) << temporary -> name
                << setw(6)  << temporary -> age
                << setw(8)  << temporary -> gender
                << setw(15) << temporary -> phone
                << setw(12) << temporary -> role
                << endl;
            temporary = temporary -> next;
            number++;
            cout << RESET;
        }
        cout << endl
            << GREEN  << "GREEN"  << RESET << " : admin\t"
            << RED    << "RED"    << RESET << " : manager\t"
            << BLUE   << "BLUE"   << RESET << " : cashier\t"
            << YELLOW << "YELLOW" << RESET << " : customer\t"
            << endl << endl;

        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User/Modify         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Add User                     " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Change information           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");check_user_modify_add_user(list);break;
            case 2:system("cls");check_user_modify_change_information(list);break;
            case 3:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void check_user_search_display_email_only(User_List* list) {
    User_Element* temp = list->head;
    int number = 1;
    cout << left << setw(8) << "No" << setw(30) << "Email" << endl;
    cout << GRAY << string(38, '-') << RESET << endl;
    while (temp != NULL) {
        cout << left << setw(8) << number << YELLOW << setw(30)  << temp->email << RESET << endl;
        temp = temp->next;
        number++;
    } cout << GRAY << string(38, '-') << RESET << endl;
}

void check_user_search_menu(User_List *list){
    string email;
    bool check = false;
    User_Element *temporary = list -> head;
    check_user_search_display_email_only(list);
    cout << endl;
    cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Admin/Check User/Search         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Email for Search          " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Email: " << YELLOW; getline(cin >> ws, email); cout << RESET; system("cls");
    while(temporary != NULL){
        if (temporary -> email == email){
            cout << GREEN;
            for (char i : temporary -> name){
                if (i == ' ') break;
                else cout << i;
            }
            cout << "'s Information" << RESET << endl;
            cout << GRAY << string(50, '-') << RESET << endl;
            cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
            cout << "Gender: " << YELLOW << temporary -> gender << RESET << endl;
            cout << "Age: " << YELLOW << temporary -> age << RESET << endl;
            cout << "Role: " << YELLOW << temporary -> role << RESET << endl;
            cout << "Email: " << YELLOW << temporary -> email << RESET << endl;
            cout << "Phone: " << YELLOW << temporary -> phone << RESET << endl;
            cout << GRAY << string(50, '-') << RESET << endl;
            check = true;
            break;
        }
        temporary = temporary -> next;
    }
    if (!check) cout << RED << "Email not found!" << RESET << endl;
    cout << endl << GRAY; system("pause"); system("cls"); cout << RESET;
}

void check_user_menu(User_List* list){
    system("cls");
    int option = 0;
    while(option != 4){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check User                " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Display                      " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Modify                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Search                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");check_user_display_menu(list);break;
            case 2:system("cls");check_user_modify_menu(list);break;
            case 3:system("cls");check_user_search_menu(list);break;
            case 4:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void exit(int time){
    for (int i = time; i > 0; i--){
        system("cls");
        cout << "The system will shut down in " << MAGENTA << i << RESET << ((i <= 1) ? " second" : " seconds");
        Sleep(1000);
    }
    system("cls");
    cout << "Goodbye! Have a nice day!\n" << endl;
    cout << GRAY; system("pause"); cout << RESET;
    system("cls");
    exit(0);
}

Login_List *create_new_login_list() {
    Login_List *newList = new Login_List;
    newList->size = 0;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

void insert_login(Login_List *list, string email, string time) {
    Login_Element *newnode = new Login_Element;
    newnode->email = email;
    newnode->time = time;
    newnode->next = NULL;

    if (list->size == 0) {
        list->head = newnode;
        list->tail = newnode;
    } else {
        list->tail->next = newnode;
        list->tail = newnode;
    }
    list->size++;
}

void display_logins(Login_List *list) {
    if (list->size == 0) {
        cout << "No login records found." << endl;
        return;
    }
    Login_Element *current = list->head;
    while (current != NULL) {
        cout << "Email: " << current->email << ", Time: " << current->time << endl;
        current = current->next;
    }
}

void delete_login_list(Login_List *list) {
    Login_Element *current = list->head;
    while (current != NULL) {
        Login_Element *temp = current;
        current = current->next;
        delete temp;
    }
    delete list;
}

void get_all_sign_in_from_csv(Login_List *list, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string email, time;
        if (getline(ss, email, ',') && getline(ss, time, ',')) {
            insert_login(list, email, time);
        }
    }
    file.close();
}

void get_all_sign_up_from_csv(Login_List *list, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, time;
        if (getline(ss, email, ',') && getline(ss, time, ',')) {
            insert_login(list, email, time);
        }
    }
    file.close();
}

void check_user_login_check_sign_in(Login_List* SignInList, User_List* user_list) {
    if (SignInList -> size == 0) {
        cout << RED << "No user record found!" << RESET << endl;
        return;
    }
    cout << GREEN << "Signed-In Users:" << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(30) << "Email"
         << setw(20) << "Time"
         << setw(12) << "Role"
         << endl;
    cout << GRAY << string(90, '-') << RESET << endl;
    User_Element* temporary_user = user_list->head;
    int number = 1;
    while (temporary_user != NULL) {
        Login_Element* temporary_sign_in = SignInList->head;
        while (temporary_sign_in != NULL) {
            if (temporary_sign_in->email == temporary_user->email) {
                cout << left
                     << setw(8)  << number
                     << setw(20) << temporary_user->name
                     << setw(30) << temporary_user->email
                     << setw(20) << temporary_sign_in->time;
                if (temporary_user->role == "admin") cout << GREEN;
                else if (temporary_user->role == "manager") cout << RED;
                else if (temporary_user->role == "cashier") cout << BLUE;
                else cout << YELLOW;
                cout << setw(12) << temporary_user->role << RESET << endl;
                number++;
            }
            temporary_sign_in = temporary_sign_in->next;
        }
        temporary_user = temporary_user->next;
    }
    if (number == 1) cout << YELLOW << "No signed-in users found!" << RESET << endl;
    else {
        cout << endl
             << GREEN  << "GREEN"  << RESET << " : admin\t"
             << RED    << "RED"    << RESET << " : manager\t"
             << BLUE   << "BLUE"   << RESET << " : cashier\t"
             << YELLOW << "YELLOW" << RESET << " : customer\t"
             << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void check_user_login_check_sign_up(Login_List* SignUpList, User_List* user_list) {
    if (SignUpList -> size == 0) {
        cout << RED << "No user record found!" << RESET << endl;
        return;
    }
    cout << GREEN << "Signed-Up Users:" << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(30) << "Email"
         << setw(20) << "Time"
         << setw(12) << "Role"
         << endl;
    cout << GRAY << string(90, '-') << RESET << endl;
    User_Element* temporary_user = user_list->head;
    int number = 1;
    while (temporary_user != NULL) {
        Login_Element* temporary_sign_up = SignUpList->head;
        while (temporary_sign_up != NULL) {
            if (temporary_sign_up -> email == temporary_user -> email) {
                cout << left
                     << setw(8)  << number
                     << setw(20) << temporary_user->name
                     << setw(30) << temporary_user->email
                     << setw(20) << temporary_sign_up->time
                     << setw(12) << temporary_user->role
                     << endl;
                number++;
            }
            temporary_sign_up = temporary_sign_up -> next;
        }
        temporary_user = temporary_user -> next;
    }
    if (number == 1) cout << YELLOW << "No signed-up users found!" << RESET << endl;
    else {
        cout << endl
             << GREEN  << "GREEN"  << RESET << " : admin\t"
             << RED    << "RED"    << RESET << " : manager\t"
             << BLUE   << "BLUE"   << RESET << " : cashier\t"
             << YELLOW << "YELLOW" << RESET << " : customer\t"
             << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void check_user_login(User_List* list) {
    int option;
    Login_List* SignInList = create_new_login_list();
    Login_List* SignUpList = create_new_login_list();
    get_all_sign_up_from_csv(SignUpList, "Database/Admin/SignUp.csv");
    get_all_sign_in_from_csv(SignInList, "Database/Admin/SignIn.csv");
    cout << string('-', 50) << endl;
    system("cls");
    do{
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Check User Sign in           " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Check User Sign up           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");check_user_login_check_sign_in(SignInList, list);break;
            case 2:system("cls");check_user_login_check_sign_up(SignUpList, list);break;
            case 3:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    } while (option != 3);
    delete_login_list(SignInList);
    delete_login_list(SignUpList);
}

void check_user_information_modify_change_information(User_List *list, string email){
    User_Element* temporary = new User_Element;
    int option = 0;
    temporary = list -> head;
    int select = 0;
    while (temporary != NULL) {
        select++;
        if (temporary -> email == email) {
            break;
        }
        temporary = temporary -> next;
    }
    while(option != 7){
        cout << "'s Information" << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;
        cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
        cout << "Gender: " << YELLOW << temporary -> gender << RESET << endl;
        cout << "Age: " << YELLOW << temporary -> age << RESET << endl;
        cout << "Role: " << YELLOW << temporary -> role << RESET << endl;
        cout << "Email: " << YELLOW << temporary -> email << RESET << endl;
        cout << "Phone: " << YELLOW << temporary -> phone << RESET << endl;
        cout << GRAY << string(50, '-') << RESET << endl;

        if (temporary -> role == "admin") cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================>" << RESET << endl;
        else if (temporary -> role == "manager") cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ==============================>" << RESET << endl;
        else if (temporary -> role == "cashier") cout << CYAN << "<===== " << GREEN << "Cashier" << CYAN << " ==============================>" << RESET << endl;
        else cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ============================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Modification                               " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter the option to modify                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 1. Name                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Gender                                  " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Age                                     " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Email                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Phone                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Password                                " << RED << "||" << RESET << endl;  
        cout << RED  << "||" << RESET << " 7. Back                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Modification option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");temporary -> name = check_user_modify_change_information_name(1);break;
            case 2:system("cls");temporary -> gender = check_user_modify_change_information_gender(1);break;
            case 3:system("cls");temporary -> age = check_user_modify_change_information_age(1);break;
            case 4:system("cls");temporary -> email = check_user_modify_change_information_email(list, 1);break;
            case 5:system("cls");temporary -> phone = check_user_modify_change_information_phone(1);break;
            case 6:system("cls");temporary -> password = check_user_modify_change_information_password(1);break;
            case 7:system("cls");break;
        }
        check_user_modify_change_information_add_to_list(list, select, temporary -> name, temporary -> gender, temporary -> age, temporary -> phone, temporary -> role, temporary -> email, temporary -> password);
        char check_if_want_to_write = 'A';
        while (check_if_want_to_write != 'N' && check_if_want_to_write != 'Y') {
            cout << "Do you want to modify something else? [Y(es)/N(o)] => "; cin >> check_if_want_to_write;
            check_if_want_to_write = toupper(check_if_want_to_write);
            switch (check_if_want_to_write){
                case 'Y':system("cls");cout << GREEN << "Information changed!!!" << RESET << endl << YELLOW << "Note: " << RESET << "It hasn't pushed to database yet." << endl;break;
                case 'N':system("cls");write_all_users_to_csv(list, "Database/user.csv"); option = 7;break;
                default :system("cls");cout << RED << "Invalid input" << RESET << endl;
            }
        }  
    }
}

void check_your_information(User_List* list, string email) {
    int option = 0;
    while (option != 2) {
        User_Element* temporary = list->head;
        while (temporary != NULL) {
            if (temporary -> email == email) {
                cout << GREEN;
                cout << "Information" << RESET << endl;
                cout << GRAY << string(50, '-') << RESET << endl;
                cout << "Name: " << YELLOW << temporary->name << RESET << endl;
                cout << "Age: " << YELLOW << temporary->age << RESET << endl;
                cout << "Gender: " << YELLOW << temporary->gender << RESET << endl;
                cout << "Email: " << YELLOW << temporary->email << RESET << endl;
                cout << "Role: " << YELLOW << temporary->role << RESET << endl;
                cout << "Phone: " << YELLOW << temporary->phone << RESET << endl;
                break;
            }
            temporary = temporary->next;
        }
        cout << GRAY << string(50, '-') << RESET << endl;
        if (temporary -> role == "admin") cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
        else if (temporary -> role == "manager") cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " =======================>" << RESET << endl;
        else if (temporary -> role == "cashier") cout << CYAN << "<===== " << GREEN << "Cashier" << CYAN << " =======================>" << RESET << endl;
        else cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =======================>" << RESET << endl;

        cout << RED  << "||" << GRAY  << " Modification                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Edit Information             " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");check_user_information_modify_change_information(list, email);break;
            case 2:system("cls");break;
            default:system("cls");cout << RED << "Invalid Input" << RESET << endl;break;
        }
    }
}

void Record_Attendent(string email, User_List* list) {
    string Pin = generatePinCode();
    ofstream Attendend_Code;
    Attendend_Code.open("Database/Cashier/AttendentCode.txt", ios::out);
    Attendend_Code << Pin;
    Attendend_Code.close();
    string input_pin;
    cout << CYAN << "<===== " << GREEN << "Cashier" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Modification                    " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Please enter attendent PIN code:" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> input_pin; cout << RESET;
    system("cls");
    if (input_pin == Pin){
        cout << GREEN << "PIN code is correct!" << RESET << endl;

        ofstream Attendent;
        Attendent.open("Database/Cashier/Attendent.csv", ios::app);
        Attendent << Pin << "," << email << "," << current_time() << endl;
        Attendent.close();

        ofstream Temporary_Cashier;
        Temporary_Cashier.open("Database/Cashier/Temporary_cashier.txt", ios::out);
        Temporary_Cashier << email;
        Temporary_Cashier.close();

        cout << GREEN << "Attendance recorded successfully!" << RESET << endl;  
        User_Element* temporary = list->head;
        while (temporary != NULL) {
            if (temporary->email == email) {
                cout << "Name:  " << YELLOW << temporary->name << RESET << endl;
                cout << "Email: " << YELLOW << temporary->email << RESET << endl;
                cout << "Time:  " << YELLOW << current_time() << RESET << endl;
                break;
            }
            temporary = temporary->next;
        } 
    } 
    else cout << RED  <<"PIN code is incorrect!"<<RESET<<endl;
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void Customer_Show_attendent(string email){
    ifstream Attendent("Database/Cashier/Attendent.csv");
    if (!Attendent.is_open()) {
        cout << RED << "Error opening attendent file!" << RESET << endl;
        return;
    }
    string line;
    bool found = false;
    cout << string(42, '-') << endl;
    cout << YELLOW;
    cout << left << setw(20) << "PIN Code" 
         << left << setw(20) << "Time of Attendance" 
         << endl << RESET;
    cout << string(42, '-') << endl;
    while (getline(Attendent, line)) {
        stringstream ss(line);
        string pin, attendent_email, time;
        getline(ss, pin, ',');
        getline(ss, attendent_email, ',');
        getline(ss, time, ',');
        if (attendent_email == email) {
            found = true;
            cout << left << setw(20) << pin 
                 << left << setw(20) << time 
                 << endl;
        }
    }
    cout << string(42, '-') << endl;
    if (!found) cout << RED << "No attendance record found for this email!" << RESET << endl;
    Attendent.close();
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void cashier_show_customers(string email, User_List* list) {
    ifstream record_income;
    record_income.open("Database/Customer/Customer_transaction.csv");
    if (!record_income.is_open()) cout << RED << "Can't open Database/Customer/Customer_transaction.csv" << RESET << endl;
    else {
        string line;
        double total_income = 0;
        cout << YELLOW;
        cout << string(50, '-') << endl;
        cout << left
             << setw(8)  << "No"
             << setw(20) << "Customer Name"
             << setw(20) << "Date" << endl;
        cout << string(50, '-') << endl;
        cout << RESET;
        int count = 1;
        while (getline(record_income, line)) {
            stringstream ss(line);
            string customer_name, total_price, date, cashier_name;
            getline(ss, customer_name, ',');
            getline(ss, total_price, ',');
            getline(ss, date, ',');
            getline(ss, cashier_name, ',');
            if (cashier_name == email){
                User_Element* temporary = list->head;
                while (temporary != NULL) {
                    if (temporary->email == customer_name) {
                        customer_name = temporary->name;
                        cout << left 
                             << setw(8) << count 
                             << setw(20) << customer_name
                             << setw(20) << date << endl;
                        break;
                    }
                    temporary = temporary->next;
                }
                count++;    
            }
        }
        record_income.close();
        cout << string(50, '-') << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void manager_money_transaction_view_transaction_history(User_List* list, bool income, bool outcome){
    ifstream record_income;
    record_income.open("Database/Manager/Money_transaction.csv");
    if (!record_income.is_open()) cout << RED << "Can't open Database/Manager/Money_transaction.csv" << RESET << endl;
    else {
        string line;
        bool income_found = false, outcome_found = false;
        double total_income = 0;
        cout << string(100, '-') << endl;
        cout << left
                 << setw(10) << "status" << RESET
                 << setw(20) << "date"
                 << setw(20) << "time"
                 << setw(10) << "amount"
                 << setw(20) << "Cashier Name"
                 << setw(20) << "Customer Name" << endl; 
        cout << string(100, '-') << endl;
        getline(record_income, line);
        while (getline(record_income, line)) {
            stringstream ss(line);
            string status, date, time, amount, cashier_email, customer_email;
            getline(ss, status, ',');
            getline(ss, customer_email, ',');
            getline(ss, amount, ',');
            getline(ss, date, ' ');
            getline(ss, time, ',');
            getline(ss, cashier_email);
            if (status == "[+]" && income) {
                cout << GREEN;
                income_found = true;
                total_income += stod(amount);
                cout << left
                     << setw(10) << status
                     << setw(20) << date
                     << setw(20) << time
                     << setw(10) << amount + " $";
                User_Element* temporary = list->head;
                while (temporary != NULL) {
                    if (temporary->email == cashier_email) {
                        cout << left << setw(20) << temporary->name;
                        break;
                    }
                    temporary = temporary->next;
                }
                temporary = list -> head;
                while (temporary != NULL) {
                    if (temporary->email == customer_email) {
                        cout << left << setw(20) << temporary->name;
                        break;
                    }
                    temporary = temporary->next;
                }
                cout << RESET << endl;
            }
            else if (status == "[-]" && outcome) {
                cout << RED;
                outcome_found = true;
                total_income -= stod(amount);
                cout << left
                     << setw(10) << status
                     << setw(20) << date
                     << setw(20) << time
                     << setw(10) << amount + " $";
                User_Element* temporary = list->head;
                while (temporary != NULL) {
                    if (temporary->email == cashier_email) {
                        cout << left << setw(20) << temporary->name;
                        break;
                    }
                    temporary = temporary->next;
                }
                cout << left << setw(20) << "Buy: " + customer_email << RESET << endl;
            }
        }
        record_income.close();
        if (!income_found && income) cout << RED << "No income transaction found!" << RESET << endl;
        if (!outcome_found && outcome) cout << RED << "No outcome transaction found!" << RESET << endl;
        if (!income_found && !outcome_found && income && outcome) cout << RED << "No transaction found!" << RESET << endl;
        cout << string(100, '-') << endl;
        cout << "Total Transaction Amount: " << GREEN << total_income << " $" << RESET << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void manager_total_money(){
    double total_money = Manager_Money();
    cout << CYAN << "<===== " << GREEN << "Manager Money" << CYAN << " ====================>" << RESET << endl;
    cout << "Total Money: " << GREEN << total_money << " $" << RESET << endl;
    cout << string(100, '-') << endl;
    cout << "Note: This is the total money in the system, including all transactions." << RESET << endl;
    cout << string(100, '-') << endl;
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void manager_money_transaction(User_List* list){
    int option = 0;
    while (option != 5) {
        cout << CYAN << "<===== " << GREEN << "Manager Money" << CYAN << " ====================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Money/Transaction            " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Balance                           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. View Transaction History          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Income                            " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Outcome                           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Back                              " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch(option){
            case 1: system("cls"); manager_total_money(); break;
            case 2: system("cls"); manager_money_transaction_view_transaction_history(list, true, true); break;
            case 3: system("cls"); manager_money_transaction_view_transaction_history(list, true, false); break;
            case 4: system("cls"); manager_money_transaction_view_transaction_history(list, false, true); break;
            case 5: system("cls"); break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void manager_money_menu(User_List* list){
    int option = 0;
    do{
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ====================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Money                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Total Money                  " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Money Transaction            " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
        switch(option){
                case 1:system("cls");manager_total_money();break;
                case 2:system("cls");manager_money_transaction(list);break;
                default:system("cls");cout << RED << "Invalid option" << RESET << endl; break;
        }
    } while (option != 3);
    
}

void manager_staff_cashier(User_List* list, string role) {
    User_Element* temporary = list->head;
    int number = 1;
    int count = 0;
    cout << GREEN << "Here are " << role << endl << RESET << endl;
    cout << left
         << setw(8)  << "No"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(8)  << "Gender"
         << setw(15) << "Phone"
         << setw(12) << "Role"
         << endl;
    cout << string(69, '-') << endl;
    while (temporary != NULL) {
        if (temporary -> role == role){
            cout << left
                 << setw(8)  << number
                 << setw(20) << temporary->name
                 << setw(6)  << temporary->age
                 << setw(8)  << temporary->gender
                 << setw(15) << temporary->phone
                 << setw(12) << temporary->role
                 << endl;
            temporary = temporary -> next;
            number++;
            count++;
        }
        else temporary = temporary -> next;
    }
    if (count == 0) {system("cls"); cout << YELLOW << "List Empty! :)" RESET;}
    cout << endl << GRAY; system("pause"); cout << RESET << endl;
    system("cls");
}

void manager_staff_attendent(User_List* list, string role){
    ifstream Attendent;
    Attendent.open("Database/Cashier/Attendent.csv");
    if (!Attendent.is_open())cout << RED << "Error opening attendent file!" << RESET << endl;
    else {
        string line;
        int number = 1;
        cout << GREEN << "Here are attendents of " << role << endl << RESET << endl;
        cout << YELLOW << left
             << setw(8)  << "No"
             << setw(20) << "PIN Code"
             << setw(30) << "Email"
             << setw(20) << "Time of Attendance"
             << endl << RESET;
        cout << string(80, '-') << endl;
        getline(Attendent, line);
        while (getline(Attendent, line)) {
            stringstream ss(line);
            string pin_code, email, time;
            getline(ss, pin_code, ',');
            getline(ss, email, ',');
            getline(ss, time);
            User_Element* temporary = list->head;
            while (temporary != NULL) {
                if (temporary->email == email && temporary->role == role) {
                    cout << left
                         << setw(8)  << number
                         << setw(20) << pin_code
                         << setw(30) << temporary->name
                         << setw(20) << time
                         << endl;
                    number++;
                    break;
                }
                temporary = temporary->next;
            }
        }
        Attendent.close();
        if (number == 1) cout << YELLOW << "List Empty! :)" RESET;
        cout << endl;
    }

}

void manager_staff (User_List* list) {
    int option = 0;
    while (option != 3) {
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ====================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Staff                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Cashier                      " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Attendent                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED  <<"||"<<RESET<<endl;
        cout<<RED<<"||"<<RESET<<" Enter option: "<<YELLOW;cin>>option;cout<<RESET;
        switch(option){
            case 1:system("cls");manager_staff_cashier(list, "cashier");break;
            case 2:system("cls");manager_staff_attendent(list, "cashier");break;
            case 3:system("cls");break;
            default:system("cls");cout<<RED<<"Invalid option"<<RESET<<endl;break;
        }
    }
}