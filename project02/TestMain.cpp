#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char** argv){

	CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();

	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);
	
	bool wasSucessful = runner.run();
	
	char* c = (char*) malloc(10 * sizeof (char));
	scanf (c,"%c");
	
	return wasSucessful ? 0 : 1;
}