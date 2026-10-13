// UMBC - CMSC 341 - Spring 2026 - Proj2
#include "streak.h"

Streak::Streak(){
    m_root = nullptr;
    m_gridID = 0;
    m_left = nullptr;
    m_right = nullptr;
}

Streak::Streak(int grid, Tiger tigers[], int population){
    m_root = nullptr;
    m_gridID = grid;
    m_left = nullptr;
    m_right = nullptr;

     for (int i = 0; i < population; i++) {
        insert(tigers[i]); // insert each tiger into the AVL tree and maintain the balance
    }
}
Streak::~Streak(){
    clear();
}
void Streak::insert(const Tiger& tiger){
    m_root = insertHelper(m_root, tiger);
}

Tiger* Streak::insertHelper(Tiger* node, const Tiger& tiger) {
    if (node == nullptr) {
        // Create a new Tiger node 
        Tiger* newNode = new Tiger(tiger.getID(), tiger.getAge(), tiger.getGender(), tiger.getState());
        return newNode;
    }

    // insert
    if (tiger.getID() < node->m_id) {
        node->m_left = insertHelper(node->m_left, tiger);
    } 
    else if (tiger.getID() > node->m_id) {
        node->m_right = insertHelper(node->m_right, tiger);
    } 
    else {
        // Duplicate IDs are not allowed; do nothing
        return node;
    }

    // Update height
    node->m_height = 1 + max(height(node->m_left), height(node->m_right));

    // Balance it
    int balance = getBalance(node);

    // Left heavy
    if (balance > 1) {
        if (tiger.getID() < node->m_left->m_id) {
            return rotateRight(node);          // LL
        } else {
            node->m_left = rotateLeft(node->m_left); // LR
            return rotateRight(node);
        }
    }

    // Right heavy
    if (balance < -1) {
        if (tiger.getID() > node->m_right->m_id) {
            return rotateLeft(node);           // RR
        } else {
            node->m_right = rotateRight(node->m_right); // RL
            return rotateLeft(node);
        }
    }

    return node;
}

void Streak::clear(){
    clearHelper(m_root);
    m_root = nullptr;
}

void Streak::clearHelper(Tiger* node) {
    if (node == nullptr) return;

    clearHelper(node->m_left);
    clearHelper(node->m_right);

    delete node;
}

void Streak::remove(int id){
    m_root = removeHelper(m_root, id);
}

Tiger* Streak::removeHelper(Tiger* node, int id) {
    if (node == nullptr) return nullptr;

    // delete
    if (id < node->m_id) {
        node->m_left = removeHelper(node->m_left, id);
    } 
    else if (id > node->m_id) {
        node->m_right = removeHelper(node->m_right, id);
    } 
    else {
        // woo node found!
        if (node->m_left == nullptr || node->m_right == nullptr) {
            Tiger* temp = (node->m_left) ? node->m_left : node->m_right;

            if (temp == nullptr) {
                // if no child
                delete node;
                return nullptr;
            } else {
                // if one child
                Tiger* toDelete = node;
                node = temp;
                delete toDelete;
            }
        } else {
            // if theres two children use inorder successor
            Tiger* succ = node->m_right;
            while (succ->m_left != nullptr)
                succ = succ->m_left;

            // Copy successor data
            node->m_id = succ->m_id;
            node->m_age = succ->m_age;
            node->m_gender = succ->m_gender;
            node->m_state = succ->m_state;

            // Delete successor
            node->m_right = removeHelper(node->m_right, succ->m_id);
        }
    }

    // Update height
    node->m_height = 1 + max(height(node->m_left), height(node->m_right));

    // Balance It out next
    int balance = getBalance(node);

    // Left heavy
    if (balance > 1) {
        if (getBalance(node->m_left) >= 0)
            return rotateRight(node);          // LL
        else {
            node->m_left = rotateLeft(node->m_left); // LR
            return rotateRight(node);
        }
    }

    // Right heavy
    if (balance < -1) {
        if (getBalance(node->m_right) <= 0)
            return rotateLeft(node);           // RR
        else {
            node->m_right = rotateRight(node->m_right); // RL
            return rotateLeft(node);
        }
    }

    return node;
}

int Streak::height(Tiger* node) {
    return (node == nullptr) ? -1 : node->m_height;
}

int Streak::getBalance(Tiger* node) {
    if (node == nullptr) return 0;
    return height(node->m_left) - height(node->m_right);
}

Tiger* Streak::rotateRight(Tiger* y) {
    Tiger* x = y->m_left;
    Tiger* T2 = x->m_right;

    x->m_right = y;
    y->m_left = T2;

    y->m_height = 1 + max(height(y->m_left), height(y->m_right));
    x->m_height = 1 + max(height(x->m_left), height(x->m_right));

    return x;
}

