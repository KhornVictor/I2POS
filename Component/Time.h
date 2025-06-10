using namespace std;

string current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << 1900 + ltm->tm_year << '-'
       << 1 + ltm->tm_mon << '-'
       << ltm->tm_mday << ' '
       << ltm->tm_hour << ':'
       << ltm->tm_min << ':'
       << ltm->tm_sec;
    return ss.str();
}