#ifndef STRINGIMP_STRLIB_H
#define STRINGIMP_STRLIB_H

// Dependencies

#include <math.h>                   // pow, ceil
#include <stdlib.h>                 // itoa, srand, rand, calloc, malloc, free, realloc
#include <stdio.h>                  // stdin, fgets, printf
#include <time.h>                   // time
#include <string.h>                 // strstr


// Constants

#define STR_MAX_LENGTH 1000000      // 10^6

#define SEARCHMODE_STD 0            // Standard searchmode for StrSearchAll
#define SEARCHMODE_START 1          // Searchmode for StrSearchAll, that only returns start indices
#define SEARCHMODE_END 2            // Searchmode for StrSearchAll, that only returns end indices
#define SEARCHALL_OCCURRENCES 128   // The amount of occurrences, StrSearchAll can find

#define SIGNMODE_US 0               // Binary Unsigned Representation
#define SIGNMODE_SBIT 1             // Binary Sign Bit Representation
#define SIGNMODE_S2C 2              // Binary Twos Complement Representation


// Datatypes

typedef char *str;      // Simple String
typedef char **str_arr; // 1D-String Array


/// In case you're wondering: DMA stands for 'Dynamic Memory Allocation'


// Function Prototypes
// Total amount of functions in strlib.h: 48 (48 defined)
int StrLength(str a);
str StrMerge(str a, str b);                                 // DMA
int StrMatch(str a, str b);
str StrReverse(str a);                                      // DMA
int StrFind(str a, str b);
int *StrSearchFirst(str a, str b);                          // DMA
float StrCompare(str a, str b);
str StrReplaceAll(str base, str what, str with);            // DMA
str StrReplaceFirst(str base, str what, str with);          // DMA
str ToUpper(str a);                                         // DMA
str ToLower(str a);                                         // DMA
str ToTitle(str a);                                         // DMA
int StrCount(str base, str what);
str StrTrim(str a);                                         // DMA
int Str2Int(str a);
str Int2Str(int a);                                         // DMA
float Str2Float(str a);
str Float2Str(float a);                                     // DMA
str StrSplitFirst(str base, str where, int half);           // DMA
str StrChangeAt(str base, int idx, char newChar);           // DMA
str StrRemoveAt(str base, int idx);                         // DMA
str StrSplitAt(str base, int idx, int fraction);            // DMA
int *StrSearchAll(str base, str what, int searchMode);      // DMA not coming soon :)
str StrZip(str a, str b, int interval);                     // DMA
str StrOptimizeSize(str a);                                 // DMA
str StrSubstituteFirst(str base, char what, char with);     // DMA
str StrSubstituteAll(str base, char what, char with);       // DMA
str StrEcho(str a, int echoCount);                          // DMA
str StrRandString(int length, int excludeWhitespaces);      // DMA
void StrRandStringInit();
str StrInput(str message);                                  // DMA
int IsNumeric(str a);
int IsAlphabetic(str a);
int IsAlphaNumeric(str a);
int IsSymbolic(str a);
int IsWhitespace(str a);
int IsUpper(str a);
int IsLower(str a);
int IsTitle(str a);
str StrMuteFirst(str base, str what, char with);            // DMA
str StrMuteAll(str base, str what, char with);              // DMA
str StrMuteEverything(str base, char with, int muteWhitespaces);   // DMA
str StrInsertAt(str base, int idx, str what);               // DMA
int IsBinary(str bin);
int IsHexadecimal(str hex);
int IsOctal(str oct);
int Bin2Dec(str bin, int signMode);
str Dec2Bin(int dec, int signMode);                         // DMA
str CaseInvert(str a);                                      // DMA


//Functions

/**
 * Finds the length of a string
 * @param a ... String to get the length of
 * @return  Length of the string
 */
int StrLength(str a){
    int len = 0;
    while (*a != '\0'){
        len++;
        *a++;
    }
    return len;
}


/**
 * Concatenates two strings ( DMA )
 * @param a ... base string
 * @param b ... string to be appended to the base string
 * @return  'a' and 'b' concatenated
 */
