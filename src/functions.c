#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"

bool ReserveTextSpace(struct EncodeThingy *encode, unsigned newcapacity)
{
    assert(encode != 0);
    if (newcapacity < MINIMUM_CAPACITY)
        newcapacity = MINIMUM_CAPACITY;
    if (newcapacity < encode->capacity)
        return true;
    Character *elements = realloc(encode->elements, newcapacity * sizeof(Character));
    if (!elements)
        return false; // out of memory
    encode->elements = elements;
    encode->count = 0;
    encode->capacity = newcapacity;
    return true;
}

void DestroyText(struct EncodeThingy *encode)
{
    if (encode != 0 && encode->elements != 0)
    {
        free(encode->elements);
        encode->elements = 0;
        encode->count = 0;
        encode->capacity = 0;
        // memset(encode, 0, sizeof(*encode));
        // simple as that ez
    }
}

bool PushCharacter(struct EncodeThingy *encode, Character character)
{
    assert(encode != 0);
    if (encode->count >= encode->capacity)
        if (!ReserveTextSpace(encode, encode->capacity * 2))
            return false; // out of memory
    encode->elements[encode->count++] = character;

    return true;
}

bool PopCharacter(struct EncodeThingy *encode, Character *CharacterPop)
{
    assert(encode != 0);
    if (encode->count == 0)
        return false; // nothing to pop
    *CharacterPop = encode->elements[encode->count--];
    return true;
}

bool InsertCharacter(struct EncodeThingy *encode, unsigned index, Character character)
{
    assert(encode != 0);
    if (index > encode->count)
        return false; // invalid index
    if (encode->count >= encode->capacity)
        if (!ReserveTextSpace(encode, encode->capacity * 2))
            return false; // out of memory
    if (index < encode->count)
        encode->elements[encode->count] = character;
    encode->elements[index] = character;
    encode->count++;
    return true;
}

bool RemoveCharacter(struct EncodeThingy *encode, unsigned index, Character *CharacterPop)
{
    assert(encode != 0);
    if (index >= encode->count)
        return false; // invalid index
    *CharacterPop = encode->elements[index];
    encode->elements[index] = encode->elements[encode->count - 1];
    encode->count--;
    return true;
}

bool IsDigit(Character character)
{
    return character.TextData >= DigitsStart && character.TextData < DigitsNine;
}

bool IsLetter(Character character)
{
    return character.TextData >= LettersA && character.TextData < LettersCapitalZ;
}

Character EncodeCharacter(Character c_character)
{
    // Implementation for encoding text
    if (IsDigit(c_character))
        c_character.TextData += 100;
    else if (IsLetter(c_character))
        c_character.TextData += 200;
    else
        c_character.TextData = InvalidCharacter;
    return c_character;
}

struct EncodeThingy EncodeText(const char *cstring)
{
    struct EncodeThingy result = {0};
    int length = strlen(cstring);
    for (int index = 0; index < length; index++)
    {
        char currentChar = cstring[index];
        PushCharacter(&result, EncodeCharacter((Character){.TextData = currentChar}));
    }
    return result;
}

void PrintEncodedText(struct EncodeThingy text)
{
    for (unsigned i = 0; i < text.count; i++)
    {
        printf("- characters[%u] = %d\n", i, text.elements[i].TextData);
    }
    printf("\n");
}
