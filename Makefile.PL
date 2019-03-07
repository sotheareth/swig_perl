use Config;
use ExtUtils::MakeMaker;
use vars qw($version);
my $version='0.1';

my $cmd = qq{swig -c++ -outdir . -o vectorstring_wrap.cxx -perl vector_string.i};
print "Executing $cmd\n";
system($cmd);
if($?==-1) {
	die("failed to execute: $!");
} elsif($?>0) {
	die("Error creating perl:wq
 wrapper: $?");
}
WriteMakefile( 	
		NAME => 'VectorString',
		CC => 'g++',
		LD => 'g++',
		CCFLAGS => '-std=c++11',
		LIBS => '-L/usr/lib64 -lmysqlcppconn',
		INC => '-I/usr/include/cppconn',
		INST_LIB => '.',
		INST_ARCHLIB => '.',
		VERSION => $version,
		PREREQ_PM => {},
		DEFINE => '-DMACOSX '.$Config{ccflags},
		INC => '',
		OBJECT => '$(O_FILES)',
		clean => { FILES => 'vectorstring.pm vectorstring_wrap.cxx auto', },
		PMLIBDIRS => [ '', '' ], );