str StrMerge(str a, str b){
    str newStr = (str) calloc(StrLength(a)+StrLength(b), 1);
    int idx = 0;
    for (int i = 0; i < StrLength(a); i++){
        newStr[i] = a[i];
        idx++;
    }
    for (int i =0 ;i < StrLength(b); i++){
        newStr[i+idx] = b[i];
    }
    idx += StrLength(b);
    newStr[idx] = '\0';
    newStr = realloc(newStr, StrLength(newStr));
    return newStr;
}

/**
 * Checks if two strings are identical
 * @param a ... first string
 * @param b ... second string
 * @return True(1) if 'a' equals 'b' , False(0) if 'a' does not equal 'b'
 */
int StrMatch(str a, str b){
    int match = 0;
    for (int i =0; i < StrLength(a); i++){
        if (a[i] == b[i]){
            match++;
        }
    }
    if (StrLength(a) != StrLength(b) || match != StrLength(a)){
        return 0;
    }
    return 1;
}

/**
 * Reverts the passed string ( DMA )
 * @param a ... string to be reverted
 * @return The reverted string
 */
str StrReverse(str a) {
    str revStr = (str) calloc(StrLength(a), 1);
    int j = 0;
    for (int i = StrLength(a)-1; i>=0; i--){
        revStr[j] = a[i];
        j++;
    }
    return revStr;
}

/**
 * Checks if substring is in base string
 * @param a ... base string
 * @param b ... substring
 * @return True(1) if 'b' in 'a', False(0) if 'b' not in 'a'
 */
int StrFind(str a, str b){
    int match = 0;
    int idx = 0;
    for (int i = 0; i < StrLength(a); i++){
        if (a[i] == b[idx] || (i == StrLength(a)-2 && idx > 0)){
            idx++;
        }
        else{
            idx=0;
        }
        if (idx == StrLength(b)){
            match++;
            break;
        }
    }
    return match;
}

/**
 * Gets the start and end index of b in a
 * @param a ... base string
 * @param b ... substring
 * @return The start and end index of 'b' in 'a', returns {-1,-1} if 'b' was not found in 'a'.
 */
int *StrSearchFirst(str a, str b){
    int *idxs = (int *) calloc(2, 4);
    if (StrLength(b) > StrLength(a)){
        idxs[0] = -1;
        idxs[1] = -1;
        return idxs;
    }
    str res = strstr(a, b);
    if (res == NULL){
        idxs[0] = -1;
        idxs[1] = -1;
        return idxs;
    }
    int startIdx = -1;
    int endIdx = -1;
    startIdx = StrLength(a) - StrLength(res);
    endIdx = startIdx + StrLength(b) - 1;
    idxs[0] = startIdx;
    idxs[1] = endIdx;
    return idxs;
}

/**
 * Compares a to b
 * @param a ... first string
 * @param b ... second string
 * @return Percentage that 'a' and 'b' match as a float
 */
float StrCompare(str a, str b){
    float equality;
    int matches = 0;
    int length;
    for (int i = 0; i < StrLength(a); i++){
        if (a[i] == b[i]){
            matches++;
        }
    }
    length = StrLength(a) > StrLength(b) ? StrLength(a) : StrLength(b);
    equality = (float)matches / (float)length;
    equality *= 100;
    return equality;
}

/**
 * replaces every occurence of 'what' in 'base' with 'with' ( DMA )
 * @param base ... base string
 * @param what ... substring
 * @param with ... new substring
 * @return ... Modified version of the base string
 */
 str StrReplaceAll(str base, str what, str with){
     int baseLen = StrLength(base);
     int withLen = StrLength(with);
     int whatLen = StrLength(what);
     str newStr = (str) calloc(baseLen, 1);
     for (int i = 0; i < baseLen; i++){
         newStr[i] = base[i];
     }
     newStr[baseLen] = 0;
     int newIdx = 0;
     int withIdx = 0;
     for (int i = 0; i < baseLen; i++){
         int *idxs_r = StrSearchFirst(base, what);
         int idxs[] = {idxs_r[0], idxs_r[1]};
         if (idxs[0] < 0){
             break;
         }
         for (int j = idxs[0]; j <= idxs[1]; j++){
             if (with[withIdx] == 0){
                 ;
             }
             else{
                 newStr[j] = with[withIdx];
                 withIdx++;
             }
         }
         if (withLen < whatLen){
             if (withLen == 1){
                 newStr[idxs[1] - withLen] = 0;
             }
             else{
                 newStr[idxs[1]] = 0;
             }
         }
     }
     return newStr;
 }

