#include "fis.h"
#include <iostream>


using namespace fis;

class FisTest: public Fis
{
	private:
	bool assertEquals(float expected, float found, const char* testName);

	public:
	bool getBallSetLeftTest();
	bool getBallSetRightTest();
	bool getBallSetFrontTest();

	bool minMaxTest();
	bool inferTest();


};


bool FisTest::assertEquals(float expected, float found, const char* testName)
{
	if(expected == found)
	{
		std::cout << testName << ": PASSED."<<"\n";
		return true;
	}else{
		std::cout << testName << ": FAILED.\n";
		std::cout << "		Expected: " << expected << " , but instead " << found <<" was found!\n";
		return false;
	}
}


bool FisTest::getBallSetLeftTest()
{
    return assertEquals(1.0 , getBallSetLeft(-180.0), "getBallSetLeftTest 0") &&
			assertEquals(0.5 , getBallSetLeft(-90.0), "getBallSetLeftTest 1") &&
			assertEquals(0.0 , getBallSetLeft(0.0), "getBallSetLeftTest 2") &&
			assertEquals(0.0 , getBallSetLeft(90.0), "getBallSetLeftTest 3") &&
			assertEquals(0.0 , getBallSetLeft(180.0), "getBallSetLeftTest 4");
}

bool FisTest::getBallSetRightTest()
{
    return assertEquals(0.0 , getBallSetRight(-180.0), "getBallSetRightTest 0") &&
			assertEquals(0.0 , getBallSetRight(-90.0), "getBallSetRightTest 1") &&
			assertEquals(0.0 , getBallSetRight(0.0), "getBallSetRightTest 2") &&
			assertEquals(0.5 , getBallSetRight(90.0), "getBallSetRightTest 3") &&
			assertEquals(1.0 , getBallSetRight(180.0), "getBallSetRightTest 4");
}

bool FisTest::getBallSetFrontTest()
{
	return assertEquals(0.0 , getBallSetFront(-180.0), "getBallSetFront 0") &&
			assertEquals(0.0 , getBallSetFront(-90.0), "getBallSetFront 1") &&
			assertEquals(0.5 , getBallSetFront(-45.0), "getBallSetFront 2") &&
			assertEquals(1.0 , getBallSetFront(0.0), "getBallSetFront 3") &&
			assertEquals(0.5 , getBallSetFront(45.0), "getBallSetFront 4") &&
			assertEquals(0.0 , getBallSetFront(90.0), "getBallSetFront 5") &&
			assertEquals(0.0 , getBallSetFront(180.0), "getBallSetFront 6");
}

bool FisTest::minMaxTest()
{
	return assertEquals(0.12, min(0.12, 0.12004), "minTest 0") &&
			assertEquals(0.0, min(0.12, 0.0), "minTest 1") &&
			assertEquals(0.18, max(0.12, 0.0, 0.18), "MaxTest 0") &&
			assertEquals(0.0000005, max(0.000000005, 0.0000000001, 0.0000005), "MaxTest 1")
			;
}

bool FisTest::inferTest()
{
	setBallSet( 0, , );
	return true;
}


int main( int argc, char* argv[] ) {

	FisTest testGetBall;

	testGetBall.getBallSetLeftTest();	
	testGetBall.getBallSetRightTest();
	testGetBall.getBallSetFrontTest();

	FisTest minMaxTest;
	minMaxTest.minMaxTest();

	FisTest inferTest;
	inferTest.inferTest();


	return 0;
}






