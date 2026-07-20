#include <stdio.h>
#include <stdlib.h>

int bit[1005][1005];
int ans[250005];
int N, M;

void update(int r, int c, int val) {
    for (int i = r; i <= N; i += i & -i) {
        for (int j = c; j <= M; j += j & -j) {
            bit[i][j] += val;
        }
    }
}

int query(int r, int c) {
    int sum = 0;
    for (int i = r; i > 0; i -= i & -i) {
        for (int j = c; j > 0; j -= j & -j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int query_rect(int r1, int c1, int r2, int c2) {
    return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
}

typedef struct {
    int type; 
    int val;
    int r1, c1, r2, c2;
    int id;
} Event;

int compare_events(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->val != e2->val) {
        if (e2->val > e1->val) return 1;
        if (e2->val < e1->val) return -1;
        return 0;
    }
    return e1->type - e2->type; 
}

Event events[1000005 + 250005];

void solve() {
    int q;
    if (scanf("%d %d %d", &N, &M, &q) != 3) return;

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            bit[i][j] = 0;
        }
    }

    int event_cnt = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            int val;
            scanf("%d", &val);
            events[event_cnt].type = 0; 
            events[event_cnt].val = val;
            events[event_cnt].r1 = i;
            events[event_cnt].c1 = j;
            event_cnt++;
        }
    }

    for (int i = 0; i < q; ++i) {
        int r1, c1, r2, c2, x;
        scanf("%d %d %d %d %d", &r1, &c1, &r2, &c2, &x);
        events[event_cnt].type = 1; 
        events[event_cnt].val = x;
        events[event_cnt].r1 = r1;
        events[event_cnt].c1 = c1;
        events[event_cnt].r2 = r2;
        events[event_cnt].c2 = c2;
        events[event_cnt].id = i;
        event_cnt++;
    }

    qsort(events, event_cnt, sizeof(Event), compare_events);

    for (int i = 0; i < event_cnt; ++i) {
        if (events[i].type == 0) {
            update(events[i].r1, events[i].c1, 1);
        } else {
            ans[events[i].id] = query_rect(events[i].r1, events[i].c1, events[i].r2, events[i].c2);
        }
    }

    for (int i = 0; i < q; ++i) {
        printf("%d\n", ans[i]);
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
