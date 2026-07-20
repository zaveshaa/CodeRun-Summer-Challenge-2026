#include <stdio.h>
#include <stdlib.h>

typedef struct { int id, score, time; } Part;
Part a[5000005];
char buf[1 << 20];

int next_int() {
    static int head = 0, tail = 0;
    while (1) {
        if (head >= tail) {
            tail = fread(buf, 1, 1 << 20, stdin);
            head = 0;
            if (!tail) return 0;
        }
        if (buf[head] >= '0' && buf[head] <= '9') break;
        head++;
    }
    int res = 0;
    while (1) {
        if (head >= tail) {
            tail = fread(buf, 1, 1 << 20, stdin);
            head = 0;
            if (!tail) break;
        }
        if (buf[head] < '0' || buf[head] > '9') break;
        res = res * 10 + (buf[head++] - '0');
    }
    return res;
}

int cmp(const void *x, const void *y) {
    Part *p1 = (Part *)x, *p2 = (Part *)y;
    if (p1->id != p2->id) 
        return (p1->id > p2->id) - (p1->id < p2->id); 
    return (p2->time > p1->time) - (p2->time < p1->time);
}

int main() {
    int m = next_int(), n = 0;
    for (int i = 0; i < m; i++) {
        int l = next_int();
        for (int j = 0; j < l; j++) {
            a[n].id = next_int();
            a[n].score = next_int();
            a[n++].time = n;
        }
    }

    qsort(a, n, sizeof(Part), cmp);

    for (int i = 0; i < n; i++) {
        if (i == 0 || a[i].id != a[i - 1].id) {
            printf("%d %d\n", a[i].id, a[i].score);
        }
    }
    return 0;
}
