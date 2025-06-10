using namespace std;

void customer_introduction(User_List* List_User, Product_List* List_Product){
        string User_Email = get_user_information("Database/temporary_user_info.csv");
        int option = 0;
        while(option != 7){
                display_product_table(List_Product, false);
                cout << endl;
                cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
                cout << RED  << "||" << GRAY  << " Customer welcome                                                                                         " << RED << "||" << RESET << endl;
                cout << RED  << "||" << YELLOW  << " Notes: " << GRAY << " You can select to buy. If you have problem you can go to 2. Help                                 " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 1. Select Product                                                                                        " << RED << "||" << RESET << endl; 
                cout << RED  << "||" << RESET << " 2. Help                                                                                                  " << RED << "||" << RESET << endl; 
                cout << RED  << "||" << RESET << " 3. Sort                                                                                                  " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 4. Search                                                                                                " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 5. Information                                                                                           " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 6. History                                                                                               " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 7. Logout                                                                                                " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 8. Exit                                                                                                  " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
                switch(option){
                        case 1:system("cls");select_product(List_Product);break;
                        case 2:system("cls");help(); cout << endl; break;
                        case 3:system("cls");display_product_table(List_Product, false);cout << endl;customer_check_product_sorting_menu(List_Product, false);cout << endl;break;
                        case 4:system("cls");display_product_table(List_Product, false);customer_check_product_searching(List_Product);break;
                        case 5:system("cls");check_your_information(List_User, User_Email);break;
                        case 6:system("cls");customer_check_product_history(List_Product, User_Email);break;
                        case 7:system("cls");break;
                        case 8:system("cls");exit(0);break;
                        default:system("cls");cout << RED << "Invalid option" << RESET << endl; break;
                }
        }
}

