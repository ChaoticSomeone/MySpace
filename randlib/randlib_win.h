#ifndef RANDLIB_RANDLIB_H
#define RANDLIB_RANDLIB_H

#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>

unsigned long long RANDLIB_MAX = 32767;
int seed;

typedef char *randlib_string;


void Set_RANDLIB_MAX(unsigned long long value){
	RANDLIB_MAX = value;
}

int NewRand(void){
	unsigned int value;
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    seed = ticks.QuadPart;
	value = 8253739 * seed + 2396403;
	value = value % RANDLIB_MAX;
	return value;
}

int Randint(int min, int max){
    if (max < min){
        max, min = min, max;
    }
    unsigned long long r = NewRand();
    return min + (r % (max - min + 1));
}

short Randshort(short min, short max){
    if (max < min){
        max, min = min, max;
    }
    unsigned long long r = NewRand();
    return min + (r % (max - min + 1));
}

long Randlong(long min, long max){
    if (max < min){
        max, min = min, max;
    }
    return min + (NewRand() % (max - min + 1));
}

float Randfloat(float min, float max){
    if (max < min){
        max, min = min, max;
    }
    long long pre;
    long double post;
    unsigned long long r = (float) NewRand();
    pre = Randint((int) min, (int) max-1);
    post =  r / pow(10,(float) log10(RANDLIB_MAX));
    return (float) pre + (float) post;
}
double Randdouble(double min, double max){
    if (max < min){
        max, min = min, max;
    }
    long long pre;
    long double post;
    unsigned long long r = (float) NewRand();
    pre = Randint((int) min, (int) max-1);
    post = (double) NewRand() / pow(10,(double) log10(RANDLIB_MAX));
    return pre + post;
}

int Randbool(){
    return 1+NewRand()%2 == 1 ? 0 : 1;
}

char Randchar(unsigned int excludeWhitespaces){
    char whitespaces[] = {'\t', '\n', ' '};
    if (excludeWhitespaces) {
        return Randint(33, 126);
    }
    else{
        return Randint(0,6) ? Randint(33, 126) : whitespaces[Randint(0, sizeof(whitespaces)-1)];
    }
}


void *Randstring(uint32_t length, int excludeWhitespaces, uint64_t adr){
    char str[length+1];
    for (int i = 0; i < length; i++){
        str[i] = Randchar(excludeWhitespaces);
        while (i > 0 && str[i] == str[i-1]){
        	str[i] = Randchar(excludeWhitespaces);
        }
    }
    str[sizeof(str)-1] = '\0';
    char *string = &str;
    char *ptr = adr;
    ptr = string;
}

#endif //RANDLIB_RANDLIB_H
