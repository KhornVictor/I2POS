using namespace std;

string get_user_information(string filename) {
    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }
    string line;
    stringstream buffer;
    while (getline(file, line)) {
        buffer << line;
    }
    return buffer.str();
}