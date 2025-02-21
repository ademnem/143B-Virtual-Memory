#ifndef VM_HPP
#define VM_HPP

#define PM_SIZE 524288
#define FRAME_SIZE 512
#define NUM_FRAMES 1024

#include <string>   

using namespace std;

extern int PM[PM_SIZE];
extern int D[NUM_FRAMES][FRAME_SIZE];
extern int nextFreeFrame;
// might need to add TLB

struct STEntry {
    int size;  
    int frame; // PT frame number
};


int getS(const int& spw);
int getP(const int& spw);
int getW(const int& spw);
int getPW(const int& spw);

STEntry* getSTEntry(const int& s); // get ST entry
int addSTEntry(const int& s, const int& z, const int& f);
int* getPTEntry(const int& s, const int& p); // get frame for PT
int addPTEntry(const int& s, const int& p, const int& f);
int addPage(const int& f);

void initialize(const string& path);
void initializeSTEntries(const string& line);
void initializePTEntries(const string& line);

void translateVirtualAddresses();
int getPhysicalAddress(const int& spw);
int loadPageTable(STEntry* const stEntry);
int loadPage(int* const ptEntry);
int getFreeFrame();
bool isFreeFrame(const int& f);

#endif
