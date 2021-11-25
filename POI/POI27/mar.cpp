//Polish Olympiad in Informatics
//Task: Marudny Bajtazar
//Score: 46/100

#include <iostream>
#include <string>
#include <unordered_set>
#define DEBUG if(0)

  int main(void) {
      std::ios_base::sync_with_stdio(false);
      std::cin.tie(0);
      std::cout.tie(0);

      int n,m;
      std::string str;
      std::cin >> n >> m >> str;

      for(int i=0; i<=m; i++) {
        if(i) {
          int test;
          std::cin >> test;
          if(str[test-1] == '0') str[test-1] = '1';
          else str[test-1] = '0';
        }

        for(int s=1; s<=(int)str.length(); s++) { //Po rozmiarze
            std::unordered_set <std::string> unikalne;
            long long int size = (long long int)((long long int)1<<(long long int)s);
            for(int p=0; p<(int)str.length()-s+1; p++) { //Pozycja startowa do rozmiaru
                unikalne.insert(str.substr(p,s));
                if(size == (long long int)unikalne.size()) break;
                DEBUG printf("Jestem na pozycji %d z rozmiarem %d i dorzucam %s\n",p,s,str.substr(p,s).c_str());
            }

            if((long long int)unikalne.size() != size) { //Jeżeli liczba różnych podciągów jest różna od 2^rozmiar to brakuje
               std::cout << s << "\n";
               break;
            }
        }

      }

      return 0;
   }
