
using namespace std;

// Admin Introduction ==========================================================================================================================================================>
void admin_option(){
    cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Admin welcome                   " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Check User                   " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Check Product                " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 3. Check Login                  " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 4. Check Your Information       " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 5. Logout                       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 6. Exit                         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: ";
}

void admin_introduction(User_List* List_User, Product_List* List_Product){
    string User_Email = get_user_information("Database/temporary_user_info.csv");
    cout << "Hello! Admin" << endl;
    cout << "Admin" << endl;
    int option = 0;
    system("cls");
    while (option != 5){
        admin_option(); cout << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1: system("cls");check_user_menu(List_User);break;
            case 2: system("cls");check_product_menu(List_Product, "admin");break;
            case 3: system("cls");check_user_login(List_User); break;
            case 4: system("cls");check_your_information(List_User, User_Email);break;
            case 5: system("cls"); cout << CYAN << "You have logged out successfully!" << RESET << endl; break;
            case 6: system("cls"); exit(3); break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}