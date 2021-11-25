//Wrocławskie Sparingi Informatyczne
//Poprawne nawiasowania
//100/100

#include <bits/stdc++.h>

std::string a;
int usunieto, dlugosc;

int popraw() {
    std::stack < char > s;

    for (int i = 0; i < a.length(); i++) {
        if (a[i] == ')' && !s.empty()) {
            if (s.top() == '(') s.pop();
            else s.push(a[i]);
        } else s.push(a[i]);
    }

    dlugosc = s.size();

    while (!s.empty() && s.top() == '(') {
        s.pop();
        usunieto++;
    }

    return (dlugosc / 2 + usunieto % 2);
}

int main(void) {
    std::cin >> a;

    printf("%d", popraw());
    return 0;
}