/**
 * replaces the first occurence of 'what' in 'base' with 'with' ( DMA )
 * @param base ... base string
 * @param what ... substring
 * @param with ... new substring
 * @return ... Modified version of the base string
 */
str StrReplaceFirst(str base, str what, str with){
    str newBase = (str) calloc(StrLength(base)+1, 1);
    strcpy(newBase, base);
    str newWith = (str) calloc(StrLength(with)+1, 1);
    strcpy(newWith, with);

    int *idxs = StrSearchFirst(base, what);
    int start = idxs[0];
    int end = idxs[1];
    if (idxs[0]  < 0){
        return base;
    }
    str newStr = (str) calloc(StrLength(base) + StrLength(with) - StrLength(what) + 1, 1);
    int idx = 0;
    for (int i = 0; i < start; i++){
        newStr[idx] = newBase[i];
        idx++;
    }
    newStr = StrMerge(newStr, newWith);
    idx += StrLength(with);
    for (int i = end+1; i < StrLength(base); i++){
        newStr[idx] = newBase[i];
        idx++;
    }
    return newStr;
}

/**
 * Turns all lowercase characters into uppercase ones
 * @param a ... string to turn to uppercases
 * @return String with only uppercases
 */
str ToUpper(str a){
    str newStr = (str) calloc(StrLength(a), 1);
    for (int i = 0; i < StrLength(a); i++){
        newStr[i] = a[i] >= 97 && a[i] <= 122 ? a[i] - 32 : a[i];
    }
    return newStr;
}

/**
 * Turns all uppercase characters into uppercase ones
 * @param a ... string to turn to lowercases
 * @return String with only lowercases
 */
str ToLower(str a){
    str newStr = (str) calloc(StrLength(a), 1);
    for (int i = 0; i < StrLength(a); i++){
        newStr[i] = a[i] >= 65 && a[i] <= 90 ? a[i] + 32 : a[i];
    }
    return newStr;
}

/**
 * Turns every character after a whitespaces and the first character into uppercases, the rest will be lowercases
 * @param a ... string to turn into a title
 * @return String as a title
 */
str ToTitle(str a){
    str newStr = (str) calloc(StrLength(a), 1);
    for (int i = 0; i < StrLength(a); i++){
        if (i == 0 || (a[i-1] <= 32 && a[i-1] > 0))
            newStr[i] = a[i] >= 97 && a[i] <= 122 ? a[i] - 32 : a[i];
        else
            newStr[i] = a[i] >= 65 && a[i] <= 90 ? a[i] + 32 : a[i];
    }
    return newStr;
}

/**
 * Finds the amount of occurrences of 'what' in 'base'
 * @param base ... base string
 * @param what ... substring
 * @return Amount of occurrences of 'what' in 'base'
 */
int StrCount(str base, str what){
    int baseLen = StrLength(base);
    int whatLen = StrLength(what);
    int matches = 0;
    int idx = 0;
    for (int i = 0; i < baseLen; i++){
        if (base[i] == what[idx])
            idx++;
        else
            idx = 0;
        if (idx == whatLen){
            matches++;
            idx = 0;
        }
    }
    return matches;
}

/**
 * Removes all whitespaces characters besides '\0'
 * @param a ... string to trim
 * @return String without whitespaces
 */
str StrTrim(str a){
    str newStr = (str) calloc(StrLength(a), 1);
    int idx = 0;
    for (int i = 0; i < StrLength(a); i++){
        if (a[i] == 0 || a[i] > 32){
            newStr[idx] = a[i];
            idx++;
        }
    }
    return newStr;
}

/**
 * Coverts a string into an integer (Numeric Literals, not ASCII-Codes)
 * @param a ... string to convert
 * @return string as an integer
 */
