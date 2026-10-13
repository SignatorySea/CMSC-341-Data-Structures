// UMBC - CMSC 341 - Spring 2026 - Proj1
#include "fuel.h"

FuelSys::FuelSys(){
    //base constructor

    m_current = nullptr;
}
FuelSys::~FuelSys(){
    //deconstrutor

    //checks if empty, if empty return
    if (m_current == nullptr) {
        return;
    }

    // holding variables
    Tank* start = m_current;
    Tank* temp = nullptr;

    //go through the list, and remove each entry
    do {
        temp = start;
        start = start -> m_next;
        delete temp;
    } while (start != m_current);

    m_current = nullptr;
}
bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0) {
    
    //creates and inserts a new tank
    
    //check failure conditions
    //check capacity
    if (tankCap <= 0){
        return false;
    }
    //check fuel
    if (tankFuel > tankCap){
        return false;
    }
    //check if id is negative
    if (tankID < 0){
        return false;
    }

    //make new tank using the constrictor
    Tank * newTank = new Tank(tankID, tankCap, tankFuel);

    //if list is empty make it the first tank
    if (m_current == nullptr) {
        Tank* newTank = new Tank(tankID, tankCap, tankFuel);
        newTank->m_next = newTank;   // points to itself
        m_current = newTank;
        return true;
    }
    
    //check for dupliate ID
    //we do this by searching the list for a matching ID
    Tank* temp = m_current;

    do {
        if (temp->m_tankID == tankID)
            return false;
        temp = temp->m_next;
    } while (temp != m_current);

    

    //if list isnt empty add after the current tank
    //set up/adjust pointers
    newTank->m_next = m_current->m_next;
    m_current->m_next = newTank;
    //add new tank
    m_current = newTank;

    //return that all worked as intended
    return true;
}

