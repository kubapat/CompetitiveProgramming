//Wrocławskie Sparingi Informatyczne
//Unikalne podsłowa
//100/100


#include <iostream>
#include <string>

int visited[130];
std::string str;

int maxLen() {
    int n = str.length();
    int cur = 1, res = 1, prev;

    for (int i = 0; i < 130; i++) visited[i] = -1;

    visited[str[0]] = 0;

    for (int i = 1; i < n; i++) {
        prev = visited[str[i]];

        if (prev == -1 || i - cur > prev) cur++;
        else {
            if (cur > res) res = cur;

            cur = i - prev;
        }

        visited[str[i]] = i;
    }

    if (cur > res) res = cur;

    return res;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> str;
    std::cout << maxLen();

    return 0;
}