int Str2Int(str a){
    int num = 0;
    int sign = 1; // 1 ... +, -1 ... -
    int digit;
    for (int i = 0; i < StrLength(a); i++){
        digit = 0;
        if((a[i] < 48 || a[i] > 57) && i > 0)
            return -1;
        if (a[i] == 45 || a[i] == 43)
            sign = a[i] == 45 ? -1 : 1;
        else
            digit = a[i] -48;
        num += digit * pow(10, StrLength(a)-i-1);
    }
    num *= sign;
    return num;
}

/**
 * Converts an integer into a string (Numeric Literals, not ASCII-Codes)
 * @param a ... integer to convert
 * @return integer as a string
 */
str Int2Str(int a){
    int a2 = a;
    int digits[(int)ceil(log10(a))];
    str newStr = (str) calloc((int)ceil(log10(a)+1), 1);
    int res;
    int i = 0;
    while (a != 0){
        res = a % 10;
        a -= res;
        a /= 10;
        digits[i] = res;
        i++;
    }
    int revDigits[(int)ceil(log10(a2))];
    i = 0;
    for (int j = ceil(log10(a2)); j > 0; j--){
        revDigits[i] = digits[j-1];
        i++;
    }
    for (i = 0; i < ceil(log10(a2)); i++){
        newStr[i]= 48 + revDigits[i];
    }
    return newStr;
}

/**
 * Converts a string to a float (Numeric Literals, not ASCII-Codes)
 * @param a ... string to convert
 * @return string as a float
 */
float Str2Float(str a){
    float num = 0;
    float factor;
    int dotCount = 0;
    int digit;
    int posts = 0;
    int sign = 1; // 1 ... +, -1 ... -
    for (int i = 0; i < StrLength(a); i++){
        digit = 0;
        if ((a[i] < 48 || a[i] > 57) && i > 0 && a[i] != 46)
            return -1;
        factor = pow(10, i);
        if (a[i] == 46)
            dotCount++;
        if (dotCount > 1)
            return -1;
        else if (dotCount == 1){
            factor = pow(10, posts);
            posts--;
        }
        if (a[i] == 45 || a[i] == 43 || a[i] == 46)
            sign = a[i] == 45 ? -1 : 1;
        else
            digit = a[i] - 48;
        if (a[i] != 46)
            num += digit * factor;
    }
    num *= sign;
    return num;
}

/**
 * Turns a float into a string (Numeric Literals, not ASCII-Codes)
 * @param a ... float to convert
 * @return float as a string
 */
str Float2Str(float a){
    float a2;
    int aInt = (int)floorf(a);
    char rawPre[STR_MAX_LENGTH/2];
    char rawPost[STR_MAX_LENGTH/2];
    str pre;
    str post;

    a -= aInt;
    itoa(aInt, rawPre, 10);
    pre = rawPre;
    while (log10f(a) < 5)
        a *= 10;
    itoa(a, rawPost, 10);
    post = rawPost;

    str newStr = StrMerge(pre, ".");
    newStr = StrMerge(newStr, post);
    return newStr;
}

/**
 * Changes a singular character within a given string
 * @param base ... base string
 * @param idx ... index at which the string should be changed
 * @param newChar ... the character to replace with
 * @return Modified version of 'base'
 */
str StrChangeAt(str base, int idx, char newChar){
    if (idx < 0 || idx > StrLength(base)-1)
        return " ";
    str newStr = (str) calloc(StrLength(base), 1);
    newStr = strcpy(newStr, base);
    newStr[idx+1] = newChar;
    return newStr;
}

/**
 * Removes the character at given index
 * @param base ... base string
 * @param idx ... index at which a character will be removed
 * @return 'base' without character at index 'idx'
 */
str StrRemoveAt(str base, int idx){
    str newStr = (str) calloc(StrLength(base), 1);
    int j = 0;
    for (int i = 0; i < StrLength(base); i++){
        if (i != idx) {
            newStr[j] = base[i];
            j++;
        }
    }
    newStr = realloc(newStr, StrLength(newStr));
    return newStr;
}

/**
 * Splits 'base' at the first occurrence of 'where'
 * @param base ... base string
 * @param where ... substring
 * @param fraction ... the fraction of the string that is returned
 * @return 'base' split at 'where'
 */
