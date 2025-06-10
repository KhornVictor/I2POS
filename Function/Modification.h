
using namespace std;

string change_string_to_lower(string str) {
    string x;
    for (char ch : str) {
        ch = tolower(ch);
        x += ch;
    }
    return x;
}