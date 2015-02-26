#!/usr/bin/perl

use strict;
use warnings;
use HexFile;

my @hexRecords = HexFile::load("b452-1.hex");

for my $rec (@hexRecords) {
	my $data_str = unpack("H*", $rec->data);
	print($rec->addr . " " . $rec->type . " " . $data_str . "\n");
}




