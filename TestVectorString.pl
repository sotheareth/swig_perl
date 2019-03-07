#!/usr/local/bin/perl
use strict;
use warnings;
use JSON;
use VectorString;
use Data::Dumper;

# passed by Reference
my $result2 = VectorString::VectorString->new();
my $x = "3";


my $refrence = $result2->addOne($x);
print "Test return as array, vector, list : ". Dumper($refrence) . "\n\n";
foreach my $item(\@{$refrence}){
	print $item."\n";
}


my $person = $result2->getPerson();
print "Name: " . $person->getName() .  "\n";
print "Age: " . $person->getAge() .  "\n";
print "Test return hash as person = " . Dumper($person);
#my %person_hash = %{$person};
#print "Display data:  " . $person_hash{name} . " " . $person_hash{age} . "\n\n";


my $person_list = $result2->getPersonList();
print "Test return array of hash = " . Dumper($person_list);
foreach my $a(@{$person_list}){
	print Dumper($a->getAddress()->getCommune());
	my $person1 = $a->getName();
	my $address = $a->getAddress();
	print $person1 . " " . $address->getStreet() . "\n";
}