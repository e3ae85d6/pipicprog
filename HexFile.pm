package HexFile;

use strict;
use warnings;
use autodie qw(:all);
use Class::Struct;

struct(HexRecord => {
	addr => '$',
	type => '$',
	data => '$',
});

sub load {
	my $hexFileName = shift(@_);

	my @hexRecords;
	open(my $hexFile, "<", $hexFileName);
	
	while(<$hexFile>) {
		my ($colon, $hex_data) = unpack("AA*");
		my $bytes = pack("H*", $hex_data);
		my $check_sum = unpack("%8W*", $bytes);
		my( $addr, $type, $data ) = unpack( "x n C X4 C x3 /a", $bytes );
		push(@hexRecords, HexRecord->new(addr=>$addr, type=>$type, data=>$data));
	}
	
	close($hexFile);
	return @hexRecords;
}

sub save() {
}

1;

