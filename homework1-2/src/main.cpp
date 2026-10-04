#include <iostream>
#include <vector>

using namespace std;

void powerset(const vector<char>& S, int index, vector<char>& current) {
    if (index == S.size()) {
        cout << "(";
        for (size_t i = 0; i < current.size(); i++) {
            cout << current[i] << (i + 1 < current.size() ? "," : "");
        }
        cout << ") ";
        return;
    }

    powerset(S, index + 1, current);

    current.push_back(S[index]);
    powerset(S, index + 1, current);
    current.pop_back();
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<char> current;

    cout << "{ ";
    powerset(S, 0, current);
    cout << "}\n";

    return 0;
}
