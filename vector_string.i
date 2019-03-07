//Author: sotheareth
//http://higepon.hatenablog.com/entry/20060223/1140684810
//https://stackoverflow.com/questions/11425970/how-do-you-write-a-swig-interface-file-for-a-function-that-uses-vectorstring
//https://stackoverflow.com/questions/11157157/stl-map-in-perl-using-swig
//https://stackoverflow.com/questions/6744080/when-is-a-typemap-necessary-for-swig
//http://web.mit.edu/svn/src/swig-1.3.25/Lib/cpointer.i
//https://perldoc.perl.org/perlguts.html#Working-with-SVs
//https://github.com/swig/swig/blob/master/Lib/perl5/std_vector.i
//https://perldoc.perl.org/perlxstypemap.html
//https://stackoverflow.com/questions/5251451/moving-binary-data-to-from-perl-using-swig
//https://github.com/swig/swig/tree/master/Source/Modules
//https://stackoverflow.com/questions/42277904/swig-typedef-return-array-to-perl
//https://perldoc.perl.org/perlguts.html#Calling-Perl-Routines-from-within-C-Programs
//https://perldoc.perl.org/perlguts.html#XSUBs-and-the-Argument-Stack
//http://www.fifi.org/doc/swig-doc/Perl5.html#n12
//https://perldoc.perl.org/perlxstut.html#TUTORIAL
//https://perldoc.perl.org/perlguts.html#How-do-I-convert-a-string-to-UTF-8%3f
//https://github.com/swig/swig/tree/master/Examples/perl5
//http://www.swig.org/Doc4.0/SWIGDocumentation.html
//https://stackoverflow.com/questions/35806541/swig-mutable-string-typemap-help-needed
//http://folk.uio.no/inf3330/scripting/doc/swig/manual/Library.html
//https://docs.huihoo.com/swig/3.0/SWIGDocumentation.html#Library_carrays
//http://www.swig.org/Doc1.3/Library.html#Library_nn14



%module VectorString
%include "std_string.i"
%include "typemaps.i"
%include "std_common.i"
%include "stl.i"
%include "std_vector.i"


%rename(FETCH)  std::vector<Person>::get;
%rename(STORE)  std::vector<Person>::set;
%rename(EXISTS) std::vector<Person>::has_key;
%rename(DELETE) std::vector<Person>::del;
%rename(SCALAR) std::vector<Person>::size;
%rename(CLEAR)  std::vector<Person>::clear;


%{
	#include "VectorString.h"
	#include "Person.h"
	#include "Address.h"
	#include <vector>
	
	extern list<string> addOne(string);
	extern Person getPerson();
	extern std::vector<Person> getPersonList();
	
	// For iteration support, will leak if iteration stops before the end ever.
	static std::vector<Person>::iterator iterstate;

	const Person * current(std::vector<Person>& map) {
		std::vector<Person>::iterator it = map.begin();
    	Person * res = &(*it);
    	return res;
	}
%}

%extend std::vector<Person> {
  std::vector<Person> *TIEHASH() {
    return $self;
  }
  const Person *FIRSTKEY() {
    iterstate = $self->begin();
    return current(*$self);
  }
  const Person *NEXTKEY(const std::vector<Person>&) {
    iterstate++;
    return current(*$self);
  }
}

//return scalar value for integer ptr return method
%typemap(out) list<string> {
    size_t len = $1.size();
    SV **svs = new SV*[len];
    for (size_t i=0; i<len; i++) {
        svs[i] = sv_newmortal();
        SV* perlval1 = newSVpvn("abc", 3);
        sv_setsv(svs[i], perlval1);
    }
    AV *myav = av_make(len, svs);
    delete[] svs;
    $result = newRV_noinc((SV*) myav);
    sv_2mortal($result);
    argvi++;
}

%typemap(out) Person {
	HV * rh = newHV();
	//rh = (HV *)sv_2mortal((SV *)newHV());
	
	STRLEN l;
	const char * name = $1.getName().c_str();
	SV* perlval1 = newSVpv(name, l);
	hv_store(rh, "name", 4, perlval1, 0);
	
	SV* t_data = newSViv($1.getAge());
	hv_store(rh, "age", 3, t_data, 0);
	
	$result = newRV_noinc((SV*) rh);
	sv_2mortal($result);
  	argvi++;
  	
}

%typemap(out) std::vector<Person> {
	AV * results = newAV();
	size_t size = $1.size();
	
	for(int i=0; i<size; i++){
		
		HV * rh = newHV();
		//rh = (HV *)sv_2mortal((SV *)newHV());
	
		SWIG_croak("#########Type $1_type $1_descriptor####$descriptor(Person)");
		STRLEN l;	
		const char * name = $1[i].getName().c_str();
		//SV* perlval1 = newSVpvn(name, l);  // this is not working
		SV* perlval1 = newSVpv(name, l);
		hv_store(rh, "name", 0, perlval1, 0);
		
		SV* t_data = newSViv($1[i].getAge());
		hv_store(rh, "age", 0, t_data, 0);
		
		av_push(results, newRV_inc((SV *)rh));
	}
	
	$result = newRV_inc((SV *)results);
	sv_2mortal($result);
  	argvi++;
}

//if you dont put this below it will throw error like below:
//Can't locate object method "FIRSTKEY" via package "_p_std__vectorT_Person_t" at /usr/lib64/perl5/vendor_perl/Data/Dumper.pm line 222.
%template(PersonVector) std::vector<Person>;

extern list<string> addOne(string INPUT);
extern Person getPerson();
extern std::vector<Person> getPersonList();

%include "VectorString.h"
%include "Person.h"
%include "Address.h"
