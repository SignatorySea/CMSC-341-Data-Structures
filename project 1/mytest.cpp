#include <iostream>
#include "fuel.h"
#include "fuel.cpp"

using namespace std;

class Tester{
    public:
    //tank tests
    bool testAddTankNormal();
    bool testAddTankDuplicate();
    bool testAddTankNegativeID();
    bool testAddTankInvalidCapacity();

    bool testRemoveTankNormal();
    bool testRemoveTankFailure();

    bool testFindTankNormal();
    bool testFindTankFailure();

    // Pump Tests
    bool testAddPumpNormal();
    bool testAddPumpDuplicate();
    bool testAddPumpInvalidTank();

    bool testRemovePumpNormal();
    bool testRemovePumpFailure();
    bool testRemovePumpInvalidTank();

    // Fill / Drain
    bool testFillNormal();
    bool testFillOverCapacity();
    bool testFillFailure();

    bool testDrainNormal();
    bool testDrainInvalidSource();
    bool testDrainFailure();
    bool testDrainOverCapacity();
    bool testDrainInvalidTarget();

    bool testDrainSourceEmpty();
    bool testDrainUnderfilledSource();

    bool testTotalFuel();
    bool testTotalFuelEmpty();

    // Assignment Operator
    bool testAssignmentNormal();
    bool testAssignmentDeepCopy();
    bool testAssignmentSelf();
};

// =================================
//              Main
// ================================

int main() {

    Tester tester;

    cout << "AddTankNormal: "
         << (tester.testAddTankNormal() ? "PASS" : "FAIL") << endl;

    cout << "AddTankDuplicate: "
         << (tester.testAddTankDuplicate() ? "PASS" : "FAIL") << endl;

    cout << "AddTankNegativeID: "
         << (tester.testAddTankNegativeID() ? "PASS" : "FAIL") << endl;

    cout << "AddTankInvalidCapacity: "
         << (tester.testAddTankInvalidCapacity() ? "PASS" : "FAIL") << endl;


    cout << "RemoveTankNormal: "
         << (tester.testRemoveTankNormal() ? "PASS" : "FAIL") << endl;

    cout << "RemoveTankFailure: "
         << (tester.testRemoveTankFailure() ? "PASS" : "FAIL") << endl;


    cout << "FindTankNormal: "
         << (tester.testFindTankNormal() ? "PASS" : "FAIL") << endl;

    cout << "FindTankFailure: "
         << (tester.testFindTankFailure() ? "PASS" : "FAIL") << endl;


    // Pump Tests
    cout << "AddPumpNormal: "
         << (tester.testAddPumpNormal() ? "PASS" : "FAIL") << endl;

    cout << "AddPumpDuplicate: "
         << (tester.testAddPumpDuplicate() ? "PASS" : "FAIL") << endl;

    cout << "AddPumpInvalidTank: "
         << (tester.testAddPumpInvalidTank() ? "PASS" : "FAIL") << endl;


    cout << "RemovePumpNormal: "
         << (tester.testRemovePumpNormal() ? "PASS" : "FAIL") << endl;

    cout << "RemovePumpFailure: "
         << (tester.testRemovePumpFailure() ? "PASS" : "FAIL") << endl;

    cout << "RemovePumpInvalidTank: "
         << (tester.testRemovePumpInvalidTank() ? "PASS" : "FAIL") << endl;


    // Fill Tests
    cout << "FillNormal: "
         << (tester.testFillNormal() ? "PASS" : "FAIL") << endl;

    cout << "FillOverCapacity: "
         << (tester.testFillOverCapacity() ? "PASS" : "FAIL") << endl;

    cout << "FillFailure: "
         << (tester.testFillFailure() ? "PASS" : "FAIL") << endl;


    // Drain Tests
    cout << "DrainNormal: "
         << (tester.testDrainNormal() ? "PASS" : "FAIL") << endl;

    cout << "DrainOverCapacity: "
         << (tester.testDrainOverCapacity() ? "PASS" : "FAIL") << endl;

    cout << "DrainInvalidSource: "
         << (tester.testDrainInvalidSource() ? "PASS" : "FAIL") << endl;

    cout << "DrainInvalidTarget: "
         << (tester.testDrainInvalidTarget() ? "PASS" : "FAIL") << endl;

    cout << "DrainFailure: "
         << (tester.testDrainFailure() ? "PASS" : "FAIL") << endl;

    cout << "DrainSourceEmpty: "
         << (tester.testDrainSourceEmpty() ? "PASS" : "FAIL") << endl;

    cout << "DrainUnderfilledSource: "
         << (tester.testDrainUnderfilledSource() ? "PASS" : "FAIL") << endl;


    // Total Fuel
    cout << "TotalFuel: "
         << (tester.testTotalFuel() ? "PASS" : "FAIL") << endl;

    cout << "TotalFuelEmpty: "
         << (tester.testTotalFuelEmpty() ? "PASS" : "FAIL") << endl;


    // Assignment Operator
    cout << "AssignmentNormal: "
         << (tester.testAssignmentNormal() ? "PASS" : "FAIL") << endl;

    cout << "AssignmentDeepCopy: "
         << (tester.testAssignmentDeepCopy() ? "PASS" : "FAIL") << endl;

    cout << "AssignmentSelf: "
         << (tester.testAssignmentSelf() ? "PASS" : "FAIL") << endl;


    return 0;
}


