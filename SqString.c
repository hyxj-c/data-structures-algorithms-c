#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

#define MAXSIZE 255

typedef struct {
  char ch[MAXSIZE + 1];
  int length;
} SqString;

// 初始化字符串
Status initString_Sq(SqString *Str) {
  Str->length = 0;
  return OK;
}

// 尾部插入字符
Status insert(SqString *Str, char c) {
  if (Str->length >= MAXSIZE)
  {
    return ERROR;
  }
  Str->ch[++Str->length] = c;
  return OK;
}

// 匹配字串在主串中的位置BF算法
int index_BF(SqString S, SqString T, int pos) {
  int i = pos, j = 1;
  while (i <= S.length && j <= T.length)
  {
    if (S.ch[i] == T.ch[j])
    {
      i++;
      j++;
    } else {
      i = i - j + 2;
      j = 1;
    }
  }
  
  if (j > T.length)
  {
    // 匹配成功
    return i - T.length;
  } else {
    return -1;
  }
}

// 匹配字符串在主串中的位置KMP算法
int index_KMP(SqString S, SqString T, int pos) {
  int next[T.length + 1];
  getNextArr(T, next);

  int i = pos, j = 1;
  while (i <= S.length && j <= T.length)
  {
    if (j == 0 || S.ch[i] == T.ch[j])
    {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }

  if (j > T.length)
  {
    return i - T.length;
  } else {
    return -1;
  }
}

// 获取KMP算法的next数组
void getNextArr(SqString S, int next[]) {
  int i = 1, j = 0;
  next[1] = 0;
  while (i < S.length)
  {
    if (j == 0 || S.ch[i] == S.ch[j])
    {
      next[++i] = ++j;
    } else {
      j = next[j];
    }
  }
}

void printStr(SqString Str) {
  for (int i = 1; i <= Str.length; i++)
  {
    printf("%c", Str.ch[i]);
  }
  printf("\n");
}

main() {
  SqString str;
  initString_Sq(&str);
  insert(&str, 'a');
  insert(&str, 'a');
  insert(&str, 'a');
  insert(&str, 'a');
  insert(&str, 'a');
  insert(&str, 'b');
  insert(&str, 'a');
  
  SqString subStr;
  initString_Sq(&subStr);
  insert(&subStr, 'a');
  insert(&subStr, 'a');
  insert(&subStr, 'a');
  insert(&subStr, 'b');
 
  printStr(str);
  printStr(subStr);
  
  printf("pos:%d\n", index_BF(str, subStr, 1));
  SqString ts;
  initString_Sq(&ts);
  insert(&ts, 'a');
  insert(&ts, 'b');
  insert(&ts, 'a');
  insert(&ts, 'b');
  insert(&ts, 'a');
  insert(&ts, 'c');
  printf("pos:%d\n", index_KMP(str, ts, 1));
}