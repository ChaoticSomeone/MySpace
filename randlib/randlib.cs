using System;
using System.Linq;

namespace Randlib
{

	public static class randlib
	{
		static private ulong RANDLIB_MAX = 32767;
		static private ulong t1, t2;
		
		public static void Randinit(){
			t1 = (ulong)DateTime.Now.Ticks;
		}
		
		public static void Set_RANDLIB_MAX(ulong value){
			RANDLIB_MAX = value;
		}
		
		private static int NewRand(){
			uint value;
			t2 = (ulong)DateTime.Now.Ticks;
			ulong seed = (ulong)(t2 - t1);
			value = (uint)((ulong)(8253738 * seed + 2396403) % RANDLIB_MAX);
			return (int)value;
		}
		
		public static int Randint(int min, int max){
			if (min > max){
				(min, max) = (max, min);
			}
			return min + (NewRand() % (max - min + 1));
		}
		
		public static short Randshort(short min, short max){
			if (min > max){
				(min, max) = (max, min);
			}
			return (short)((int)min + (NewRand() % (int)(max - min + 1)));
		}
		
		public static long Randlong(long min, long max){
			if (min > max){
				(min, max) = (max, min);
			}
			return (long)((int)min +(NewRand() % (int)(max - min +1)));
		}
		
		public static float Randfloat(float min, float max){
			if (min > max){
				(min, max) = (max, min);
			}
			long pre;
			float post;
			pre = Randint((int)min, (int)(max-1));
			post = (float)NewRand() / (float)Math.Pow(10, (float) Math.Log10(RANDLIB_MAX));
			return (float)post + (float)pre;
		}
		
		public static double Randdouble(double min, double max){
			if (min > max){
				(min, max) = (max, min);
			}
			long pre;
			double post;
			pre = Randint((int)min, (int)(max-1));
			post = (double)NewRand() / (double)Math.Pow(10, (double)Math.Log10(RANDLIB_MAX));
			return (double)post + (double)pre;
		}
		
		public static bool Randbool(){
			return Randint(0,1) == 1;
		}
		
		public static char Randchar(bool excludeWhitespaces){
			char[] whitespaces = {' ', '\t', '\n'};
			if (excludeWhitespaces){
				return (char)Randint(33, 126);
			}
			else{
				return Randint(0,6) != 0 ? (char)Randint(33, 126) : whitespaces[Randint(0, whitespaces.Length-1)];
			}
		}
		
		public static string Randstring(uint length, bool excludeWhitespaces){
			string text = "";
			for (int i = 0; i < length; i++){
				text += Randchar(excludeWhitespaces);
			}
			return text;
		}
		
		
	}
}
