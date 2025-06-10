#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>

#include "Color/Color.h"

#include "Component/Time.h"
#include "Component/Money.h"
#include "Component/UserInformation.h"
#include "Component/Pos_introduction.h"
#include "Component/GenerateRandomCode.h"

#include "Help/Customer.h"

#include "Src/Login.h"
#include "Src/Product.h"
#include "Src/User.h"

#include "Function/Condition.h"
#include "Function/Modification.h"

#include "Log/SignUp.h"
#include "Log/SignIn.h"
#include "Log/Login.h"

#include "Controller/Product.h"
#include "Controller/User.h"

#include "Routes/Admin.h"
#include "Routes/Cashier.h"
#include "Routes/Customer.h"
#include "Routes/Manager.h"

using namespace std;

enum ROLE{
    CUSTOMER = 1,
    CASHIER = 2,
    MANAGER = 3,
    ADMIN = 4
};

int main(){
    POS_SIGN();
    while(true){
        User_List *List_User = create_new_user_list();
        Product_List *List_Product = create_new_product_list();
        get_all_users_from_csv(List_User, "Database/user.csv");
        get_all_products_from_csv(List_Product, "Database/products.csv");
        switch(login()){
            case CUSTOMER:customer_introduction(List_User, List_Product);break;
            case CASHIER:cashier_introduction(List_User, List_Product);break;
            case MANAGER:manager_introduction(List_User, List_Product);break;
            case ADMIN:admin_introduction(List_User, List_Product);break;
        }
    }
}

