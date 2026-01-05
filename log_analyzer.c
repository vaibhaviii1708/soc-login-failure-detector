#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_NAME_LEN 50
#define ALERT_THRESHOLD 3

int main() {
    FILE *file;
    char line[200];

    char users[MAX_USERS][MAX_NAME_LEN];
    int failCount[MAX_USERS];
    int userCount = 0;

    file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Failed login")) {

            char username[MAX_NAME_LEN];
            sscanf(line, "Failed login for user %s", username);

            int found = 0;

            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i], username) == 0) {
                    failCount[i]++;
                    found = 1;

                    if (failCount[i] == ALERT_THRESHOLD) {
                        printf("ALERT: User %s has %d failed login attempts!\n",
                               users[i], failCount[i]);
                    }
                    break;
                }
            }

            if (!found && userCount < MAX_USERS) {
                strcpy(users[userCount], username);
                failCount[userCount] = 1;
                userCount++;
            }
        }
    }

    fclose(file);

    printf("\n--- Security Summary ---\n");
    for (int i = 0; i < userCount; i++) {
        printf("User: %s | Failed Attempts: %d\n", users[i], failCount[i]);
    }

    return 0;
}
