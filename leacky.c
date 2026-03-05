#include <stdio.h>
#include <stdlib.h>

int main() {
    int bucketSize, outputRate, n, i;
    int packetSize, bucketContent = 0;

    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);

    printf("Enter output rate: ");
    scanf("%d", &outputRate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    for(i = 1; i <= n; i++) {
        printf("\nEnter size of packet %d: ", i);
        scanf("%d", &packetSize);

        // Add packet to bucket
        if(bucketContent + packetSize > bucketSize) {
            printf("Bucket overflow! Packet dropped.\n");
        } else {
            bucketContent += packetSize;
            printf("Packet added. Bucket content: %d\n", bucketContent);
        }

        // Transmit packets
        if(bucketContent > 0) {
            if(bucketContent < outputRate) {
                printf("Transmitted: %d\n", bucketContent);
                bucketContent = 0;
            } else {
                printf("Transmitted: %d\n", outputRate);
                bucketContent -= outputRate;
            }
        }

        printf("Remaining bucket content: %d\n", bucketContent);
    }

    return 0;
}