Tiger* Streak::rotateLeft(Tiger* x) {
    Tiger* y = x->m_right;
    Tiger* T2 = y->m_left;

    y->m_left = x;
    x->m_right = T2;

    x->m_height = 1 + max(height(x->m_left), height(x->m_right));
    y->m_height = 1 + max(height(y->m_left), height(y->m_right));

    return y;
}

void Streak::listTigers() const {
    listTigersHelper(m_root);
}

void Streak::listTigersHelper(Tiger* node) const {
    if (node == nullptr) return; // aint no empty list getting through here

    //do left subtree first cause its smaller
    listTigersHelper(node->m_left);
    cout << "ID: " << node->m_id 
         << ", Age: " << node->getAgeStr()
         << ", Gender: " << node->getGenderStr()
         << ", State: " << node->getStateStr() 
         << endl;

    //do right subtree last cause its bigger
    //this recalls this function on the right subtree
    listTigersHelper(node->m_right);
}


bool Streak::setState(int id, STATE state){
    return setStateHelper(m_root, id, state);
}

bool Streak::setStateHelper(Tiger* node, int id, STATE state) {
    if (node == nullptr) return false; //no empty case processing here

    if (id < node->m_id) {
        return setStateHelper(node->m_left, id, state);
    } 
    else if (id > node->m_id) {
        return setStateHelper(node->m_right, id, state);
    } 
    else { //tiger is found!
        node->m_state = state;
        return true;
    }
}

void Streak::removeDead(){
    m_root = removeDeadHelper(m_root);
}

Tiger* Streak::removeDeadHelper(Tiger* node) {
    if (node == nullptr) return nullptr; //empty list catch

    //check through left and right nodes
    node->m_left = removeDeadHelper(node->m_left);
    node->m_right = removeDeadHelper(node->m_right);

    if (node->m_state == DEAD) {
        return removeHelper(node, node->m_id); // reuse existing remove logic
    }

    return node;
}

bool Streak::findTiger(int id) const {
    return findTigerHelper(m_root, id);
}

bool Streak::findTigerHelper(Tiger* node, int id) const {
    if (node == nullptr) return false; //empty list catch

    if (id < node->m_id) {
        return findTigerHelper(node->m_left, id);
    } 
    else if (id > node->m_id) {
        return findTigerHelper(node->m_right, id);
    } 
    else { //tiger is found!
        return true;
    }
}

int Streak::count(AGE age) const{
    return countAgeHelper(m_root, age);
}

int Streak::countAgeHelper(Tiger* node, AGE age) const {
    if (node == nullptr) return 0; //empty list catch

    int count = 0;
    if (node->m_age == age) {
        count = 1; // count this tiger
    }

    // count in left and right subtrees
    return count + countAgeHelper(node->m_left, age) + countAgeHelper(node->m_right, age);
}

int Streak::count(STATE state) const{
    return countStateHelper(m_root, state);
}

int Streak::countStateHelper(Tiger* node, STATE state) const {
    if (node == nullptr) return 0; //empty list catch

    int count = 0;
    if (node->m_state == state) {
        count = 1; // count this tiger
    }

    // count in left and right subtrees
    return count + countStateHelper(node->m_left, state) + countStateHelper(node->m_right, state);
}

/**********************************
Provided by Assignment dont modify
***********************************/
void Streak::dumpTree() const {dump(m_root);}
void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

//////////////////////////////////////////////////////////////////////
Grid::Grid(){
    m_root = nullptr;
}

Grid::~Grid(){
    
}

bool Grid::insert(int grid, Tiger tigers[], int population){
    if (grid <= 0 || population < 0) {
    return false; //invalid input catch
    }

    //check for duplicate key
    m_root = splay(m_root, grid);
    if (m_root != nullptr && m_root->m_gridID == grid) {
        return false; //duplicate grid ID catch
    }

    //make a new streak
    Streak* newNode = new Streak(grid, tigers, population);

    //insert into the splay tree
    if (m_root == nullptr) {
        m_root = newNode; //empty tree case
    } else if (grid < m_root->m_gridID) {
        newNode->m_left = m_root->m_left;
        newNode->m_right = m_root;
        m_root->m_left = nullptr;
        m_root = newNode;
    } else { // grid > m_root->m_gridID
        newNode->m_right = m_root->m_right;
        newNode->m_left = m_root;
        m_root->m_right = nullptr;
        m_root = newNode;
    }
    return true;
}