str StrSplitFirst(str base, str where, int fraction){
    str newStr1 = (str) calloc(STR_MAX_LENGTH, 1);
    str newStr2 = (str) calloc(STR_MAX_LENGTH, 1);
    int *idxs = StrSearchFirst(base, where);
    int startIdx = idxs[0];
    int endIdx = idxs[1];
    int idx = 0;
    int endFlag = 0;
    for (int i = 0; i < StrLength(base); i++){
        if (i < startIdx){
            newStr1[idx] = base[i];
            idx++;
        }
        else if (i > endIdx){
            if (!endFlag){
                endFlag = 1;
                idx = 0;
            }
            newStr2[idx] = base[i];
            idx++;
        }
    }
    newStr1 = realloc(newStr1, StrLength(newStr1));
    newStr2 = realloc(newStr2, StrLength(newStr2));
    if (fraction == 0) {
        free(newStr2);
        return newStr1;
    }
    else if (fraction == 1) {
        free(newStr1);
        return newStr2;
    }
    else
        return " ";
}

/**
 * Splits the string into two at the given index
 * @param base ... base string
 * @param idx ... index to split at
 * @param fraction ... the "half" to return
 * @return
 */
str StrSplitAt(str base, int idx, int fraction) {
    if (fraction < 0 || fraction > 1 || idx < 0 || idx > StrLength(base) - 1)
        return " ";
    str newStr = (str) calloc(StrLength(base), 1);
    //memset(newStr, 0, sizeof newStr);
    int currentIdx = 0;
    for (int i = 0; i < StrLength(base); i++) {
        if ((i < idx && !fraction) || (i > idx && fraction)){
            newStr[currentIdx] = base[i];
            currentIdx++;
        }
    }
    newStr = realloc(newStr, StrLength(newStr));
    return newStr;
}


/**
 * Finds the start and/or end indices of 'what' in 'base' (SEARCHALL_OCCURRENCES defines how many occurrences can be found)
 * As a lot of uninitialized memory can be returned, use 'StrCount(base, what)*2' to know what elements of the returned array are relevant
 * @param base ... base string
 * @param what ... substring to search in 'base'
 * @param searchMode ... defines whether to return start and/or end indices
 * @return An array, that contains the start and/or end indices at which 'what' was found in 'base'
 */
int *StrSearchAll(str base, str what, int searchMode) {
    str text = base;
    int matches = 0;
    static int indices[SEARCHALL_OCCURRENCES*2];
    int startIdx, endIdx;
    for (int i = 0; i < StrLength(base); i+=2) {
        int *idxs = StrSearchFirst(base, what);
        startIdx = idxs[0];
        endIdx = idxs[1];
        if (startIdx >= 0)
            matches++;
        for (int j = startIdx; j <= endIdx+1; j++) {
            if (j < endIdx+1)
                text = StrRemoveAt(text, j);
        }
        base = text;
        indices[i] = startIdx;
        indices[i+1] = endIdx;
        if (matches > 1){
            indices[i] +=  StrLength(what) != 1 ? matches : matches-1;
            indices[i+1] += StrLength(what) != 1 ? matches : matches-1;
        }
    }
    if (searchMode == SEARCHMODE_STD){
        return indices;
    }
    else if (searchMode == SEARCHMODE_START){
        static int startIndices[SEARCHALL_OCCURRENCES];
        int idx = 0;
        for (int i = 0; i < matches * 2; i += 2){
            startIndices[idx] = indices[i];
            idx++;
        }
        return startIndices;
    }
    else if (searchMode == SEARCHMODE_END){
        static int endIndices[SEARCHALL_OCCURRENCES];
        int idx = 0;
        for (int i = 1; i < matches * 2; i += 2){
            endIndices[idx] = indices[i];
            idx++;
        }
        return endIndices;
    }
    else{
        static int voided[2] = {-1,-1};
        return voided;
    }
}

/**
 * Zips two strings together, thus the characters of 'a' and 'b' will alternate in the returned string
 * @param a ... 1st string
 * @param b ... 2nd string
 * @param interval ... how frequently 'a' and 'b' alternate
 * @return 'a' and 'b' joined and alternated
 */
