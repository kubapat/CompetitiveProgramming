//Polish Olympiad in Informatics
//Task: Robocik
//Score: 40/100

#include <bits/stdc++.h>

 int main() {
     int n,x,y,curins=0,licznik=0;
     long long int curx=0,cury=0,t;
     short kierunek=0;

     scanf("%d %lld",&n,&t);
     int program[n];

     for(int i=0;i<n;i++) scanf("%d",&program[i]);

     scanf("%d %d",&x,&y);


     while(t>=0) {

       if((t-program[curins])<=1) {
          if(kierunek == 0 && curx == x && (y>=cury && y<=(cury+t))) licznik++;
          else if(kierunek == 1 && cury == y && (x>=curx && x<=(curx+t))) licznik++;
          else if(kierunek == 2 && curx == x && (y<=cury && y>=(cury-t))) licznik++;
          else if(kierunek == 3 && cury == y && (x<=curx && x>=(curx-t))) licznik++;
          break;

        } else {

           if(kierunek == 0 && curx == x && (y>=cury && y<(cury+program[curins])) ) licznik++;
           else if(kierunek == 1 && cury == y && (x>=curx && x<(curx+program[curins])) ) licznik++;
           else if(kierunek == 2 && curx == x && (y<=cury && y>(cury-program[curins])) ) licznik++;
           else if(kierunek == 3 && cury == y && (x<=curx && x>(curx-program[curins])) ) licznik++;

           if(kierunek == 0) cury+=program[curins];
           else if(kierunek == 1) curx+=program[curins];
           else if(kierunek == 2) cury-=program[curins];
           else curx-=program[curins];

           t -= (program[curins]+1);

           if(kierunek == 3) kierunek=0;
           else kierunek++;

           if((curins+1) == n) curins=0;
           else curins++;
         }
      }

      printf("%d",licznik);

      return 0;
 }
