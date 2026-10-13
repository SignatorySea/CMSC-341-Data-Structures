class Tester; // forward declaration of Tester class
#include "streak.h"

#include <iostream>
#include <vector>
#include <random>
#include <climits>
#include <cmath>

using namespace std;

//random class to use for testing
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
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
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

//my tester class
class Tester {
    public:
    bool testAVLInsertBalance(){
        const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);
        return isAVL(streak.m_root);
    }

    bool testAVLRemoveBalance(){
        const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);
        //removes half of the population to test if tree remains balanced after removals
        for (int i =0; i < population/2; i++) {
            streak.remove(tigers[i].getID());
        }
        return isAVL(streak.m_root);
    }
    
    bool testBSTInsert(){const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);
        return isBST(streak.m_root, INT_MIN, INT_MAX);
    }
    bool testBSTRemove(){
        const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);

        //removes half of the population to test if tree remains a BST after removals
        for (int i =0; i < population/2; i++) {
            streak.remove(tigers[i].getID());
        }

        return isBST(streak.m_root, INT_MIN, INT_MAX);
    }

    bool testRemoveFunction(){
        const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);
        
        for (int i = 0; i < 50; i++) {
            streak.remove(tigers[i].getID());
            if (streak.findTiger(tigers[i].getID())) {
                return false; // if findTiger returns true after removal, test fails
            }
        }
        return true;
    }

    bool testFindTiger(){
        const int population = 100;
        Tiger tigers[population];
        generateTigers(tigers, population);

        Streak streak(1, tigers, population);
        
        for (int i = 0; i < population/2; i++) {
            if (!streak.findTiger(tigers[i].getID())) {
                return false; // if findTiger returns false for an existing tiger, test fails
            }
        }
        return true;
    }

    bool testSetState(){
        Tiger t[1] = {Tiger(12345, CUB, MALE, ALIVE)};
        Streak streak(1, t, 1);

        streak.setState(12345, DEAD);
        return streak.count(DEAD) == 1; // if count returns 1 for DEAD state, test passes
    }

    bool testCount(){
        Tiger t[3] = {
            Tiger(12345, CUB, MALE, ALIVE),
            Tiger(12346, CUB, FEMALE, DEAD),
            Tiger(12347, OLD, MALE, DEAD)
        };

        Streak streak(1, t, 3);

        return (streak.count(CUB) == 2 && streak.count(OLD) == 1 && streak.count(DEAD) == 2); // if counts match expected values, test passes
    }

    bool testRemoveDead(){
        Tiger t[3] = {
            Tiger(12345, CUB, MALE, ALIVE),
            Tiger(12346, CUB, FEMALE, DEAD),
            Tiger(12347, OLD, MALE, DEAD)
        };

        Streak streak(1, t, 3);
        streak.removeDead();
        return (streak.count(DEAD) == 0); // if no dead tigers remain, test passes
    }

    //grid tests
    bool testSplayInsert(){
        Grid grid;
        Tiger t1[1] = {Tiger(10000)};

        grid.insert(10, t1, 1);
        grid.insert(20, t1, 1);

        // After inserting 10 and 20, 20 should be at the root due to splay operation
        return (grid.m_root->m_gridID == 20); // if root grid ID is 20, test passes
    }

    bool testGridCountSplay(){
        Grid grid;
        Tiger t1[1] = {Tiger(10000)};

        grid.insert(10, t1, 1);
        grid.insert(20, t1, 1);

        grid.count(10, ALIVE);
        return (grid.m_root->m_gridID == 10); // if root grid ID is 10 after counting, test passes
    }

    bool testGridSetState(){
        Grid grid;
        Tiger t1[1] = {Tiger(10000)};

        grid.insert(10, t1, 1);
        grid.setState(10, 10000, DEAD);

        return (grid.m_root->m_gridID == 10 && grid.count(10, DEAD) == 0); // if root grid ID is 10 and count of DEAD tigers is 0, test passes
    }

    bool testSplayBST(){
        Grid grid;
        Tiger t1[1] = {Tiger(10000)};

        for (int i = 1; i <= 20; i++) {
            grid.insert(i, t1, 1);
        }

        return checkSplayBST(grid.m_root, INT_MIN, INT_MAX); // if splay tree maintains BST properties, test passes
    }

    bool testEmptyStreak(){
        Streak streak;
        return (streak.m_root == nullptr); // if root is nullptr for an empty streak, test passes
    }

    bool testRemoveNonExistentTiger(){
        const int SIZE = 50;
        Tiger t[SIZE];

        generateTigers(t, SIZE);

        Streak s(1, t, SIZE);

        int fakeID = MAXID + 1;
        s.remove(fakeID);

        for (int i = 0; i < SIZE; i++) {
            if (!s.findTiger(t[i].getID())) return false;
        }

        return true;
    }

    bool testDuplicateInsert(){
        const int SIZE = 50;
        Tiger t[SIZE];

        generateTigers(t, SIZE);

        int duplicateID = t[0].getID();

        for (int i = 0; i < SIZE / 2; i++) {
            t[i] = Tiger(duplicateID);
        }

        Streak s(1, t, SIZE);

        return s.findTiger(duplicateID); // if duplicate ID is found, test passes (since it should be inserted only once)
    }

    bool testingSingleNodeRemove(){
            Tiger t[1];

        generateTigers(t, 1);

        Streak s(1, t, 1);

        int id = t[0].getID();
        s.remove(id);

        return !s.findTiger(id) && s.m_root == nullptr;    
    }

    bool testRemoveRootRepeatedly() {
        const int SIZE = 30;
        Tiger t[SIZE];

        generateTigers(t, SIZE);

        Streak s(1, t, SIZE);

        for (int i = 0; i < SIZE; i++) {
            if (s.m_root == nullptr) return false;

                int rootID = s.m_root->m_id;
                s.remove(rootID);
            }

        return s.m_root == nullptr;
    }

    bool testGridRemoveNonExistentTiger() {
        Grid g;

        const int SIZE = 20;
        Tiger t[SIZE];

        generateTigers(t, SIZE);

        g.insert(1, t, SIZE);

        int fakeID = MAXID + 5;
        return !g.removeTiger(1, fakeID, false);
    }
    
    bool testLargeInsert() {
        const int SIZE = 1000;
        Tiger t[SIZE];

        generateTigers(t, SIZE);

        Streak s(1, t, SIZE);

        return isAVL(s.m_root) && isBST(s.m_root, INT_MIN, INT_MAX);
    }
    //helper functions
    private:
    bool checkSplayBST(Streak* node, int min, int max){
        if (!node) return true;

        if (node->m_gridID <= min || node->m_gridID >= max)
            return false;

        return checkSplayBST(node->m_left, min, node->m_gridID) &&
               checkSplayBST(node->m_right, node->m_gridID, max);
    }

    bool isBST(Tiger* node, int min, int max){
        if (!node) return true; // empty tree is a BST
        if (node->m_id <= min || node->m_id > max) return false; // violates BST property
        return isBST(node->m_left, min, node->m_id) && isBST(node->m_right, node->m_id, max);
    }

    bool isAVL(Tiger* node){
        if (!node) return true; // empty tree is AVL

        int leftH = (node->m_left) ? node->m_left->m_height : -1;
        int rightH = (node->m_right) ? node->m_right->m_height : -1;

        if (abs(leftH - rightH) > 1) return false; // balance factor check
        if (node->m_height != 1 + max(leftH, rightH)) return false; // height check

        return isAVL(node->m_left) && isAVL(node->m_right);
    }

    void generateTigers(Tiger arr[], int size) {
        Random idGen(MINID, MAXID);
        Random ageGen(0, 2);
        Random genderGen(0, 2);

        for (int i = 0; i < size; i++) {
            int id = idGen.getRandNum();
            AGE age = static_cast<AGE>(ageGen.getRandNum());
            GENDER gender = static_cast<GENDER>(genderGen.getRandNum());

            arr[i] = Tiger(id, age, gender, ALIVE);}
    }
};

