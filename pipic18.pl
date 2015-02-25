#!/usr/bin/perl

use strict;
use warnings;
use autodie qw(:all);

=begin
open(my $hex, "<", "b452-1.hex");

while(<$hex>) {
	#my $bytes = pack( "x[C]H*", $_);
	#print unpack("H*", $bytes);
	print("$_[0]\n");

	#print unpack( "%8C*", $binrec ) . "\n";
	#my ( $addr, $type, $data ) = unpack( "x n C X4 C x3 /a", $binrec );

	#my $data_bytes = unpack("H*", $data);

	#print("$addr $type $data_bytes\n");
}

close($hex);/

=end

=cut

$_ = ":1000600000F0052E22EF00F0120037EF00F00150F3";

for

