#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

void printFrames(int frames[], int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d(%d) ", frames[i], i + 1);
        }
    }
    printf("\n");
}

void fifo(int pages[], int n, int capacity) {
    int frames[MAX_FRAMES];
    int faults = 0;
    int frameIndex = 0;

    printf("\nFIFO Page Replacement Algorithm:\n");
    for (int i = 0; i < n; ++i) {
        int found = 0;
        for (int j = 0; j < capacity; ++j) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++;
            if (frameIndex < capacity) {
                frames[frameIndex++] = pages[i];
            } else {
                int oldest = 0;
                for (int j = 1; j < capacity; ++j) {
                    if (frames[j] < frames[oldest]) {
                        oldest = j;
                    }
                }
                frames[oldest] = pages[i];
            }
        }

        printf("Frames: ");
        printFrames(frames, capacity);
    }

    printf("Total Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int capacity) {
    int frames[MAX_FRAMES];
    int lru[MAX_FRAMES];
    int faults = 0;
    int i, j;

    printf("LRU Page Replacement Algorithm:\n");
    for (i = 0; i < n; ++i) {
        int found = 0;
        for (j = 0; j < capacity; ++j) {
            if (frames[j] == pages[i]) {
                found = 1;
                lru[j] = i;
                break;
            }
        }

        if (!found) {
            faults++;
            printf("MISS: Page %d\n", pages[i]);
            if (i < capacity) {
                frames[i] = pages[i];
                lru[i] = i;
            } else {
                int least = 0;
                for (j = 1; j < capacity; ++j) {
                    if (lru[j] < lru[least]) {
                        least = j;
                    }
                }
                frames[least] = pages[i];
                lru[least] = i;
            }
        } else {
            printf("HIT: Page %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n\n", faults);
}

void optimal(int pages[], int n, int capacity) {
    int frames[MAX_FRAMES];
    int faults = 0;
    int i, j, k;

    printf("Optimal Page Replacement Algorithm:\n");
    for (i = 0; i < n; ++i) {
        int found = 0;
        for (j = 0; j < capacity; ++j) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++;
            printf("MISS: Page %d\n", pages[i]);
            if (i < capacity) {
                frames[i] = pages[i];
            } else {
                int index[MAX_FRAMES];
                for (j = 0; j < capacity; ++j) {
                    index[j] = -1;
                    for (k = i + 1; k < n; ++k) {
                        if (frames[j] == pages[k]) {
                            index[j] = k;
                            break;
                        }
                    }
                }

                int furthest = 0;
                for (j = 1; j < capacity; ++j) {
                    if (index[j] == -1 || index[j] > index[furthest]) {
                        furthest = j;
                    }
                }
                frames[furthest] = pages[i];
            }
        } else {
            printf("HIT: Page %d\n", pages[i]);
        }
    }

    printf("Total Page Faults: %d\n\n", faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fcfs(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}