str StrZip(str a, str b, int interval){
    str newStr = (str) calloc(StrLength(a) + StrLength(b), 1);
    int idxA = 0;
    int idxB = 0;
    int i = 0;
    for (; i < StrLength(a)*(interval+1);){
        do {
            newStr[i] = a[idxA];
            i++;
            idxA++;
        } while (idxA % interval != 0);
        do {
            newStr[i] = b[idxB];
            i++;
            idxB++;
        } while (idxB % interval != 0);
    }
    return newStr;
}

/**
 * Just in case you need to break down the memory required to a minimum
 * @param a ... string to optimize
 * @return 'a' but with optimized memory
 */
str StrOptimizeSize(str a){
    str newStr = realloc(a, StrLength(a));
    return newStr;
}
/**
 * Creates a string that contains 'a' repeated by 'echoCount' times
 * @param a ... string to echo
 * @param echoCount ... amount of echos
 * @return 'a' repeated by 'echoCount' times
 */
str StrEcho(str a, int echoCount){
    str newStr = (str) calloc((StrLength(a)-1)*echoCount+1, 1);
    for (int i = 0; i < echoCount * StrLength(a); i += StrLength(a)){
        for (int j = 0; j < StrLength(a); j++){
            newStr[i+j] = a[j];
        }
    }
    return newStr;
}

/**
 * Required to initialize 'StrRandString'
 */
void StrRandStringInit(){
    srand(time(NULL));
}

/**
 * Generates a random string
 * @param length ... length of the random string
 * @param excludeWhitespaces ... defines whether whitespaces can be generated or not
 * @return random string
 */
str StrRandString(int length, int excludeWhitespaces){
    str newStr = (str) calloc(length+1, 1);
    char whitespaces[3] = {' ', '\t', '\n'};
    for (int i = 0; i < length; i++){
        if (excludeWhitespaces)
            newStr[i] = (char)(33 + rand() % 94);
        else{
            newStr[i] = !(rand() % 7) ? whitespaces[rand() % 4] : (char)(33 + rand() % 94);
        }
    }
    return newStr;
}

/**
 * Takes a string input similar to 'scanf', but can also read-in whitespace characters
 * @param message ... input prompt message
 * @return whatever string the user entered
 */
str StrInput(str message){
    str newStr = (str) calloc(STR_MAX_LENGTH, 1);
    printf("%s", message);
    fgets(newStr, STR_MAX_LENGTH, stdin);
    fflush(stdin);
    newStr[StrLength(newStr)-1] = '\0';
    newStr = realloc(newStr, StrLength(newStr)+1);
    return newStr;
}

/**
 * Substitutes the first occurrence of char 'what' with 'whit' in 'base'
 * @param base ... base string
 * @param what ... character to replace
 * @param with ... character to replace with
 * @return Modified base string
 */
str StrSubstituteFirst(str base, char what, char with){
    str newStr = (str) calloc(StrLength(base), 1);
    int canReplace = 1;
    for (int i = 0; i < StrLength(base); i++){
        if (base[i] == what && canReplace){
            canReplace = 0;
            newStr[i] = with;
        }
        else{
            newStr[i] = base[i];
        }
    }
    return newStr;
}

/**
 * Substitutes every occurrence of char 'what' with 'whit' in 'base'
 * @param base ... base string
 * @param what ... character to replace
 * @param with ... character to replace with
 * @return Modified base string
 */
str StrSubstituteAll(str base, char what, char with){
    str newStr = (str) calloc(StrLength(base), 1);
    for (int i = 0; i < StrLength(base); i++){
        if (base[i] == what){
            newStr[i] = with;
        }
        else{
            newStr[i] = base[i];
        }
    }
    return newStr;
}

/**
 * Checks if the given string only contains the digits 0-9
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is numeric
 */
int IsNumeric(str a){
    for (int i = 0; i < StrLength(a); i++){
        if (a[i] < 48 || a[i] > 90){
            return 0;
        }
    }
    return 1;
}

/**
 * Checks if the given string only contains the letters a-z or A-Z
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is alphabetic
 */
int IsAlphabetic(str a){
    for (int i = 0; i < StrLength(a); i++){
        if (!(a[i] >= 65 && a[i] <= 90 || a[i] >= 97 && a[i] <= 122)){
            return 0;
        }
    }
    return 1;
}

/**
 * Checks if the given string only contains digits(0-9) or letters(a-z, A-Z)
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is alphanumerical
 */
