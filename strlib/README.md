# Strlib
String Implmenetation for C11

Just so you know, this library is pronounced as s-t-r-lib (or alternativly string-lib) not str-lib. 

```Strlib``` is not compatible with Linux or Unix based OS, due to Cs standard libraries being OS-dependent and do not contain required functions like ```itoa```.
So I guess it's not Linux, but rather Linot (pun based on windon't)



# Details
This library adds a string datatype called ```str```, this type is compatible with other string datatypes, that are defined as ```char *``` and several funtions that make working with strings in C a lot easier. As of right now, the library can only work with strings that consist of up to 1000000 (10^6) characters, this may be changed sooner or later (you can change the constant for that in the source code at own risk). 

Be aware, that while a function of this library is being executed, 1 - 3 MB of RAM are occupied, due to the max string length being very high (10^6 characters * 1 Byte pre character = 1MB).


# Extensions
Disclaimer: All extensions of Strlib are independent of strlib.h, but strlib is compatible with its extensions (obviously) and vice versa!
- strcolor.h: colored string printing
- strlist.h: string linked list implementation


# Include the library
1) Add ```strlib.h``` to your project directory
2) Add following line to you .c file: ```#include "strlib.h"```


# Constants
- ```STR_MAX_LENGTH```: 1000000 (10^6), max. amount of characters in a strlib string. (Will be removed soon :) )
- ```SEARCHMODE_STD```: 0, Searchmode for ```StrSearchAll```, that returns start and end indices.
- ```SEARCHMODE_START```: 1, Searchmode for ```StrSearchAll```, that only returns start indices
- ```SEARCHMODE_END```: 2, Searchmode for ```StrSearchAll```, that only returns end indices
- ```SEARCHALL_OCCURRENCES```: 128, amount of indices returned by ```StrSearchAll```.
- ```SIGNMODE_US```: 0, binary unsigned representation
- ```SIGNMODE_SBIT```: 1, binary sign bit representation
- ```SIGNMODE_S2C```: 2, binary twos complement representation

# Datatypes
- ```str```: datatype for simple strings, defined as ```char *```
- ```str_arr```: datatype for 1D string arrays, defined as ```char **```



# Functions
- ```int StrLength(str a)```:

    Returns the length of a string as an integer value.
    
    
- ```str StrMerge(str a, str b)```:

    Adds string ```b``` to string ```a``` and returns the resulting string.
    
    
- ```int StrMatch(str a, str b)```:
    
    Returns true(1) if both given strings are exactly the same, else this function returns false(0).
    
	
- ```str StrReverse(str a)```:
	
	Reverts the order of characters in the given string and returns it afterwards (what else did you expect?).
	
	
- ```int StrFind(str a, str b)```:
	
	Returns true(1) if the substring ```b``` was found in string ```a```, else returns false(0).


- ```int *StrSearchFirst(str a, str b)```:
	
	Looks for the first occurence of substring ```b``` in string ```a``` and returns an array of integers in the form of a pointer, 
	that contains the index at which the substring starts and the index, at which the substring ends.
	Returns ```{-1,-1}``` if b was not found in a


- ```float StrCompare(str a, str b)```:
	
	Returns a percantage as a float, which represents the equality of ```a``` and ```b```.
	


- ```str StrReplaceAll(str base, str what, str with)```:
	
	Replaces every occurence of ```what``` in ```base``` with ```with```. If ```with``` contains less characters than ```what```, then Spaces will be used to
	fill the remaining gaps (if it wasn't for this, than it would cut off the string), but if ```with``` contains just one character, then every occurence of
	```what``` will be replaced by a sequence of ```with```. This describtion is quite rough to understand, just try it out if you want to know precisely :).



- ```str StrReplaceFirst(str base, str what, str with)```:
		
	Replaces the first occurence of ```what``` in ```base``` with ```with```. If ```with``` contains less characters than ```what```, then Spaces will be used to
	fill the remaining gaps (if it wasn't for this, than it would cut off the string), but if ```with``` contains just one character, then every occurence of
	```what``` will be replaced by a sequence of ```with```. This describtion is quite rough to understand, just try it out if you want to know precisely :).
	
- ```str ToUpper(str a)```:
	
	Converts all lowercases to uppercases
	
- ```str ToLower(str a)```:
	
	Converts all uppercases to lowercases
	
- ```str ToTitle(str a)```:
	
	Converts the first character, as well as all characters after a whitespace into uppercases.
	The remaining characters will be lowercases.
	
- ```int StrCount(str base, str what)```:
	
	Returns the amount of occurrences of ```what``` in ```base```.

- ```str StrTrim(str a)```:

	Removes all whitespaces from ```a```.


- ```int Str2Int(str a)```:
	
	Turns ```a``` into an integer

- ```str Int2Str(int a)```:
	
	Turns ```a``` into a string

- ```float Str2Float(str a)```:
	
	Turns ```a``` into a float (slight rounding inaccuray due to binary encoding)

