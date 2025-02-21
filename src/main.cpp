#include "vm.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2)
        return EXIT_FAILURE;
    
    initialize(argv[1]);
    translateVirtualAddresses();

    return EXIT_SUCCESS;
}
