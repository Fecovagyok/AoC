use strict;
use warnings;

my $file_name = "$ARGV[0]/input.txt";
open(my $input, "<", $file_name) or die "Could not open $!\n";

my $sum = 0;
while(<$input>){
  while(/mul\((\d{1,3}),(\d{1,3})\)/g){
    $sum += int($1) * int($2);
  }
}
print $sum."\n";
