export class Randlib{

    static RANDLIB_MAX: number = 32767;

    static INT_MAX: number = 2147483647;

    static prev_seed: number = 0;
    static seed: number = 0;

    Set_RANDLIB_MAX(value: number){
        Randlib.RANDLIB_MAX = value;
    }

    NewRand(){
        let value: number = 0;
        while (Randlib.seed == Randlib.prev_seed){
            Randlib.seed = Date.now();
        }
        value = ((8253739 * Randlib.seed + 2396403)%Randlib.INT_MAX)%Randlib.RANDLIB_MAX;
        Randlib.prev_seed = Randlib.seed
        return value;
    }

    Randint(min:number, max: number){
        if (min > max){
            let max1: number = max;
            max = min;
            min = max1;
        }
        let value: number = min + (this.NewRand() % (max-min+1));
        return value;
    }

    Randfloat(min:number, max:number, decimals:number=-1){
        if (min > max){
            let max1: number = max;
            max = min;
            min = max1;
        }
        let pre: number = this.Randint(Math.round(min), Math.round(max)-1);
        let post: number = this.NewRand() / Math.pow(10, Math.log10(Randlib.RANDLIB_MAX));
        let value: number = pre + post;
        if (decimals > 0){
            return value.toFixed(decimals);
        }
        else{
            return value;
        }
    }

    Randbool(){
        return (1+this.randint(0,1))%2 == 1;
    }

    Randchar(excludeWhitespaces:boolean=true){
        let chars: string[] = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~"];
        if (excludeWhitespaces){
            return chars[this.Randint(0, chars.length-1)];
        }
        else{
            chars.push(" ", "\n", "\t");
            return chars[this.Randint(0, chars.length-1)];
        }
    }

    Randstring(length:number, excludeWhitespaces:boolean=true){
        let text: string = "";
        for (let i = 0; i<length; i++){
            text += this.Randchar(excludeWhitespaces);
        }
        return text;
    }
}
