#include "encode.h"
#include <stdio.h>

int main(int ac, char **av)
{
    struct EncodeThingy encode = {0};
    if (!ReserveTextSpace(&encode, 10))
    {
        printf("vince this program sucks ass \n");
        return 1;
    }
    PushCharacter(&encode, (Character){.TextData = 7});
    PushCharacter(&encode, (Character){.TextData = 145});
    PushCharacter(&encode, (Character){.TextData = 42});

    printf("encode list :\n");
    for (unsigned i = 0; i < encode.count; i++)
    {
        printf("- characters[%u] = %d\n", i, encode.elements[i].TextData);
    }
    Character poppedCharacter;
    RemoveCharacter(&encode, 1, &poppedCharacter);
    printf("encode list after kicing 1:\n");
    for (unsigned i = 0; i < encode.count; i++)
    {
        printf("- characters[%u] = %d\n", i, encode.elements[i].TextData);
    }

    DestroyText(&encode);
    return 0;
}