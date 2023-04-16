import time as t
import math

__RANDLIB_MAX = 32767
__INT_LIMIT = (2**31)-1
seed = 0
t1, t2 = 0,0
	
def Randinit():
	t1 = t.monotonic_ns()

def Set_RANDLIB_MAX(value):
	__RANDLIB_MAX = int(round(value))

def NewRand():
	t2 = t.monotonic_ns()
	seed = t2 - t1
	value = (8253739 * seed + 2396403) % __INT_LIMIT
	return value % __RANDLIB_MAX

def Randint(min, max):
	min = int(round(min))
	max = int(round(max))
	if min > max:
		min, max = max, min
	return min + (NewRand() % (max - min +1))

def Randfloat(min, max, decimals=0):
	if min > max:
		min, max = max, min
	pre, post = Randint(min, max-1), NewRand() / 10**math.log10(__RANDLIB_MAX)
	if decimals > 0:
		post = round(post,decimals)
	return pre + post

def Randbool():
	return True if Randint(0,1) == 1 else False

def Randchar(excludeWhitespaces):
	chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@#€&_-()=%*':/!?+.,$~<>^[]{}`;\|¦"
	if not excludeWhitespaces:
		chars += " \n\t"
	return chars[Randint(0,len(chars)-1)]

def Randstring(length, excludeWhitespaces):
	length *= -1 if length < 0 else 1
	text = ""
	for _ in range(length):
		text += Randchar(excludeWhitespaces)
	return text
		
