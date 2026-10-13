#include "art.h"
#include "art.cpp"

class Tester{
    public:

    bool testConstructorErrorCase(); //tests the case of creating an art object with invalid dimensions
    bool testConstructorEdgeCase(); //tests the case of creating an art object with dimensions of 1
    bool testConstructorNormalCase(); //tests the case of creating an art object with valid dimensions

    bool testCopyConstructorNormalCase(); //tests copy constructor in a normal instance
    bool testCopyConstructorEdgeCase(); //tests copy constructor in an edge case of copying an empty object

    //tests assignment operatior
    bool testAssignmentOperatorNormalCase();
    bool testAssignmentOperatorEdgeCase();
    bool testAssignmentOperatorSelfAssignment();

    //tests left2Right in normal and edge cases
    bool testLeft2RightNormalCase();
    bool testLeft2RightDifferentHeightsErrorCase();
    bool testLeft2RightNormalToEmpty();
    bool testLeft2RightEmptyToNormal();
    bool testLeft2RightSelfAppend();

    //tests top2Bottom in normal and edge cases
    bool testTop2BottomNormalCase();
    bool testTop2BottomDifferentWidthsErrorCase();
    bool testTop2BottomNormalToEmpty();
    bool testTop2BottomEmptyToNormal();
    bool testTop2BottomSelfAppend();

    //tests reverse in normal and edge cases
    bool testReverseNormalCase();
    bool testReverseEmptyCase();
    bool testReverseEdgeCase();

    //tests rotate in normal and edge cases
    bool testRotateNormalCase();
    bool testRotateEmptyCase();
    bool testRotateEdgeCase();

    private:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
};