int IsAlphaNumeric(str a){
    for (int i = 0; i < StrLength(a); i++){
        if (!(a[i] >= 65 && a[i] <= 90 || a[i] >= 97 && a[i] <= 122 || a[i] >= 48 && a[i] <= 90)){
            return 0;
        }
    }
    return 1;
}

/**
 * Checks if the given string only contains symbols
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' only contains symbols
 */
int IsSymbolic(str a){
    for (int i = 0; i < StrLength(a); i++){
        if (!(a[i] >= 33 && a[i] <= 47 || a[i] >= 58 && a[i] <= 64 || a[i] >= 91 && a[i] <= 96 || a[i] >= 123 && a[i] <= 126)){
            return 0;
        }
    }
    return 1;
}

/**
 * Checks if the given string only contains whitespaces
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' only contains whitespaces
 */
int IsWhitespace(str a){
    for (int i = 0; i < StrLength(a); i++){
        if (a[i] > 32){
            return 0;
        }
    }
    return 1;
}

/**
 * Checks if all characters are uppercase
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is uppercased
 */
int IsUpper(str a){
    return StrMatch(a, ToUpper(a));
}

/**
 * Checks if all characters are lowercase
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is lowercased
 */
int IsLower(str a){
    return StrMatch(a, ToLower(a));
}

/**
 * Checks if the string follows strlibs definition of a title
 * @param a ... string to check
 * @return Integer value to represent a boolean if 'a' is a title
 */
int IsTitle(str a){
    return StrMatch(a, ToTitle(a));
}

/**
 * Overwrites the first occurrence of 'what' in 'base' with a sequence of 'with'
 * @param base ... base string
 * @param what ... string to mute
 * @param with ... character to mute with
 * @return Muted version of 'base'
 */
str StrMuteFirst(str base, str what, char with){
    str newStr = (str) calloc(StrLength(base), 1);
    int *idxs = StrSearchFirst(base, what);
    int startIdx = idxs[0];
    int endIdx = idxs[1];
    for (int i = 0; i < StrLength(base); i++){
        if (i >= startIdx && i <= endIdx)
            newStr[i] = with;
        else
            newStr[i] = base[i];
    }
    newStr[StrLength(base)] = '\0';
    return newStr;
}

/**
 * Overwrites every occurrence of 'what' in 'base' with a sequence of 'with'
 * @param base ... base string
 * @param what ... string to mute
 * @param with ... character to mute with
 * @return Muted version of 'base'
 */
str StrMuteAll(str base, str what, char with){
    str newStr = (str) calloc(StrLength(base), 1);
    str newBase = (str) calloc(StrLength(base), 1);
    for (int j = 0; j < StrLength(base); j++){
        newBase[j] = base[j];
    }
    for (int j = 0; j < StrCount(base, what); j++){
        int *idxs = StrSearchFirst(newBase, what);
        int startIdx = idxs[0];
        int endIdx = idxs[1];
        for (int i = 0; i < StrLength(base); i++){
            if (i >= startIdx && i <= endIdx) {
                newStr[i] = with;
                newBase[i] = with;
            }
            else {
                newStr[i] = newBase[i];
            }
        }
    }
    free(newBase);
    newStr[StrLength(base)] = '\0';
    return newStr;
}

/**
 * Overwrites the entirety of the passed string with 'with'
 * @param base ... base string
 * @param with ... character to mute with
 * @param muteWhitespaces ... defined whether whitespaces can be muted
 * @return Muted version of 'base'
 */
str StrMuteEverything(str base, char with, int muteWhitespaces){
    str newStr = (str) calloc(StrLength(base), 1);
    for (int i = 0; i < StrLength(base); i++){
        if (!muteWhitespaces && base[i] <= 32 && base[i] > 0)
            newStr[i] = base[i];
        else
            newStr[i] = with;
    }
    return newStr;
}

/**
 * Inserts 'what' into 'base' at 'idx'
 * @param base ... base string
 * @param idx ... index to insert at
 * @param what ... the character to insert
 * @return 'base' with 'what' inserted
 */
