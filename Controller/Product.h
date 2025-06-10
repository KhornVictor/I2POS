using namespace std;

Product_List *create_new_product_list(){
    Product_List *New_Product_List = new Product_List;
    New_Product_List -> size = 0;
    New_Product_List -> head = NULL;
    New_Product_List -> tail = NULL;
    return New_Product_List;
}

string Capitalization(string index){
    string capitalization;
    bool condition = true;
    for (char i : index){
        if (condition) {capitalization += toupper(i); condition = false;}
        else if (i == ' ') {capitalization += i; condition = true;}
        else capitalization += i;
    }
    return capitalization;
}

void insert_product_begin(Product_List *list, string id, string name,string category, string brand, double price, string unit, int stock){
    Product_Element *newnode = new Product_Element; 
    newnode -> id = id;
    newnode -> name = name;
    newnode -> category = category;
    newnode -> brand = brand;
    newnode -> price = price;   
    newnode -> unit = unit;
    newnode -> stock = stock;                                                              
    newnode -> previous = NULL;                                                                   
    newnode -> next = list -> head;                                                            
    if(list -> size == 0) list -> tail = newnode;                                                  
    else list -> head -> previous = newnode;                                                        
    list -> head = newnode;                                                                      
    list -> size++;                                                                             
}

void insert_product_end(Product_List *list, string id, string name, string category, string brand, double price, string unit, int stock) {
    Product_Element *newnode = new Product_Element;
    newnode->id = id;
    newnode->name = name;
    newnode->category = category;
    newnode->brand = brand;
    newnode->price = price;
    newnode->unit = unit;
    newnode->stock = stock;
    newnode->next = NULL;
    newnode->previous = list->tail;
    if (list->size == 0)
        list->head = newnode;
    else
        list->tail->next = newnode;
    list->tail = newnode;
    list->size++;
}

void add_product_specific(Product_List *list, int position, string id, string name,string category, string brand, double price, string unit, int stock){
    Product_Element* newnode = new Product_Element;
    newnode -> id = id;
    newnode -> name = name;
    newnode -> category = category;
    newnode -> brand = brand;
    newnode -> price = price;   
    newnode -> unit = unit;
    newnode -> stock = stock;    
    if (position == 1 || list -> size == 0) insert_product_begin(list, id, name, category, brand, price, unit, stock);
    else if (position == list -> size + 1) insert_product_end(list, id, name, category, brand, price, unit, stock); 
    else if(position < 0 || position > list -> size) cout << "Invalid Position" << endl;
    else {
        Product_Element* temporary = list->head;
        for (int i = 1; i < position - 1; i++){temporary = temporary -> next;}
        newnode -> previous = temporary;
        newnode -> next = temporary -> next; 
        if (temporary -> next != NULL) temporary -> next -> previous = newnode;
        temporary -> next = newnode;
        list -> size++;
    }
}

void delete_end2(Product_List* list) {
    if (list -> size == 0) return;                                                         
    Product_Element *temporary = list -> tail;                                                      
    list -> tail = list -> tail -> previous;                                              
    if (list -> tail != NULL) list -> tail -> next = NULL;                                 
    else list -> head = NULL;                                                                     
    delete temporary;                                                                        
    list -> size--;                                                                                  
}

void delete_begin2 (Product_List* list) {
    if (list -> size == 0) return;                                                            
    Product_Element *temporary = list -> head;                                                       
    list -> head = list -> head -> next;                                                     
    if (list->head != NULL) list -> head -> previous = NULL;                                   
    else list->tail = NULL;                                                                        
    delete temporary;                                                                   
    list->size--;                                                           
}

void delete_random_variablesx_by_index2(Product_List* list, int index_that_have_to_delete){
    if (list -> size == 0 || index_that_have_to_delete < 0) return;
    if (index_that_have_to_delete == list -> size) delete_end2(list);
    else if (index_that_have_to_delete == 1) delete_begin2(list);
    else {
        Product_Element *temporary = list->head;
        for (int i = 0; i < index_that_have_to_delete - 1; i++) temporary = temporary->next;
        if (temporary->previous != NULL) temporary->previous->next = temporary->next;
        else list->head = temporary->next;
        if (temporary->next != NULL) temporary->next->previous = temporary->previous;
        else list->tail = temporary->previous;
        delete temporary;                                                            
        list->size--;                                                                  
    }
}

void delete_all_products(Product_List* list) {
    while (list->size > 0) {
        delete_begin2(list);
    }
}

void get_all_products_from_csv(Product_List* list, const string filename) {
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cout << RED << "Cannot open the product file!" << RESET << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, category, brand, priceStr, unit, stockStr;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, brand, ',');
        getline(ss, priceStr, ',');
        getline(ss, unit, ',');
        getline(ss, stockStr);
        double price = stod(priceStr);
        int stock = stoi(stockStr);
        insert_product_end(list, id, name, category, brand, price, unit, stock);

    }
    file.close();
}

