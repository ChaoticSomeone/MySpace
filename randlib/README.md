# Randlib
Random Number Generation Library for C/C++, C#, Python, Kotlin, Go, TypeScript, JavaScript, Lua, Perl, Fortran, Rust, Dart and Java

# Include the Library
Include the library in a .cpp or .c file using: ```#include "randlib_win.h"``` or ```#include "randlib_lnx.h"```

Use ```randlib_win.h``` if you are using a windows device or use ```randlib_lnx.h``` if you are using a UNIX or Linux based OS.
There's ```randlib.h``` now which should adjust to your OS.

Include the library in a python-file using:
```import randlib```


Include the library in a .cs (C#) file using:
```using Randlib;```


(altough the 'R' is capitalized for C#, functions are called using a lower-case 'r' instead - e.g. ```randlib.Randinit();```) 

Include the library in a .java (Java) or in a .kt (Kotlin) file using (Dont forget to add the path where the library is being saved):
````import randlib.java````
````import randlib.kt````

Include the library in a .go file using: ```import "randlib"```

Include the library in a .ts (TypeScript) file using:

```
import {Randlib} from "./randlib";
let randlib = new Randlib();
```

For the TypeScript Implementation make sure, that ```randlib.ts``` is saved in the same directory as the file you want to include it in.

Include the library in a .js file using: ```var randlib = new Randlib();```

Include the library in a .lua file using:

```
local modPath = "./"
package.path = modPath .. "?.lua;" .. package.path
randlib = require "Randlib"
```

Again, make sure that ```randlib.lua``` is saved in the same directory as your main-file.

Include the library in a .pl (Perl) file using:

```
use lib 'C:/Users/<users>/path/to/the/library';
use randlib;
```

Include the library in a .f90 (Fortran) file using: <see below under ```Details for Frotran```>

# Files
- randlib.py: Python Implementation
- randlib.cs: C# Implementation 
- randlib.go: Go Source Code
- randlib_win.h: C/C++ Implementation for Windows
- randlib_lnx.h: C/C++ Implementation for Linux
- randlib.java: Java Implementation 
- randlib.kt: Kotlin Implementation 
- randlib.zip: Go Implementation
- randlib.ts: TypeScript Implementation
- randlib.js: JS Implementation
- randlib.lua: Lua Implementation
- randlib.pm: Perl Implementation
- randlib.f90: Fortran Implementation
- randlib_collection.zip: contains all the above
- randlib.dart: Dart Source Code
- randlib_dart.zip: Dart Implementation
- randlib.h: C Implementation for Windows and Linux

# General Details
This Library generates random Numbers using time as a seed. 
The library usually has a millisecond precision for C/C++ (on Linux), Python, Java, Kotlin, TypeScript, Lua, Perl, Fortran, Dart and C#, but keep in mind, that
randlib for C/C++ (on Windows) has a precision of microsecond/10, JS has a Microsecond precision and a nanosecond precision on Go. 

The implementation for TypeScript, Python, Lua, Perl, Fortran, Dart and JS do not have a definition for randdouble, randshort and randlong.

The Implementation for Perl will throw an error, if too many or too few parameters are passed, as otherwise you would be able to pass an undefined amount of parameters.

Some Implementations add a ```decimals``` parameter to randfloat/randdouble of type ```int```, it defines the amount of digits after the comma.

The Implementations for Go, TS, JS, Lua, Fortran and Perl cannot generate same seeds back to back.

All Functions now start with a capital (uppercase) letter, due to naming conventions.

If a function claims, that it returns a value between min and max, min and max are included are as possible results.

# Details for Go
1) Download ```randlib.zip```
2) Extract the zip-folder to ```GOROOT\src\``` (when using Windows, the default path should be: ```C:\Users\<user>\go\go<verison>\src\```)
3) Open your .go-file and add the following line of code: ```import "randlib"```

# Details for Fortran
This Implementation does not contain a defininition for ```set_RANDLIB_MAX```, instead most functions take an additional parameter called ```RANDLIB_MAX```

```randlib.f90``` was developed for Fortran90, as the file extension might already suggest.

Includation Instructions (Windows):

Lets just assume, that our main-file is called ```main.f90```
1) Add the line ```use randlib``` to ```main.f90```, right AFTER defining the start of your program
2) Download ```randlib.f90``` or get the file from ```randlib_collection.zip```
3) Add ```randlib.f90``` to your project folder
4) Download the gfortran compiler from e.g. https://www.intel.com/content/www/us/en/developer/tools/oneapi/fortran-compiler.html#gs.qudajx and follow the installation instructions
5) Open the command prompt
6) run following command: ```cd path\to\your\project\folder```
7) run following command: ```gfortran -c randlib.f90```
8) run following command: ```gfortran -c main.f90```
9) run following command: ```gfortran main.f90 randlib.o```
10) This will generate a executable file called ```a.exe```, which you can execute by running the command ```a.exe``` in the command prompt

# Functions
- ```randinit()```:

	initilaize the library (only run this function once!, initializes the time counter). This function doesn't exist in ```randlib_win.h```,  ````randlib.java````, ```randlib.go```, ```randlib.lua```, ```randlib.pm``` or ```randlib.ts```.


- ```set_RANDLIB_MAX(unsigned long long value)``` :
	
	Sets the maximum number that can be generated by randlib. 
	Standard value of RANDLIB_MAX: 32767.

- ```newRand()```:

	The aquivalent to stdlib.h's 'rand()' function.
	This function is not supposed to be used for generation, instead it is used by the other functions in this library.


- ```randint(int min, int max)```:

	returns integer between min and max
- ```randshort(short min, short max)```:

	returns short int between min and max
- ```randlong(long min, long max)```:

	returns long int between min and max
	
- ```randfloat(float min, float max)```:

	returns float between min and max
- ```randdouble(double min, double max)```:

	returns double between min and max
- ```randbool()```:

	returns either true or false (in C returns 1 or 0) 
- ```randchar(int excludeWhitespaces)```:

	returns a random ASCII-char (excludes tab, newline, space if excludeWhitespaces is true, in case of C: 1).
	If excludeWhitespaces is false, theres a 1 in 6 (roughly 16.67%) chance to genrate a space(' '), tab('\t') or new line('\n').

- ```randstring(unsigned int length, bool excludeWhitespaces)```:
	
	Generates and returns a random string, which consists of randomly chosen ASCII-characters.
	This function works the same for Python, C#, TypeScript and Go, for C/C++ details - view below.
	The 'length' parameter defines the length of the string and the 'excludeWhitespaces' parameter defines wheter whitespaces can be generated or not.
	In ```randlib_win.h``` there also is the 'adr' parameter, of the type ```long long```, it defines the address in memory to write to. 
	Currently this function is not implemented in Java/Kotlin, if you want to complain about that, @http9 is responsible for those languages :).
	```randlib.pm``` and ```randlib.f90``` also do not contain a definition for this function and will be implemented in the near future (@ChaoticSomeone is responsible for that).

	
	Details for ```randlib_win.h ```:

	Although this function does not return anything (because it's a void), you need to assign a variable to the result of this function.
	
	e.g.: ```randlib_string <var> = randstring(4, 1, &<var>);```
	
	Details for ```randlib_lnx.h```:

	The function can only genrated strings, that consist of up to 256 characters. This limit is defined by the ```LENGTH``` constant. 


# Other
- ```randlib_string```

	This is a datatype for strings in C/C++, currently this datatype is only present in C/C++, as it is only required for these languages. 

	In case you want to know how this datatype works: it basically is just a pointer that contains a char-array.
	
	
	
	
	
