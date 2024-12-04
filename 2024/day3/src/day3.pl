use strict;
use warnings;

my $file_name = "$ARGV[0]/input.txt";
open(my $input, "<", $file_name) or die "Could not open $!\n";

my $sum = 0;
my $state = 0;
while(<$input>){
  while(/(.*?)mul\((\d{1,3}),(\d{1,3})\)/g){
    my $rest = $1;
    my $first = $2;
    my $second = $3;
    if($state == 0){
      if($rest =~ /don't\(\).*?$/g){
        if($rest =~ /do\(\).*?$/g){
          print "Oh bizony van\n";
          $sum += int($first) * int($second);
        } else {
          $state = 1;
        }
      } else {
        $sum += int($first) * int($second);
      }
    } else {
      if($rest =~ /do\(\).*?$/g){
        if($rest =~ /don't\(\).*?$/g){
          print "Oh bizony van\n";
        } else {
          $sum += int($first) * int($second);
          $state = 0;
        }
      }
    }
  }
}
print $sum."\n";