Streak* Grid::splay(Streak* root, int key){
     if (root == nullptr || root->m_gridID == key)
        return root;

    // Key is in LEFT subtree
    if (key < root->m_gridID) {
        if (root->m_left == nullptr)
            return root;

        // check Left Left
        if (key < root->m_left->m_gridID) {
            root->m_left->m_left = splay(root->m_left->m_left, key);
            root = rotateRight(root);
        }
        // check Left Right
        else if (key > root->m_left->m_gridID) {
            root->m_left->m_right = splay(root->m_left->m_right, key);
            if (root->m_left->m_right != nullptr)
                root->m_left = rotateLeft(root->m_left);
        }

        return (root->m_left == nullptr) ? root : rotateRight(root);
    }

    // Key is in RIGHT subtree
    else {
        if (root->m_right == nullptr)
            return root;

        // check Right Right
        if (key > root->m_right->m_gridID) {
            root->m_right->m_right = splay(root->m_right->m_right, key);
            root = rotateLeft(root);
        }
        // check Right Left
        else if (key < root->m_right->m_gridID) {
            root->m_right->m_left = splay(root->m_right->m_left, key);
            if (root->m_right->m_left != nullptr)
                root->m_right = rotateRight(root->m_right);
        }

        return (root->m_right == nullptr) ? root : rotateLeft(root);
    }
}
//support functions for splay tree rotations
Streak* Grid::rotateRight(Streak* x) {
    Streak* y = x->m_left;
    x->m_left = y->m_right;
    y->m_right = x;
    return y;
}

Streak* Grid::rotateLeft(Streak* x) {
    Streak* y = x->m_right;
    x->m_right = y->m_left;
    y->m_left = x;
    return y;
}

int Grid::count(int grid, STATE state){
    if (m_root == nullptr || grid <= 0) {
    return 0; //error catch
    }
    //bring target to root
    m_root = splay(m_root, grid);

    //if it doesnt exist
    if(m_root == nullptr || m_root->m_gridID != grid) {
        return 0; //grid not found catch
    }
    // use streaks count function to save recoding
    return m_root->count(state);
}

int Grid::count(int grid, AGE age){
    if(m_root == nullptr || grid <= 0) {
        return 0; //error catch
    }
    //bring target to root
    m_root = splay(m_root, grid);

    //if it doesnt exist
    if(m_root == nullptr || m_root->m_gridID != grid) {
        return 0; //grid not found catch
    }
    // use streaks count function to save recoding
    return m_root->count(age);
}

bool Grid::removeTiger(int grid, int tiger, bool all){
    if(m_root == nullptr || grid <= 0) {
        return false; //error catch
    }

    //bring target grid to root
    m_root = splay(m_root, grid);

    //oop no grid
    if(m_root == nullptr || m_root->m_gridID != grid) {
        return false; //grid not found catch
    }

    //remove all dead tigers if all is true
    if (all) {
        m_root->removeDead();
        return true;
    }

    //remove a specific tiger
    //check if tiger exists first
    if (!m_root->findTiger(tiger)) {
        return false; //tiger not found catch
    }

    m_root->remove(tiger);
    return true;

}

int Grid::getGridHeight(int grid){
    if (m_root == nullptr || grid <= 0) {
        return -1; //error catch
    }

    //bring target grid to root
    m_root = splay(m_root, grid);

    //check existance
    if(m_root == nullptr || m_root->m_gridID != grid) {
        return -1; //grid not found catch
    }

    //check streak isnt empty
    if(m_root->m_root == nullptr) {
        return -1; //empty grid catch
    }

    //return the height
    return m_root->m_root->m_height;
}

bool Grid::setState(int grid, int tiger, STATE state){
    if(m_root == nullptr || grid <= 0) {
        return false; //error catch
    }

    //bring target grid to root
    m_root = splay(m_root, grid);

    //make sure grid is real
    if(m_root == nullptr || m_root->m_gridID != grid) {
        return false; //grid not found catch
    }

    //try to set state and return result
    if (!m_root->findTiger(tiger)) {
        return false; //tiger not found catch
    }  
    m_root->setState(tiger, state);
    
    if (state == DEAD) {
        m_root->removeDead(); // remove all dead tigers if this tiger is now dead
    }
    return true;
}

/* **********************************
 Provided by Assignment dont modify
************************************ */
void Grid::dump(bool verbose) const{
	dumpHelper(m_root, verbose);
    cout << endl;
}

void Grid::dumpHelper(Streak* root, bool verbose) const{
    if (root != nullptr){
        {
            cout << "(";
            dumpHelper( root->m_left, verbose );
            if (verbose)
                cout << root->m_gridID << ":" << root->m_root->m_id;
            else
                cout << root->m_gridID;
            dumpHelper( root->m_right, verbose );
            cout << ")";
        }
    }
}