int main(){

        Tester tester;// test object

        //constrictor tests
        {
            // testing constructor for normal case
            cout << "\nTesting the normal case of the constructor:\n\n";
            if (tester.testConstructorNormalCase() == true) {
                cout << "\tNormal case of constructor passed!\n";
            } else {
                cout << "\tNormal case of constructor failed!\n";
            }
            
            // testing constructor for error case
            cout << "\nTesting the error case of the constructor:\n\n";
            if (tester.testConstructorErrorCase() == true) {
                cout << "\tError case of constructor passed!\n";
            } else {
                cout << "\tError case of constructor failed!\n";
            }
    
            // testing constructor for edge case
            cout << "\nTesting the edge case of the constructor:\n\n";
            if (tester.testConstructorEdgeCase() == true) {
                cout << "\tEdge case of constructor passed!\n";
            } else {
                cout << "\tEdge case of constructor failed!\n";
            }
        }

        //copy constructor tests
        {
            // testing copy constructor for normal case
            cout << "\nTesting the normal case of the copy constructor:\n\n";
            if (tester.testCopyConstructorNormalCase() == true) {
                cout << "\tNormal case of copy constructor passed!\n";
            } else {
                cout << "\tNormal case of copy constructor failed!\n";
            }
    
            // testing copy constructor for edge case
            cout << "\nTesting the edge case of the copy constructor:\n\n";
            if (tester.testCopyConstructorEdgeCase() == true) {
                cout << "\tEdge case of copy constructor passed!\n";
            } else {
                cout << "\tEdge case of copy constructor failed!\n";
            }
        }

        //assignment operator tests
        {
            // testing assignment operator for normal case
            cout << "\nTesting the normal case of the assignment operator:\n\n";
            if (tester.testAssignmentOperatorNormalCase() == true) {
                cout << "\tNormal case of assignment operator passed!\n";
            } else {
                cout << "\tNormal case of assignment operator failed!\n";
            }
    
            // testing assignment operator for edge case
            cout << "\nTesting the edge case of the assignment operator:\n\n";
            if (tester.testAssignmentOperatorEdgeCase() == true) {
                cout << "\tEdge case of assignment operator passed!\n";
            } else {
                cout << "\tEdge case of assignment operator failed!\n";
            }

            // testing assignment operator for self-assignment case
            cout << "\nTesting the self-assignment case of the assignment operator:\n\n";
            if (tester.testAssignmentOperatorSelfAssignment() == true) {
                cout << "\tSelf-assignment case of assignment operator passed!\n";
            } else {
                cout << "\tSelf-assignment case of assignment operator failed!\n";
            }
        }

        // left2Right tests
        {
            // testing left2Right for normal case
            cout << "\nTesting the normal case of left2Right:\n\n";
            if (tester.testLeft2RightNormalCase() == true) {
                cout << "\tNormal case of left2Right passed!\n";
            } else {
                cout << "\tNormal case of left2Right failed!\n";
            }
    
            // testing left2Right for different heights error case
            cout << "\nTesting the different heights error case of left2Right:\n\n";
            if (tester.testLeft2RightDifferentHeightsErrorCase() == true) {
                cout << "\tDifferent heights error case of left2Right passed!\n";
            } else {
                cout << "\tDifferent heights error case of left2Right failed!\n";
            }

            // testing left2Right when current object is empty and rhs is normal
            cout << "\nTesting left2Right when current object is empty and rhs is normal:\n\n";
            if (tester.testLeft2RightNormalToEmpty() == true) {
                cout << "\tLeft2Right empty to normal case passed!\n";
            } else {
                cout << "\tLeft2Right empty to normal case failed!\n";
            }

            // testing left2Right when current object is normal and rhs is empty
            cout << "\nTesting left2Right when current object is normal and rhs is empty:\n\n";
            if (tester.testLeft2RightEmptyToNormal() == true) {
                cout << "\tLeft2Right normal to empty case passed!\n";
            } else {
                cout << "\tLeft2Right normal to empty case failed!\n";
            }

            // testing left2Right self-append case
            cout << "\nTesting left2Right self-append case:\n\n";
            if (tester.testLeft2RightSelfAppend() == true) {
                cout << "\tLeft2Right self-append case passed!\n";
            } else {
                cout << "\tLeft2Right self-append case failed!\n";
            }
        }

        // top2Bottom tests
        {
            // testing top2Bottom for normal case
            cout << "\nTesting the normal case of top2Bottom:\n\n";
            if (tester.testTop2BottomNormalCase() == true) {
                cout << "\tNormal case of top2Bottom passed!\n";
            } else {
                cout << "\tNormal case of top2Bottom failed!\n";
            }
    
            // testing top2Bottom for different widths error case
            cout << "\nTesting the different widths error case of top2Bottom:\n\n";
            if (tester.testTop2BottomDifferentWidthsErrorCase() == true) {
                cout << "\tDifferent widths error case of top2Bottom passed!\n";
            } else {
                cout << "\tDifferent widths error case of top2Bottom failed!\n";
            }

            // testing top2Bottom when current object is empty and rhs is normal
            cout << "\nTesting top2Bottom when current object is empty and rhs is normal:\n\n";
            if (tester.testTop2BottomNormalToEmpty() == true) {
                cout << "\tTop2Bottom empty to normal case passed!\n";
            } else {
                cout << "\tTop2Bottom empty to normal case failed!\n";
            }

            // testing top2Bottom when current object is normal and rhs is empty
            cout << "\nTesting top2Bottom when current object is normal and rhs is empty:\n\n";
            if (tester.testTop2BottomEmptyToNormal() == true) {
                cout << "\tTop2Bottom normal to empty case passed!\n";
            } else {
                cout << "\tTop2Bottom normal to empty case failed!\n";
            }

            // testing top2Bottom self-append case
            cout << "\nTesting top2Bottom self-append case:\n\n";
            if (tester.testTop2BottomSelfAppend() == true) {
                cout << "\tTop2Bottom self-append case passed!\n";
            } else {
                cout << "\tTop2Bottom self-append case failed!\n";
            }
        }

        //reverse tests
        {
            // testing reverse for normal case
            cout << "\nTesting the normal case of reverse:\n\n";
            if (tester.testReverseNormalCase() == true) {
                cout << "\tNormal case of reverse passed!\n";
            } else {
                cout << "\tNormal case of reverse failed!\n";
            }
    
            // testing reverse for empty case
            cout << "\nTesting the empty case of reverse:\n\n";
            if (tester.testReverseEmptyCase() == true) {
                cout << "\tEmpty case of reverse passed!\n";
            } else {
                cout << "\tEmpty case of reverse failed!\n";
            }

            // testing reverse for edge case
            cout << "\nTesting the edge case of reverse:\n\n";
            if (tester.testReverseEdgeCase() == true) {
                cout << "\tEdge case of reverse passed!\n";
            } else {
                cout << "\tEdge case of reverse failed!\n";
            }
        }

        //rotate tests
        {
            // testing rotate for normal case
            cout << "\nTesting the normal case of rotate:\n\n";
            if (tester.testRotateNormalCase() == true) {
                cout << "\tNormal case of rotate passed!\n";
            } else {
                cout << "\tNormal case of rotate failed!\n";
            }
    
            // testing rotate for empty case
            cout << "\nTesting the empty case of rotate:\n\n";
            if (tester.testRotateEmptyCase() == true) {
                cout << "\tEmpty case of rotate passed!\n";
            } else {
                cout << "\tEmpty case of rotate failed!\n";
            }

            // testing rotate for edge case
            cout << "\nTesting the edge case of rotate:\n\n";
            if (tester.testRotateEdgeCase() == true) {
                cout << "\tEdge case of rotate passed!\n";
            } else {
                cout << "\tEdge case of rotate failed!\n";
            }
        }

    cout << "\nTesting complete!\n";
    cout << "\n\n Sig is hoping this worked right.\n";
    return 0;
} 


