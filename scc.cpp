/* 1.読み取り ("slim --nd -t ../../../cpn.lmn" による出力)
 * 2.字句解析・構文解析的な処理
 * 3.tarjanのアルゴリズムでsccグラフを計算
 * 4.書き出し (SCCグラフについての情報) */

/* とりあえず標準入力から読み取り、標準出力へ書き出す(リダイレクトを使う)
 * オプションで処理を分ける (-aオプションでSCCグラフについての情報をいろいろ出せるようにすることを考えている) */

#include <stdio.h>
#include <string.h>

int main(void) {
  char s[1024];
  int count=0, states;
  
/* 1,2
 * States読み取りの段階で状態数がわかるのでこれをもとに配列を用意
 * SCCグラフの計算はTransitionsによる状態ノード間のつながりの情報だけあればできるはず */
  do {
    fgets(s,1024,stdin); count++;
    //    fputs(s,stdout);
  } while (strncmp(s,"init",4)!=0);

  states = count-4;

  printf("%d\n",states);

  int path[states][states];
  int src,dst;
  
  scanf("%d", &src);
  scanf("::");
  scanf("%d", &path[src][dst]);

  printf("%d\n", path[src][dst]);
// 3

// 4
  
  return 0;
}