void display_product_table(Product_List* list, bool clear) {
    Product_Element* temp = list->head;
    cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
    cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    while (temp != NULL) {                  
        cout << "| "
             << RED     << setw(8)  << left << temp->id        << RESET << " | "
             << GREEN   << setw(28) << left << temp->name      << RESET << " | "
             << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
             << BLUE    << setw(20) << left << temp->category  << RESET << " | "
             << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
             << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
             << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
        temp = temp->next;
    }
    cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

Product_List* copy_product_list(Product_List* original_list) {
    Product_List* copied_list = create_new_product_list();
    Product_Element* temp = original_list -> head;
    while (temp != NULL) {
        insert_product_end(copied_list, temp -> id, temp -> name, temp -> category, temp -> brand, temp -> price, temp -> unit, temp -> stock);
        temp = temp -> next;
    }
    return copied_list;
}

void sort_product_by_price(Product_List* list, bool descending) {
    if (list->size <= 1) return;
    bool swapped;
    do {
        swapped = false;
        Product_Element* current = list->head;
        while (current != NULL && current->next != NULL) {
            if ((descending && current->price < current->next->price) || 
                (!descending && current->price > current->next->price)) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->category, current->next->category);
                swap(current->brand, current->next->brand);
                swap(current->price, current->next->price);
                swap(current->unit, current->next->unit);
                swap(current->stock, current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_and_display_product_by_price(Product_List* original_list, bool descending, bool clear) {

    Product_List* copied_list = copy_product_list(original_list);

    sort_product_by_price(copied_list, descending);
    display_product_table(copied_list, clear);

    while (copied_list->size > 0) {
        delete_begin2(copied_list);
    }
    delete copied_list;
}

void check_product_sorting_price(Product_List *original_list, bool clear, string role){
    int option;
    Product_List* copied_list = copy_product_list(original_list);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Price          " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Price        " << RED << "||" << RESET << endl;
    }   
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                              " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 2. Ascending                               " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: "; cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_price(original_list, descending, clear);
}

void sort_product_by_name(Product_List* list, bool descending) {
    if (list->size <= 1) return;
    bool swapped;
    do {
        swapped = false;
        Product_Element* current = list->head;
        while (current != NULL && current->next != NULL) {
            if ((descending && current->name < current->next->name) || 
                (!descending && current->name > current->next->name)) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->category, current->next->category);
                swap(current->brand, current->next->brand);
                swap(current->price, current->next->price);
                swap(current->unit, current->next->unit);
                swap(current->stock, current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_and_display_product_by_name(Product_List* original_list, bool descending, bool clear) {
    Product_List* copied_list = copy_product_list(original_list);
    sort_product_by_name(copied_list, descending);
    display_product_table(copied_list, clear);
    while (copied_list->size > 0) {
        delete_begin2(copied_list);
    }
    delete copied_list;
}

void check_product_sorting_name(Product_List *original_list, bool clear, string role){
    int option;
    Product_List* copied_list = copy_product_list(original_list);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Name           " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Name         " << RED << "||" << RESET << endl;
    }  
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                              " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 2. Ascending                               " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: "; cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:break;
    }
    sort_and_display_product_by_name(original_list, descending, clear);
}

void sort_product_by_stock(Product_List* list, bool descending) {
    if (list->size <= 1) return;
    bool swapped;
    do {
        swapped = false;
        Product_Element* current = list->head;
        while (current != NULL && current->next != NULL) {
            if ((descending && current->stock < current->next->stock) || 
                (!descending && current->stock > current->next->stock)) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->category, current->next->category);
                swap(current->brand, current->next->brand);
                swap(current->price, current->next->price);
                swap(current->unit, current->next->unit);
                swap(current->stock, current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_and_display_product_by_stock(Product_List* original_list, bool descending, bool clear) {
    Product_List* copied_list = copy_product_list(original_list);
    sort_product_by_stock(copied_list, descending);
    display_product_table(copied_list, clear);
    while (copied_list->size > 0) {
        delete_begin2(copied_list);
    }
    delete copied_list;
}

void check_product_sorting_stock(Product_List *original_list, bool clear, string role){
    int option;
    Product_List* copied_list = copy_product_list(original_list);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Stock          " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Stock        " << RED << "||" << RESET << endl;
    }  
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                              " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 2. Ascending                               " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: "; cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_stock(original_list, descending, clear);
}

void sort_product_by_category(Product_List* list, bool descending) {
    if (list->size <= 1) return;
    bool swapped;
    do {
        swapped = false;
        Product_Element* current = list->head;
        while (current != NULL && current->next != NULL) {
            if ((descending && current->category < current->next->category) || 
                (!descending && current->category > current->next->category)) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->category, current->next->category);
                swap(current->brand, current->next->brand);
                swap(current->price, current->next->price);
                swap(current->unit, current->next->unit);
                swap(current->stock, current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_and_display_product_by_category(Product_List* original_list, bool descending, bool clear) {
    Product_List* copied_list = copy_product_list(original_list);
    sort_product_by_category(copied_list, descending);
    display_product_table(copied_list, clear);
    while (copied_list->size > 0) {
        delete_begin2(copied_list);
    }
    delete copied_list;
}

void check_product_sorting_category(Product_List *original_list, bool clear, string  role){
    int option;
    Product_List* copied_list = copy_product_list(original_list);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =====================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Category          " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ===================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Category        " << RED << "||" << RESET << endl;
    }  
    cout << RED  << "||" << RESET << "-----------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                 " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 2. Ascending                                  " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "===============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: "; cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_category(original_list, descending, clear);
}

void sort_product_by_brand(Product_List* list, bool descending) {
    if (list->size <= 1) return;
    bool swapped;
    do {
        swapped = false;
        Product_Element* current = list->head;
        while (current != NULL && current->next != NULL) {
            if ((descending && current->brand < current->next->brand) || 
                (!descending && current->brand > current->next->brand)) {
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->category, current->next->category);
                swap(current->brand, current->next->brand);
                swap(current->price, current->next->price);
                swap(current->unit, current->next->unit);
                swap(current->stock, current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sort_and_display_product_by_brand(Product_List* original_list, bool descending, bool clear) {
    Product_List* copied_list = copy_product_list(original_list);
    sort_product_by_brand(copied_list, descending);
    display_product_table(copied_list, clear);
    while (copied_list->size > 0) {
        delete_begin2(copied_list);
    }
    delete copied_list;
}

void check_product_sorting_brand(Product_List *original_list, bool clear, string role){
    int option;
    Product_List* copied_list = copy_product_list(original_list);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Brand          " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Brand        " << RED << "||" << RESET << endl;
    }  
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                              " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 2. Ascending                               " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: "; cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_brand(original_list, descending, clear);
}

void check_product_sorting_menu(Product_List *original_list, bool clear, string role){
    int option = 0;
    while (option != 6){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ============================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Sorting/Price    " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ==========================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Sorting/Price  " << RED << "||" << RESET << endl;
        }  
        cout << RED  << "||" << RESET << "--------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Price                             " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Name                              " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 3. Stock                             " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 4. Brand                             " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 5. Category                          " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 6. Back                              " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "======================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls");check_product_sorting_price(original_list, clear, role);break;
            case 2: system("cls");check_product_sorting_name(original_list, clear, role);break;
            case 3: system("cls");check_product_sorting_stock(original_list, clear, role);break;
            case 4: system("cls");check_product_sorting_brand(original_list, clear, role);break;
            case 5: system("cls");check_product_sorting_category(original_list, clear, role);break;
            case 6: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void customer_check_product_sorting_name(Product_List *original_list, bool clear){
    int option;
    display_product_table(original_list, false);
    cout << endl;
    Product_List* copied_list = copy_product_list(original_list);
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Sort/Name                                                                                       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                                                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Ascending                                                                                             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_name(original_list, descending, clear);
}

void customer_check_product_sorting_stock(Product_List *original_list, bool clear){
    int option;
    display_product_table(original_list, false);
    cout << endl;
    Product_List* copied_list = copy_product_list(original_list);
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Sort/Stock                                                                                      " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                                                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Ascending                                                                                             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_stock(original_list, descending, clear);
}

void customer_check_product_sorting_price(Product_List *original_list, bool clear){
    int option;
    display_product_table(original_list, false);
    cout << endl;
    Product_List* copied_list = copy_product_list(original_list);
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Sort/price                                                                                      " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                                                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Ascending                                                                                             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_price(original_list, descending, clear);
}

void customer_check_product_sorting_brand(Product_List *original_list, bool clear){
    int option;
    display_product_table(original_list, false);
    cout << endl;
    Product_List* copied_list = copy_product_list(original_list);
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Sort/Brand                                                                                      " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                                                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Ascending                                                                                             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_brand(original_list, descending, clear);
}

void customer_check_product_sorting_category(Product_List *original_list, bool clear){
    int option;
    display_product_table(original_list, false);
    cout << endl;
    Product_List* copied_list = copy_product_list(original_list);
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Sort/Category                                                                                   " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " 1. Descending                                                                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << " 2. Ascending                                                                                             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
    bool descending;
    system("cls");
    switch (option){
        case 1:system("cls");descending = true;break;
        case 2:system("cls");descending = false;break;
        case 3:system("cls");break;
        default:
            break;
    }
    sort_and_display_product_by_category(original_list, descending, clear);
}

void customer_check_product_sorting_menu(Product_List *original_list, bool clear){
        int option = 0;
        while(option != 6){
                cout << endl;
                cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
                cout << RED  << "||" << GRAY  << " Customer/Sort                                                                                            " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 1. Price                                                                                                 " << RED << "||" << RESET << endl; 
                cout << RED  << "||" << RESET << " 2. Name                                                                                                  " << RED << "||" << RESET << endl; 
                cout << RED  << "||" << RESET << " 3. Stock                                                                                                 " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 4. Brand                                                                                                 " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 5. Category                                                                                              " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " 6. Back                                                                                                  " << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
                cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
                switch (option){
                    case 1: system("cls");customer_check_product_sorting_price(original_list, clear);break;
                    case 2: system("cls");customer_check_product_sorting_name(original_list, clear);break;
                    case 3: system("cls");customer_check_product_sorting_stock(original_list, clear);break;
                    case 4: system("cls");customer_check_product_sorting_brand(original_list, clear);break;
                    case 5: system("cls");customer_check_product_sorting_category(original_list, clear);break;
                    case 6: system("cls");display_product_table(original_list, clear);break;
                    default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
                }
        }
}

void check_product_filtering_brand(Product_List *list, bool clear, string role){
    string brand;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Sorting/Price  " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Sorting/Price" << RED << "||" << RESET << endl;
    }   
    cout << RED  << "||" << RESET << " Enter brand name :)                        " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Brand name: " << YELLOW; getline(cin >> ws, brand); cout << RESET;
    brand = Capitalization(brand);
    int count = 0;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> brand == brand) count ++;
        temp = temp -> next;
    }
    if (count == 0) cout << RED << "Invalid input, there isn't " << brand << " in the system!!!" << RESET << endl;
    else {
        temp = list -> head;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        while (temp != NULL) {    
            if (temp -> brand == brand){
                cout << "| "
                     << RED     << setw(8)  << left << temp->id        << RESET << " | "
                     << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                     << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                     << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                     << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                     << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                     << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
            }
            temp = temp -> next;
        }              
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_filtering_category(Product_List *list, bool clear, string role){
    string category;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/filtering/Category     " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/filtering/Category   " << RED << "||" << RESET << endl;
    }   
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter category name :)                     " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Category name: " << YELLOW; getline(cin >> ws, category); cout << RESET;
    category = Capitalization(category);
    int count = 0;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> category == category) count ++;
        temp = temp -> next;
    }
    if (count == 0) cout << RED << "Invalid input, there isn't " << category << " in the system!!!" << RESET << endl;
    else {
        temp = list -> head;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        while (temp != NULL) {    
            if (temp -> category == category){
                cout << "| "
                     << RED     << setw(8)  << left << temp->id        << RESET << " | "
                     << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                     << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                     << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                     << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                     << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                     << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
            }
            temp = temp -> next;
        }              
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_filtering_price(Product_List *list, bool clear, string role){
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/filtering/brand        " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/filtering/brand      " << RED << "||" << RESET << endl;
    }   
    double price_min, price_max;
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's price range:)          " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Price minmum: " << YELLOW; cin >> price_min; cout << RESET;
    cout << RED  << "||" << RESET << " Price maximum: " << YELLOW; cin >> price_max; cout << RESET;
    int count = 0;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> price >= price_min && temp -> price <= price_max) count ++;
        temp = temp -> next;
    }
    if (count == 0) cout << RED << "Invalid input, there isn't product that has price between " << price_min << "$ and " << price_max << "$ in the system!!!" << RESET << endl;
    else {
        temp = list -> head;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        while (temp != NULL) {    
            if (temp -> price >= price_min && temp -> price <= price_max){
                cout << "| "
                     << RED     << setw(8)  << left << temp->id        << RESET << " | "
                     << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                     << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                     << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                     << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                     << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                     << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
            }
            temp = temp -> next;
        }              
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_filtering_stock(Product_List *list, bool clear, string role){
    int stock;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/filtering/Stock        " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/filtering/Stock      " << RED << "||" << RESET << endl;
    }   
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's stock left:)           " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Stock: " << YELLOW; cin >> stock; cout << RESET;
    int count = 0;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> stock <= stock) count ++;
        temp = temp -> next;
    }
    if (count == 0) cout << RED << "Invalid input, there isn't product that have have the stock less than " << stock << "!!!" << RESET << endl;
    else {
        temp = list -> head;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        while (temp != NULL) {    
            if (temp -> stock <= stock){
                cout << "| "
                     << RED     << setw(8)  << left << temp->id        << RESET << " | "
                     << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                     << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                     << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                     << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                     << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                     << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
            }
            temp = temp -> next;
        }              
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_filtering(Product_List *list, string role){
    int option = 0;
    while (option != 5){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Filtering   " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " =====================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Filtering " << RED << "||" << RESET << endl;
        }   
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Brand                        " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Category                     " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 3. Price                        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Stock                        " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Back                         " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls"); check_product_filtering_brand(list, true, role);break;
            case 2: system("cls"); check_product_filtering_category(list, true, role);break;
            case 3: system("cls"); check_product_filtering_price(list, true, role);break;
            case 4: system("cls"); check_product_filtering_stock(list, true, role);break;
            case 5: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void check_product_searching_name(Product_List* list,bool clear, string role){
    string name;
    bool check = false;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Searching/Name         " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Searching/Name       " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's name :)                " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's name: " << YELLOW; getline(cin >> ws, name); cout << RESET;
    name = Capitalization(name);
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> name == name) {check = true; break;}
        temp = temp -> next;
    }
    if (!check) cout << RED << "Product not found!" << RESET << endl;
    else{
        cout << GREEN << "Product found!: " << name << RESET << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| "
                << RED     << setw(8)  << left << temp->id        << RESET << " | "
                << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_searching_ID(Product_List* list, bool clear, string role){
    string ID;
    bool check = false;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Searching/ID           " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Searching/ID         " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID        :)           " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's name: " << YELLOW; getline(cin >> ws, ID); cout << RESET;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> id == ID) {check = true; break;}
        temp = temp -> next;
    }
    if (!check) cout << RED << "Product not found!" << RESET << endl;
    else{
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| "
                << RED     << setw(8)  << left << temp->id        << RESET << " | "
                << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void check_product_searching(Product_List* list, string role){
    int option = 0;
    while (option != 3){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Searching   " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " =====================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Searching " << RED << "||" << RESET << endl;
        }
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Name                         " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. ID                           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                         " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls"); check_product_searching_name(list, true, role);break;
            case 2: system("cls"); check_product_searching_ID(list, true, role);break;
            case 3: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void customer_check_product_searching_name(Product_List* list,bool clear){
    string name;
    bool check = false;
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ===============================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Search                            " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's name :)                " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's name: " << YELLOW; getline(cin >> ws, name); cout << RESET;
    name = Capitalization(name);
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> name == name) {check = true; break;}
        temp = temp -> next;
    }
    if (!check) cout << RED << "Product not found!" << RESET << endl;
    else{
        cout << GREEN << "Product found!: " << name << RESET << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| "
                << RED     << setw(8)  << left << temp->id        << RESET << " | "
                << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void customer_check_product_searching_ID(Product_List* list, bool clear){
    string ID;
    bool check = false;
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ===============================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer/Search                            " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "--------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID        :)           " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "============================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's name: " << YELLOW; getline(cin >> ws, ID); cout << RESET;
    system("cls");
    Product_Element* temp = list -> head;
    while (temp != NULL){
        if (temp -> id == ID) {check = true; break;}
        temp = temp -> next;
    }
    if (!check) cout << RED << "Product not found!" << RESET << endl;
    else{
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| ID       | Name                         | Brand    | Catgry               | Price    | Unit       | Stock  |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
        cout << "| "
                << RED     << setw(8)  << left << temp->id        << RESET << " | "
                << GREEN   << setw(28) << left << temp->name      << RESET << " | "
                << YELLOW  << setw(8)  << left << temp->brand     << RESET << " | "
                << BLUE    << setw(20) << left << temp->category  << RESET << " | "
                << MAGENTA << setw(8)  << left << fixed << setprecision(2) << temp->price << RESET << " | "
                << CYAN    << setw(10) << left << temp->unit      << RESET << " | "
                << ORANGE  << setw(6)  << left << temp->stock     << RESET << " |" << endl;
        cout << "+----------+------------------------------+----------+----------------------+----------+------------+--------+" << endl;
    }
    if (clear) {cout << GRAY; system("pause"); cout << RESET << endl; system("cls");}
}

void customer_check_product_searching(Product_List* list){
    int option = 0;
    while (option != 3){
        cout << endl;
        cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " =============================================================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Customer/Search                                                                                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "----------------------------------------------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Name                                                                                                  " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. ID                                                                                                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                                                                                                  " << RED << "||" << RESET << endl;  
        cout << RED  << "||" << RESET << "==========================================================================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW;cin >> option; cout << RESET;
        switch (option){
            case 1: system("cls"); customer_check_product_searching_name(list, false);break;
            case 2: system("cls"); customer_check_product_searching_ID(list, false);break;
            case 3: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void check_product_group_and_aggregation_count_product_brand(Product_List* list, string role){
    string brand;
    int count = 0;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Count Product/Brand   " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Count Product/Brand " << RED << "||" << RESET << endl;
    }  
    cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter brand's name to count                                      " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Brand: "; getline(cin >> ws, brand);
    brand = Capitalization(brand);
    Product_Element* temporary = list -> head;
    system("cls");
    bool check = false;
    while (temporary != NULL){
        if (temporary -> brand == brand) check = true;
        temporary = temporary -> next;
    }
    if (!check) cout << RED << "Invalid Category"  << RESET << endl;
    else{
        temporary = list -> head;
        while(temporary != NULL){
            if (temporary -> brand == brand) {
                count ++;
            }
            temporary = temporary -> next;
        }
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Count Product/Brand   " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Count Product/Brand " << RED << "||" << RESET << endl;
        }  
        cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Average number of " << brand << "'s brand is: " << count << "\t\t\t    " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void check_product_group_and_aggregation_count_product_category(Product_List* list, string role){
    string category;
    int count = 0;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =================================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Count Product/Category         " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ===============================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Count Product/Category       " << RED << "||" << RESET << endl;
    } 
    cout << RED  << "||" << RESET << "---------------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter category's name to count                                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "===========================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Category: "; getline(cin >> ws, category);
    category = Capitalization(category);
    Product_Element* temporary = list -> head;
    system("cls");
    bool check = false;
    while (temporary != NULL){
        if (temporary -> category == category) check = true;
        temporary = temporary -> next;
    }
    if (!check) cout << RED << "Invalid Category"  << RESET << endl;
    else{
        temporary = list -> head;
        while(temporary != NULL){
            if (temporary -> category == category) {
                count ++;
            }
            temporary = temporary -> next;
        }
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Count Product/Category" << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Count Product/Catego" << RED << "||" << RESET << endl;
        } 
        cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Average number of " << category << "'s category is: " << count << "\t\t\t    " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void check_product_group_and_aggregation_count_product(Product_List* list, string role){
    int option = 0;
    while (option != 3){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Count Product         " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Count Product       " << RED << "||" << RESET << endl;
        } 
        cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Brand                                                         " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Category                                                      " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                                                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls"); check_product_group_and_aggregation_count_product_brand(list,role);break;
            case 2: system("cls"); check_product_group_and_aggregation_count_product_category(list,role);break;
            case 3: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void check_product_group_and_aggregation_average_price(Product_List* list, string role){
    string category;
    int sum = 0,count = 0;
    double average;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Average Price         " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Average Price       " << RED << "||" << RESET << endl;
    } 
    cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Category to check average price                            " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter Category: "; getline(cin >> ws, category);
    category = Capitalization(category);
    Product_Element* temporary = list -> head;
    system("cls");
    bool check = false;
    while (temporary != NULL){
        if (temporary -> category == category) check = true;
        temporary = temporary -> next;
    }
    if (!check) cout << RED << "Invalid Category"  << RESET << endl;
    else{
        temporary = list -> head;
        while(temporary != NULL){
            if (temporary -> category == category) {
                sum += temporary -> price;
                count ++;
            }
            temporary = temporary -> next;
        }
        average = (sum*1.0) / count;
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation/Average Price         " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation/Average Price       " << RED << "||" << RESET << endl;
        } 
        cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Average price of " << category << "'s category is: "<< fixed << setprecision(2) << average << "$" << RED << "\t\t\t    ||" << RESET << endl; 
        cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void check_product_group_and_aggregation(Product_List* list, string role){
    int option = 0;
    while (option != 3){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ========================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin/Check Product/Grouping & Aggregation                       " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager/Check Product/Grouping & Aggregation                     " << RED << "||" << RESET << endl;
        } 
        cout << RED  << "||" << RESET << "------------------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Count Product                                                 " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Average Price                                                 " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Back                                                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "==================================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls"); check_product_group_and_aggregation_count_product(list,role);break;
            case 2: system("cls"); check_product_group_and_aggregation_average_price(list,role);break;
            case 3: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void check_product_check_inventory(Product_List* list){
    cout << GREEN << "This is all products and stock" << RESET << endl;
    Product_Element* temp = list->head;
    int no = 1;
    cout << "+------+------------------------------------+--------+" << endl;
    cout << "| No   | Product Name                       | Stock  |" << endl;
    cout << "+------+------------------------------------+--------+" << endl;
    while (temp != NULL) {
        if (temp -> stock == 0) cout << RED;
        else if (temp -> stock < 100) cout << YELLOW;
        cout << "| ";
        cout << setw(3)  << left << no << "  | ";
        cout << setw(35) << left << temp->name << "| ";
        cout << setw(6)  << left << temp->stock << " |" << endl;
        cout << RESET;
        temp = temp->next;
        no++;
    }
    cout << "+------+------------------------------------+--------+" << endl;
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

bool check_product_check_inventory_add_check_category(string category){
    string array[] = {"Fruit", "Meat", "Electronics", "Canned", "Bakery", "Vegetable", "Dairy", "Snacks", "Household", "Beverage", "Dessert", "Personal Care", "Stationery", "Baking", "Breakfast", "Condiment", "Grains", "Nutrition", "Meat Alternative"};
    for (string i : array){if (i == category) return true;}
    return false;
}   

void check_product_check_write_back_to_file(Product_List* list){
    ofstream file;
    file.open("Database/products.csv", ios::out | ios::trunc);
    if (!file.is_open()){
        cout << RED << "Error opening file!" << RESET << endl;
        return;
    }
    Product_Element* temp = list -> head;
    int count = 1;
    file << "ID,Name,Category,Brand,Price,Unit,Stock" << endl;
    while (temp != NULL){
        temp -> id = to_string(count);
        file << temp -> id << ","
             << temp -> name << ","
             << temp -> category << ","
             << temp -> brand << ","
             << fixed << setprecision(2) << temp -> price << ","
             << temp -> unit << ","
             << temp -> stock << endl;
        count++;
        temp = temp -> next;
    }
    file.close();
}

void check_product_check_inventory_add(Product_List* list,string role){
    Product_Element Product;
    Product_Element *temporary;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Adding                     " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Adding                   " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter follow information to add product                " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << endl;
    cout << "Product Name: " << YELLOW;getline(cin >> ws, Product.name);cout << RESET;
    Product.name = Capitalization(Product.name);
    Product.id = to_string(list -> size + 1);
    cout << "Product ID: " << YELLOW << Product.id << RESET << endl;
    system("cls");
    while (true){
        cout << YELLOW << "Note: " << RESET << " Please enter the right category " << endl;
        cout << YELLOW << "Category index:" << RESET << " {Fruit, Meat, Electronics, Canned, Bakery, Vegetable, Dairy, Snacks, Household, Beverage, Dessert, Personal Care, Stationery, Baking, Breakfast, Condiment, Grains, Nutrition, Meat Alternative}" << endl;
        cout << "Category: " YELLOW; getline(cin >> ws, Product.category); cout << RESET;
        Product.category = Capitalization(Product.category);
        system("cls");
        if (check_product_check_inventory_add_check_category(Product.category)) break;
        else cout << RED << "Invalid Input!" << RESET;
    }
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Adding                     " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Adding                   " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter follow information to add product                " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << endl;
    cout << "Product Name:     " << YELLOW << Product.name << RESET << endl;
    cout << "Product ID:       " << YELLOW << Product.id << RESET << endl;
    cout << "Product Category: " << YELLOW << Product.category << RESET << endl;
    cout << "Product Brand:    " << YELLOW; getline(cin >> ws, Product.brand); cout << RESET;
    system("cls");
    Product.brand = Capitalization(Product.brand);
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Adding                     " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Adding                   " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter follow information to add product                " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << endl;
    cout << "Product Name:     " << YELLOW << Product.name << RESET << endl;
    cout << "Product ID:       " << YELLOW << Product.id << RESET << endl;
    cout << "Product Category: " << YELLOW << Product.category << RESET << endl;
    cout << "Product Brand:    " << YELLOW << Product.brand << RESET << endl;
    insert_product_end(list, Product.id, Product.name, Product.category, Product.brand, Product.price, Product.unit, 0);
    check_product_check_write_back_to_file(list);
    cout << GRAY; system("pause"); cout << RESET << endl;   
    system("cls");
}

void check_product_check_inventory_remove(Product_List* list, string role){
    string ID;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Removing                   " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Removing                 " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID to remove                       " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's ID: "; getline(cin >> ws, ID); cout << RESET;
    system("cls");
    Product_Element* temporary = list -> head;
    bool check = false;
    while (temporary != NULL){
        if (temporary -> id == ID) check = true;
        temporary = temporary -> next;
    }
    if (!check) cout << RED <<"Product not found!"<< RESET<<endl;
    else{
        int id = stoi(ID);
        delete_random_variablesx_by_index2(list, id);
        cout<< GREEN <<"Product removed successfully!"<<RESET<<endl;
        check_product_check_write_back_to_file(list);
    }
    cout<< GRAY; system("pause"); cout<<RESET<<endl; system("cls");
}

void check_product_edit_product_name(Product_List* list, Product_Element* temporary){
    cout << GREEN << temporary -> name << "'s information" << RESET << endl;
    string previous = temporary -> name;
    string name;
    cout << GRAY << "Current Name: " << YELLOW << previous << RESET << endl;
    cout << "Enter new name: " << YELLOW; getline(cin >> ws, name); cout << RESET;
    name = Capitalization(name);
    temporary -> name = name;
    system("cls");
    cout << GREEN << "Product's name updated successfully!" << RESET << endl;
    cout << RED << previous << RESET << " -> " << GREEN << name << RESET << endl; 
}

void check_product_edit_product_category(Product_List* list, Product_Element* temporary){
    cout << GREEN << temporary -> name << "'s information" << RESET << endl;
    string previous = temporary -> category;
    string category;
    while (true){
        cout << YELLOW << "Note: " << RESET << " Please enter the right category " << endl;
        cout << YELLOW << "Category index:" << RESET << " {Fruit, Meat, Electronics, Canned, Bakery, Vegetable, Dairy, Snacks, Household, Beverage, Dessert, Personal Care, Stationery, Baking, Breakfast, Condiment, Grains, Nutrition, Meat Alternative}" << endl;
        cout << GRAY << "Current Category: " << YELLOW << previous << RESET << endl;
        cout << "Enter new category: " << YELLOW; getline(cin >> ws, category); cout << RESET;
        category = Capitalization(category);
        system("cls");
        if (check_product_check_inventory_add_check_category(category)) break;
        else cout << RED << "Invalid Input!" << RESET;
    }
    category = Capitalization(category);
    temporary -> category = category;
    system("cls");
    cout << GREEN << "Product's category updated successfully!" << RESET << endl;
    cout << RED << previous << RESET << " -> " << GREEN << category << RESET << endl; 
}

void check_product_edit_product_brand(Product_List* list, Product_Element* temporary){
    cout << GREEN << temporary -> name << "'s information" << RESET << endl;
    string previous = temporary -> brand;
    string brand;
    cout << GRAY << "Current Brand: " << YELLOW << previous << RESET << endl;
    cout << "Enter new brand: " << YELLOW; getline(cin >> ws, brand); cout << RESET;
    brand = Capitalization(brand);
    temporary -> brand = brand;
    system("cls");
    cout << GREEN << "Product's brand updated successfully!" << RESET << endl;
    cout << RED << previous << RESET << " -> " << GREEN << brand << RESET << endl; 
}

void check_product_edit_product_price(Product_List* list, Product_Element* temporary){
    cout << GREEN << temporary -> name << "'s information" << RESET << endl;
    double previous = temporary -> price;
    double price;
    cout << GRAY << "Current Price: " << YELLOW << fixed << setprecision(2) << previous << "$" << RESET << endl;
    cout << "Enter new price: " << YELLOW; cin >> price; cout << RESET;
    temporary -> price = price;
    system("cls");
    cout << GREEN << "Product's price updated successfully!" << RESET << endl;
    cout << RED << fixed << setprecision(2) << previous << "$" << RESET << " -> " 
         << GREEN << fixed << setprecision(2) << price << "$" << RESET << endl; 
}

void check_product_edit_product_unit(Product_List* list, Product_Element* temporary){
    cout << GREEN << temporary -> name << "'s information" << RESET << endl;
    string previous = temporary -> unit;
    string unit;
    cout << GRAY << "Current Unit: " << YELLOW << previous << RESET << endl;
    cout << "Note: Please enter the right unit (e.g. kg, g, lb, oz, l, ml, pcs)" << endl;
    cout << "Enter new unit: " << YELLOW; getline(cin >> ws, unit); cout << RESET;
    temporary -> unit = unit;
    system("cls");
    cout << GREEN << "Product's unit updated successfully!" << RESET << endl;
    cout << RED << previous << RESET << " -> " << GREEN << unit << RESET << endl; 
}

void check_product_edit_product(Product_List* list, string role){
    string ID;
    if (role == "admin"){
        cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Editing                    " << RED << "||" << RESET << endl;
    }
    else if (role == "manager"){
        cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Editing                  " << RED << "||" << RESET << endl;
    }
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID to edit                         " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's ID: "; getline(cin >> ws, ID); cout << RESET;
    int position = stoi(ID);
    system("cls");
    Product_Element* temporary = list -> head;
    bool check = false;
    while (temporary != NULL){
        if (temporary -> id == ID) {
            check = true;
            break;
        }
        temporary = temporary -> next;
    }
    if (!check) cout<<RED<<"Product not found!"<<RESET<<endl;
    else{
        cout << GREEN << temporary -> name << "'s information" << RESET << endl;
        cout << "Name: " << YELLOW << temporary -> name << RESET << endl;
        cout << "ID: " << YELLOW << temporary -> id << RESET << endl;
        cout << "Category: " << YELLOW << temporary -> category << RESET << endl;
        cout << "Brand: " << YELLOW << temporary -> brand << RESET << endl;
        cout << "Price: " << YELLOW << fixed << setprecision(2) << temporary -> price << "$" << RESET << endl;
        cout << "Unit: " << YELLOW << temporary -> unit << RESET << endl;
        cout << endl;
        int option;
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " ==============================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin welcome/Check Product/Editing                    " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager welcome/Check Product/Editing                  " << RED << "||" << RESET << endl;
        }
        cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Name                                                " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Category                                            " << RED << "||" << RESET << endl;	
        cout << RED  << "||" << RESET << " 3. Brand                                               " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Price                                               " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Unit                                                " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Back                                                " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Option: " << YELLOW; cin >> option; cout << RESET;
        switch (option){
            case 1:system("cls");check_product_edit_product_name(list, temporary);break;
            case 2:system("cls");check_product_edit_product_category(list, temporary);break;
            case 3:system("cls");check_product_edit_product_brand(list, temporary);break;
            case 4:system("cls");check_product_edit_product_price(list, temporary);break;
            case 5:system("cls");check_product_edit_product_unit(list, temporary);break;
            case 6:system("cls");break;
            default:cout << RED << "Invalid option" << RESET << endl; break;
        }
        string id = temporary -> id;
        string name = temporary -> name;
        string category = temporary -> category;
        string brand = temporary -> brand;
        double price = temporary -> price;
        string unit = temporary -> unit;
        int stock = temporary -> stock;

        cout << endl << GRAY << "Review Product" << RESET << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Name:     " << YELLOW << name << RESET << endl;
        cout << "ID:       " << YELLOW << id << RESET << endl;
        cout << "Category: " << YELLOW << category << RESET << endl;
        cout << "Brand:    " << YELLOW << brand << RESET << endl;
        cout << "Price:    " << YELLOW << fixed << setprecision(2) << price << "$" << RESET << endl;
        cout << "Unit:     " << YELLOW << unit << RESET << endl;
        cout << "Stock:    " << YELLOW << stock << RESET << endl;
        cout << "---------------------------------------------------" << endl;

        delete_random_variablesx_by_index2(list, position);
        add_product_specific(list, position, id, name, category, brand, price, unit, stock);
        check_product_check_write_back_to_file(list);
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void check_product_menu(Product_List *list, string role){
    int option = 0;
    while (option != 10){
        if (role == "admin"){
            cout << CYAN << "<===== " << GREEN << "Admin" << CYAN << " =======================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Admin welcome/Check Product     " << RED << "||" << RESET << endl;
        }
        else if (role == "manager"){
            cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ======================>" << RESET << endl;
            cout << RED  << "||" << GRAY  << " Manager welcome/Inventory       " << RED << "||" << RESET << endl;
        }
        cout << RED  << "||" << RESET << "---------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. All Product                  " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 2. Sorting                      " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << " 3. Filtering                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Searching                    " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 5. Grouping & Aggregation       " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 6. Checking Inventory           " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 7. Adding Products              " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 8. Removing Products            " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 9. Edit Product                 " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 10. Back                        " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "=================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: "; cin >> option;
        switch (option){
            case 1: system("cls");display_product_table(list, true);break;
            case 2: system("cls");check_product_sorting_menu(list, true, role);break;
            case 3: system("cls");check_product_filtering(list, role);break;
            case 4: system("cls");check_product_searching(list, role);break;
            case 5: system("cls");check_product_group_and_aggregation(list, role);break;
            case 6: system("cls");check_product_check_inventory(list);break;
            case 7: system("cls");check_product_check_inventory_add(list, role);break;
            case 8: system("cls");check_product_check_inventory_remove(list, role);break;
            case 9: system("cls");check_product_edit_product(list, role);break;
            case 10: system("cls");break;
            default: system("cls"); cout << RED << "Invalid option" << RESET << endl; break;
        }
    }
}

void display_product_that_customer_bought(Product_List* Buy_List){
    cout << "\t\t\t" << GREEN << "POS" << RESET << endl;
    double Total_price = 0;
    Product_Element* Temporary = Buy_List -> head;
    int No = 1;
    cout << current_time() << endl;
    cout << string(50, '-') << endl;
    while (Temporary != NULL){
        cout << Temporary -> id << setw(5) <<  "." 
             << setw(20) <<  Temporary -> name  
             << Temporary -> stock << " " << setw(15) << Temporary -> unit 
             << fixed << setprecision(2) << Temporary -> price << " $" << endl;
        No++;
        Total_price += Temporary -> price;
        Temporary = Temporary -> next;
    }
    cout << string(50, '-') << endl;
    cout << "Total Price = " << Total_price << " $" << endl;
}

int select_product_add_product_to_cart(Product_List* list, Product_List* Buy_List, int number_of_product){
    string ID;
    int unit;
    do{
        display_product_table(list, false);
        cout << endl;
        display_product_that_customer_bought(Buy_List);
        cout << endl;
        cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Customer welcome/Select Product/Add to Cart            " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter the product's ID to add to cart                  " << RED << "||" << RESET << endl; 
        cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Product's ID: "; getline(cin >> ws, ID); cout << RESET;
        system("cls");
        Product_Element* temporary = list -> head;
        bool check = false;
        while (temporary != NULL){
            if (temporary -> id == ID) check = true;
            temporary = temporary -> next;
        }
        if (!check) cout<<RED<<"Product not found!"<<RESET<<endl;
        else{
            temporary = list -> head;
            while (temporary != NULL){
                if (temporary -> id == ID) {
                    cout << GREEN << "Product Details:" << RESET << endl;
                    cout << "ID:       " << YELLOW << temporary -> id << RESET << endl;
                    cout << "Name:     " << YELLOW << temporary -> name << RESET << endl;
                    cout << "Category: " << YELLOW << temporary -> category << RESET << endl;
                    cout << "Brand:    " << YELLOW << temporary -> brand << RESET << endl;
                    cout << "Price:    " << YELLOW << fixed << setprecision(2) << temporary -> price << "$" << RESET << endl;
                    cout << "Unit:     " << YELLOW; cin >> unit; cout << RESET;
                    if (unit <= 0) {
                        system("cls");
                        cout << RED << "Invalid quantity. Please enter a positive number." << RESET << endl;
                        break;
                    }
                    else if (unit > temporary -> stock) {
                        system("cls");
                        cout << RED << "Insufficient stock. Available stock: " << temporary -> stock << RESET << endl;
                        break;
                    }
                    else {
                        number_of_product ++;
                        temporary -> stock -= unit;
                        check_product_check_write_back_to_file(list);
                    }
                    system("cls");
                    cout << GREEN << "Product Details:" << RESET << endl;
                    cout << "ID:       " << YELLOW << temporary -> id << RESET << endl;
                    cout << "Name:     " << YELLOW << temporary -> name << RESET << endl;
                    cout << "Category: " << YELLOW << temporary -> category << RESET << endl;
                    cout << "Brand:    " << YELLOW << temporary -> brand << RESET << endl;
                    cout << "Price:    " << YELLOW << fixed << setprecision(2) << temporary -> price << "$" << RESET << endl;
                    cout << "Unit:     " << YELLOW << unit << RESET << endl;
                    cout << string(50, '-') << endl;
                    cout << "Total Price: " << fixed << setprecision(2) << temporary -> price * unit << "$" << endl;
                    cout << GRAY; system("pause"); cout << RESET << endl;system("cls");
                    string str_number_of_product = to_string(number_of_product);
                    insert_product_end(Buy_List, str_number_of_product, temporary -> name, temporary -> category, temporary -> brand, temporary -> price * unit, temporary -> unit, unit);
                    cout<< GREEN <<"Product added to cart successfully!"<<RESET<<endl;
                    return number_of_product;
                }
                temporary = temporary -> next;
            }
        }
    }while (ID != "0");
}

int select_product_remove_product_from_cart(Product_List* Buy_List, Product_List* list, int number_of_product){
    string ID;
    Product_Element* temporary = Buy_List -> head;
    bool check = false;
    display_product_that_customer_bought(Buy_List);
    cout << endl;
    cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ==============================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Customer welcome/Select Product/Remove from Cart       " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID to remove from cart             " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's ID: "; getline(cin >> ws, ID); cout << RESET;
    system("cls");
    while (temporary != NULL){
        if (temporary -> id == ID) check = true;
        temporary = temporary -> next;
    }
    if (!check) cout<<RED<<"Product not found!"<<RESET<<endl;
    else{
        temporary = Buy_List -> head;
        int count = 1;
        while (temporary != NULL){
            if (temporary -> id == ID) {
                delete_random_variablesx_by_index2(Buy_List, count);
                Product_Element *temporary_list = list -> head;
                while (temporary_list != NULL) {
                    if (temporary_list -> name == temporary -> name) {
                        temporary_list -> stock += temporary -> stock;
                        check_product_check_write_back_to_file(list);
                        temporary = Buy_List -> head;
                        count = 1;
                        string strcount;
                        cout << "Hasha" << endl;
                        while (temporary != NULL){
                            strcount = to_string(count);
                            temporary -> id = strcount;
                            count++;
                            temporary = temporary -> next;
                        }
                        cout << "Hasha" << endl;
                        break;
                    }
                    temporary_list = temporary_list -> next;
                }
                cout << "dfefsd" << endl;
                count = count - 1;
                return count;
            }
            count++;
            temporary = temporary -> next;
        }
    }
    return number_of_product;
}

double total_price_of_products(Product_List* Buy_List){
    double total_price = 0;
    Product_Element* temporary = Buy_List -> head;
    while (temporary != NULL){
        total_price += temporary -> price;
        temporary = temporary -> next;
    }
    return total_price;
}

void select_product_checkout(Product_List* list, Product_List* Buy_List){
    double main_money = Manager_Money();
    display_product_that_customer_bought(Buy_List);
    cout << endl;
    main_money = main_money + total_price_of_products(Buy_List);

    ofstream file;
    file.open("Database/Manager/Money.csv", ios::out | ios::trunc);
    file << fixed << setprecision(2) << main_money << endl;
    file.close();

    string buyer_name = get_user_information("Database/temporary_user_info.csv");
    ofstream receipt_file;
    receipt_file.open("Database/Customer/Customer_detail.csv", ios::app);
    if (!receipt_file.is_open()){
        cout << RED << "Error opening file!" << RESET << endl;
        return;
    }
    Product_Element* temporary = Buy_List -> head;
    while (temporary != NULL){
        receipt_file << buyer_name << ","
                     << temporary -> id << ","
                     << temporary -> name << ","
                     << temporary -> category << ","
                     << temporary -> brand << ","
                     << fixed << setprecision(2) << temporary -> price << ","
                     << temporary -> unit << ","
                     << temporary -> stock << endl;
        temporary = temporary -> next;
    }
    receipt_file.close();

    ifstream cashier_checkout;
    cashier_checkout.open("Database/Cashier/Temporary_cashier.txt");
    if (!cashier_checkout.is_open()){
        cout << RED << "Error opening file!" << RESET << endl;
        return;
    }
    string cashier_name;
    getline(cashier_checkout, cashier_name);
    cashier_checkout.close();

    ofstream customer_transaction;
    customer_transaction.open("Database/Customer/Customer_transaction.csv", ios::app);
    if (!customer_transaction.is_open()){
        cout << RED << "Error opening file!" << RESET << endl;
        return;
    }
    customer_transaction << buyer_name << "," << fixed << setprecision(2) << total_price_of_products(Buy_List) << "," << current_time() << "," << cashier_name << endl;
    customer_transaction.close();

    ofstream money_transaction;
    money_transaction.open("Database/Manager/Money_transaction.csv", ios::app);
    if (!money_transaction.is_open()){
        cout << RED << "Error opening file!" << RESET << endl;
        return;
    }
    money_transaction << "[+]," << buyer_name << "," << fixed << setprecision(2) << total_price_of_products(Buy_List) << "," << current_time() << "," << cashier_name << endl;
    money_transaction.close();

    cout << YELLOW << "Thank you for shopping with us!" << RESET << endl;
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void customer_select_product_cancel(Product_List* Buy_List, Product_List* list){
    Product_Element* temporary = Buy_List -> head;
    while (temporary != NULL){
        Product_Element* temp_list = list -> head;
        while (temp_list != NULL){
            if (temp_list -> name == temporary -> name) {
                temp_list -> stock += temporary -> stock;
                check_product_check_write_back_to_file(list);
                break;
            }
            temp_list = temp_list -> next;
        }
        temporary = temporary -> next;
    }
}

void select_product(Product_List* list){
    Product_List* Buy_List = new Product_List;
    Buy_List = create_new_product_list();
    int option = 0;
    int number_of_product = 0;
    do{
        display_product_table(list, false);
        cout << endl;
        display_product_that_customer_bought(Buy_List);
        cout << endl;
        cout << CYAN << "<===== " << GREEN << "Customer" << CYAN << " ==============================================>" << RESET << endl;
        cout << RED  << "||" << GRAY  << " Customer welcome/Select Product                          " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "----------------------------------------------------------" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 1. Add Product to Cart                                   " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 2. Remove Product from Cart                              " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 3. Checkout                                              " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " 4. Cancel                                                " << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << "==========================================================" << RED << "||" << RESET << endl;
        cout << RED  << "||" << RESET << " Enter option: " << YELLOW; cin >> option; cout << RESET;
        switch (option) {
            case 1:system("cls");number_of_product = select_product_add_product_to_cart(list, Buy_List, number_of_product);break;
            case 2:system("cls");number_of_product = select_product_remove_product_from_cart(Buy_List, list, number_of_product);break;
            case 3:system("cls");select_product_checkout(list, Buy_List);break;
            case 4:system("cls");customer_select_product_cancel(Buy_List, list); break;
            default:cout << RED << "Invalid option. Please try again." << RESET << endl; break;
        }
    } while (option != 4 && option != 3);
    delete_all_products(Buy_List);
    delete Buy_List;
}

void customer_check_product_history(Product_List* List_Product, string User_Email){
    ifstream history_file("Database/Customer/Customer_detail.csv");
    if (!history_file.is_open()) {
        cout << RED << "Error opening file! Database/Customer/Customer_detail.csv" << RESET << endl;
        return;
    }
    string line;
    cout << YELLOW;
    cout << string(100, '-') << endl;
    cout << setw(15) << "Product ID" 
         << setw(20) << "Product Name" 
         << setw(20) << "Category" 
         << setw(20) << "Brand" 
         << setw(10) << "Price" 
         << setw(10) << "Unit" 
         << setw(10) << "Stock" << endl;
    cout << string(100, '-') << endl;
    cout << RESET;
    while (getline(history_file, line)) {
        stringstream ss(line);
        string email, product_id, product_name, category, brand, price, unit, stock;
        getline(ss, email, ',');
        getline(ss, product_id, ',');
        getline(ss, product_name, ',');
        getline(ss, category, ',');
        getline(ss, brand, ',');
        getline(ss, price, ',');
        getline(ss, unit, ',');
        getline(ss, stock, ',');

        if (email == User_Email) {
            cout << setw(15) << product_id 
                 << setw(20) << product_name 
                 << setw(20) << category 
                 << setw(20) << brand 
                 << setw(10) << price 
                 << setw(10) << unit 
                 << setw(10) << stock << endl;
        }
    }
    history_file.close();
    cout << string(100, '-') << endl;
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void cashier_record_income(string email){
    ifstream record_income;
    record_income.open("Database/Customer/Customer_transaction.csv");
    if (!record_income.is_open()) cout << RED << "Can't open Database/Customer/Customer_transaction.csv" << RESET << endl;
    else {
        string line;
        double total_income = 0;
        cout << YELLOW;
        cout << string(60, '-') << endl;
        cout << left
             << setw(8)  << "No"
             << setw(20) << "Customer Name" 
             << setw(20) << "Total Price" 
             << setw(20) << "Date" << endl;
        cout << string(60, '-') << endl;
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
                total_income += stod(total_price);
                cout << left
                     << setw(8)  << count
                     << setw(20) << customer_name 
                     << setw(20) << fixed << setprecision(2) << stod(total_price) 
                     << setw(20) << date << endl;
                count++;
            }
        }
        record_income.close();
        cout << string(60, '-') << endl;
        cout << "Total Income: " << fixed << setprecision(2) << total_income << "$" << endl;
    }
    cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
}

void get_product_information_into_stock(Product_List* list, string User_Email) {
    string ID;
    double money = Manager_Money();
    display_product_table(list, false);
    cout << CYAN << "<===== " << GREEN << "Manager" << CYAN << " ============================================>" << RESET << endl;
    cout << RED  << "||" << GRAY  << " Manager/ Add Product to stock                          " << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << "--------------------------------------------------------" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Enter the product's ID to add                          " << RED << "||" << RESET << endl; 
    cout << RED  << "||" << RESET << "========================================================" << RED << "||" << RESET << endl;
    cout << RED  << "||" << RESET << " Product's ID: "; getline(cin >> ws, ID); cout << RESET;
    int position = stoi(ID);
    system("cls");
    Product_Element* temporary = list -> head;
    bool check = false;
    while (temporary != NULL){
        if (temporary -> id == ID) {
            check = true;
            break;
        }
        temporary = temporary -> next;
    }
    if (!check) cout<<RED<<"Product not found!"<<RESET<<endl;
    else{
        cout << GREEN << temporary -> name << "'s information" << RESET << endl;
        double previous = temporary -> stock;
        int stock;
        cout << GRAY << "Current Money: " << YELLOW << fixed << setprecision(2) << money << "$"<< RESET << endl;
        cout << GRAY << "Current Stock: " << YELLOW << temporary -> stock << RESET << endl;
        cout << temporary -> price << "$" << " -> " << temporary -> price * 0.9 << "$" << endl;
        cout << "Add Stock: " << YELLOW; cin >> stock; cout << RESET;
        temporary -> stock += stock;
        system("cls");
        double Total_Price = (temporary -> price * 0.9) * stock;
        double previous_money = money;
        money -= Total_Price;
        ofstream file;
        file.open("Database/Manager/Money.csv", ios::out | ios::trunc);
        if (!file.is_open()) cout << RED << "Error opening file: Database/Manager/Money.csv" << RESET << endl;
        else {
            file << fixed << setprecision(2) << money << endl;
            file.close();
        }

        ofstream money_transaction;
        money_transaction.open("Database/Manager/Money_transaction.csv", ios::app);
        if (!money_transaction.is_open()) {
            cout << RED << "Error opening file: Database/Manager/Money_transaction.csv" << RESET << endl;
            return;
        }
        money_transaction << "[-]," << temporary -> name << "," << fixed << setprecision(2) 
                          << Total_Price << "," << current_time() << "," << User_Email << endl;
        money_transaction.close();
        check_product_check_write_back_to_file(list);
        system("cls");
        
        cout << GREEN << "Money updated successfully!" << RESET << endl;
        cout << GREEN << "Product's stock updated successfully!" << RESET << endl;
        cout << RED << fixed << setprecision(2) << previous_money << "$" << RESET << " -> " 
             << GREEN << fixed << setprecision(2) << money << "$" << RESET << endl;
        cout << RED  << previous << RESET << " -> " 
            << GREEN << temporary -> stock << RESET << endl; 
        cout << "Cost of product: " << RED << fixed << setprecision(2) 
             << Total_Price << "$" << RESET << endl << endl;

        cout << "Review Product" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Name:     " << YELLOW << temporary -> name << RESET << endl;
        cout << "ID:       " << YELLOW << temporary -> id << RESET << endl;
        cout << "Category: " << YELLOW << temporary -> category << RESET << endl;
        cout << "Brand:    " << YELLOW << temporary -> brand << RESET << endl;
        cout << "Price:    " << YELLOW << fixed << setprecision(2) << temporary -> price << "$" << RESET << endl;
        cout << "Unit:     " << YELLOW << temporary -> unit << RESET << endl;
        cout << "Stock:    " << YELLOW << temporary -> stock << RESET << endl;
        cout << "---------------------------------------------------" << endl;
        cout << GRAY; system("pause"); cout << RESET << endl; system("cls");
    }
}