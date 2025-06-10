using namespace std;

double Manager_Money(){
    ifstream file("Database/Manager/Money.csv");
    if (!file.is_open()) {
        cerr << "Error opening file: Database/Manager/Money.csv" << endl;
        return 0.0;
    }
    string line;
    double total_money = 0.0;
    while (getline(file, line)) {
        total_money += stod(line);
    }
    file.close();
    return total_money;
}