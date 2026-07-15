/* 1. Coderun and bike rental on the embankment */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

long long read() {
    long long c = getchar_unlocked(), res = 0;
    while (c <= 32 && c != EOF) c = getchar_unlocked();
    if (c == EOF) return 0;
    while (c > 32) { res = res * 10 + (c - '0'); c = getchar_unlocked(); }
    return res;
}

int main() {
    int n = read(), t = read();
    long long *diff = calloc(t + 2, sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        int a = read(), f = read();
        long long s = read();
        
        if (a <= t) diff[a] += s;
        if (f <= t) diff[f] -= s;
    }

    long long max = 0, cur = 0;
    for (int i = 0; i <= t; i++) {
        cur += diff[i];
        if (cur > max) max = cur;
    }
  
    printf("%lld\n", max);
    free(diff);
    return 0;
}
