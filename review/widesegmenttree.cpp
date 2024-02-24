const int b = 4, B = (1 << b); // cache line size (in integers, not bytes)

// the height of the tree over an n-element array 
constexpr int height(int n) {
    return (n <= B ? 1 : height(n / B) + 1);
}

// where the h-th layer starts
constexpr int offset(int h) {
    int s = 0, n = N;
    while (h--) {
        n = (n + B - 1) / B;
        s += n * B;
    }
    return s;
}

constexpr int H = height(N);
alignas(64) int t[offset(H)]; // an array for storing nodes
