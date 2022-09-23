#include <stdio.h>
int main()
{
    int i_1 = 5;
    float f_1 = i_1;
    printf("i_1 = %d, f_1 = %f\n", i_1, f_1);

    int i_2 = 37;
    float f_2 = *(float *)&i_2;
    printf("i_2 = %d, f_2 = %f\n", i_2, f_2);

    float f_3 = 7.0;
    short sh_3 = *(((short *)&f_3) + 1); // little endian-ის გამო რასაც float-ის დასაწყისში ველით რომ ეწერება, ბოლოში წერია. +1ით ფლოატის მეორე და პირველ ბაიტებზე ვდგებით.
    printf("f_3 = %f, sh_3 = %hd\n", f_3, sh_3);
}