//Polish Olympiad in Informatics
//Task: Największa wspólna wielokrotność
//Score: 100/100

#include <stdio.h>
#include <algorithm>
#include <cmath>
#define SIZE 5000000
const long long int MAXSTART = 2097151;
  std::pair <long long int,std::pair<int,int>> przedzialy[SIZE];


  int bin_s(int l, int p, long long int s) {
    int mid=(l+p)/2;

    while(l<p) {
      mid=(l+p)/2;
      if(l >= p) return l;
      else if(przedzialy[mid].first >= s) p=mid;
      else l=mid+1;
    }

    return l;
  }


  int main(void) {
    int cur=0;
    for(long long int i=1; i<=MAXSTART; i++) {
      if(i == 2) continue;

      long long nww=i*(i+1);
      for(long long int end=i+2; end<(i+100); end++) {
          nww = (nww/std::__gcd(nww,end))*end;
          if(nww < 0) break;

          przedzialy[cur++] = {nww,{i,end}};
      }
    }
    std::sort(przedzialy,przedzialy+cur);

    int tests;
    scanf("%d",&tests);

    while(tests--) {
      long long int k;
      scanf("%lld",&k);

      if(k%2) { //Jak nieparzysta
         printf("NIE\n");
         continue;
       }
       long long int res = bin_s(0,cur-1,k);
       if(res != -1 && przedzialy[res].first == k) { //Jeżeli przedział nieregularny
         for(int i=res-1; i>=0; i--) {
             if(przedzialy[i].first == k) res=i;
             else break;
         }
         printf("%d %d\n",przedzialy[res].second.first,przedzialy[res].second.second);
         continue;
       }
       long long int delta = 4*k + 1;
       long long int pierw = sqrtl(delta);
       if(pierw*pierw != delta) printf("NIE\n"); //Jeżeli nie pierwiastek całkowity
       else {
         long long int res = (pierw-1)/2;
         if(res*(res+1) == k) printf("%lld %lld\n",res,res+1); //Jak n(n+1) = nww
         else printf("NIE\n");
       }
   }

   return 0;
 }
