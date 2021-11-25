//Polish Olympiad in Informatics
//Task: Drzewo Czwórkowe
//Score: 24/100


#include <iostream>
#include <vector>
#include <cmath>
#define DEBUG if(0)
#define LL long long int
#define MOD 1000000007
#define SIZE 1500

  bool plansza[SIZE][SIZE];
  std::pair <int,int> tab[SIZE][SIZE];
  LL ile[SIZE][SIZE];

  std::pair <int,int> Find(std::pair<int,int> pos) {
     if(tab[pos.first][pos.second] == pos) return pos;
     return Find(tab[pos.first][pos.second]);
  }

  void Union(std::pair <int,int> a, std::pair <int,int> b) { //Łączy kwadraty
     DEBUG printf("Łączymy pozycję {%d,%d} z {%d,%d}\n",a.first,a.second,b.first,b.second);
     auto fa = Find(a);
     auto fb = Find(b);

     if(fa == fb) return;
     else if(ile[fa.first][fa.second] > ile[fb.first][fb.second]) {
          tab[fb.first][fb.second] = fa;
          ile[fa.first][fa.second] += ile[fb.first][fb.second];
     } else {
          tab[fa.first][fa.second] = fb;
          ile[fb.first][fb.second] += ile[fa.first][fa.second];
     }
  }

  std::string tree;
  int m;

  //Zwraca pozycję lewego górnego rogu dla następnego sektora w danym poziomie
  std::pair <LL,LL> nextPos(LL curX, LL curY, int curTurn, int level) {
         LL len = (LL)1<<(LL)level;
         if(curTurn == 1) return {curX+len,curY};
         else if(curTurn == 2) return {curX-len,curY+len};
         return {curX+len,curY};
  }

  //Konwertuje rekurencyjnie stringa do drzewa
  int read(int level, int turn, int pos, std::pair <LL,LL> left) {
      DEBUG printf("Pozycja %d w słowie, Pozycja %d na poziomie %d w (%lld,%lld)\n",pos+1,turn,level,left.first,left.second);
      if(pos == (int)tree.length()) return (int)tree.length();
      else if(tree[pos] == '0') {
          if(level == m || turn == 4) return pos;
          else if(turn != 4) return read(level,turn+1,pos+1,nextPos(left.first,left.second,turn,level));
      } else if(tree[pos] == '1') {
          int len = 1<<level;
          DEBUG printf("Zamaluj w %lld %lld do %lld %lld\n",left.first,left.second,left.first+len-1,left.second+len-1);
          for(int y=left.second; y<=left.second+len-1; y++) {
             for(int x=left.first; x<=left.first+len-1; x++) {
                   plansza[x][y] = true;
             }
          }
          if(level == m || turn == 4) return pos;
          else if(turn != 4) return read(level,turn+1,pos+1,nextPos(left.first,left.second,turn,level));
      } else {
            int lastPos = read(level-1,1,pos+1,left);
            if(level == m || turn == 4) return lastPos;
            else if(turn != 4) return read(level,turn+1,lastPos+1,nextPos(left.first,left.second,turn,level));
      }

      return pos;
  }

  int main(void) {
     std::ios_base::sync_with_stdio(false);
     std::cin.tie(0);
     std::cout.tie(0);

     std::cin >> m >> tree;

     read(m,1,0,{0,0});
     LL size=(LL)1<<(LL)m;

     for(int y=0; y<size; y++) {
       for(int x=0; x<size; x++) {
           tab[x][y] = {x,y};
           if(plansza[x][y]) ile[x][y] = 1;
           else ile[x][y] = 0;
        }
     }

     for(int y=0; y<size; y++) {
        for(int x=0; x<size; x++) {
             DEBUG {
                 if(plansza[x][y]) printf("#");
                 else printf(".");
             }

             if(!plansza[x][y]) continue;
             if(x>0 && plansza[x-1][y]) Union({x,y},{x-1,y});
             if(y>0 && plansza[x][y-1]) Union({x,y},{x,y-1});
             if(plansza[x+1][y]) Union({x,y},{x+1,y});
             if(plansza[x][y+1]) Union({x,y},{x,y+1});
        }

        DEBUG printf("\n");
     }

     int licznik=0;
     LL max=0;
     for(int x=0; x<size; x++) {
       for(int y=0; y<size; y++) {
          if(Find({x,y}) != std::make_pair(x,y) || !plansza[x][y]) continue;

          licznik++;
          max = std::max(max,ile[x][y]);
       }
     }

     printf("%d\n%lld",licznik,max%MOD);
     return 0;
  }
