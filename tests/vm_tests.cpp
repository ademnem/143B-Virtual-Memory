#include "vm.hpp"

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

using func = bool(void);

void executeTests(const string name, func* const f) {
    cout << "Testing " << name << "..."; 
    cout << (f() ? "OK" : "\e[1;31mFAILED\e[0;37m") << endl;
}
void test(const bool& result, bool& passed) {   
    passed = passed ? result : false;
}


bool testGetSPW(void) {
    bool passed = true;

    int spw = 2098193;
    test(getS(spw) == 8, passed);
    test(getP(spw) == 2, passed); 
    test(getW(spw) == 17, passed);
    test(getPW(spw) == 1041, passed);

    spw = 512;
    test(getS(spw) == 0, passed);
    test(getP(spw) == 1, passed); 
    test(getW(spw) == 0, passed);
    test(getPW(spw) == 512, passed);

    spw = 0;
    test(getS(spw) == 0, passed);
    test(getP(spw) == 0, passed); 
    test(getW(spw) == 0, passed);
    test(getPW(spw) == 0, passed);

    return passed;
}
bool testSTEntry(void) {
    bool passed = true;

    test(addSTEntry(8, 4000, 3) == 8, passed);
    test(addSTEntry(9, 5000, -7) == 9, passed);

    test(getSTEntry(8)->size == 4000, passed);
    test(getSTEntry(8)->frame == 3, passed);
    test(getSTEntry(9)->size == 5000, passed);
    test(getSTEntry(9)->frame == -7, passed);

    return passed;
}
bool testPTEntry(void) {
    bool passed = true;

    test(addPTEntry(8, 0, 10) == 8, passed);
    test(addPTEntry(8, 1, -20) == 8, passed);
    test(addPTEntry(9, 0, 13) == 9, passed);
    test(addPTEntry(9, 1, -25) == 9, passed);

    test(*getPTEntry(8, 0) == 10, passed);
    test(*getPTEntry(8, 1) == -20, passed);
    test(*getPTEntry(9, 0) == 13, passed);
    test(*getPTEntry(9, 1) == -25, passed); 

    return passed;
}
bool testIsFreeFrame(void) {
    bool passed = true;

    test(!isFreeFrame(0), passed);
    test(!isFreeFrame(3), passed);
    test(isFreeFrame(2), passed);
    PM[FRAME_SIZE * 2] = 1;
    test(!isFreeFrame(2), passed);
    PM[FRAME_SIZE * 2] = 0;
    test(isFreeFrame(2), passed);

    return passed;
}
bool testGetFreeFrame(void) {
    bool passed = true;

    test(getFreeFrame() == 2, passed);
    test(getFreeFrame() == 4, passed);
    test(getFreeFrame() == 5, passed);
    nextFreeFrame = 2;

    return passed;
}
bool testGetPhysicalAddress(void) {
    bool passed = true;
    
    int va = 2097162; // S = 8, P = 0, W = 10, PW = 10
    test(getPhysicalAddress(va) == 5130, passed);
    test(nextFreeFrame == 2, passed);

    va = 2097674; // S = 8, P = 1, W = 10, PW = 522
    test(getPhysicalAddress(va) == 1034, passed);
    test(nextFreeFrame == 3, passed);

    va = 2359306; // S = 9, P = 0, W = 10, PW = 10
    test(getPhysicalAddress(va) == 6666, passed);
    test(nextFreeFrame == 5, passed);

    va = 2359818; // S = 9, P = 1, W = 10, PW = 522
    test(getPhysicalAddress(va) == 2570, passed);
    test(nextFreeFrame == 6, passed);

    return passed;
}

int main() {
    executeTests("getSPW", testGetSPW);
    executeTests("STEntry functions", testSTEntry);
    executeTests("PTEntry functions", testPTEntry);
    executeTests("isFreeFrame", testIsFreeFrame);
    executeTests("getFreeFrame", testGetFreeFrame);
    executeTests("getPhysicalAddress", testGetPhysicalAddress);
    return 0;
}

