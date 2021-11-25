//Polish Olympiad in Informatics
//Task: Pomniejszenie
//Score: 85/100

#include <iostream>
#include <vector>
#include <set>
#define DEBUG if(0)

 std::string a,b,c;
 int tmp,k;
 bool less;
 std::set <int> pos;

  void jednoK() {
    std::vector <int> wieksze,mniejsze;
    for(int i=0; i<a.length(); i++) {
        if(a[i] > b[i]) wieksze.push_back(i);
        if(a[i] < b[i]) mniejsze.push_back(i);
    }

    for(int i=0; i<a.length(); i++) {
        if(a[i] <= b[i]) continue;

        if(b[i] == '0') {
           if(i+1 != a.length() && mniejsze.size() && (wieksze.size() == 1 || (wieksze.size() > 1 && mniejsze[0] < wieksze[1]))) c[i]='0';
           else {
             bool changed = false;
             for(int k=i-1; k>=0; k--) {
                 if(b[k] != '0') {
                    c[k] = b[k]-1;
                    changed = true;
                    break;
                 }
             }

             if(!changed) {
               c[i] = b[i];
               break;
             }
           }
        } else if(mniejsze.size() && i+1 != a.length() && (wieksze.size() == 1 || (wieksze.size() > 1 && mniejsze[0] < wieksze[1]))) c[i] = b[i];
        else c[i] = b[i]-1;
        break;
    }

    if(c>=b) c="-1";
  }

  bool backtrace(int i) {
    bool kon=false;
    for(int j=i-1; j>=0; j--) {
          if(b[j] == '0') continue; //Jeżeli nie można zmniejszyć

          DEBUG printf("Co powiesz na pozycję %d, gdzie a[%d]=%c b[%d]=%c\n",j,j,a[j],j,b[j]);

          int used = std::distance(pos.begin(), pos.lower_bound(j));
          DEBUG printf("Wcześniej ruszaliśmy %d\n",used);
          int left = k-used;

          if(!tmp && !left) continue;

          if(b[j]-1 == a[j]) { //Jeżeli pomniejszona pozycja to wartość
             if(j+left == a.length()) { //Jeżeli trzeba zmieniać
                if(b[j]-2 < '0') continue;

                auto it = pos.upper_bound(j); //Usuwamy wszystkie późniejsze akcje
                pos.erase(it,pos.end()); pos.insert(j);
                c[j] = b[j]-2;
                less = true;
                tmp  = k-used-1;
                for(int l=j+1; l<=i; l++) {
                    if(a[l] == '9' && tmp) c[l] = '8';
                    else if(tmp) c[l] = '9';
                    else c[l] = a[l];
                    tmp--;
                }
                kon = true;
                break;
             } else { //Jeżeli nie ma potrzeby zmieniać
                tmp  = k-used;
                less = true;
                c[j] = b[j]-1;
                auto it = pos.upper_bound(j); //Usuwamy wszystkie późniejsze akcje
                pos.erase(it,pos.end()); pos.erase(j);


                for(int l=j+1; l<=i; l++) {
                     if(a[l] != '9' && tmp) {
                        pos.insert(l);
                        c[l] = '9';
                        tmp--;
                     } else if(a[l] == '9' && tmp) {
                        if(a.length()-tmp != l) {
                          c[l] = a[l];
                          continue;
                        }
                        tmp--;
                        c[l] = '8';
                        pos.insert(l);
                     } else if(!tmp) c[l] = a[l];
                }
                kon = true;
                break;
             }
          } else { //Jak nie to na luzie zmieniamy
             c[j] = b[j]-1;
             less = true;
             auto it = pos.upper_bound(j); //Usuwamy wszystkie późniejsze akcje
             pos.erase(it,pos.end()); pos.insert(j);
             tmp = k-used-1;

             for(int l=j+1; l<=i; l++) {
                 if(a[l] != '9' && tmp) {
                     pos.insert(l);
                     c[l] = '9';
                     tmp--;
                 } else if(a[l] == '9' && tmp) {
                     if(a.length()-tmp != l) {
                       c[l] = a[l];
                       continue;
                     }
                     tmp--;
                     c[l] = '8';
                     pos.insert(l);
                 } else if(!tmp) c[l] = a[l];
             }
             kon = true;
             break;
          }
    }

    if(!kon) {
        c = "-1";
        return false;
    } else return true;
  }

  void slowWork() {
    tmp=k;
    less=false;
    pos.clear();

    for(int i=0; i<a.length(); i++) {
        if(a.length()-tmp == i) {
           if(!less) {
              if((a[i] == '0' && b[i] == '0') || (b[i] == '0' && tmp==1)) {
                 if(!backtrace(i)) break;
              } else { //Jeżeli jeszcze trzeba zmieniać ale nie ma problemu jeszcze
                 if(a[i] == b[i] || (i+1)==a.length()) {
                    if(a[i] == (b[i]-1)) {
                        if(a[i]-1 >= '0') {
                            c[i] = a[i]-1;
                            pos.insert(i);
                            tmp--;
                        } else if(!backtrace(i)) break;
                        less = true;
                    } else {
                        c[i] = b[i]-1;
                        pos.insert(i);
                        less = true;
                        tmp--;
                    }
                 } else {
                     c[i] = b[i];
                     pos.insert(i);
                     tmp--;
                 }
              }
           } else { //Jeżeli trzeba zmieniać, ale jesteśmy na zmniejszaniu
              if(a[i] == '9') c[i] = '8';
              else c[i] = '9';
              tmp--;
           }
        } else { //Jeżeli nie ma przymusu ze strony k
           if(!less) { //Jeżeli jesteśmy na równi
             if(tmp && a[i] != b[i]) {
                 c[i] = b[i];
                 pos.insert(i);
                 tmp--;
             } else if(!tmp) {
                 DEBUG printf("Wyzerowane na pozycji %d a[i]=%c b[i]=%c, a.length()=%d\n",i+1,a[i],b[i],a.length());
                 if(a[i] < b[i]) less = true;
                 else if(a[i] > b[i]) {
                    if(!backtrace(i)) break;
                 } else if(a[i] == b[i] && (i+1)==a.length()) {
                    DEBUG printf("Jestem tu\n");
                    if(!backtrace(i)) break;
                 }
             }
           } else { //Jeżeli jesteśmy na zmniejszaniu
              if(a[i] != '9' && tmp) {
                 pos.insert(i);
                 c[i] = '9';
                 tmp--;
              } else if(a[i] == '9') {
                 if(!tmp || a.length()-tmp != i) continue;
                 tmp--;
                 a[i] = '8';
                 pos.insert(i);
              }
           }

        }
    }

    return;
  }

  int main(void) {
     std::ios_base::sync_with_stdio(0);
     std::cin.tie(0);
     std::cout.tie(0);

     short int tests;
     std::cin >> tests;

     while(tests--) {
        std::cin >> a >> b >> k;
        c = a;

        //if(k==1) jednoK();
        //else
 slowWork();
        std::cout << c << "\n";
     }

     return 0;
  }
