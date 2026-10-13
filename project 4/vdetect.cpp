// CMSC 341 - Spring 26 - Project 4
#include "vdetect.h"
VDetect::VDetect(int size, hash_fn hash, prob_t probing = DEFPOLCY){
    if (size < MINPRIME) size = MINPRIME;
    else if (size > MAXPRIME) size = MAXPRIME;

    if (!isPrime(size)) size = findNextPrime(size);
    if (size > MAXPRIME) size = MAXPRIME;

    m_currentCap = size;
    m_currentTable = new Virus*[m_currentCap];

    for (int i = 0; i < m_currentCap; i++) {
        m_currentTable[i] = nullptr; //empty slot
    }

    m_currentSize = 0;
    m_currNumDeleted = 0;
    m_currProbing = probing;

    m_oldTable = nullptr;
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;
    m_oldProbing = probing;

    m_transferIndex = 0;

    m_hash = hash;
    m_newPolicy = probing;
}

VDetect::~VDetect(){
    if (m_currentTable != nullptr) {
        for (int i = 0; i < m_currentCap; i++) {
            delete m_currentTable[i];
        }
        delete[] m_currentTable;
        m_currentTable = nullptr;
    }

    if (m_oldTable != nullptr) {
        for (int i = 0; i < m_oldCap; i++) {
            delete m_oldTable[i];
        }
        delete[] m_oldTable;
        m_oldTable = nullptr;
    }
    
}

void VDetect::changeProbPolicy(prob_t policy){
    m_newPolicy = policy;
}

bool VDetect::insert(Virus virus) {
    if (virus.getID() < MINID || virus.getID() > MAXID)
        return false;

    if (getVirus(virus.getKey(), virus.getID()).getID() != -1)
        return false;

    int index = m_hash(virus.getKey()) % m_currentCap;

    int i = 0;
    while (i < m_currentCap) {
        int probeIndex;

        if (m_currProbing == LINEAR)
            probeIndex = (index + i) % m_currentCap;
        else if (m_currProbing == QUADRATIC)
            probeIndex = (index + i * i) % m_currentCap;
        else {
            int step = 1 + (m_hash(virus.getKey()) % (m_currentCap - 1));
            probeIndex = (index + i * step) % m_currentCap;
        }

        if (m_currentTable[probeIndex] == nullptr ||
            !m_currentTable[probeIndex]->getUsed()) {

            if (m_currentTable[probeIndex] == nullptr) {
                m_currentTable[probeIndex] = new Virus(virus);
                m_currentSize++;
            }else {
                *m_currentTable[probeIndex] = virus;
                m_currNumDeleted--;
            }
            m_currentTable[probeIndex]->setUsed(true);
            
            break;
        }

        i++;
    }


    float loadFactor = float(m_currentSize) / m_currentCap;

    if (loadFactor > 0.5 && m_oldTable == nullptr) {
        m_oldTable = m_currentTable;
        m_oldCap = m_currentCap;
        m_oldSize = m_currentSize;
        m_oldNumDeleted = m_currNumDeleted;
        m_oldProbing = m_currProbing;

        int newSize = findNextPrime(4 * (m_oldSize - m_oldNumDeleted));

        m_currentCap = newSize;
        m_currentTable = new Virus*[m_currentCap];

        for (int i = 0; i < m_currentCap; i++)
            m_currentTable[i] = nullptr;

        m_currentSize = 0;
        m_currNumDeleted = 0;
        m_currProbing = m_newPolicy;
        m_transferIndex = 0;
    }
    
    rehashStep();

    return true;
}

