#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define INF 1e19

unsigned long long a[MAXN];
unsigned long long pref_sum[MAXN];
unsigned long long pref_xor[MAXN];
unsigned long long f_val[MAXN];
unsigned long long ans[MAXN];
int deque[MAXN];

unsigned long long get_f(int l, int r) {
    unsigned long long sum = pref_sum[r] - pref_sum[l - 1];
    unsigned long long xor_val = pref_xor[r] ^ pref_xor[l - 1];
    return sum - xor_val;
}

void solve() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return;

    pref_sum[0] = 0;
    pref_xor[0] = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%llu", &a[i]);
        pref_sum[i] = pref_sum[i - 1] + a[i];
        pref_xor[i] = pref_xor[i - 1] ^ a[i];
        ans[i] = INF;
    }

    int segments_cnt = n - k + 1;
    for (int l = 1; l <= segments_cnt; ++l) {
        f_val[l] = get_f(l, l + k - 1);
    }

    int head = 0, tail = 0;
    for (int i = 1; i <= n; ++i) {
        if (i <= segments_cnt) {
            while (head < tail && f_val[deque[tail - 1]] >= f_val[i]) {
                tail--;
            }
            deque[tail++] = i;
        }

        while (head < tail && deque[head] < i - k + 1) {
            head++;
        }

        if (head < tail) {
            ans[i] = f_val[deque[head]];
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%llu%c", ans[i], (i == n) ? '\n' : ' ');
    }
}

int main() {
    int t;
    if (scanf("%d", &t) != 1) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