int main() {
    Tester t;

    cout << "AVL Insert Balance: " << (t.testAVLInsertBalance() ? "PASS" : "FAIL") << endl;
    cout << "BST Insert: " << (t.testBSTInsert() ? "PASS" : "FAIL") << endl;
    cout << "AVL Remove Balance: " << (t.testAVLRemoveBalance() ? "PASS" : "FAIL") << endl;
    cout << "BST Remove: " << (t.testBSTRemove() ? "PASS" : "FAIL") << endl;
    cout << "Remove Function: " << (t.testRemoveFunction() ? "PASS" : "FAIL") << endl;
    cout << "Find Tiger: " << (t.testFindTiger() ? "PASS" : "FAIL") << endl;
    cout << "Set State: " << (t.testSetState() ? "PASS" : "FAIL") << endl;
    cout << "Count Function: " << (t.testCount() ? "PASS" : "FAIL") << endl;
    cout << "Remove Dead: " << (t.testRemoveDead() ? "PASS" : "FAIL") << endl;

    cout << "Splay Insert: " << (t.testSplayInsert() ? "PASS" : "FAIL") << endl;
    cout << "Grid Count Splay: " << (t.testGridCountSplay() ? "PASS" : "FAIL") << endl;
    cout << "Grid SetState: " << (t.testGridSetState() ? "PASS" : "FAIL") << endl;
    cout << "Splay BST: " << (t.testSplayBST() ? "PASS" : "FAIL") << endl;

    cout << "Empty Streak: " << (t.testEmptyStreak() ? "PASS" : "FAIL") << endl;
    cout << "Remove Non-Existent Tiger: " << (t.testRemoveNonExistentTiger() ? "PASS" : "FAIL") << endl;
    cout << "Duplicate Insert: " << (t.testDuplicateInsert() ? "PASS" : "FAIL") << endl;
    cout << "Single Node Remove: " << (t.testingSingleNodeRemove() ? "  PASS" : "FAIL") << endl;
    cout << "Remove Root Repeatedly: " << (t.testRemoveRootRepeatedly() ? "PASS" : "FAIL") << endl;
    cout << "Grid Remove Non-Existent Tiger: " << (t.testGridRemoveNonExistentTiger() ? "PASS" : "FAIL") << endl;
    cout << "Large Insert (1000 Tigers): " << (t.testLargeInsert()  ? "PASS" : "FAIL") << endl;
     
    cout << "\nAll tests completed.\n" << endl;
    return 0;
}