bool Tester::testConstructorNormalCase(){
    // this function tests the normal case of the constructor, where the dimensions are valid
    Art art(10,10);
    if (art.m_height == 10 && art.m_width == 10 && art.m_painting != nullptr){
        return true;
    }
    return false;
}

bool Tester::testConstructorErrorCase(){
    // this function tests the error case of the constructor, where the dimensions are invalid
    Art art(-1,10);
    if (art.m_height == 0 && art.m_width == 0 && art.m_painting == nullptr){
        return true;
    }
    return false;
}

bool Tester::testConstructorEdgeCase(){
    // this function tests the edge case of the constructor, where the dimensions are 1
    Art art(1,1);
    if (art.m_height == 1 && art.m_width == 1 && art.m_painting != nullptr){
        return true;
    }
    return false;
}

bool Tester::testCopyConstructorNormalCase(){
    // this function tests the normal case of the copy constructor, where the source object is valid and has data
    // copy constrictor is ART(const Art& rhs)

    Art art(10,10);
    art.create(10);
    Art copyArt(art);
    if (copyArt.m_height == 10 && copyArt.m_width == 10 && copyArt.m_painting != nullptr){
        for (int i=0; i < art.m_height; i++){
            for (int j=0; j < art.m_width; j++){
                //checks that all values of both arrays match
                if (copyArt.m_painting[i][j] != art.m_painting[i][j]){
                    return false;
                }
            }   
        }
    }

    //modify the original to check for deep copy
    art.m_painting[0][0] = 42;

    if (copyArt.m_painting[0][0] == 42){
        return false; //if the copy was modified, it was a shallow copy
    }
    //all checks passed
    return true;
    
}

bool Tester::testCopyConstructorEdgeCase(){
    // this function tests the edge case of the copy constructor, where the source object is empty
    // copy constrictor is ART(const Art& rhs)
    Art art; //default constructor creates empty object
    Art copyArt(art);
    if (copyArt.m_height == 0 && copyArt.m_width == 0 && copyArt.m_painting == nullptr){
        return true;
    }
    return false;
}

bool Tester::testAssignmentOperatorNormalCase(){
    // this function tests the normal case of the assignment operator, where the source object is valid and has data
    // Art operator= (const Art& rhs)

    Art art(10,10);
    art.create(10);
    Art assignArt;
    assignArt = art;

    //checks that dimensions match as expected
    if (assignArt.m_height != 10  || assignArt.m_width != 10 || assignArt.m_painting == nullptr){
        return false;
    }

    for (int i=0; i < art.m_height; i++){
        for (int j=0; j < art.m_width; j++){
            //checks that all values of both arrays match
            if (assignArt.m_painting[i][j] != art.m_painting[i][j]){
                return false;
            }
        }   
    }

    return true;
}

