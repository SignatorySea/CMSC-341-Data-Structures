// UMBC - CMSC 341 - Spring 2026 - Proj0
#include "art.h"

Art::Art(){
    m_height = 0;
    m_width = 0;
    m_painting = nullptr;
}
Art::Art(int height, int width){
    if (height <= 0 || width <= 0){
        m_height = 0;
        m_width = 0;
        m_painting = nullptr;
        return;
    }
    m_height = height;
    m_width = width;
    m_painting = new int*[m_height];
    for (int i=0;i < m_height;i++){
        m_painting[i] = new int[m_width];
    }
}
Art::~Art(){
    if (m_painting != nullptr){
        for (int i=0;i < m_height;i++){
            delete[] m_painting[i];
        }
        delete[] m_painting;
    }
}

void Art::clear(){
    if (m_painting != nullptr){
        for (int i=0;i < m_height;i++){
            delete[] m_painting[i];
        }
        delete[] m_painting;
    }
    m_height = 0;
    m_width = 0;
    m_painting = nullptr;
}

void Art::create(int initiate){
    //check youre meant to create
    if (initiate == 0){
        return;
    }

    //check valid painting
    if (m_height <= 0 || m_width <= 0 || m_painting == nullptr){
        return;
    }
    
    //make sure the rng number is 2 digits.
    Random rng(10,99);

    //populate
    for (int i=0;i < m_height;i++){
        for (int j=0;j < m_width;j++){
            m_painting[i][j] = rng.getRandNum();
        }
    }
}
void Art::dumpColors(string pixel) const{
    if (m_height > 0 && m_width > 0 && m_painting != nullptr){
        for (int i=1;i <= m_height;i++){
            for (int j=1;j<=m_width;j++){
                std::cout << "\x1b[38;5;" << to_string(m_painting[i-1][j-1]) << "m" << pixel << pixel << RESET;
            }
            cout << endl;
        }
        cout << endl;
    }
}
void Art::dumpValues() const{
    if (m_height > 0 && m_width > 0 && m_painting != nullptr){
        for (int i=1;i <= m_height;i++){
            for (int j=1;j<=m_width;j++){
                cout << m_painting[i-1][j-1] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
Art::Art(const Art& rhs){
    
    m_height = rhs.m_height;
    m_width = rhs.m_width;
    //if the rhs painting is not null, copy it
    if (rhs.m_painting != nullptr){
        m_painting = new int*[m_height];
        for (int i = 0; i < m_height; i++){
            m_painting[i] = new int[m_width];
            for (int j = 0; j < m_width; j++){
                m_painting[i][j] = rhs.m_painting[i][j];
            }
        }   
    } else {
        m_painting = nullptr;
    }
}
const Art& Art::operator=(const Art& rhs){
    //protects against assigning to self
    if (this == &rhs){
        return *this;
    }
    clear(); //empty current object for the new data

    m_height = rhs.m_height;
    m_width = rhs.m_width;
    //if the rhs painting is not null, copy it
    if (rhs.m_painting != nullptr) {
        m_painting = new int*[m_height]; //set up rows

        for (int i = 0; i < m_height; i++) {
            m_painting[i] = new int[m_width]; //set up columns

            for (int j = 0; j < m_width; j++) {
                m_painting[i][j] = rhs.m_painting[i][j];
            }
        }
    } else {
        m_painting = nullptr;
    }
    //return the new object
    return *this;
}

bool Art::left2Right(const Art& rhs){
    //if either painting is null, return false
    if (rhs.m_painting == nullptr || m_painting == nullptr){
        return false;
    }
    //if the heights are not the same, return false
    if (rhs.m_height != m_height){
        return false;  
    }

    //handle self appending safely
    if (this == &rhs){
        Art temp(rhs); //create a copy to append from to avoid deleting data before its copied
        return left2Right(temp);
    }

    //save data incase of self appending
    int oldWidth = m_width;
    int** oldPainting = m_painting;
    
    //create new painting
    m_width = oldWidth + rhs.m_width;
    m_painting = new int*[m_height];

    for(int i=0;i < m_height;i++){
        m_painting[i] = new int[m_width];
        
        //copy left
        for (int j=0;j < oldWidth;j++){
            m_painting[i][j] = oldPainting[i][j];
        }
        //copy right into place
        for (int j=0;j < rhs.m_width;j++){
            m_painting[i][j + oldWidth] = rhs.m_painting[i][j];
        }
    }

    //remove old memory to keep things clean
    for (int i=0;i < m_height;i++){
        delete[] oldPainting[i];
    }
    delete[] oldPainting;

    return true;
}
bool Art::top2Bottom(const Art& bottom){
    //this is similar to left2right but with heights instead of widths

    //if either painting is null, return false
    if (bottom.m_painting == nullptr || m_painting == nullptr){
        return false;
    }
    //if the widths are not the same, return false
    if (bottom.m_width != m_width){
        return false;
    }

    if (this == &bottom){
        Art temp(bottom); //create a copy to append from to avoid deleting data before its copied
        return top2Bottom(temp);
    }

    //save data incase of self appending
    int oldHeight = m_height;
    int** oldPainting = m_painting;

    //create new painting
    m_height = oldHeight + bottom.m_height;
    m_painting = new int*[m_height];
    
    //copy top
    for (int i = 0; i < oldHeight; i++) {
        m_painting[i] = new int[m_width];
        for (int j = 0; j < m_width; j++)
            m_painting[i][j] = oldPainting[i][j];
    }

    //copy bottom into place
    for (int i = 0; i < bottom.m_height; i++) {
        m_painting[oldHeight + i] = new int[m_width];
        for (int j = 0; j < m_width; j++)
            m_painting[oldHeight + i][j] = bottom.m_painting[i][j];
    }

    //remove old memory to keep things clean
    for (int i = 0; i < oldHeight; i++){
        delete[] oldPainting[i];
    }
    delete[] oldPainting;

    return true;
}

bool Art::reverse(){
    //validation
    if (m_painting == nullptr){
        return false;
    }
    //swap values
    for (int i = 0; i < m_height; i++){
        for (int j = 0; j < m_width / 2; j++){
            int temp = m_painting[i][j];
            m_painting[i][j] = m_painting[i][m_width - 1 - j];
            m_painting[i][m_width - 1 - j] = temp;
        }
    }
    return true;
}
bool Art::rotate(){
    //validation
    if (m_painting == nullptr){
        return false;
    }
    
    if (m_height % 2 != 0 || m_width % 2 != 0){
        return false;
    }

    //midpoints
    int hMid = m_height / 2;
    int wMid = m_width / 2;
    
    for (int i=0;i < hMid;i++) {
        for (int j=0;j < wMid;j++){
            int temp = m_painting [i + hMid][j]; //bottom left quarter
            
            m_painting [i + hMid][j] = m_painting [i + hMid][j + wMid]; //bottom right
            m_painting [i + hMid][j + wMid] = m_painting [i][j + wMid]; //top right
            m_painting [i][j + wMid] = m_painting [i][j]; //top left
            
            m_painting [i][j] = temp; //complete the swap
        }
    }
    return true;
}
