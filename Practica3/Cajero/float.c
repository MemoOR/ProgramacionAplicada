#include<stdio.h>
#include<string.h>

int main()
{
  char str[100] ="4.0800" ;
  const char s[2] = "-";
  char *token;
  float x;
  /* get the first token */
  token = strtok(str, s);
  sscanf(token,"%f",&x);
  printf( " %f",x+5 );

  return 0;
}
