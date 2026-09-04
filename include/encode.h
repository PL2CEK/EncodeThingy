#ifndef ENCODE_H
#define ENCODE_H

#include <stdbool.h>
typedef struct
{
    int TextData;
} Character;

struct EncodeThingy
{
    unsigned count;
    unsigned capacity;
    Character *elements;
};

enum CharacterValues
{
    DigitsStart = 1,
    DigitsCount = 10,
    LettersCount = 26,
    InvalidCharacter = 0,
};

enum NotVincesEncoding
{
    DigitsZero = DigitsStart,
    DigitsNine = DigitsStart + DigitsCount,
    LettersA,
    LettersZ = LettersA + LettersCount,
    LettersCapitalA,
    LettersCapitalZ = LettersCapitalA + LettersCount,
    Space,
    EndOfText,
};

enum
{
    MINIMUM_CAPACITY = 67,
};

bool ReserveTextSpace(struct EncodeThingy *encode, unsigned newcapacity);
void DestroyText(struct EncodeThingy *encode);
bool PushCharacter(struct EncodeThingy *encode, Character character);
bool PopCharacter(struct EncodeThingy *encode, Character *CharacterPop);
bool InsertCharacter(struct EncodeThingy *encode, unsigned index, Character character);
bool RemoveCharacter(struct EncodeThingy *encode, unsigned index, Character *CharacterPop);
bool IsDigit(Character character);
bool IsLetter(Character character);
void PrintEncodedText(struct EncodeThingy text);
Character EncodeCharacter(Character c_character);

#endif // ENCODE_H