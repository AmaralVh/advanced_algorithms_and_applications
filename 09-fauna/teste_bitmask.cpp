#include <iostream>

using namespace std;


int main() {
    int i;

    cin >> i;

    int bitmask = 1 << i;

    printf("%d\n", bitmask);
    printf("%d\n", i & bitmask);

    return 0;
}