bool VDetect::remove(Virus virus) {

    int index = m_hash(virus.getKey()) % m_currentCap;

    for (int i = 0; i < m_currentCap; i++) {
        int probeIndex;

        if (m_currProbing == LINEAR)
            probeIndex = (index + i) % m_currentCap;
        else if (m_currProbing == QUADRATIC)
            probeIndex = (index + i * i) % m_currentCap;
        else {
            int step = 1 + (m_hash(virus.getKey()) % (m_currentCap - 1));
            probeIndex = (index + i * step) % m_currentCap;
        }

        if (m_currentTable[probeIndex] == nullptr)
            break;

        if (m_currentTable[probeIndex]->getUsed() &&
            m_currentTable[probeIndex]->getKey() == virus.getKey() &&
            m_currentTable[probeIndex]->getID() == virus.getID()) {

            m_currentTable[probeIndex]->setUsed(false);
            m_currNumDeleted++;

            float ratio = deletedRatio();

            if (ratio > 0.8 && m_oldTable == nullptr) {
                m_oldTable = m_currentTable;
                m_oldCap = m_currentCap;
                m_oldSize = m_currentSize;
                m_oldNumDeleted = m_currNumDeleted;
                m_oldProbing = m_currProbing;

                int newSize = findNextPrime(4 * (m_oldSize - m_oldNumDeleted));

                m_currentCap = newSize;
                m_currentTable = new Virus*[m_currentCap];

                for (int j = 0; j < m_currentCap; j++)
                    m_currentTable[j] = nullptr;

                m_currentSize = 0;
                m_currNumDeleted = 0;
                m_currProbing = m_newPolicy;
                m_transferIndex = 0;
            }

            rehashStep();

            return true;
        }
    }
    rehashStep();

    return false;
}


const Virus VDetect::getVirus(string sequence, int id) const
{
    // ---- search current ----
    int index = m_hash(sequence) % m_currentCap;

    for (int i = 0; i < m_currentCap; i++) {
        int probeIndex;

        if (m_currProbing == LINEAR)
            probeIndex = (index + i) % m_currentCap;
        else if (m_currProbing == QUADRATIC)
            probeIndex = (index + i*i) % m_currentCap;
        else {
            int step = 1 + (m_hash(sequence) % (m_currentCap - 1));
            probeIndex = (index + i * step) % m_currentCap;
        }

        if (m_currentTable[probeIndex] == nullptr)
            break;

        if (m_currentTable[probeIndex]->getUsed() &&
            m_currentTable[probeIndex]->getKey() == sequence &&
            m_currentTable[probeIndex]->getID() == id) {

            return *(m_currentTable[probeIndex]);
        }
    }

    // ---- search old ----
    if (m_oldTable != nullptr) {

        int indexOld = m_hash(sequence) % m_oldCap;

        for (int i = 0; i < m_oldCap; i++) {
            int probeIndex;

            if (m_oldProbing == LINEAR)
                probeIndex = (indexOld + i) % m_oldCap;
            else if (m_oldProbing == QUADRATIC)
                probeIndex = (indexOld + i*i) % m_oldCap;
            else {
                int step = 1 + (m_hash(sequence) % (m_oldCap - 1));
                probeIndex = (indexOld + i * step) % m_oldCap;
            }

            if (m_oldTable[probeIndex] == nullptr)
                break;

            if (m_oldTable[probeIndex]->getUsed() &&
                m_oldTable[probeIndex]->getKey() == sequence &&
                m_oldTable[probeIndex]->getID() == id) {

                return *(m_oldTable[probeIndex]);
            }
        }
    }

    return Virus("", -1, false);
}

