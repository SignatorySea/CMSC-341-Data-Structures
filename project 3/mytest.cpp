#include "shop.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL, SHUFFLE};
class Random {
public:
    Random(){}
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_unidist = uniform_int_distribution<>(min,max);
        }
        else if (type == UNIFORMREAL) { //the case of UNIFORMREAL to generate real numbers
            m_generator = mt19937(10);// 10 is the fixed seed value
            m_uniReal = uniform_real_distribution<double>((double)min,(double)max);
        }
        else { //the case of SHUFFLE to generate every number only once
            m_generator = mt19937(m_device());
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = mt19937(seedNum);
    }
    void init(int min, int max){
        m_min = min;
        m_max = max;
        m_type = UNIFORMINT;
        m_generator = mt19937(10);// 10 is the fixed seed value
        m_unidist = uniform_int_distribution<>(min,max);
    }
    void getShuffle(vector<int> & array){
        // this function provides a list of all values between min and max
        // in a random order, this function guarantees the uniqueness
        // of every value in the list
        // the user program creates the vector param and passes here
        // here we populate the vector using m_min and m_max
        for (int i = m_min; i<=m_max; i++){
            array.push_back(i);
        }
        shuffle(array.begin(),array.end(),m_generator);
    }

    void getShuffle(int array[]){
        // this function provides a list of all values between min and max
        // in a random order, this function guarantees the uniqueness
        // of every value in the list
        // the param array must be of the size (m_max-m_min+1)
        // the user program creates the array and pass it here
        vector<int> temp;
        for (int i = m_min; i<=m_max; i++){
            temp.push_back(i);
        }
        shuffle(temp.begin(), temp.end(), m_generator);
        vector<int>::iterator it;
        int i = 0;
        for (it=temp.begin(); it != temp.end(); it++){
            array[i] = *it;
            i++;
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = floor(result*100.0)/100.0;
        return result;
    }

    string getRandString(int size){
        // the parameter size specifies the length of string we ask for
        // to use ASCII char the number range in constructor must be set to 97 - 122
        // and the Random type must be UNIFORMINT (it is default in constructor)
        string output = "";
        for (int i=0;i<size;i++){
            output = output + (char)getRandNum();
        }
        return output;
    }
    
    int getMin(){return m_min;}
    int getMax(){return m_max;}
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    random_device m_device;
    mt19937 m_generator;
    normal_distribution<> m_normdist;//normal distribution
    uniform_int_distribution<> m_unidist;//integer uniform distribution
    uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

// the followings are sample priority functions to be used by Shop class
// Priority functions compute an integer priority for a order.
int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP


int priorityFn1(const Order &order) {
    //this function works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0 => 1 
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    if (priority == 0 ) priority = 1;
    return priority;
}

int priorityFn2(const Order &order) {
    //this function works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0 => 1
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    if (priority == 0 ) priority = 1;
    return priority;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Everything above here was provided in the project description, I've added my tester classes and main below
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tester{
    public:
    bool testMinHeapInsert();
    bool testMaxHeapInsert();
    bool testMinHeapRemove();
    bool testMaxHeapRemove();
    bool testLeftistNPL();
    bool testLeftistProperty();
    bool testPriorityChange();
    bool testMergeEmpty();
    bool testCopyConstructorNormal();
    bool testCopyConstructorEdge();
    bool testAssignmentOperatorNormal();
    bool testAssignmentOperatorEdge();
    bool testEmptyRemove();
    bool testMergeException();
    bool testSelfAssignment();
    
    private:
    bool checkHeapProperty(Order* node, prifn_t priFn, HEAPTYPE heapType);
    bool checkLeftistProperty(Order* node);
    bool checkNPL(Order* node);
    int computeNPL(Order* node);
};

int main(){
    Tester t;

    cout << "===== SHOP TEST RESULTS =====\n\n";

    cout << "1. Min-Heap Insertion:        " << (t.testMinHeapInsert() ? "PASS" : "FAIL") << endl;
    cout << "2. Max-Heap Insertion:        " << (t.testMaxHeapInsert() ? "PASS" : "FAIL") << endl;
    cout << "3. Min-Heap Removal:          " << (t.testMinHeapRemove() ? "PASS" : "FAIL") << endl;
    cout << "4. Max-Heap Removal:          " << (t.testMaxHeapRemove() ? "PASS" : "FAIL") << endl;
    cout << "5. Leftist NPL Correctness:   " << (t.testLeftistNPL() ? "PASS" : "FAIL") << endl;
    cout << "6. Leftist Property:          " << (t.testLeftistProperty() ? "PASS" : "FAIL") << endl;
    cout << "7. Priority Function Change:  " << (t.testPriorityChange() ? "PASS" : "FAIL") << endl;
    cout << "8. Merge Empty Queue:         " << (t.testMergeEmpty() ? "PASS" : "FAIL") << endl;
    cout << "9. Copy Constructor (Normal): " << (t.testCopyConstructorNormal() ? "PASS" : "FAIL") << endl;
    cout << "10. Copy Constructor (Edge):  " << (t.testCopyConstructorEdge() ? "PASS" : "FAIL") << endl;
    cout << "11. Assignment (Normal):      " << (t.testAssignmentOperatorNormal() ? "PASS" : "FAIL") << endl;
    cout << "12. Assignment (Edge):        " << (t.testAssignmentOperatorEdge() ? "PASS" : "FAIL") << endl;
    cout << "13. Empty Removal Exception:  " << (t.testEmptyRemove() ? "PASS" : "FAIL") << endl;
    cout << "14. Merge Exception:          " << (t.testMergeException() ? "PASS" : "FAIL") << endl;

    cout << "\n===== END OF TESTS =====\n";

    return 0;
}

bool Tester::checkHeapProperty(Order* node, prifn_t priFn, HEAPTYPE heapType) {
    if (node == nullptr) {
        return true;
    }

    if (node->m_left != nullptr) {
        int parent = priFn(*node);
        int leftChild = priFn(*(node->m_left));

        if ((heapType == MINHEAP && parent > leftChild) || (heapType == MAXHEAP && parent < leftChild)) {
            return false;
        }
    }

    if (node->m_right != nullptr) {
        int parent = priFn(*node);
        int rightChild = priFn(*(node->m_right));

        if ((heapType == MINHEAP && parent > rightChild) || (heapType == MAXHEAP && parent < rightChild)) {
            return false;
        }
    }
    return true;
}

bool Tester::checkLeftistProperty(Order* node) {
    if (node == nullptr) {
        return true;
    }

    int leftNPL = (node->m_left == nullptr) ? -1 : node->m_left->m_npl;
    int rightNPL = (node->m_right == nullptr) ? -1 : node->m_right->m_npl;

    if (leftNPL < rightNPL) {
        return false;
    }

    return checkLeftistProperty(node->m_left) && checkLeftistProperty(node->m_right);
}

int Tester::computeNPL(Order* node) {
    if (node == nullptr) {
        return -1;
    }

    return 1 + min(computeNPL(node->m_left), computeNPL(node->m_right));
}

bool Tester::checkNPL(Order* node) {
    if (node == nullptr) {
        return true;
    }

    int expectedNPL = computeNPL(node);

    if (node->m_npl != expectedNPL) {
        return false;
    }

    return checkNPL(node->m_left) && checkNPL(node->m_right);
}

bool Tester::testMinHeapInsert() {
    Random rand(1, 100);
    Shop testShop(priorityFn2, MINHEAP, SKEW, 1, 1);

   for (int i = 0; i < 300; i++) {
        Order o(COFFEE, ONE, TIER1, rand.getRandNum(), i, i);
        testShop.insertOrder(o);
    }

    return checkHeapProperty(testShop.m_heap, testShop.getPriorityFn(), MINHEAP);
}

bool Tester::testMaxHeapInsert() {
    Random rand(1, 100);
    Shop testShop(priorityFn1, MAXHEAP, SKEW, 1, 1);

   for (int i = 0; i < 300; i++) {
        Order o(COFFEE, ONE, TIER1, rand.getRandNum(), i, i);
        testShop.insertOrder(o);
    }

    return checkHeapProperty(testShop.m_heap, testShop.getPriorityFn(), MAXHEAP);
}

bool Tester::testMinHeapRemove() {
    Random rand(1, 100);
    Shop shop(priorityFn2, MINHEAP, SKEW, 1, 1);

    vector<int> priorities;

    for (int i = 0; i < 300; i++) {
        int val = rand.getRandNum();

        Order o(COFFEE, ONE, TIER1, val, i, i);

        int p = priorityFn2(o);
        priorities.push_back(p);

        shop.insertOrder(o);
    }
    sort(priorities.begin(), priorities.end());
    for (int i = 0; i < 300; i++) {
        Order o = shop.getNextOrder();

        if (priorityFn2(o) != priorities[i])
            return false;
    }

    return true;
}

bool Tester::testMaxHeapRemove() {
    Random rand(1, 100);
    Shop shop(priorityFn1, MAXHEAP, SKEW, 1, 1);

    vector<int> values;

    for (int i = 0; i < 300; i++) {
        int val = rand.getRandNum();
        values.push_back(val);
        shop.insertOrder(Order(COFFEE, ONE, TIER1, val, i, i));
    }

    sort(values.begin(), values.end(), greater<int>()); // descending

    for (int i = 0; i < 300; i++) {
        Order o = shop.getNextOrder();
        if (priorityFn1(o) != values[i]) return false;
    }

    return true;
}

bool Tester::testLeftistNPL() {
    Random rand(1, 100);
    Shop shop(priorityFn2, MINHEAP, LEFTIST, 1, 1);

    for (int i = 0; i < 200; i++) {
        shop.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    return checkNPL(shop.m_heap);
}

bool Tester::testLeftistProperty() {
    Random rand(1, 100);
    Shop shop(priorityFn2, MINHEAP, LEFTIST, 1, 1);

    for (int i = 0; i < 200; i++) {
        shop.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    return checkLeftistProperty(shop.m_heap);
}


bool Tester::testPriorityChange() {
    Random rand(1, 100);
    Shop shop(priorityFn2, MINHEAP, SKEW, 1, 1);

    for (int i = 0; i < 100; i++) {
        shop.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    shop.setPriorityFn(priorityFn1, MAXHEAP);

    return checkHeapProperty(shop.m_heap, shop.getPriorityFn(), MAXHEAP);
}

bool Tester::testMergeEmpty() {
    Shop empty(priorityFn2, MINHEAP, SKEW, 1, 1);
    Shop full(priorityFn2, MINHEAP, SKEW, 1, 2);

    Random rand(1, 100);

    for (int i = 0; i < 50; i++) {
        full.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    empty.mergeWithQueue(full);

    return empty.numOrders() == 50 && full.numOrders() == 0;
}

bool Tester::testCopyConstructorNormal() {
    Random rand(1, 100);
    Shop original(priorityFn2, MINHEAP, SKEW, 1, 1);

    // populate original
    for (int i = 0; i < 100; i++) {
        original.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    Shop copy(original);

    // check size
    if (copy.numOrders() != original.numOrders()) return false;

    // check heap property
    if (!checkHeapProperty(copy.m_heap, copy.getPriorityFn(), MINHEAP)) return false;

    original.getNextOrder(); // modify original

    if (copy.numOrders() == original.numOrders()) return false;

    return true;
}

bool Tester::testCopyConstructorEdge() {
    Shop original(priorityFn2, MINHEAP, SKEW, 1, 1);

    // empty copy
    Shop copy(original);

    // both should be empty
    if (copy.numOrders() != 0) return false;

    // modifying original shouldn't affect copy
    original.insertOrder(Order());

    if (copy.numOrders() != 0) return false;

    return true;
}

bool Tester::testAssignmentOperatorNormal() {
    Random rand(1, 100);
    Shop original(priorityFn2, MINHEAP, SKEW, 1, 1);

    for (int i = 0; i < 100; i++) {
        original.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    Shop assigned(priorityFn2, MINHEAP, SKEW, 2, 2);

    assigned = original;

    // size check
    if (assigned.numOrders() != original.numOrders()) return false;

    // heap property
    if (!checkHeapProperty(assigned.m_heap, assigned.getPriorityFn(), MINHEAP)) return false;

    // deep copy
    original.getNextOrder();

    if (assigned.numOrders() == original.numOrders()) return false;

    return true;
}

bool Tester::testAssignmentOperatorEdge() {
    Shop original(priorityFn2, MINHEAP, SKEW, 1, 1);
    Shop assigned(priorityFn2, MINHEAP, SKEW, 2, 2);

    // assign empty to empty
    assigned = original;

    if (assigned.numOrders() != 0) return false;

    // modify original
    original.insertOrder(Order());

    // assigned should remain unchanged
    if (assigned.numOrders() != 0) return false;

    return true;
}

bool Tester::testEmptyRemove() {
    Shop shop(priorityFn2, MINHEAP, SKEW, 1, 1);

    try {
        shop.getNextOrder();
    } catch (out_of_range&) {
        return true;
    }

    return false;
}

bool Tester::testMergeException() {
    Shop a(priorityFn1, MAXHEAP, SKEW, 1, 1);
    Shop b(priorityFn2, MINHEAP, SKEW, 1, 2);

    try {
        a.mergeWithQueue(b);
    } catch (domain_error&) {
        return true;
    }

    return false;
}

bool Tester::testSelfAssignment() {
    Random rand(1, 100);
    Shop shop(priorityFn2, MINHEAP, SKEW, 1, 1);

    for (int i = 0; i < 50; i++) {
        shop.insertOrder(Order(COFFEE, ONE, TIER1, rand.getRandNum(), i, i));
    }

    shop = shop; // self assignment

    return checkHeapProperty(shop.m_heap, shop.getPriorityFn(), MINHEAP);
}