- ```str Float2Str(float a)```:
	
	Turns ```a``` into a string  (slight rounding inaccuray due to binary encoding)

- ```str StrSplitFirst(str base, str where, int half)```:
	
	Splits ```base``` into two halves, where ```where``` was found, ```where``` will not be included in either half.
	Using the ```half``` parameter you can select, if you want to have the first(0) or second(1) half, if this parameter is set to neither 0 or 1, this function
	will return ```" "``` instead.
	
	
- ```str StrChangeAt(str base, int idx, char newChar)```:
	
	Replaces the character at index ```idx``` in ```base``` with ```newChar```.
	

- ```str StrRemoveAt(str base, int index)```:
	
	Removes the charcter at index ```index``` from ```base```.
	

- ```str StrSplitAt(str base, int idx, int fraction)```:
	
	Splits ```base``` at index ```idx``` into two. The ```fraction``` parameter defines, which of the two halves are returned.
	

- ```int *StrSearchAll(str base, str what, int searchMode)```:

	Finds the start and/or end indices of ```what``` in ```base``` (```SEARCHALL_OCCURRENCES``` defines how many occurrences can be found)
 	As a lot of uninitialized memory can be returned, use ```StrCount``` to know what elements of the returned array are relevant
	
	Occupies 128 bytes (by default) IF this function is called.


- ```str StrZip(str a, str b, int interval)```:
	
	Merges ```a``` and ```b```, but unlike ```StrMerge``` the 2 strings are combined using the principle of a ziplock.
	```interval``` defines how frequently ```a``` and ```b``` alternate.


- ```str StrEcho(str a, int echoCount)```:
	
	Duplicates string ```a``` by ```echoCount``` times and joins the duplicates together


- ```void StrRandStringInit()```:
	
	Initializes ```StrRandString```, only run this function once!


- ```str StrRandString(int length, int excludeWhitespaces)```:

	Generates a random string (yeah both randlib and strlib have this function), ```length``` defines the length of the string.
	```excludeWhitespaces``` should represent a boolean value to define whether whitespaces can be generated or not.


- ```str StrSubstituteFirst(str base, char what, char with)```:
	
	Works similar to ```StrReplaceFirst``` but only replaces singular characters
	

- ```str StrSubstituteAll(str base, char what, char with)```:
	
	Works similar to ```StrReplaceAll``` but only replaces singular characters


- ```str StrInput(str message)```:
	
	Allows the user to enter a string (like ```scanf```), but unlike ```scanf``` you do not need a seperate ```printf``` for the input prompt and can also
	accept whitespaces as input (which ```scanf``` can't).
	```message``` defines the text for the input prompt.
	
- ```int IsNumeric(str a)```:
	
	Checks whether ```a``` only contains the characters 0-9 or not

- ```int IsAlphabetic(str a)```:
	
	Checks wheter ```a``` only contains the characters a-z or A-Z

- ```int IsAlphaNumeric(str a)```:
	
	Checks whether ```a``` only contains the characters a-z, A-Z or 0-9

- ```int IsSymbolic(str a)```:
	
	Checks whether ```a``` only contains special chatacters / symbols

- ```int IsWhitespace(str a)```:
	
	Checks whether ```a```'s characters all have a ASCII-Code of 32 or less

- ```int IsUpper(str a)```:

	Checks whether all letters in ```a``` are uppercase
	
- ```int IsLower(str a)```:

	Checks whether all letters in ```a``` are lowercase
	
- ```int IsTitle(str a)```:

	Checks if ```a``` follows strlib's title decribtion

- ```str StrMuteFirst(str base, str what, char with)```:
	
	Overwrites the 1st occurrence of ```what``` in ```base``` by repeating ```with```

- ```str StrMuteAll(str base, str what, char with)```:
	
	Overwrites evvery occurrence of ```what``` in ```base``` by repeating ```with```

- ```str StrMuteEverything(str base, char with, int muteWhitespaces)```:
	
	Overwrites every character in ```base``` with ```with```, if muteWhitespaces is true, then even whitespaces are overwritten

- ```str StrInsertAt(str base, int idx, str what)```:
	
	Inserts the string ```what```(of length 1) into ```base``` at index ```idx```

- ```int IsBinary(str bin)```:
	
	Checks whether ```bin``` contains only the characters 0 and 1

- ```int IsHexadecimal(str hex)```:
	
	Checks whether ```hex``` contains only the characters 0-9, a-f or A-F

- ```int IsOctal(str oct)```:
		
	Checks whether ```oct``` contains only the characters 0-7

- ```int Bin2Dec(str bin, int signMode)```:
	
	Converts the binary string ```bin``` into a integer number. ```signmMode``` defines the whether the binary string is signed or unsigned

- ```str Dec2Bin(int dec, int signMode)```:
	
	Converts the integer number ```dec``` into a binary string. ```signmMode``` defines the whether the binary string is signed or unsigned

- ```str CaseInvert(str a)```:
	
	Switches lowercases and uppercases
	
