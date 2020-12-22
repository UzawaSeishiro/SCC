/* 1.読み取り ("slim --nd -t ../../../cpn.lmn" による出力)
 * 2.字句解析・構文解析的な処理
 * 3.tarjanのアルゴリズムでsccグラフを計算
 * 4.書き出し (SCCグラフについての情報) */

/* とりあえず標準入力から読み取り、標準出力へ書き出す(リダイレクトを使う)
 * オプションで処理を分ける (-aオプションでSCCグラフについての情報をいろいろ出せるようにすることを考えている) */

#include <stdio.h>
#include <string.h>

int main(void) {
  char s[1024],ch;
  int count=0, states;
  
  do {
    fgets(s,1024,stdin); count++;
  } while (strncmp(s,"init",4)!=0);

  states = count-4;

  int transition[states][states];
  int src,dst,i,j;

  for (i=0; i<states; i++) {
    for (j=0; j<states; j++) {
      transition[i][j] = 0;
    }
  }
  
  for (i=0; i<states; i++) {
    scanf("%d::",&src);
    if (scanf("%d",&dst) == 0) continue;
    j=0;
    transition[src-1][j]=dst;
    while ((ch = getchar()) == ',') {
      scanf("%d",&dst);
      j++;
      transition[src-1][j] = dst;
    }
  }

  for (i=0; i<states; i++) {
    printf("%d",transition[i][0]);
    for (j=1; j<states; j++) {
      printf(" %d",transition[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}
