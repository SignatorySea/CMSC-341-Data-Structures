// CMSC 341 - Spring 2026 - Project 3
#include "shop.h"
Shop::Shop(){ // empty object
  m_shopID = 0;
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = nullptr;
  m_heapType = NOTYPE;
  m_structure = NOSTRUCT;
  m_regPrior = 0;
}

Shop::Shop(prifn_t priFn, HEAPTYPE heapType, 
          STRUCTURE structure, int regPrior,
          int id)
{
  m_shopID = id;
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = priFn; //sort priority function
  m_heapType = heapType;
  m_structure = structure;
  m_regPrior = regPrior; //priority of shop
}

void Shop::clearHeap(Order* node) {
    if (node == nullptr) {
        return;
    }
    clearHeap(node->m_left);
    clearHeap(node->m_right);
    delete node;
}

Shop::~Shop()
{
 clearHeap(m_heap); //delete tree
 
 //reset everything to 0 or null
  m_heap = nullptr;
  m_size = 0;
  m_priorFunc = nullptr;
}

void Shop::clear() {
    clearHeap(m_heap);

    //unlike ~shop this clears the data but keeps the object.
    m_heap = nullptr;
    m_size = 0;

}

Order* Shop::cloneHeap(const Order* node) {
  if (node == nullptr) {
    return nullptr;
  }

  //new node to copy the data
  Order* newNode =new Order();

  //copy data fields of the order
    newNode->m_item = node->m_item;
    newNode->m_count = node->m_count;
    newNode->m_membership = node->m_membership;
    newNode->m_points = node->m_points;
    newNode->m_customerID = node->m_customerID;
    newNode->m_orderID = node->m_orderID;
    newNode->m_npl = node->m_npl;

  //copy the kids
  newNode->m_left = cloneHeap(node->m_left);
  newNode->m_right = cloneHeap(node->m_right);

  return newNode;
}

Shop::Shop(const Shop& rhs)
{
  //copy simple values
  m_shopID = rhs.m_shopID;
  m_size = rhs.m_size;
  m_priorFunc = rhs.m_priorFunc;
  m_heapType = rhs.m_heapType;
  m_structure = rhs.m_structure;
  m_regPrior = rhs.m_regPrior;

  //deep copy the heap
  m_heap = cloneHeap(rhs.m_heap);
}

Shop& Shop::operator=(const Shop& rhs) {
  if (this == &rhs) {
    return *this; // self assignment check
  }

  //clear existing heap
  clear();

  //copy simple values
  m_shopID = rhs.m_shopID;
  m_priorFunc = rhs.m_priorFunc;
  m_heapType = rhs.m_heapType;
  m_structure = rhs.m_structure;
  m_regPrior = rhs.m_regPrior;

  //deep copy the heap
  m_heap = cloneHeap(rhs.m_heap);
  m_size = rhs.m_size;

  return *this;
}

Order* Shop::merge(Order* h1, Order* h2) {
  //base  case
  if (h1 == nullptr) return h2;
  if (h2 == nullptr) return h1;

  // compare priority
  int p1 = m_priorFunc(*h1);
  int p2 = m_priorFunc(*h2);

  if ((m_heapType == MINHEAP && p1 > p2) || (m_heapType == MAXHEAP && p1 < p2)) {
    swap(h1, h2);
  };

  //merge into right subtree
  h1->m_right = merge(h1->m_right, h2);

  //structure
  if (m_structure == SKEW) {
    //skew heap: always swap
    swap(h1->m_left, h1->m_right);
  } else {
    //leftist heap: swap if left npl is less than right npl
    int leftNPL = (h1->m_left == nullptr) ? -1 : h1->m_left->m_npl;
    int rightNPL = (h1->m_right == nullptr) ? -1 : h1->m_right->m_npl;

    if (leftNPL < rightNPL) {
      swap(h1->m_left, h1->m_right);
    }

    h1->m_npl = (h1->m_right == nullptr) ? 0 : h1->m_right->m_npl + 1;
  }
  return h1;
}

