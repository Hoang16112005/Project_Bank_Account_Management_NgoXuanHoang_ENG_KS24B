#include <string.h>

#include <stdbool.h>


void userMenu(){
	printf("   *****Bank Management System*****\n");
	printf("             USER SCREEN        \n");
	printf("          [1].LOGIN [2].Back    \n");
	printf("  ====================================   \n");
}

int readAccountUser(User acc[]){    //read user infor function
	FILE *file;
	file=fopen("userInfor.bin", "rb");
	int n=0;
	while(fread(&acc[n], sizeof(User), 1, file)){
		n++;
	}
	fclose(file);
	return n;
}

bool logInUserAccount(User acc[], int n, char *loggedInEmail, char *loggedInPhone) {
    char email[30];
    char phone[20];

    while (1) {
        fflush(stdin);
        printf("Enter user name (your email): ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = 0;

        printf("Enter password (your phone number): ");
        getPassword(phone, sizeof(phone));

        for (int i = 0; i < n; i++) {
            if (strcmp(acc[i].email, email) == 0 && strcmp(acc[i].phone, phone) == 0) {
                printf("Log in successfully\n");
                strcpy(loggedInEmail, email);  
                strcpy(loggedInPhone, phone); 
                return true;
            }
        }

        printf("Log in failed. Please try again.\n");
    }
    return false;
}

void userMenuAfterLogin(){
	printf("Log in successfully\n");
	printf("*****User Account Management System*****\n");
	printf("\n");
	printf("\t       MENU \n");
	printf("=================================\n");
	printf("[1] Show user informaion.\n");
	printf("[0] Back to main menu.\n");
	printf("=================================\n");
}

void showLoggedInUser(User acc[], int n, const char *email, const char *phone) { 
    for (int i = 0; i < n; i++) {
        if (strcmp(acc[i].email, email) == 0 && strcmp(acc[i].phone, phone) == 0) {
            printf("|===============|======================|==============================|======================|==========|\n");
            printf("|      ID       |         NAME         |             EMAIL            |         Phone        |  Status  |\n");
            printf("|===============|======================|==============================|======================|==========|\n");
            printf("| %-15s | %-20s | %-28s | %-20s | %-8s |\n", 
                    acc[i].userId, acc[i].name, acc[i].email, acc[i].phone, acc[i].lock ? "Locked" : "Unlocked");
            printf("|---------------|----------------------|------------------------------|----------------------|----------|\n");
            return;  
        }
    }
    printf("No account found with the provided email and phone.\n");
}
