using namespace std;

void manager_introduction(User_List* List_User, Product_List* List_Product){
    string User_Email = get_user_information("Database/temporary_user_info.csv");
    int option = 0;
    while(option != 6){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ====================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome                 " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Inventory                    " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Money                        " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 3. Staff                        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Information                  " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Get Product                  " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Logout                       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Exit                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
        switch(option){
                case 1:system("cls");check_product_menu(List_Product, "manager");break;
                case 2:system("cls");manager_money_transaction(List_User);break;
                case 3:system("cls");manager_staff(List_User);break;
                case 4:system("cls");check_your_information(List_User, User_Email);break;
                case 5:system("cls");get_product_information_into_stock(List_Product, User_Email);break;
                case 6:system("cls");break;
                case 7:system("cls");exit(0);break;
                default:system("cls");cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}