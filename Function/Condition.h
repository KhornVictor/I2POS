
using namespace std;

bool isAllAlphabets(string str) {
    for (char ch : str) {if (!(isalpha(ch) || isspace(ch))) return false;}
    return true;
}

bool isAllDigits(string str) {
    for (char ch : str) {if (!isdigit(ch)) return false;}
    return true;
}

bool check_validation_of_email(User_List *s, string email){
    User_Element* temporary = s -> head;
    bool check = false;
    while (temporary != NULL){
        if(temporary -> email == email) { 
            system("cls");
            cout << RED << "This email has used by other user!" << RESET << endl;
            check = true;  
            break;
        }temporary = temporary -> next;
    }return check;
}