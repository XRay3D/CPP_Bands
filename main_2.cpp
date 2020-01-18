#include <iostream>
#include <stdint.h>
#include <strstream>
#include <vector>

using namespace std;

int main()
{
#ifdef __TEST__
    strstream cin;
    cin << 1000000 << endl;
    for (int i = 0; i < 1000000; ++i) {
        cin << 1000000000 << ' ';
    }
    cin << endl;
    cout << 1000000000 << endl;
#endif

    int n; // < 1'000'000
    cin >> n;
    vector<int32_t> temperatures(n);
    int64_t sum = 0;
    for (auto& temperature : temperatures) {
        cin >> temperature;
        sum += temperature;
    }

    int64_t average = sum / n;

#ifdef __TEST__
    cout << average << endl;
    return 0;
#endif

    vector<int32_t> result_indices;
    for (int i = 0; i < n; ++i) {
        if (temperatures[i] > average) {
            result_indices.push_back(i);
        }
    }

    cout << result_indices.size() << endl;
    for (auto result_index : result_indices) {
        cout << result_index << " ";
    }
    cout << endl;

    return 0;
}