void Shop::mergeWithQueue(Shop& rhs) {
  //self merge catch
  if (this == &rhs) {
    throw domain_error("Self merge not allowed");
  }

  //compatability check
  if (m_priorFunc != rhs.m_priorFunc ||
    m_structure != rhs.m_structure ||
    m_heapType != rhs.m_heapType) {
    throw domain_error("Incompatible heaps");
  }

  //merge
  m_heap = merge(m_heap, rhs.m_heap);
  m_size += rhs.m_size;

  //empty rhs
  rhs.m_heap = nullptr;
  rhs.m_size = 0;
}

bool Shop::insertOrder(const Order& order) {
    //make new node
    Order* newNode = new Order();

    //copy data fields of the order
    *newNode = order;

    //heap pointers
    newNode->m_left = nullptr;
    newNode->m_right = nullptr;

    //initialize npl if leftist heap
    if (m_structure == LEFTIST) {
        newNode->m_npl = 0;
    };

    //merge
    m_heap = merge(m_heap, newNode);
    m_size++;

    return true;
  }

int Shop::numOrders() const
{
  return m_size;
}

prifn_t Shop::getPriorityFn() const {
  return m_priorFunc;
}

Order Shop::getNextOrder() {
    if (m_heap == nullptr)
        throw std::out_of_range("Heap is empty");

    Order* oldRoot = m_heap;

    // save children first
    Order* left = oldRoot->m_left;
    Order* right = oldRoot->m_right;

    // extract data BEFORE deletion
    ITEM item = oldRoot->getItem();
    COUNT count = oldRoot->getCount();
    MEMBERSHIP membership = oldRoot->getMemebership();
    int points = oldRoot->getPoints();
    int customerID = oldRoot->getCustomerID();
    int orderID = oldRoot->getOrderID();

    delete oldRoot;

    // fix heap
    m_heap = merge(left, right);
    m_size--;

    // return DIRECTLY
    return Order(item, count, membership, points, customerID, orderID);
}

void Shop::rebuildHeap(Order* node) {
    if (node == nullptr) {
        return;
    }

    //store kids for detaching
    Order* left = node->m_left;
    Order* right = node->m_right;

    //detach
    node->m_left = nullptr;
    node->m_right = nullptr;
    node->m_npl = 0;

    //merge back
    m_heap = merge(m_heap, node);
    m_size++;

    //recurse on kids
    rebuildHeap(left);
    rebuildHeap(right);
}

void Shop::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  //update rules
  m_priorFunc = priFn;
  m_heapType = heapType;

  //save old heap
  Order* oldRoot = m_heap;
  m_heap = nullptr;
  m_size = 0;

  //rebuild w/ old nodes
  rebuildHeap(oldRoot);
}

void Shop::rebuildStructure(Order* node) {
    if (node == nullptr) {
        return;
    }

    Order* left = node->m_left;
    Order* right = node->m_right;

    //detatch
    node->m_left = nullptr;
    node->m_right = nullptr;
    node->m_npl = 0;

    //insert into new heap
    m_heap = merge(m_heap, node);
    m_size++;

    rebuildStructure(left);
    rebuildStructure(right);
}

void Shop::setStructure(STRUCTURE structure){
    //save old heap
    Order* oldRoot = m_heap;

    //reset
    m_heap = nullptr;
    m_size = 0;

    //update structure
    m_structure = structure;

    rebuildStructure(oldRoot);
}

STRUCTURE Shop::getStructure() const {
  return m_structure;
}

void Shop::printPreOrder(Order* node) const {
    if (node == nullptr) {
        return;
    }

    cout << m_priorFunc(*node) << ":" << node->m_orderID << " ";
    printPreOrder(node->m_left);
    printPreOrder(node->m_right);
}

void Shop::printOrdersQueue() const {
  printPreOrder(m_heap);
}
/////////////////////////////////
// Provided functions, dont alter them

void Shop::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    cout << "Shop " << m_regPrior << ": => ";
    dump(m_heap);
  }
  cout << endl;
}
void Shop::dump(Order *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
        cout << m_priorFunc(*pos) << ":" << pos->m_orderID;
    else
        cout << m_priorFunc(*pos) << ":" << pos->m_orderID << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order ID: " << order.getOrderID() 
        << ", item: " << order.getItem()
        << ", count: " << order.getCount();
  return sout;
}

