import "dart:math";
int seed = 0;
int prevSeed = seed;

int NewRand(int RANDLIB_MAX){
  while (seed == prevSeed){
    seed = DateTime.now().millisecondsSinceEpoch;
  }
  prevSeed = seed;
  int value =  (8253739 * seed + 2396403) % RANDLIB_MAX;
  return value;
}

int Randint(int min, int max, int RANDLIB_MAX){
  if (min > max){
    int max1 = max;
    max = min;
    min = max1;
  }
  int value = min + (NewRand(RANDLIB_MAX) % (max - min +1));
  return value;
}

double Randfloat(double min, double max, int RANDLIB_MAX){
  if (min > max){
    double max1 = max;
    max = min;
    min = max1;
  }
  double pre, post;
  pre = Randint(min.floor(), max.floor()-1, 32767).toDouble();
  post = NewRand(32767) / pow(10, (log(RANDLIB_MAX)/ln10).floor()+1);
  return pre + post;
}

bool Randbool(){
  return Randint(0,1,32767) == 1;
}

String Randchar(bool excludeWhitespaces){
  int ascii_code=0;
  var whitespaces = [9, 10, 32];
  if (!excludeWhitespaces && randint(0,6,32767) == 0){
    ascii_code = ascii_code = whitespaces[Randint(0,2,32767)];
  }
  else{
    ascii_code = Randint(33,126,32767);
  }
  return String.fromCharCode(ascii_code);
  
}

String Randstring(int length, bool excludeWhitespaces){
  String text = "";
  for (int i = 0; i < length; i++){
    text += Randchar(excludeWhitespaces);
  }
  return text;
}