// =====================================
//       Tester implementations
// =====================================

bool Tester::testAddTankNormal(){
    FuelSys sys;
    bool a = sys.addTank(1, 100, 50);
    bool b = sys.addTank(2,200,0);
    bool c = sys.addTank(3, 300, 0);

    return a && b && c;
}

bool Tester::testAddTankDuplicate(){
    FuelSys sys;
    sys.addTank(1,100,0);
    return !sys.addTank(1,200,0);
}

bool Tester::testAddTankNegativeID(){
    FuelSys sys;
    return !sys.addTank(-1, 100, 0);
}

bool Tester::testAddTankInvalidCapacity(){
    FuelSys sys;
    return !sys.addTank(1, -100, 0);
}


bool Tester::testRemoveTankNormal(){
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 0);
    sys.addTank(3, 100, 0);

    bool a = sys.removeTank(1);
    bool b = sys.removeTank(2);
    bool c = sys.removeTank(3);

    return a && b && c && sys.totalFuel() == 0;
}

bool Tester::testRemoveTankFailure(){
    FuelSys sys;
    sys.addTank(1,100,0);
    return !sys.removeTank(2);
}

bool Tester::testFindTankNormal() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 0);
    sys.addTank(3, 100, 0);

    bool a = sys.findTank(1);
    bool b = sys.findTank(2);
    bool c = sys.findTank(3);

    return a && b && c;
}

bool Tester::testFindTankFailure() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    return !sys.findTank(99);
}


bool Tester::testAddPumpNormal() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 0);

    bool a = sys.addPump(1, 10, 2);
    bool b = sys.addPump(1, 20, 2);

    return a && b;
}

bool Tester::testAddPumpDuplicate() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 0);

    sys.addPump(1, 10, 2);
    return !sys.addPump(1, 10, 2);
}

bool Tester::testAddPumpInvalidTank(){
    FuelSys sys;
    sys.addTank(1,20,0);
    return !sys.addPump(2, 30, 3);
}

bool Tester::testRemovePumpNormal(){
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 0);

    sys.addPump(1, 10, 2);
    sys.addPump(1, 20, 2);

    bool a = sys.removePump(1, 10);
    bool b = sys.removePump(1, 20);

    return a && b;
}

bool Tester::testRemovePumpFailure(){
    FuelSys sys;
    sys.addTank(1,100,50);
    return !sys.removePump(1,99);
}

bool Tester::testRemovePumpInvalidTank(){
    FuelSys sys;
    sys.addTank(1, 100, 0);

    return !sys.removePump(1, 99);
}


bool Tester::testFillNormal() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.fill(1, 50);
    return sys.totalFuel() == 50;
}

bool Tester::testFillOverCapacity() {
    FuelSys sys;
    sys.addTank(1, 100, 0);
    sys.fill(1, 200);
    return sys.totalFuel() == 100;
}

bool Tester::testFillFailure() {
    FuelSys sys;
    return !sys.fill(99, 50);
}




