#!/usr/bin/perl

use strict;
use warnings;
use autodie qw(:all);
use Class::Struct;

struct(HexRecord => {
	addr => '$',
	type => '$',
	data => '$',
});

sub readHexFile() {
	open(my $hexFile, "<", "test.hex");
	while(<$hexFile>) {
		my ($colon, $hex_data) = unpack("AA*");
		my $bytes = pack("H*", $hex_data);
		my $check_sum = unpack("%8W*", $bytes);
		my( $addr, $type, $data ) = unpack( "x n C X4 C x3 /a", $bytes );
		my $rec = HexRecord->new(addr=>$addr, type=>$type, data=>$data);
		my $data_str = unpack("H*", $rec->data);
		print($rec->addr . " " . $rec->type . " " . $data_str . "\n");
	}
	close($hexFile);
}

readHexFile();
