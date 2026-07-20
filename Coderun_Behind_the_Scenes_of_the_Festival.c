#include <stdio.h>

char arr[10000005], buf[1 << 20];
int h = 0, t = 0;

int next_int() {
    while (1) {
        if (h >= t) {
            t = fread(buf, 1, 1 << 20, stdin);
            h = 0;
            if (!t) return 0;
        }
        if (buf[h] >= '0' && buf[h] <= '9') break;
        h++;
    }
    int res = 0;
    while (1) {
        if (h >= t) {
            t = fread(buf, 1, 1 << 20, stdin);
            h = 0;
            if (!t) break;
        }
        if (buf[h] < '0' || buf[h] > '9') break;
        res = res * 10 + (buf[h++] - '0');
    }
    return res;
}

int main() {
    int n = next_int(), exp = 1, cur = 0, max = 0, id;
    while ((id = next_int())) {
        arr[id] = 1, cur++;
        while (arr[exp]) cur--, exp++;
        if (cur > max) max = cur;
    }
    printf("%d\n", max);
    return 0;
}
