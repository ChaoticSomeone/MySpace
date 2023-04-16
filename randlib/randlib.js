
var RANDLIB_MAX = 32767;
const INT_LIMIT = 2147483647;
var seed = window.performance.now();
var prevSeed = seed;

class Randlib{
    set_RANDLIB_MAX(value){
        RANDLIB_MAX = value;
    }

    NewRand(){
        seed = window.performance.now();
        while (seed <= prevSeed + 0.5){
            seed = window.performance.now();
        }
        var seed1 = Math.round(seed.toString().slice(-3)*3 + seed.toString().slice(-2)*7*prevSeed);
        prevSeed = seed;
        var value = ((8253739 * seed1 + 2396403) % INT_LIMIT) % RANDLIB_MAX;
        return value;
    }

    Randint(min, max){
        if (min > max){
            var max1 = max;
            max = min;
            min = max1;
        }
        return min + (this.NewRand() % (max - min +1));
    }

    Randfloat(min, max){
        if (min > max){
            var max1 = max;
            max = min;
            min = max1;
        }
        var pre = this.Randint(Math.round(min),Math.round(max)-1);
        var post = ((8253739 * seed + 2396403) % INT_LIMIT) % RANDLIB_MAX;
        post /= Math.pow(10, Math.floor(Math.log10(32767))+1);
        return pre + post;
    }

    Randbool(){
        return this.Randint(0, 1) !== 0;
    }

    Randchar(excludeWhitespaces){
        var chars;
        if (excludeWhitespaces){
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@#€&_-()=%*':/!?+.,$~<>^[]{}`;\\|\" \t\n";
        }
        else{
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@#€&_-()=%*':/!?+.,$~<>^[]{}`;\\|\"";
        }
        return chars[this.Randint(0, chars.length-1)];
    }

    Randstring(length, excludeWhitespaces){
        var text = "";
        var chars;
        if (excludeWhitespaces){
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@#€&_-()=%*':/!?+.,$~<>^[]{}`;\\|\" \t\n";
        }
        else{
            chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890@#€&_-()=%*':/!?+.,$~<>^[]{}`;\\|\"";
        }
        for (var i = 0; i<length*2; i++){
            seed = window.performance.now();
            while (seed <= prevSeed + 0.5){
                seed = window.performance.now();
            }
            var seed1 = Math.round(seed.toString().slice(-3)*3 + seed.toString().slice(-2)*7*prevSeed);
            prevSeed = seed;
            if (i % 2 === 1)
                text += chars[((8253739 * seed1 + 2396403) % INT_LIMIT) % RANDLIB_MAX % chars.length];
        }
        return text;
    }

}