bool FuelSys::removeTank(int tankID){
    //removes a tank and reallocates pointers
    //check that the list isnt empty
        if (m_current == nullptr){
        return false;
    }
    //see if theres only one node and handle it
    if (m_current->m_next == m_current &&
        m_current->m_tankID == tankID){
            delete m_current;
            m_current = nullptr;
            return true;
        }
    // Check if current node is the one to remove
    if (m_current->m_tankID == tankID) {

        // Find the node before current
        Tank* prev = m_current;
        while (prev->m_next != m_current)
            prev = prev->m_next;

        prev->m_next = m_current->m_next;
        Tank* temp = m_current;
        m_current = prev;  // move current
        delete temp;
        return true;
    }
    //removing some node when there is more than one node
    Tank* prev = m_current;
    Tank* current =m_current->m_next;
    do {
        if (current->m_tankID == tankID){
            //remove it and realocate pointers
            prev->m_next = current->m_next;
            delete current;
            return true;
        }
        prev = current;
        current = current->m_next;
    } while (prev != m_current);

    return false; //not found
}
bool FuelSys::findTank(int tankID){
    //locates a tanks position and makes it the next node
    //check for an empty list to prevent errors
    if (m_current == nullptr){
        return false;
    }
    
    Tank* temp = m_current;

    //loop until you find the id
    do{
        if(temp->m_next->m_tankID == tankID){
            //changes where the current pointer is to the node before the ID
            m_current = temp; 
            return true;
        }
        //keep looking
        temp = temp->m_next;
    } while (temp != m_current);

    //couldnt be found
    return false;
}
bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
    //adds a pump to a specifc tank
    //check that tank exists
    if (!findTank(tankID)){
        return false;
    }

    if(!findTank(targetTank)){
        return false;
    }

    //use tank ID to find the pointer for the tank you want.
    findTank(tankID);

    Tank* parentTank = m_current->m_next;

    //check that the pump doesnt already exist
    Pump* curr = parentTank->m_pumps;
    while (curr != nullptr) {
        if (curr->m_pumpID == pumpID)
            return false;   // duplicates are a nono
        curr = curr->m_next;
    }

    //add a pump you create to the tank
    Pump* newPump = new Pump(pumpID, targetTank, parentTank->m_pumps);
    parentTank->m_pumps = newPump;

    return true;
}
bool FuelSys::removePump(int tankID, int pumpID){
    //removes a pump from a specific tank

    //check tank exists
    if(!findTank(tankID)){
        return false;
    }

    Tank* parentTank = m_current->m_next;
    //see if pump list is empty
    if(parentTank->m_pumps == nullptr){
        return false;
    }

    //traverse the pump list
    Pump* current = parentTank->m_pumps;
    Pump* previous = nullptr;

    while (current != nullptr){
        if (current->m_pumpID == pumpID){
            //removing head pump catch
            if(previous == nullptr){
                parentTank->m_pumps = current->m_next;
            } else {
                previous->m_next = current->m_next;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->m_next;
    }

    //pump failed to find
    return false;
}
int FuelSys::totalFuel() const{
    //calulates and returns fuel in all tanks
    //traverses the circulare list and adds values
    //if list is empty there is no fuel
    if (m_current == nullptr){
        return 0;
    }

    int total = 0;
    Tank* temp = m_current;

    do{
        total += temp->m_tankFuel;
        temp = temp->m_next;
    } while (temp != m_current);

    return total;
}
bool FuelSys::drain(int tankID, int pumpID, int fuel){
    //moves fuel from tank a to tank b via the pump
    
    //find source tank
    if (!findTank(tankID)){
        return false;
    }

    Tank* source = m_current->m_next;

    //find the pump
    Pump* pump = source->m_pumps;
    while (pump != nullptr && pump->m_pumpID != pumpID){
        pump = pump->m_next;
    }
    if (pump == nullptr){
        return false;
    }

    //find the target tank
    int targetID = pump->m_target;
    if (!findTank(targetID)){
        return false;
    }
    Tank* target = m_current->m_next;

    //find amount being transfered
    int sourceFuel = source->m_tankFuel;
    int targetEmpty = target->m_tankCapacity - target->m_tankFuel;

    int transferAmount = fuel;

    if (transferAmount > sourceFuel){
        transferAmount = sourceFuel;
    }
    //if theres not enough space only transfer what will fit
    if (transferAmount > targetEmpty){
        transferAmount = targetEmpty;
    }

    //perform the transfer
    source->m_tankFuel -= transferAmount;
    target->m_tankFuel += transferAmount;

    return true;

}
bool FuelSys::fill(int tankID, int fuel){
    //fills tank with specified amount of fuel
    //classic start find the tank
    if(!findTank(tankID)){
        return false;
    }

    Tank* tank = m_current->m_next;
    
    //check the space
    int emptySpace = tank->m_tankCapacity - tank->m_tankFuel;

    //how much we adding boys?
    int amountToAdd = fuel;
    if (amountToAdd > emptySpace){
        amountToAdd = emptySpace;
    }

    //add her in
    tank->m_tankFuel += amountToAdd;

    return true; //even if the tank was full and added nothing this passes
}
const FuelSys & FuelSys::operator=(const FuelSys & rhs){
    //makes a deep copy of the rhs

    //check self assignemnt
    if (this == &rhs){
        return *this;
    }
    //clear existing data so we dont have memory leaks
    if (m_current != nullptr){
        Tank* start = m_current->m_next;
        Tank* temp = start;

        do {
            //remove pumps
            Pump* p = temp->m_pumps;
            while (p != nullptr){
                Pump* deletePump = p;
                p = p->m_next;
                delete deletePump;
            }
            
            Tank* deleteTank = temp;
            temp = temp->m_next;
            delete deleteTank;
        } while (temp != start);

        m_current = nullptr;
    }

    //is rhs empty?
    if (rhs.m_current == nullptr){
        m_current = nullptr;
        return *this;
    }

    //copy it all
    Tank* rhsStart = rhs.m_current->m_next;
    Tank* rhsTemp = rhsStart;

    Tank* newStart = nullptr;
    Tank* newPrev = nullptr;

    do {
        Tank* newTank = new Tank(
            rhsTemp->m_tankID,
            rhsTemp->m_tankCapacity,
            rhsTemp->m_tankFuel
        );

        //copy pumps of the tank
        Pump* rhsPump = rhsTemp->m_pumps;
        Pump* prevPump = nullptr;

        while (rhsPump != nullptr){
            Pump* newPump = new Pump(
                rhsPump->m_pumpID,
                rhsPump->m_target
            );

            if (prevPump == nullptr){
                newTank->m_pumps = newPump;
            } else {
                prevPump->m_next = newPump;
            }

            prevPump = newPump;
            rhsPump = rhsPump->m_next;
        }
        if (newStart == nullptr){
            newStart = newTank;
        } else {
            newPrev->m_next = newTank;
        }

        newPrev = newTank;
        rhsTemp = rhsTemp->m_next;
    } while (rhsTemp != rhsStart);
    
    newPrev->m_next = newStart;

    //set current so the new copy can be called/found
    Tank* findCurrent = newStart;
    Tank* rhsFind = rhsStart;

    do{
        if(rhsFind == rhs.m_current){
            m_current = findCurrent;
            break;
        }

        findCurrent = findCurrent->m_next;
        rhsFind = rhsFind->m_next;
    } while (rhsFind != rhsStart);

    return *this;
}

/* ******************************************************
  Everything below here was provided by the assignment so dont touch it
********************************************************* */
void FuelSys::dumpSys() const{
    if (m_current != nullptr){
        Tank* tempTank = m_current->m_next;//we start at front item
        //we continue visting nodes until we reach the cursor
        while(m_current != nullptr && tempTank != m_current){
            cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
            // now dump the targets for all pumps in this tank
            // we need to traverse the list of pumps
            dumpPumps(tempTank->m_pumps);
            tempTank = tempTank->m_next;
        }
        //at the end we visit the cursor (current)
        //this also covers the case that there is only one item
        cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
        dumpPumps(tempTank->m_pumps);
        cout << "The current tank is " << m_current->m_tankID << endl;
    }
    else
        cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const{
    // this traverses the linked list to the end
    Pump* tempPump = pumps;
    while (tempPump != nullptr){
        cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
        tempPump = tempPump->m_next;
    }
}