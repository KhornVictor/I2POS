
using namespace std;


void cashier_option(){
    cout << CYAN << "<===== " << GREEN << "Cashier" << CYAN << " =====================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Cashier welcome                 " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Show Information             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Record Attendent             " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 3. Show Attendent               " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 4. Show income                  " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 5. Show Customers               " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 6. Logout                       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 7. Exit                         " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: ";
}

void cashier_introduction(User_List* List_User, Product_List* List_Product){
    string User_Email = get_user_information("Database/temporary_user_info.csv");
    cout << "Hello! Admin" << endl;
    cout << "Admin" << endl;
    int option = 0;
    system("cls");
    while (option != 6){
        cashier_option(); cout << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1: system("cls"); check_your_information(List_User, User_Email);break;
            case 2: system("cls"); Record_Attendent(User_Email, List_User);break;
            case 3: system("cls"); Customer_Show_attendent(User_Email); break;
            case 4: system("cls"); cashier_record_income(User_Email);break;
            case 5: system("cls"); cashier_show_customers(User_Email, List_User); break;
            case 6: system("cls"); cout << CYAN << "You have logged out successfully!" << RESET << endl; break;
            case 7: system("cls"); exit(3); break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}
