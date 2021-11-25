//Polish Olympiad in Informatics
//Task: Układ scalony
//Score: 72/100

#include <stdio.h>
#include <algorithm>
#include <vector>
#define SIZE 1005
#define DEBUG if(0)

  bool visited[SIZE][SIZE];
  std::vector <std::pair<std::pair<int,int>,std::pair<int,int>>> conns,base,end;

  bool areAllConnected(int n, int m) {
      for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) if(!visited[i][j]) return false; //Jeśli nie wszystko podłączone

      return true;
  }

  bool sameOnSame(int n, int m, int k, bool even) {
       int x=1, y=1,cur=0,mid=(m/2);
       if(!even) mid=(m/2)+1;

       for(int i=1; i<=mid; i++) {
            y=i;
            if(i != mid) {
               base.push_back({{x,y},{x,y+1}});
               cur++;
            }
            visited[x][y] = true;
       }

       for(int i=1; i<=n; i++) {
            x=i;
            if(i != n) {
               base.push_back({{x,y},{x+1,y}});
               cur++;
            }
            visited[x][y] = true;
       }

       for(int i=y; i<=m; i++) {
            y=i;
            if(i != m) {
               base.push_back({{x,y},{x,y+1}});
               cur++;
            }
            visited[x][y] = true;
       }

       if(k<cur) return false; //Jeśli krótsze od najkrótszej ścieżki to nie ma opcji

       int left = k-cur,l,r;
       if(left%2 == 0) { //Podział na ilość połączeń do dołączenia
           l = left/2;
           r = left/2;
       } else {
           l = (left/2)+1;
           r = left/2;
       }

       x=1,y=1;
       bool dir=true; //true - dół, false - góra
       while(l) { //Wydłużanie po lewej stronie
         bool del = false;
         if(dir) { //Jeżeli idziemy w dół
            if(x == n) {
               if(visited[x][y+1]) break;
               conns.push_back({{x,y+1},{x,y}});
               y++;
               dir = false, del = true;
               visited[x][y] = true;
               l--;
            } else {
               conns.push_back({{x+1,y},{x,y}});
               x++;
               visited[x][y] = true;
               l--, del=true;
            }
         } else { //Jeżeli idziemy w górę
            if(visited[x-1][y]) { //
               if(visited[x][y+1]) break;
               conns.push_back({{x,y+1},{x,y}});
               y++;
               dir = true, del=true;
               visited[x][y] = true;
               l--;
            } else {
               conns.push_back({{x-1,y},{x,y}});
               x--;
               visited[x][y] = true;
               l--, del=true;
            }
         }

         if(!del) break;
       }

       r += l;
       x=n,y=m;
       dir = false; //true - dół, false-góra
       while(r) { //Wydłużanie po prawej stronie
         bool del=true;
         if(dir) { //Jeżeli idziemy w dół
            if(visited[x+1][y]) {
               if(visited[x][y-1]) return false;
               end.push_back({{x,y},{x,y-1}});
               y--;
               dir = false, del=true;
               visited[x][y] = true;
               r--;
            } else {
               end.push_back({{x,y},{x+1,y}});
               x++;
               visited[x][y] = true;
               r--, del=true;
            }
         } else { //Jeżeli idziemy w górę
            if(x==1) {
               if(visited[x][y-1]) return false;
               end.push_back({{x,y},{x,y-1}});
               y--;
               dir = true, del=true;
               visited[x][y] = true;
               r--;
            } else {
               end.push_back({{x,y},{x-1,y}});
               x--;
               visited[x][y] = true;
               r--, del = true;
            }
         }

         if(!del) return false;
       } //W tym momencie mamy stworzoną najdłuższą ścieżkę

       std::reverse(conns.begin(),conns.end());
       conns.insert(conns.end(),base.begin(),base.end());
       conns.insert(conns.end(),end.begin(),end.end()); //Łączenie w posortowano i ciągłą ścieżkę

       int size = conns.size();
       bool was=false;
       for(int i=0; i<size; i++) {
          x = conns[i].first.first, y=conns[i].first.second;
          int len = std::min(i,size-i);
          if(!i) continue;
          if(x == 1 && y == mid) was = true;
          if(x == n && y > mid) was = false;

          if(!was) continue;

          int left=len,tmpX=x,tmpY=y;
          while(left) { //W lewo
            if(tmpY-1>=1 && !visited[tmpX][tmpY-1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY-1}});
                tmpY--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W górę
            if(tmpX-1>=1 && !visited[tmpX-1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX-1,tmpY}});
                tmpX--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W prawo
            if(tmpY+1<=m && !visited[tmpX][tmpY+1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY+1}});
                tmpY++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W dół
            if(tmpX+1<=n && !visited[tmpX+1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX+1,tmpY}});
                tmpX++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          x = conns[i].second.first, y = conns[i].second.second;
       }

       size = conns.size();
       for(int i=0; i<size; i++) {
          x = conns[i].first.first, y=conns[i].first.second;
          int len = std::min(i,size-i);
          if(!i) continue;

          int left=len,tmpX=x,tmpY=y;
          while(left) { //W lewo
            if(tmpY-1>=1 && !visited[tmpX][tmpY-1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY-1}});
                tmpY--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W górę
            if(tmpX-1>=1 && !visited[tmpX-1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX-1,tmpY}});
                tmpX--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W prawo
            if(tmpY+1<=m && !visited[tmpX][tmpY+1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY+1}});
                tmpY++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W dół
            if(tmpX+1<=n && !visited[tmpX+1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX+1,tmpY}});
                tmpX++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          x = conns[i].second.first, y = conns[i].second.second;
       }

       return areAllConnected(n, m);
  }

  bool oddOnEven(int n, int m, int k) {
       int x=1, y=1,cur=0;

       for(int i=1; i<=(n/2)+1; i++) {
            x=i;
            if(i != (n/2)+1) {
               base.push_back({{x,y},{x+1,y}});
               cur++;
            }
            visited[x][y] = true;
       }

       for(int i=1; i<=m; i++) {
            y=i;
            if(i != m) {
               base.push_back({{x,y},{x,y+1}});
               cur++;
            }
            visited[x][y] = true;
       }

       for(int i=x; i<=n; i++) {
            x=i;
            if(i != n) {
               base.push_back({{x,y},{x+1,y}});
               cur++;
            }
            visited[x][y] = true;
       }

       if(k<cur) return false; //Jeśli krótsze od najkrótszej ścieżki to nie ma opcji

       int left = k-cur,l,r;
       if(left%2 == 0) { //Podział na ilość połączeń do dołączenia
           l = left/2;
           r = left/2;
       } else {
           l = (left/2)+1;
           r = left/2;
       }

       x=1,y=1;
       bool dir=true; //true - prawo, false - lewo
       while(l) { //Wydłużanie po lewej stronie
         bool del = false;
         if(dir) { //Jeżeli idziemy w prawo
            if(y == m) {
               if(visited[x+1][y]) break;
               conns.push_back({{x+1,y},{x,y}});
               x++;
               dir = false, del = true;
               visited[x][y] = true;
               l--;
            } else {
               conns.push_back({{x,y+1},{x,y}});
               y++;
               visited[x][y] = true;
               l--, del=true;
            }
         } else { //Jeżeli idziemy w lewo
            if(visited[x][y-1]) {
               if(visited[x+1][y]) return false;
               conns.push_back({{x+1,y},{x,y}});
               x++;
               dir = true, del=true;
               visited[x][y] = true;
               l--;
            } else {
               conns.push_back({{x,y-1},{x,y}});
               y--;
               visited[x][y] = true;
               l--, del=true;
            }
         }

         if(!del) break;
       }

       r += l;
       x=n,y=m;
       dir = false; //true - prawo, false - lewo
       while(r) { //Wydłużanie po prawej stronie
         bool del=true;
         if(dir) { //Jeżeli idziemy w prawo
            if(visited[x][y+1]) {
               if(visited[x-1][y]) return false;
               end.push_back({{x,y},{x-1,y}});
               x--;
               dir = false, del=true;
               visited[x][y] = true;
               r--;
            } else {
               end.push_back({{x,y},{x,y+1}});
               y++;
               visited[x][y] = true;
               r--, del=true;
            }
         } else { //Jeżeli idziemy w lewo
            if(y==1) {
               if(visited[x-1][y]) return false;
               end.push_back({{x,y},{x-1,y}});
               x--;
               dir = true, del=true;
               visited[x][y] = true;
               r--;
            } else {
               end.push_back({{x,y},{x,y-1}});
               y--;
               visited[x][y] = true;
               r--, del = true;
            }
         }

         if(!del) return false;
       } //W tym momencie mamy stworzoną najdłuższą ścieżkę

       std::reverse(conns.begin(),conns.end());
       conns.insert(conns.end(),base.begin(),base.end());
       conns.insert(conns.end(),end.begin(),end.end()); //Łączenie w posortowano i ciągłą ścieżkę

       int size = conns.size();
       bool was=false;
       for(int i=0; i<size; i++) {
          x = conns[i].first.first, y=conns[i].first.second;
          int len = std::min(i,size-i);
          if(!i) continue;
          if(x == (n/2)+1 && y == 1) was = true;
          if(x > (n/2)+1 && y == m) was = false;

          if(!was) continue;

          int left=len,tmpX=x,tmpY=y;
          while(left) { //W lewo
            if(tmpY-1>=1 && !visited[tmpX][tmpY-1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY-1}});
                tmpY--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W górę
            if(tmpX-1>=1 && !visited[tmpX-1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX-1,tmpY}});
                tmpX--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W prawo
            if(tmpY+1<=m && !visited[tmpX][tmpY+1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY+1}});
                tmpY++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W dół
            if(tmpX+1<=n && !visited[tmpX+1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX+1,tmpY}});
                tmpX++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          x = conns[i].second.first, y = conns[i].second.second;
       }

       size = conns.size();
       for(int i=0; i<size; i++) {
          x = conns[i].first.first, y=conns[i].first.second;
          int len = std::min(i,size-i);
          if(!i) continue;

          int left=len,tmpX=x,tmpY=y;
          while(left) { //W lewo
            if(tmpY-1>=1 && !visited[tmpX][tmpY-1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY-1}});
                tmpY--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W górę
            if(tmpX-1>=1 && !visited[tmpX-1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX-1,tmpY}});
                tmpX--;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W prawo
            if(tmpY+1<=m && !visited[tmpX][tmpY+1]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX,tmpY+1}});
                tmpY++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          left=len,tmpX=x,tmpY=y;
          while(left) { //W dół
            if(tmpX+1<=n && !visited[tmpX+1][tmpY]) {
                left--;
                conns.push_back({{tmpX,tmpY},{tmpX+1,tmpY}});
                tmpX++;
                visited[tmpX][tmpY] = true;
            } else break;
          }

          x = conns[i].second.first, y = conns[i].second.second;
       }

       return areAllConnected(n, m);
  }

  void outputConns() {
    printf("TAK\n");
    for(auto el : conns) {
       printf("%d %d %d %d\n",el.first.first,el.first.second,el.second.first,el.second.second);
    }

    DEBUG printf("SIZE: %d",conns.size());
  }

  int main(void) {
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);

    if(k > (n*m-1)) {
       printf("NIE");
       return 0;
    }

    // Rozmiar 1x1
    if(n == 1 && m == 1) {
        if(!k) printf("TAK");
        else printf("NIE");
        return 0;
    }

    // Rozmiar 2x2
    if(n == 2 && m == 2) {
        if(k == 3) printf("TAK\n1 1 1 2\n1 1 2 1\n2 1 2 2");
        else printf("NIE");
        return 0;
    }

    //Rozmiar 1xm
    if(n == 1) {
        if(k != m-1) {
            printf("NIE");
            return 0;
        }
        printf("TAK\n");
        for(int i=1; i<m; i++) printf("1 %d 1 %d\n",i,i+1);
        return 0;
    }

    //Rozmiar nx1
    if(m == 1) {
        if(k != n-1) {
           printf("NIE");
           return 0;
        }
        printf("TAK\n");
        for(int i=1; i<n; i++) printf("%d 1 %d 1\n",i,i+1);
        return 0;
    }

    if(n%2 == 0 && m%2 == 0) {
       bool res = sameOnSame(n,m,k,true);
       if(!res) printf("NIE");
       else outputConns();
    } else if((n%2 && m%2) || (n%2 == 0 && m%2)) {
       bool res = sameOnSame(n,m,k,false);
       if(!res) printf("NIE");
       else outputConns();
    } else if(n%2 && m%2 == 0) {
       bool res = oddOnEven(n,m,k);
       if(!res) printf("NIE");
       else outputConns();
    }

    return 0;
  }