str StrInsertAt(str base, int idx, str what){
    if (StrLength(what) != 1)
        return " ";
    char prev = base[idx];
    char rprevChar[] = {prev, 0};
    str prevChar = rprevChar;
    str half1 = StrSplitAt(base, idx, 0);
    str mergedString = StrMerge(half1, what);
    str half2 = StrSplitAt(base, idx, 1);
    mergedString = StrMerge(mergedString, prevChar);
    mergedString = StrMerge(mergedString, half2);
    free(half1);
    free(half2);
    return mergedString;
}

/**
 * Checks if the string is binary (only contains 1 and 0)
 * @param bin ... string to check
 * @return Integer value to represent a boolean if 'bin' is binary
 */
int IsBinary(str bin){
    for (int i = 0; i < StrLength(bin); i++){
        if (!(bin[i] == '0' || bin[i] == '1'))
            return 0;
    }
    return 1;
}

/**
 * Check if the string is hexadecimal (only contains 0-9, a-f, A-F)
 * @param hex ... string to check
 * @return Integer value to represent a boolean if 'hex' is a hexadecimal
 */
int IsHexadecimal(str hex){
    for (int i = 0; i < StrLength(hex); i++){
        if (!(hex[i] >= 48 && hex[i] <= 57 || hex[i] >= 65 && hex[i] <= 70 || hex[i] >= 97 && hex[i] <= 102))
            return 0;
    }
    return 1;
}

/**
 * Check if the string is octal (only contains 0-7)
 * @param oct ... string to check
 * @return Integer value to represent a boolean if 'oct' is octal
 */
int IsOctal(str oct){
    for (int i = 0; i < StrLength(oct); i++){
        if (!(oct[i] >= 48 && oct[i] <= 55))
            return 0;
    }
    return 1;
}

/**
 * Converts a binary string into a decimal integer
 * @param bin ... string to convert
 * @param signMode ... defines how 'bin' should be represented
 * @return 'bin' as a decimal integer
 */
int Bin2Dec(str bin, int signMode){
    if (signMode < 0 || signMode > 2 || !IsBinary(bin))
        return -1;
    int i = 0;
    int dec = 0;
    str revBin = StrReverse(bin);
    for (; i < StrLength(bin); i++){
        int val = revBin[i] == '0' ? 0 : 1;
        dec += pow(2, i) * val;
    }
    if (signMode == SIGNMODE_SBIT && revBin[i-1] == '1'){
        dec -= pow(2, i-1);
        dec *= -1;
    }
    else if (signMode == SIGNMODE_S2C && revBin[i-1] == '1'){
        dec -= pow(2, i);
    }
    return dec;
}

/**
 *
 * @param dec
 * @param signMode
 * @param address
 * @return
 */
str Dec2Bin(int dec, int signMode){
    int dec2 = dec;
    str bin = (char *) calloc(STR_MAX_LENGTH, 1);
    int i;
    if (signMode == SIGNMODE_US){
        i = 1;
        bin[0] = '1';
    }
    else{
        i = 0;
    }
    if (signMode == SIGNMODE_S2C)
        dec2 += 1;
    do{
        int res = dec2 % 2;
        dec2 /= 2;
        bin[i] = abs(res) == 1 ? '1' : '0';
        if (signMode == SIGNMODE_S2C)
            bin[i] = res ? '0' : '1';
        i++;
    } while (dec2 != 0);
    if (signMode == SIGNMODE_SBIT) {
        bin[i] = dec < 0 ? '1' : '0';
        i++;
    }
    if (signMode == SIGNMODE_S2C && dec < 0) {
        bin[i] = '1';
        i++;
    }
    i++;
    str newBin = StrReverse(bin);
    if (signMode == SIGNMODE_US)
        newBin = StrRemoveAt(newBin, 0);
    newBin = realloc(newBin, StrLength(newBin)+1);
    return newBin;
}

/**
 * Turns Uppercases into Lowercases and Lowercases into Uppercases
 * @param base ... string to case-invert
 * @return case-inverted string
 */
str CaseInvert(str a){
    str newStr = (str) calloc(StrLength(a), 1);
    for (int i = 0; i < StrLength(a); i++){
        if ((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z')){
            newStr[i] = a[i] ^ 32;
        }
        else{
            newStr[i] = a[i];
        }
    }
    return newStr;
}


#endif