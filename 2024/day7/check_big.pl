use strict;
use warnings;

open(my $file, '<', './2024/day7/input.txt') or die "Could not: $!";
my $max = 4294967295;
while(<$file>){
  if(/^(\d+):/){
    my $num = $1;
    my $len = length($num);
    if($len > $max){
      $max = $len
    }
  } else {
    print   "asdkjasdkaj";
  }
}

print $max;
print "\n";
