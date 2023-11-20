#include <stdio.h>
#include <stdlib.h>

// Function to perform SCAN disk scheduling
void SCAN(int *requests, int head, int size, int direction) {
    int seek_count = 0;
    int distance, cur_track;
    int left = head, right = head;

    int visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = 0;
    }

    printf("Seek Sequence: ");

    while (1) {
        if (direction == 1) {
            for (cur_track = right; cur_track < size; cur_track++) {
                if (visited[cur_track] == 0) {
                    distance = abs(requests[cur_track] - head);
                    seek_count += distance;
                    head = requests[cur_track];
                    visited[cur_track] = 1;
                    printf("%d ", head);
                }
            }
            direction = -1;
        } else if (direction == -1) {
            for (cur_track = left; cur_track >= 0; cur_track--) {
                if (visited[cur_track] == 0) {
                    distance = abs(requests[cur_track] - head);
                    seek_count += distance;
                    head = requests[cur_track];
                    visited[cur_track] = 1;
                    printf("%d ", head);
                }
            }
            direction = 1;
        }

        int flag = 0;
        for (int i = 0; i < size; i++) {
            if (visited[i] == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            break;
        }
    }

    printf("\nTotal seek count: %d\n", seek_count);
}

// Function to perform C-LOOK disk scheduling
void CLOOK(int *requests, int head, int size) {
    int seek_count = 0;
    int distance, cur_track;

    printf("Seek Sequence: ");

    int cur_index = 0;
    for (cur_track = 0; cur_track < size; cur_track++) {
        if (requests[cur_track] >= head) {
            cur_index = cur_track;
            break;
        }
    }

    for (int i = cur_index; i < size; i++) {
        distance = abs(requests[i] - head);
        seek_count += distance;
        head = requests[i];
        printf("%d ", head);
    }

    if (cur_index != 0) {
        for (int i = 0; i < cur_index; i++) {
            distance = abs(requests[i] - head);
            seek_count += distance;
            head = requests[i];
            printf("%d ", head);
        }
    }

    printf("\nTotal seek count: %d\n", seek_count);
}

// Function to perform SSTF disk scheduling
void SSTF(int *requests, int head, int size) {
    int seek_count = 0;
    int distance, cur_track, min_distance, next_track;

    printf("Seek Sequence: ");

    while (size != 0) {
        min_distance = INT_MAX;
        for (int i = 0; i < size; i++) {
            distance = abs(requests[i] - head);
            if (distance < min_distance) {
                min_distance = distance;
                next_track = i;
            }
        }
        seek_count += min_distance;
        head = requests[next_track];
        printf("%d ", head);
        requests[next_track] = requests[size - 1];
        size--;
    }

    printf("\nTotal seek count: %d\n", seek_count);
}

int main() {
    int size, head, i, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &size);

    int *requests = (int *)malloc(size * sizeof(int));

    printf("Enter the requests: ");
    for (i = 0; i < size; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (1 for right, -1 for left): ");
    scanf("%d", &direction);

    SCAN(requests, head, size, direction);

     free(requests);

    return 0;
}