bool Tester::testAssignmentOperatorEdgeCase(){
    // this function tests the edge case of the assignment operator, where the source object is empty
    // art operator= (const Art& rhs)
    Art art; //default constructor creates empty object
    Art assignArt;
    assignArt = art;
    if (assignArt.m_height == 0 && assignArt.m_width == 0 && assignArt.m_painting == nullptr){
        return true;
    }
    return false;
}

bool Tester::testAssignmentOperatorSelfAssignment(){
    // this function tests the self-assignment case of the assignment operator
    // art operator= (const Art& rhs)
    Art art(10,10);
    art.create(10);
    //store original data for comparison
    int originalValue = art.m_painting[0][0];
    art = art; //self-assignment

    //check that dimensions are unchanged
    if (art.m_height != 10 || art.m_width != 10 || art.m_painting == nullptr){
        return false;
    }

    //check that data is unchanged
    if (art.m_painting[0][0] != originalValue){
        return false;
    }

    return true;
}

bool Tester::testLeft2RightNormalCase(){
    // this function tests the normal case of left2Right, where both objects are valid and have the same height
    //art left2Right(const Art& rhs)
    Art art1(5,10);
    art1.create(10);
    Art art2(5,10);
    art2.create(5);

    //make copies for comparison
    Art leftCopy(art1);
    Art rightCopy(art2);
    
    //append art2 to the right of art1
    bool result = art1.left2Right(art2);
    if (!result){
        return false; //function should return true in this case
    }
    //check dimensions of the result
    if (art1.m_height != 5 || art1.m_width != 20 || art1.m_painting == nullptr){
        return false;
    }
    //check that the left part of the painting matches art1 and the right part matches art2
    for (int i=0; i < art1.m_height; i++){
        //left side
        for (int j = 0; j < leftCopy.m_width; j++){
            if (art1.m_painting[i][j] != leftCopy.m_painting[i][j]){
                return false;
            }
        }   

        //right side
        for (int j = 0; j < rightCopy.m_width; j++){
            if (art1.m_painting[i][j + leftCopy.m_width] != rightCopy.m_painting[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool Tester::testLeft2RightDifferentHeightsErrorCase(){
    // this function tests the error case of left2Right, where the objects have different heights
    Art art1(5,10);
    art1.create(10);
    Art art2(4,10);
    art2.create(5);

    //copy for comparison
    Art original(art1);


    bool result = art1.left2Right(art2);
    if (result){
        return false; //function should return false in this case
    }
    //check that art1 is unchanged
    if (art1.m_height != original.m_height || art1.m_width != original.m_width || art1.m_painting == nullptr){
        return false;
    }
    for (int i=0; i < art1.m_height; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != original.m_painting[i][j]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testLeft2RightNormalToEmpty(){
    // this function tests left2Right when the current object is empty and the rhs is normal

    Art art1; //empty object
    Art art2(5,10);
    art2.create(5);

    //copy for comparison
    Art leftCopy(art1);

    bool result = art1.left2Right(art2);
    if (result){
        return false; //function should fail
    }

    //check dimensions of the results
    if (art1.m_height != leftCopy.m_height || art1.m_width != leftCopy.m_width || art1.m_painting != leftCopy.m_painting){
        return false;
    }
    return true;
}

bool Tester::testLeft2RightEmptyToNormal(){
    // this function tests left2Right when the current object is normal and the rhs is empty

    Art art1(5,10);
    art1.create(10);
    Art art2; //empty object

    //copy for comparison
    Art leftCopy(art1);

    bool result = art1.left2Right(art2);
    if (result){
        return false; //function should fail
    }
    //check dimensions of the result
    if (art1.m_height != leftCopy.m_height || art1.m_width != leftCopy.m_width || art1.m_painting == nullptr){
        return false;
    }
    
    // check contents matchs copy
    for (int i = 0; i < art1.m_height; i++){
        for (int j = 0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != leftCopy.m_painting[i][j]){
                return false;
            }
        }
    }

    return true;
}

bool Tester::testLeft2RightSelfAppend(){
    // this function tests left2Right when the current object is appended to itself

    Art art1(5,10);
    art1.create(10);

    // copy for comparison
    Art original(art1);

    bool result = art1.left2Right(art1);
    if (!result){
        return false; //function should return true in this case
    }

    //check dimensions of the result
    if (art1.m_height != original.m_height || art1.m_width != (2 * original.m_width) || art1.m_painting == nullptr){
        return false;
    }
    //check that the left part of the painting matches the original and the right part also matches the original
    for (int i=0; i < art1.m_height; i++){
        for (int j=0; j < original.m_width; j++){
            if (art1.m_painting[i][j] != original.m_painting[i][j]){
                return false;
            }
        }   
        for (int j=original.m_width; j < (2 * original.m_width); j++){
            if (art1.m_painting[i][j] != original.m_painting[i][j - original.m_width]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testTop2BottomNormalCase(){
    // this function tests the normal case of top2Bottom, where both objects are valid and have the same width
    //art top2Bottom(const Art& bottom)
    Art art1(5,10);
    art1.create(10);
    Art art2(5,10);
    art2.create(5);

    //make copies for comparison
    Art topCopy(art1);
    Art bottomCopy(art2);

    bool result = art1.top2Bottom(art2);
    if (!result){
        return false; //function should return true in this case
    }
    //check dimensions of the result
    if (art1.m_height != 10 || art1.m_width != 10 || art1.m_painting == nullptr){
        return false;
    }
    //check that the top part of the painting matches art1 and the bottom part matches art2
    for (int i=0; i < 5; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != topCopy.m_painting[i][j]){
                return false;
            }
        }   
    }
    for (int i=5; i < 10; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != bottomCopy.m_painting[i-5][j]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testTop2BottomDifferentWidthsErrorCase(){
    // this function tests the error case of top2Bottom, where the objects have different widths
    Art art1(5,10);
    art1.create(10);
    Art art2(5,9);
    art2.create(5);

    //copy for comparison
    Art original(art1);

    bool result = art1.top2Bottom(art2);
    if (result){
        return false; //function should return false in this case
    }
    //check that art1 is unchanged
    if (art1.m_height != original.m_height || art1.m_width != original.m_width || art1.m_painting == nullptr){
        return false;
    }
    for (int i=0; i < art1.m_height; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != original.m_painting[i][j]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testTop2BottomNormalToEmpty(){
    // this function tests top2Bottom when the current object is empty and the rhs is normal

    Art art1; //empty object
    Art art2(5,10);
    art2.create(5);

    //copy for comparison
    Art topCopy(art1);

    bool result = art1.top2Bottom(art2);
    if (result){
        return false;
    }

    //check dimensions of the result
    if (art1.m_height != topCopy.m_height || art1.m_width != topCopy.m_width || art1.m_painting != topCopy.m_painting){
        return false;
    }
    
    return true;
}

bool Tester::testTop2BottomEmptyToNormal(){
    // this function tests top2Bottom when the current object is normal and the rhs is empty

    Art art1(5,10);
    art1.create(10);
    Art art2; //empty object

    //copy for comparison
    Art topCopy(art1);

    bool result = art1.top2Bottom(art2);
    if (result){
        return false;
    }
    //check dimensions of the result
    if (art1.m_height != topCopy.m_height || art1.m_width != topCopy.m_width || art1.m_painting == nullptr){
        return false;
    }

    //check that the painting matches the original art1
    for (int i=0; i < art1.m_height; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != topCopy.m_painting[i][j]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testTop2BottomSelfAppend(){
    // this function tests top2Bottom when the current object is appended to itself

    Art art1(5,10);
    art1.create(10);

    //copy for comparison
    Art original(art1);

    bool result = art1.top2Bottom(art1);
    if (!result){
        return false; //function should return true in this case
    }

    //check dimensions of the result
    if (art1.m_height != (original.m_height * 2) || art1.m_width != original.m_width || art1.m_painting == nullptr){
        return false;
    }

    //check that the top part of the painting matches the original and the bottom part also matches the original
    for (int i=0; i < original.m_height; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != original.m_painting[i][j]){
                return false;
            }
        }   

        
    }
    for (int i=original.m_height; i < art1.m_height; i++){
        for (int j=0; j < art1.m_width; j++){
            if (art1.m_painting[i][j] != original.m_painting[i - original.m_height][j]){
                return false;
            }
        }   
    }

    return true;
}

bool Tester::testReverseNormalCase(){
    // this function tests the normal case of reverse, where the object is valid and has data
    Art art(5,10);
    art.create(10);

    //copy for comparison
    Art original(art);

    bool result = art.reverse();
    if (!result){
        return false; //function should return true in this case
    }
    //check that the painting is reversed correctly
    for (int i=0; i < art.m_height; i++){
        for (int j=0; j < art.m_width; j++){
            if (art.m_painting[i][j] != original.m_painting[i][art.m_width - 1 - j]){
                return false;
            }
        }   
    }
    return true;
}

bool Tester::testReverseEmptyCase(){
    // this function tests the case of reverse when the object is empty
    Art art; //empty object
    bool result = art.reverse();

    if (result){
        return false; //function should return false in this case
    }
    //check that the object is unchanged
    if (art.m_height != 0 || art.m_width != 0 || art.m_painting != nullptr){
        return false;
    }
    return true;
}

bool Tester::testReverseEdgeCase(){
    // this function tests the case of reverse when the object has dimensions of 1
    Art art(1,1);
    art.create(10);

    //copy for comparison
    Art original(art);

    bool result = art.reverse();
    if (!result){
        return false; //function should return true in this case
    }
    //check that the painting is unchanged as reversing a 1x1 should have no effect
    if (art.m_painting[0][0] != original.m_painting[0][0]){
        return false;
    }
    return true;
}

bool Tester::testRotateNormalCase(){
    // this function tests the normal case of rotate, where the object is valid and has data
    Art art(4,4);
    art.create(10);
    
    //original quadrants for comparison
    int hMid = art.m_height / 2;
    int wMid = art.m_width / 2;

    vector<vector<int>> Q1(hMid, vector<int>(wMid)); // top-left
    vector<vector<int>> Q2(hMid, vector<int>(wMid)); // top-right 
    vector<vector<int>> Q3(hMid, vector<int>(wMid)); // bottom-left
    vector<vector<int>> Q4(hMid, vector<int>(wMid)); // bottom-right

    for (int i = 0; i < hMid; i++) {
        for (int j = 0; j < wMid; j++) {
            Q1[i][j] = art.m_painting[i][j];           // top-left
            Q2[i][j] = art.m_painting[i][j + wMid];   // top-right
            Q3[i][j] = art.m_painting[i + hMid][j];   // bottom-left
            Q4[i][j] = art.m_painting[i + hMid][j + wMid]; // bottom-right
        }
    }

    bool result = art.rotate();
    if (!result){
        return false; 
    }

    //check that the painting is rotated correctly
    //top-left = old bottom-left
    for (int i=0; i < hMid; i++){
        for (int j=0; j < wMid; j++){
            if (art.m_painting[i][j] != Q3[i][j]){
                return false;
            }
        }   
    }

    //top right = old top-left
    for (int i=0; i < hMid; i++){
        for (int j=0; j < wMid; j++){
            if (art.m_painting[i][j + wMid] != Q1[i][j]){
                return false;
            }
        }   
    }

    //bottom right = old top-right
    for (int i=0; i < hMid; i++){
        for (int j=0; j < wMid; j++){
            if (art.m_painting[i + hMid][j + wMid] != Q2[i][j]){
                return false;
            }
        }   
    }

    //bottom left = old bottom-right
    for (int i=0; i < hMid; i++){
        for (int j=0; j < wMid; j++){
            if (art.m_painting[i + hMid][j] != Q4[i][j]){
                return false;
            }
        }   
    }

    return true;
}

bool Tester::testRotateEmptyCase(){
    // this function tests the case of rotate when the object is empty
    Art art; //empty object
    bool result = art.rotate();
    if (result){
        return false; //function should return false in this case
    }

    //check that the object is unchanged
    if (art.m_height != 0 || art.m_width != 0 || art.m_painting != nullptr){
        return false;
    }
    return true;
}

bool Tester::testRotateEdgeCase(){
    // this function tests the case of rotate when the object has odd dimensions
    Art art(3,3);
    art.create(10);
    bool result = art.rotate();

    //if the painting is rotated it messed up
    if (result){
        return false; 
    }
    
    return true;
}