bool VDetect::updateID(Virus virus, int id){
    if (id < MINID || id > MAXID) return false;

    if (getVirus(virus.getKey(), virus.getID()).getID() == -1) return false;

    int index = m_hash(virus.getKey()) % m_currentCap;

    for (int i = 0; i < m_currentCap; i++) {
        int probeIndex;

        if (m_currProbing == LINEAR) {
            probeIndex = (index + i) % m_currentCap;
        } else if (m_currProbing == QUADRATIC) {
            probeIndex = (index + i * i) % m_currentCap;
        } else {
            int step = 1 + (m_hash(virus.getKey()) % (m_currentCap - 1));
            probeIndex = (index + i * step) % m_currentCap;
        }

        if (m_currentTable[probeIndex] == nullptr) {
            break; // not found
        }

        if (m_currentTable[probeIndex]->m_used &&
            m_currentTable[probeIndex]->getKey() == virus.getKey() &&
            m_currentTable[probeIndex]->getID() == virus.getID()) {

            m_currentTable[probeIndex]->setID(id);
            return true;
        }
    }

    if (m_oldTable != nullptr) {
        int indexOld = m_hash(virus.getKey()) % m_oldCap;

        for (int i = 0; i < m_oldCap; i++) {
            int probeIndex;

            if (m_oldProbing == LINEAR) {
                probeIndex = (indexOld + i) % m_oldCap;
            } 
            else if (m_oldProbing == QUADRATIC) {
                probeIndex = (indexOld + i * i) % m_oldCap;
            } 
            else {
                int step = 1 + (m_hash(virus.getKey()) % (m_oldCap - 1));
                probeIndex = (indexOld + i * step) % m_oldCap;
            }

            if (m_oldTable[probeIndex] == nullptr) {
                break;
            }

            if (m_oldTable[probeIndex]->m_used &&
                m_oldTable[probeIndex]->getKey() == virus.getKey() &&
                m_oldTable[probeIndex]->getID() == virus.getID()) {

                m_oldTable[probeIndex]->setID(id);
                return true;
            }
        }
    }

    return false;
}

float VDetect::lambda() const {
    
    if (m_oldTable != nullptr) {
        return float(m_oldSize) / m_oldCap;
    }

    return float(m_currentSize) / m_currentCap;
}


float VDetect::deletedRatio() const {
    if (m_oldTable != nullptr) {
        if (m_oldSize == 0) return 0.0f;
        return float(m_oldNumDeleted) / m_oldSize;
    }

    if (m_currentSize == 0) return 0.0f;
    return float(m_currNumDeleted) / m_currentSize;
}


void VDetect::insertInternal(Virus virus, Virus** table, int cap, prob_t policy) {
    int index = m_hash(virus.getKey()) % cap;

    int i = 0;
    while (i < cap) {
        int probeIndex;

        if (policy == LINEAR)
            probeIndex = (index + i) % cap;
        else if (policy == QUADRATIC)
            probeIndex = (index + i * i) % cap;
        else {
            int step = 1 + (m_hash(virus.getKey()) % (cap - 1));
            probeIndex = (index + i * step) % cap;
        }

        if (table[probeIndex] == nullptr || !table[probeIndex]->getUsed()) {
            if (table[probeIndex] == nullptr)
                table[probeIndex] = new Virus(virus);
            else
                *table[probeIndex] = virus;

            table[probeIndex]->setUsed(true);
            return;
        }
        i++;
    }
}

void VDetect::rehashStep() {
    if (m_oldTable == nullptr)
        return;

    int transferCount = m_oldCap / 4;

    for (int i = 0; i < transferCount && m_transferIndex < m_oldCap; i++, m_transferIndex++) {

        Virus* v = m_oldTable[m_transferIndex];

        if (v != nullptr && v->getUsed()) {
            insertInternal(*v, m_currentTable, m_currentCap, m_currProbing);
        }

        if (v != nullptr) {
            delete m_oldTable[m_transferIndex];
            m_oldTable[m_transferIndex] = nullptr;
        }
    }

    if (m_transferIndex >= m_oldCap) {

        delete[] m_oldTable;
        m_oldTable = nullptr;

        m_oldCap = 0;
        m_oldSize = 0;
        m_oldNumDeleted = 0;

        m_transferIndex = 0;
    }
}

// ------------------------------------
//   Provided by project do not edit below this line
//-------------------------------------
void VDetect::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool VDetect::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int VDetect::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}