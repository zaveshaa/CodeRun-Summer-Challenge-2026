#include <stdio.h>

long long M;

typedef struct {
    long long mat[2][2];
} Matrix;

Matrix get_identity() {
    Matrix res;
    res.mat[0][0] = 1; res.mat[0][1] = 0;
    res.mat[1][0] = 0; res.mat[1][1] = 1;
    return res;
}

Matrix multiply(Matrix A, Matrix B) {
    Matrix res;
    res.mat[0][0] = (long long)(((__int128)A.mat[0][0] * B.mat[0][0] + (__int128)A.mat[0][1] * B.mat[1][0]) % M);
    res.mat[0][1] = (long long)(((__int128)A.mat[0][0] * B.mat[0][1] + (__int128)A.mat[0][1] * B.mat[1][1]) % M);
    res.mat[1][0] = (long long)(((__int128)A.mat[1][0] * B.mat[0][0] + (__int128)A.mat[1][1] * B.mat[1][0]) % M);
    res.mat[1][1] = (long long)(((__int128)A.mat[1][0] * B.mat[0][1] + (__int128)A.mat[1][1] * B.mat[1][1]) % M);
    return res;
}

Matrix power(Matrix base, long long p) {
    Matrix res = get_identity();
    while (p != 0) {
        if (p & 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        p /= 2;
    }
    return res;
}

int main() {
    long long a, b;
    if (scanf("%lld %lld", &a, &b) != 2) return 0;
    if (scanf("%lld", &M) != 1) return 0;
    
    int Q;
    if (scanf("%d", &Q) != 1) return 0;
    
    Matrix T;
    T.mat[0][0] = (a % M + M) % M;
    T.mat[0][1] = (b % M + M) % M;
    T.mat[1][0] = 1 % M;
    T.mat[1][1] = 0;
    
    while (Q--) {
        long long x, y, n;
        if (scanf("%lld %lld %lld", &x, &y, &n) != 3) break;
        
        if (n == 0) {
            printf("%lld\n", (x % M + M) % M);
            continue;
        }
        if (n == 1) {
            printf("%lld\n", (y % M + M) % M);
            continue;
        }
        
        Matrix Tn = power(T, n - 1);
        
        __int128 ans = (__int128)Tn.mat[0][0] * ((y % M + M) % M) + 
                       (__int128)Tn.mat[0][1] * ((x % M + M) % M);
        
        long long final_ans = (long long)((ans % M + M) % M);
        printf("%lld\n", final_ans);
    }
    
    return 0;
}
