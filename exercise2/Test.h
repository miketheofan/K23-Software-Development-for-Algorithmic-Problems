#ifndef TEST_H
#define TEST_H

#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <cstring>

#include "./headers/items.h"
#include "./headers/Curve.h"

class itemTest : public CPPUNIT_NS::TestFixture{

private:

	CPPUNIT_TEST_SUITE(itemTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testSettersGetters);
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void testConstructor();
	void testSettersGetters();

};

class curveTest : public CPPUNIT_NS::TestFixture{

private:

	CPPUNIT_TEST_SUITE(curveTest);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testSettersGetters);
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp();
	void tearDown();

	void testConstructor();
	void testSettersGetters();
};

#endif