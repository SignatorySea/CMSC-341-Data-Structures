// UMBC - CMSC 341 - Spring 2026 - Proj0
#include "art.h"
#include "art.cpp"

class Tester{
    public:
    // the following tests the normal case of create() function
    bool testCreateNormal(Art & art);

    private:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
};

int main(){

    // the following is a sample usage of the Art class
    // we create two objects and append them
    cout << "\nSample usage of the Art class:\n\n";
    Art art1(5,10);
    art1.create(10);
    cout << endl << "Dump of a 5x10 object:\n\n";
    art1.dumpColors("\u2588");// prints a box
    art1.dumpValues();
    Art art2(5,10);
    art2.create(5);
    cout << endl << "Dump of a 5x10 object:\n\n";
    art2.dumpColors("\u2588");
    art2.dumpValues();
    art1.top2Bottom(art2);
    cout << endl << "Dump of the append result (10x10):\n\n";
    art1.dumpColors("\u2588");
    cout << endl << "Dump of the append result (10x10) values:\n\n";
    art1.dumpValues();
    
    Tester tester;// test object
    {
        // testing create function for normal case
        Art art(10,10);
        cout << "\nTesting the normal case of create function:\n\n";
        if (tester.testCreateNormal(art) == true)
            cout << "\tNormal case of create passed!\n";
        else
            cout << "\tNormal case of create failed!\n";
    }
    
    cout << endl;
    return 0;
}

bool Tester::testCreateNormal(Art & art){
    // this function assumes the art object is not empty
    // all color codes must be within the correct range
    bool result = true;
    art.create(10);
    if (art.m_height > 0 && art.m_width > 0 && art.m_painting != nullptr){
        for (int i=0; i < art.m_height; i++){
            for (int j=0; j < art.m_width; j++){
                if(art.m_painting[i][j] < 10 ||
                    art.m_painting[i][j] > 99)
                    result = false;
            }   
        }
    }
    else{
        result = false;
        cout << "\tA proper object is not passed to testCreateNormal()\n";
    }
    return result;
}