#include "vdetect.h"
#include "vdetect.cpp"
#include <random>
#include <vector>
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


///////////////////////////////////////

class Tester{
    public:
        bool testInsertNoCollision();
        bool testInsertWithCollision();
        bool testGetVirusNotFound();
        bool testGetVirusNonColliding();
        bool testGetVirusColliding();
        bool testRemoveNonColliding();
        bool testRemoveColliding();
        bool testRehashTriggerInsert();
        bool testRehashCompletionInsert();
        bool testRehashTriggerRemove();
        bool testRehashCompletionRemove();
};

//helper function
unsigned int simpleHash(string key) {
    unsigned int hash = 0;
    for (char c : key)
        hash = hash * 31 + c;
    return hash;
}

bool Tester::testInsertNoCollision() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<pair<string,int>> data;

    int i = 0;
    while (data.size() < 50) {
        int id = randGen.getRandNum();
        string key = "key" + to_string(i);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            data.push_back({key, id});
        }
        i++;
    }

    for (auto &p : data) {
        if (table.getVirus(p.first, p.second).getID() == -1)
            return false;
    }

    return true;
}

bool Tester::testInsertWithCollision() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<int> ids;

    while (ids.size() < 50) {
        int id = randGen.getRandNum();

        if (table.getVirus("sameKey", id).getID() == -1) {
            table.insert(Virus("sameKey", id));
            ids.push_back(id);
        }
    }

    for (int id : ids) {
        if (table.getVirus("sameKey", id).getID() == -1)
            return false;
    }

    return true;
}

bool Tester::testGetVirusNotFound() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    int id = randGen.getRandNum();
    return table.getVirus("ghost", id).getID() == -1;
}

bool Tester::testGetVirusNonColliding() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<pair<string,int>> data;

    int i = 0;
    while (data.size() < 50) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(i);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            data.push_back({key, id});
        }
        i++;
    }

    for (auto &p : data) {
        if (table.getVirus(p.first, p.second).getID() == -1)
            return false;
    }

    return true;
}

bool Tester::testGetVirusColliding() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<int> ids;

    while (ids.size() < 50) {
        int id = randGen.getRandNum();

        if (table.getVirus("collision", id).getID() == -1) {
            table.insert(Virus("collision", id));
            ids.push_back(id);
        }
    }

    for (int id : ids) {
        if (table.getVirus("collision", id).getID() == -1)
            return false;
    }

    return true;
}

bool Tester::testRemoveNonColliding() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<pair<string,int>> data;

    int i = 0;
    while (data.size() < 50) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(i);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            data.push_back({key, id});
        }
        i++;
    }

    for (int i = 0; i < 25; i++) {
        if (!table.remove(Virus(data[i].first, data[i].second)))
            return false;
    }

    for (int i = 0; i < 25; i++) {
        if (table.getVirus(data[i].first, data[i].second).getID() != -1)
            return false;
    }

    return true;
}

bool Tester::testRemoveColliding() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<int> ids;

    while (ids.size() < 50) {
        int id = randGen.getRandNum();

        if (table.getVirus("same", id).getID() == -1) {
            table.insert(Virus("same", id));
            ids.push_back(id);
        }
    }

    for (int i = 0; i < 25; i++) {
        if (!table.remove(Virus("same", ids[i])))
            return false;
    }

    for (int i = 0; i < 25; i++) {
        if (table.getVirus("same", ids[i]).getID() != -1)
            return false;
    }

    return true;
}

bool Tester::testRehashTriggerInsert() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    int count = 0;

    while (count < 70) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(count);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            count++;
        }
    }
    return table.lambda() < 0.5;
}

bool Tester::testRehashCompletionInsert() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    int count = 0;

    while (count < 120) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(count);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            count++;
        }
    }

    return table.m_oldTable == nullptr;
}

bool Tester::testRehashTriggerRemove() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<pair<string,int>> data;

    int i = 0;
    while (data.size() < 50) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(i);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            data.push_back({key, id});
        }
        i++;
    }

    for (int i = 0; i < 45; i++) {
        table.remove(Virus(data[i].first, data[i].second));
    }

    return table.deletedRatio() < 0.8;
}

bool Tester::testRehashCompletionRemove() {
    VDetect table(101, simpleHash, LINEAR);
    Random randGen(MINID, MAXID);

    vector<pair<string,int>> data;

    int i = 0;
    while (data.size() < 50) {
        int id = randGen.getRandNum();
        string key = "k" + to_string(i);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            data.push_back({key, id});
        }
        i++;
    }

    for (int i = 0; i < 45; i++) {
        table.remove(Virus(data[i].first, data[i].second));
    }

    int count = 0;
    while (count < 50) {
        int id = randGen.getRandNum();
        string key = "x" + to_string(count);

        if (table.getVirus(key, id).getID() == -1) {
            table.insert(Virus(key, id));
            count++;
        }
    }

    return table.m_oldTable == nullptr;
}

void printResult(string name, bool result) {
    cout << name << ": " << (result ? "PASS" : "FAIL") << endl;
}

int main() {
    Tester t;

    printResult("Insert No Collision", t.testInsertNoCollision());
    printResult("Insert With Collision", t.testInsertWithCollision());
    printResult("Get Not Found", t.testGetVirusNotFound());
    printResult("Get Non-Colliding", t.testGetVirusNonColliding());
    printResult("Get Colliding", t.testGetVirusColliding());
    printResult("Remove Non-Colliding", t.testRemoveNonColliding());
    printResult("Remove Colliding", t.testRemoveColliding());
    printResult("Rehash Trigger Insert", t.testRehashTriggerInsert());
    printResult("Rehash Completion Insert", t.testRehashCompletionInsert());
    printResult("Rehash Trigger Remove", t.testRehashTriggerRemove());
    printResult("Rehash Completion Remove", t.testRehashCompletionRemove());
    
    return 0;
}