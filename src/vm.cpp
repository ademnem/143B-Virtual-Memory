#include "vm.hpp"

#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

int PM[524288] = {0};
int D[1024][512] = {0};
int nextFreeFrame = 2;


int getS(const int& spw) {
    int s = (spw & 0x7FFFFFF) >> 18; 
    return s;
}
int getP(const int& spw) {
    int p = (spw & 0x3FFFF) >> 9; 
    return p;
}
int getW(const int& spw) {
    int w = spw & 0x1FF;
    return w;
}
int getPW(const int& spw) {
    int pw = spw & 0x3FFFF; 
    return pw;
}


STEntry* getSTEntry(const int& s) {
    return (STEntry*)&(PM[2 * s]);
}
int addSTEntry(const int& s, const int& z, const int& f) {
    STEntry *entry = getSTEntry(s);
    entry->size = z;
    entry->frame = f;
    return s;
}
int* getPTEntry(const int& s, const int& p) {
    STEntry *pt = getSTEntry(s);
    if (pt->frame < 0)
        return (int*)&(D[abs(pt->frame)][p]);
    return (int*)&(PM[pt->frame * FRAME_SIZE + p]);
}
int addPTEntry(const int& s, const int& p, const int& f) {
    int* entry = getPTEntry(s, p);
    *entry = f;
    addPage(f);
    return s;
}
int addPage(const int& f) {
    if (f < 0) 
        D[abs(f) / FRAME_SIZE][0] = 1;
    else
        PM[f * FRAME_SIZE] = 1;
    return f;
}


void initialize(const string& path) {
    ifstream in;
    in.open(path);
    if (!in.is_open())
        exit(EXIT_FAILURE);

    string line;
    getline(in, line);
    initializeSTEntries(line);

    getline(in, line);
    initializePTEntries(line);

    in.close();
}
void initializeSTEntries(const string& line) { // get each word
    stringstream ss{line}; 
    for (int s, z, f; ss >> s && ss >> z && ss >> f; )
        addSTEntry(s, z, f);      
}
void initializePTEntries(const string& line) {
    stringstream ss{line};
    for (int s, p, f; ss >> s && ss >> p && ss >> f; )
        addPTEntry(s, p, f);
}


void translateVirtualAddresses() {
    for (int spw; cin >> spw; )
        cout << getPhysicalAddress(spw) << ' ';
    cout << endl;
}
int getPhysicalAddress(const int& spw) {
    int s = getS(spw);
    int p = getP(spw);
    int w = getW(spw);
    int pw = getPW(spw);

    STEntry* stEntry = getSTEntry(s);
    if (pw >= stEntry->size)
        return -1; // error

    if (stEntry->frame < 0)
        loadPageTable(stEntry);
    else if (stEntry->frame == 0 && stEntry->size == 0)
        return -1;
    int* ptEntry = getPTEntry(s, p);
 
    if (*ptEntry < 0)
        loadPage(ptEntry);
    else if (ptEntry == 0)
        return -1;

    return *ptEntry * FRAME_SIZE + w;
}
int loadPageTable(STEntry* const stEntry) { 
    int freeFrame = getFreeFrame();
    memcpy(&(PM[freeFrame * FRAME_SIZE]), D[abs(stEntry->frame)], FRAME_SIZE * sizeof(int));
    stEntry->frame = freeFrame;
    return freeFrame;
}
int loadPage(int* const ptEntry) {
    int freeFrame = getFreeFrame();
    memcpy(&(PM[freeFrame * FRAME_SIZE]), D[abs(*ptEntry)], FRAME_SIZE * sizeof(int));
    *ptEntry = freeFrame;
    return freeFrame;
}
int getFreeFrame() {
    for (; nextFreeFrame < NUM_FRAMES && !isFreeFrame(nextFreeFrame); ++nextFreeFrame);
    return nextFreeFrame++;
}
bool isFreeFrame(const int& f) {
    for (int i = 0; i < FRAME_SIZE; ++i)
        if (PM[f * FRAME_SIZE + i] != 0)
            return false;
    return true;
}
