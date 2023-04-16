# Initialize Module #1
package randlib;
use strict;
use warnings;
use Exporter;

use Time::HiRes qw(time);
use POSIX;
our $seed = 0;
our $prevSeed = $seed;
our $RANDLIB_MAX = 32767;

# Initialize Module #2
our @ISA= qw( Exporter );
our @EXPORT = qw( NewRand Randint Randfloat Randbool Randchar );
our @EXPORT_OK = qw( NewRand Randint Randfloat Randbool Randchar );

our sub NewRand{
	while ($seed == $prevSeed){
		$seed = ceil(time());
	}
	$prevSeed = $seed;
	my $value =(8253739 * $seed + 2396403)%$RANDLIB_MAX;
	return $value;
}

our sub Randint{
	my @params = @_;
	if (scalar @params != 2){
		my $len = scalar @params;
		die "ParameterError: \'Randint\' takes 2 parameters, $len given!"
	}
	my $min = $params[0];
	my $max = $params[1];
	if ($min > $max){
		my $max1 = $max;
		$max = $min;
		$min = $max1;
	}
	my $value = $min + (NewRand() % ($max - $min +1));
	return $value;
}

our sub Randfloat{
	my @params = @_;
	if (scalar @params != 2){
		my $len = scalar @params;
		die "ParameterError: \'Randfloat\' takes 2 parameters, $len given!"
	}
	my $min = $params[0];
	my $max = $params[1];
	if ($min > $max){
		my $max1 = $max;
		$max = $min;
		$min = $max1;
	}
	my $pre = Randint(floor($min),floor($max)-1);
	my $post = NewRand() / pow(10, floor(log10($RANDLIB_MAX)));
	return $pre + $post;
}

our sub Randbool{
	my @params = @_;
	if (scalar @params != 0){
		my $len = scalar @params;
		die "ParameterError: \'Randbool\' takes 0 parameters, $len given!"
	}
	return Randint(0,1);
}

our sub Randchar{
	my @params = @_;
	if (scalar @params != 0){
		my $len = scalar @params;
		die "ParameterError: \'Randchar\' takes 1 parameter, $len given!"
	}
	my $excludeWhitespaces = $params[0];
	my @whitespaces = (" ", "\t", "\n");
	if ($excludeWhitespaces){
		return chr(Randint(33,126));
	}
	else{
		if (Randint(0,6) != 0){
			return chr(33);
		}
	}
}
