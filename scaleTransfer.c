#include <stdio.h>

//进制转换,十六进制使用大写
void transfer(int m, int n, char* num)
{
    int i = 0;
    char str[16] = {0};
    char* s = &str[0];
    while(*num != '\0')
    {
        //转为十进制
        if(*num >= 'A')
            i = i*m + *num++ - 'A' + 10;
        else if(*num > '0')
            i = i*m + *num++ - '0';     
        else 
            return;
    }
    //反向转为n进制
    while(i)
    {
        *s++ = i%n < 10 ? (i%n + '0') : (i%n - 10 + 'A');
        i /= n;
    }
    *s-- = '\0';  //注意s多了一次++操作
    char* s1 = &str[0];
    char c;
    //逆反回来
    while(s > s1)
    {
        c = *s;
        *s-- = *s1;
        *s1++ = c;
    }
    printf("after transfer: %s\n",str);
    printf("after transfer: %d\n",atoi(str));
}

int main(int argc, char* args[])
{
   printf("num: %s\n",args[3]); 
   transfer(atoi(args[1]), atoi(args[2]), args[3]);
   return 0;
}
