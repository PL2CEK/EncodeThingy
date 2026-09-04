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
    PrintEncodedText(encode);
    Character poppedCharacter;
    RemoveCharacter(&encode, 1, &poppedCharacter);
    PrintEncodedText(encode);

    DestroyText(&encode);
    return 0;
}