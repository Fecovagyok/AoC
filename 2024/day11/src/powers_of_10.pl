use strict;
use warnings;

my $count = 0;
while($count < 21){
  my $inner_count = 0;
    print "1";
  while($inner_count < $count){
    print "0";
    $inner_count++;
  }
  print "ULL,";
  $count++;
}
