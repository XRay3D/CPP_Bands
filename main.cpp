#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
- добавление события:                        Add Дата Событие
- удаление события:                          Del Дата Событие
- удаление всех событий за конкретную дату:  Del Дата
- поиск событий за конкретную дату:          Find Дата
- печать всех событий за все даты:           Print

Add 0-1-2 event1
Add 1-2-3 event2
Find 0-1-2
"
Del 0-1-2
Print
Del 1-2-3 event2
Del 1-2-3 event2
Add 0-13-32 event1

*/

class Date {
    int y;
    int d;
    int m;

    friend ostream& operator<<(ostream& s, const Date& d);
    friend istream& operator>>(istream& s, Date& d);
    friend bool operator<(const Date& l, const Date& r);

public:
    //    int GetYear( ) const;
    //    int GetMonth( ) const;
    //    int GetDay( ) const;
};

bool operator<(const Date& l, const Date& r)
{
    if (l.y == r.y && l.m == r.m) {
        return l.d < r.d;
    } else if (l.y == r.y && l.m != r.m) {
        return l.m < r.m;
    } else {
        return l.y < r.y;
    }
}

istream& operator>>(istream& s, Date& d)
{
    string str, end;
    s >> str;
    istringstream ss(str);

#ifdef __TEST__
    cout << "str: " << str << endl;
#endif
    //    regex word_regex("^(\\d+)-(-?\\d+)-(-?\\d+)$", regex_constants::ECMAScript | regex_constants::icase);
    //    smatch pieces_match;
    //    if (regex_match(str, pieces_match, word_regex)) {
    //        for (size_t i = 1; i < pieces_match.size(); ++i) {
    //            ssub_match sub_match = pieces_match[i];
    //            if (i == 1) {
    //                d.y = stoi(sub_match.str());
    //            } else if (i == 2) {
    //                d.m = stoi(sub_match.str());
    //            } else if (i == 3) {
    //                d.d = stoi(sub_match.str());
    //            }
    //#ifdef __TEST__
    //            cout << i << "  : " << sub_match.str() << '\n';
    //#endif
    //        }
    //    }
    char c1, c2;
    d.d = numeric_limits<int>::max();
    d.m = numeric_limits<int>::max();
    d.y = numeric_limits<int>::max();
    ss >> d.y >> c1 >> d.m >> c2 >> d.d >> end;
#ifdef __TEST__
    cout << end << ' '
         << c1 << ' '
         << c2 << ' '
         << (d.y == numeric_limits<int>::max()) << ' '
         << (d.m == numeric_limits<int>::max()) << ' '
         << (d.d == numeric_limits<int>::max()) << endl;
#endif
    if (end.size()
        || c1 != '-'
        || c2 != '-'
        || d.d == numeric_limits<int>::max()
        || d.m == numeric_limits<int>::max()
        || d.y == numeric_limits<int>::max()) {
        throw invalid_argument("Wrong date format: " + str);
    }
    if (d.m < 1 || d.m > 12) {
        throw invalid_argument("Month value is invalid: " + to_string(d.m));
    }
    if (d.d < 1 || d.d > 31) {
        throw invalid_argument("Day value is invalid: " + to_string(d.d));
    }

    return s;
}
ostream& operator<<(ostream& s, const Date& d)
{
    s << setw(4) << setfill('0') << d.y << '-'
      << setw(2) << setfill('0') << d.m << '-'
      << setw(2) << setfill('0') << d.d;
    return s;
}

bool operator<(const Date& l, const Date& r);

class Database {
    map<Date, set<string>> data;

public:
    void AddEvent(const Date& date, const string& event)
    {
        data[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        if (data.count(date) && data[date].count(event)) {
            data[date].erase(event);
            return true;
        }
        return false;
    }
    int DeleteDate(const Date& date)
    {
        int count = 0;
        if (data.count(date)) {
            count = static_cast<int>(data[date].size());
            data.erase(date);
        }
        return count;
    }
    bool Find(const Date& date) const
    {
        if (data.count(date)) {
            vector<string> v(begin(data.at(date)), end(data.at(date)));
            //            sort(begin(v), end(v),
            //                // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
            //                [](const string& l, const string& r) {
            //                    // сравниваем лексикографически...
            //                    return lexicographical_compare(
            //                        // ... все символы строки l ...
            //                        begin(l), end(l),
            //                        // ... со всеми символами строки r ...
            //                        begin(r), end(r),
            //                        // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
            //                        [](char cl, char cr) { return tolower(cl) < tolower(cr); });
            //                });
            for (auto e : v) {
                cout << e << endl;
            }
            return true;
        }
        return false;
    }
    void Print() const
    {
        for (const auto& [date, sets] : data) {
            vector<string> v(begin(sets), end(sets));
            //            sort(begin(v), end(v),
            //                // компаратор для сортировки — лямбда-функция, сравнивающая строки без учёта регистра
            //                [](const string& l, const string& r) {
            //                    // сравниваем лексикографически...
            //                    return lexicographical_compare(
            //                        // ... все символы строки l ...
            //                        begin(l), end(l),
            //                        // ... со всеми символами строки r ...
            //                        begin(r), end(r),
            //                        // ..., используя в качестве компаратора сравнение отдельных символов без учёта регистра
            //                        [](char cl, char cr) { return tolower(cl) < tolower(cr); });
            //                });
            for (auto e : v) {
                cout << date << ' ' << e << endl;
            }
        }
    }
};
/*
Failed case #22/34: Wrong answer
*/
int main()
{

#ifdef __TEST__
    stringstream ssTestData(
        "Add 0-13-32 event1\n"
        "Add 1---2 event1\n"
        "Add 1---2---3- event1\n"
        "Add 1--1 event1\n"
        "Add 1--2--3 event1\n"
        "Add 1--2-3 event1\n"
        "Add 1-1- event1\n"
        "Add 1-2--3 event1\n"
        "Add 1-2-3 event1\n"
        "Add 1-2-3- event1\n"
        /**/);

    stringstream& cin = ssTestData;
#endif

    Database db;

    string command;
    while (getline(cin, command)) {
        if (command.empty())
            continue;
        try {
            stringstream parser(command);
            string cmd;
            parser >> cmd;
            if (cmd == "Add") {
                Date date;
                string event;
                parser >> date;
                parser >> event;
                //                if (event.empty()) {
                //                    //                    stringstream ss;
                //                    //                    ss << "Wrong date format: " << date;
                //                    //                    throw runtime_error(ss.str());
                //                    cout << "Event not found" << endl;
                //                } else {
                db.AddEvent(date, event);
                //                }
            } else if (cmd == "Del") {
                Date date;
                string event;
                parser >> date;
                parser >> event;
                if (event.empty()) {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                } else {
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            } else if (cmd == "Find") {
                Date date;
                parser >> date;
                if (!db.Find(date)) {
                    // cout << "Event not found" << endl;
                }
            } else if (cmd == "Print") {
                db.Print();
            } else if (cmd.empty()) {
                continue;
            } else {
                throw invalid_argument("Unknown command: " + cmd);
            }
        } catch (invalid_argument& e) {
#ifdef __TEST__
            cout << "==============================" << endl;
#endif
            cout << e.what() << endl;
#ifdef __TEST__
            cout << "==============================" << endl;
#else
            return 0;
#endif
        }
    }
    return 0;
}