bool Tester::testDrainNormal() {
    FuelSys sys;
    sys.addTank(1, 100, 50);
    sys.addTank(2, 100, 0);
    sys.addPump(1, 10, 2);

    sys.drain(1, 10, 30);

    return sys.totalFuel() == 50; 
}

bool Tester::testDrainInvalidSource() {
    FuelSys sys;
    return !sys.drain(99, 1, 10);
}

bool Tester::testDrainFailure() {
    FuelSys sys;
    sys.addTank(1, 100, 50);
    return !sys.drain(1, 99, 10);
}

bool Tester::testDrainOverCapacity(){
    FuelSys sys;

    sys.addTank(1, 100, 80);

    // Target tank: 90 fuel (only 10 space left)
    sys.addTank(2, 100, 90);

    // Add pump from tank 1 → tank 2
    sys.addPump(1, 10, 2); 

    // Try to drain 50 (but only 10 can fit)
    bool result = sys.drain(1, 10, 50);

    if (!result)
        return false;

    Tank* source = sys.findTank(1) ? sys.m_current->m_next : nullptr;
    Tank* target = sys.findTank(2) ? sys.m_current->m_next : nullptr;

    if (source == nullptr || target == nullptr)
        return false;

    // Source should lose only 10
    if (source->m_tankFuel != 70)
        return false;

    // Target should now be full
    if (target->m_tankFuel != 100)
        return false;

    return true;
}

bool Tester::testDrainInvalidTarget() {
    FuelSys sys;

    // Only source tank exists
    sys.addTank(1, 100, 80);

    // Pump points to non-existent tank 999
    sys.addPump(1, 10, 999);

    bool result = sys.drain(1, 10, 20);

    if (result)   // should fail
        return false;

    // Fuel should remain unchanged
    if (sys.findTank(1)) {
        Tank* source = sys.m_current->m_next;
        if (source->m_tankFuel != 80)
            return false;
    }

    return true;
}

bool Tester::testDrainSourceEmpty() {
    FuelSys sys;

    sys.addTank(1, 100, 0);
    sys.addTank(2, 100, 20);

    sys.addPump(1, 10, 2);

    bool result = sys.drain(1, 10, 50);

    if (!result)
        return false;

    // Source should still be 0
    if (sys.findTank(1)) {
        Tank* source = sys.m_current->m_next;
        if (source->m_tankFuel != 0)
            return false;
    }

    // Target should remain unchanged
    if (sys.findTank(2)) {
        Tank* target = sys.m_current->m_next;
        if (target->m_tankFuel != 20)
            return false;
    }

    return true;
}

bool Tester::testDrainUnderfilledSource() {
    FuelSys sys;

    sys.addTank(1, 100, 10);
    sys.addTank(2, 100, 0);

    sys.addPump(1, 10, 2);

    bool result = sys.drain(1, 10, 50);

    if (!result)
        return false;

    // Source should now be empty
    if (sys.findTank(1)) {
        Tank* source = sys.m_current->m_next;
        if (source->m_tankFuel != 0)
            return false;
    }

    // Target should gain only 10
    if (sys.findTank(2)) {
        Tank* target = sys.m_current->m_next;
        if (target->m_tankFuel != 10)
            return false;
    }

    return true;
}

bool Tester::testTotalFuel() {
    FuelSys sys;
    sys.addTank(1, 100, 40);
    sys.addTank(2, 100, 60);
    return sys.totalFuel() == 100;
}

bool Tester::testTotalFuelEmpty() {
    FuelSys sys;
    return sys.totalFuel() == 0;
}

bool Tester::testAssignmentNormal() {
    FuelSys a;
    a.addTank(1, 100, 50);

    FuelSys b;
    b = a;

    return b.totalFuel() == 50;
}

bool Tester::testAssignmentDeepCopy() {
    FuelSys a;
    a.addTank(1, 100, 50);

    FuelSys b;
    b = a;

    b.fill(1, 20);

    return a.totalFuel() == 50 && b.totalFuel() == 70;
}

bool Tester::testAssignmentSelf() {
    FuelSys a;
    a.addTank(1, 100, 50);

    a = a;

    return a.totalFuel() == 50;
}