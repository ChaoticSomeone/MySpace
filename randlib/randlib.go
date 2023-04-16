package randlib

import (
	"math"
	"time"
)

var seed uint64 = 0
var RANDLIB_MAX uint64 = 32767
var prevSeed uint64 = 0

func Set_RANDLIB_MAX(value uint64) {
	RANDLIB_MAX = value
}

func NewRand() int32 {
	for seed == prevSeed {
		seed = uint64(time.Now().UnixNano()*9457372 + 231453)
	}
	prevSeed = seed
	return int32(seed % RANDLIB_MAX)
}

func Randint(min, max int32) int32 {
	if min > max {
		max, min = min, max
	}
	var value int32 = min + (NewRand() % (max - min + 1))
	return value
}

func Randshort(min, max int16) int16 {
	if min > max {
		max, min = min, max
	}
	var value int16 = min + (int16(NewRand()) % (max - min + 1))
	return value
}

func Randlong(min, max int64) int64 {
	if min > max {
		max, min = min, max
	}
	var value int64 = min + (int64(NewRand()) % (max - min + 1))
	return value
}

func Randfloat(min, max float32) float32 {
	if min > max {
		min, max = max, min
	}
	var pre, post float32
	pre = float32(Randint(int32(min), int32(max-1)))
	post = float32(float64(NewRand()) / math.Pow(10, math.Log10(float64(RANDLIB_MAX))))
	return pre + post
}

func Randdouble(min, max float64) float64 {
	if min > max {
		min, max = max, min
	}
	var pre, post float64
	pre = float64(Randint(int32(min), int32(max-1)))
	post = float64(float64(NewRand()) / math.Pow(10, math.Log10(float64(RANDLIB_MAX))))
	return pre + post
}

func Randbool() bool {
	var value bool = false
	if Randint(0, 1) == 1 {
		value = true
	}
	return value
}

func Randchar(excludeWhitespaces bool) string {
	chars := []string{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~"}
	whitespaces := []string{" ", "\n", "\t"}
	length := int32(len(chars) - 1)
	var char string
	if excludeWhitespaces {
		char = chars[Randint(0, length)]
	} else {
		if Randint(0, 16) == 0 {
			char = whitespaces[Randint(0, 2)]
		} else {
			char = chars[Randint(0, length)]
		}

	}
	return char
}

func Randstring(excludeWhitespaces bool, length int32) string {
	var text string
	var char string
	for i := 0; i < int(length); i++ {
		char = Randchar(excludeWhitespaces)
		text += char
	}
	return text
}
