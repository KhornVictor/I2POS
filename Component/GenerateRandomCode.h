using namespace std;

string generatePinCode() {
    string pin;
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 6; ++i) {
        int digit = rand() % 10;
        pin += to_string(digit);
    }
    return pin;
}