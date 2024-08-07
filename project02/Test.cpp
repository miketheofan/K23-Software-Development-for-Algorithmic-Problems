#include "./Test.h"

void itemTest::setUp(){}

void itemTest::tearDown(){}

CPPUNIT_TEST_SUITE_REGISTRATION(itemTest);

void itemTest::testConstructor(){

	vector<double> Vector = {1.5,2.5};
	item i("testItem",Vector);

	string testID = i.getID();
	CPPUNIT_ASSERT(testID == "testItem");

	vector<double>* testVector = i.getVector();
	CPPUNIT_ASSERT(*testVector == Vector);
}

void itemTest::testSettersGetters(){

	vector<double> Vector = {1.5,2.5};
	item i("testItem",Vector);

	int32_t testInteger = 20;
	i.setTrick(testInteger);
	CPPUNIT_ASSERT_EQUAL(20,i.getTrick());

	int testFlag = 5;
	i.setFlag(testFlag);
	CPPUNIT_ASSERT_EQUAL(5,i.getFlag());
}

void curveTest::setUp(){}

void curveTest::tearDown(){}

CPPUNIT_TEST_SUITE_REGISTRATION(curveTest);

void curveTest::testConstructor(){

	curve testCurve("testItem");

	string testID = testCurve.getID();
	CPPUNIT_ASSERT(testID == "testItem");
}

void curveTest::testSettersGetters(){

	curve testCurve("testItem");

	vector<double> Vector = {1.5,2.5};
	item i("testItem",Vector);

	testCurve.addCoordinate(&i);

	CPPUNIT_ASSERT_EQUAL(1,testCurve.getSize());
	CPPUNIT_ASSERT_EQUAL(2,(int)testCurve.getCoordinateat(0)->getVector()->size());
}