//////////////////////////////////////////////////////////////
Region::Region(int size){
  m_capacity = size;
  m_size = 0;

  m_heap = new Shop [m_capacity + 1 ]; // 1-based indexing for easier parent/child calculations
}

Region::~Region(){
  delete [] m_heap;
  m_heap = nullptr;
  m_capacity = 0;
  m_size = 0;
}

bool Region::addShop(Shop & aShop){
  //check capacity if full return
  if (m_size == m_capacity) {
    return false;
  }
  //insert shop at end
  m_heap[m_size] = aShop;
  
  int index = m_size;
  m_size++;

  while (index > 1) {
    int parent = (index) / 2;

    if (m_heap[parent].m_regPrior < m_heap[index].m_regPrior) {
      std::swap(m_heap[parent], m_heap[index]);
      index = parent;
    } else {
      break;
    }
  }
  return true;
}

bool Region::getShop(Shop & aShop){
  //empty check
  if (m_size == 0) {
    return false;
  }

  aShop = m_heap[1];

  //move last to root
  m_heap[1] = m_heap[m_size];
  m_size--;

  //heapify down
  int parent = 1;

  while (true) {
    int left = 2 * parent;
    int right = 2 * parent + 1;
    int smallest = parent;


    //check left
    if (left < m_size && m_heap[left].m_regPrior < m_heap[smallest].m_regPrior) {
      smallest = left;
    }
    //check right
    if (right < m_size && m_heap[right].m_regPrior < m_heap[smallest].m_regPrior) {
      smallest = right;
    }
    //stop if heap is valid
    if (smallest == parent) {
      break;
    }

    //swap and continue
    swap(m_heap[parent], m_heap[smallest]);
    parent = smallest;
  }

  return true;
}

bool Region::getNthShop(Shop & aShop, int n){
  if(n <= 0 || n > m_size) {
    return false;
  }

  //temp sotrage
  Shop* temp = new Shop[n-1];

  // remove n-1 shops
  for (int i = 0; i < n-1; i++) {
    getShop(temp[i]);
  }

  getShop(aShop);

  //reinsert removed shops
  for (int i = 0; i < n-1; i++) {
    addShop(temp[i]);
  }

  delete [] temp;

  return true;
}

bool Region::setPriorityFn(prifn_t priFn, HEAPTYPE heapType, int n){
  if ( n <= 0 || n > m_size) {
    return false;
  }

  //temp sotrage
  Shop* temp = new Shop[n-1];

  //remove n-1 shops
  for (int i = 0; i < n-1; i++) {
    getShop(temp[i]);
  }

  //isolate nth shop and update
  Shop target;
  getShop(target);

  //modify its internal heap
  target.setPriorityFn(priFn, heapType);

  //reinsert modified shop
  addShop(target);

  //restore others
  for (int i = 0; i < n-1; i++) {
    addShop(temp[i]);
  }

  delete [] temp;

  return true;
}

bool Region::setStructure(STRUCTURE structure, int n){
  if (n <= 0 || n > m_size) {
    return false;
  }

  Shop* temp = new Shop[n-1];

  for (int i = 0; i < n-1; i++) {
    getShop(temp[i]);
  }

  Shop target;
  getShop(target);

  target.setStructure(structure);

  addShop(target);

  for (int i = 0; i < n-1; i++) {
    addShop(temp[i]);
  }

  delete [] temp;

  return true;
}

bool Region::getOrder(Order & order){
  if (m_size == 0) {
    return false;
  }

  Shop current;

  while (m_size > 0) {
    getShop(current);

    //ignore/skip empty shops
    if (current.numOrders() == 0) {
      continue;
    }

    order = current.getNextOrder();

    //reinsert shop if it still has orders
    if (current.numOrders() > 0) {
      addShop(current);
    }

    return true;
  }

  return false;
}

////////////////////////////////////
//Provided functions, dont alter them.
void Region::dump(){
    dump(ROOTINDEX);
    cout << endl;
}
void Region::dump(int index){
  if (index <= m_size){
    cout << "(";
    dump(index*2);
    cout << m_heap[index].m_regPrior;
    dump(index*2 + 1);
    cout << ")";
  }
}