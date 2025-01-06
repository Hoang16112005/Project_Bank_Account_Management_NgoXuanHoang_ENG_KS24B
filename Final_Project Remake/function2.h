#include <string.h>
#include "datatype.h"
#include <stdbool.h>
#include <conio.h>


void clearScreen() { //refresh terminal screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void mainMenu(){
	printf("*****Bank Management System*****\n");
	printf("        Choose your role      \n");
	printf("      ====================    \n");
	printf("      [1] Admin               \n");
	printf("      [2] User               \n");
	printf("      [0] Exit               \n");
	printf("      ====================    \n");
}

void adminMenu(){
	printf("   *****Bank Management System*****\n");
	printf("             ADMIN SCREEN        \n");
	printf("    [1].REGISTER [2].LOGIN [3].Back    \n");
	printf("  ====================================   \n");
}

int saveAccount(adminAccount acc[], int n){  //save admin account function
	FILE *file;
	file = fopen("adminAccount.txt", "w");
	if(file == NULL){
		printf("Can't open file\n");
		return 1;
	}
	fwrite(acc, sizeof(adminAccount), n, file);
	fclose(file);
}

void getPassword(char *password, int maxLength) {  // * password function
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) { // Phím Enter
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) { // Phím Backspace
            printf("\b \b");
            i--;
        } else if (i < maxLength - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}



void registerAdminAccount(adminAccount acc[], int *n){  //register admin account function
	char nameAdmin[50];
	char passAdmin[50];
	char confirmPassAdmin[50];
	fflush(stdin);
	printf("Enter new admin name: ");
	fgets(nameAdmin, sizeof(nameAdmin), stdin);
	nameAdmin[strcspn(nameAdmin, "\n")] = '\0';


	for(int i = 0; i < *n; i++){
		if(strcmp(acc[i].nameAdmin, nameAdmin) == 0){
			printf("Account existed, try another account\n");
			return;
		}
		
	}

	printf("Enter password: ");
	fgets(passAdmin, sizeof(passAdmin), stdin);
	passAdmin[strcspn(passAdmin, "\n")] = '\0';

	printf("Enter password again: ");
	fgets(confirmPassAdmin, sizeof(confirmPassAdmin), stdin);
	confirmPassAdmin[strcspn(confirmPassAdmin, "\n")] = '\0';

	if(strcmp(passAdmin, confirmPassAdmin) != 0){
		printf("Password doesn't match, try again\n");
		return;
	}
	strcpy(acc[*n].nameAdmin, nameAdmin);
	strcpy(acc[*n].passAdmin, passAdmin);
	(*n)++;
	saveAccount(acc, *n);
	printf("Register completed\n");

}


int readAccount(adminAccount acc[]){
	FILE *file;
	file=fopen("adminAccount.txt", "r");
	int n=0;
	while(fread(&acc[n], sizeof(adminAccount), 1, file)){
		n++;
	}
	fclose(file);
	return n;
}

bool logInAdminAccount(adminAccount acc[], int n) {
    char nameAdmin[50];
    char passAdmin[50];

    while (1) {
    	fflush(stdin);
        printf("Enter admin name: ");
        fgets(nameAdmin, sizeof(nameAdmin), stdin);
        nameAdmin[strcspn(nameAdmin, "\n")] = 0;
		
		printf("Enter password: ");
       	getPassword(passAdmin, sizeof(passAdmin));
        
		for (int i = 0; i < n; i++) {
            if (strcmp(acc[i].nameAdmin, nameAdmin) == 0 && strcmp(acc[i].passAdmin, passAdmin) == 0) {
                printf("Log in successfully\n");
                return true;
            }
        }

        printf("Log in failed. Please try again.\n");
	}
    return false;
}


void adminMenuAfterLogin(){
	printf("Log in successfully\n");
	printf("*****Bank Management System*****\n");
	printf("\n");
	printf("\t   MENU \n");
	printf("=================================\n");
	printf("[1] Add A New user.\n");
	printf("[2] Show All users\n");
	printf("[3] Show detail an user.\n");
	printf("[4] Lock (Unlock) an  user\n");
	printf("[5] Arrange user by Name\n");
	printf("[0] Back to main menu.\n");
	printf("=================================\n");
}



int readUsers(User users[]) {    // read user infor
    FILE *file = fopen("userInfor.bin", "rb");
    if (file == NULL) {
        return 0;
    }
    int n = 0;
    while (fread(&users[n], sizeof(User), 1, file)) {
        n++;
    }
    fclose(file);
    return n;
}


bool wasDuplicated(User *users, int n, const char *userId, const char *email, const char *phone, const char *name) {  // duplicate check function
    for (int i = 0; i < n; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            return true;
        }
        if (strcmp(users[i].email, email) == 0) {
            return true; 
        }
        if (strcmp(users[i].phone, phone) == 0) {
            return true; 
        }
        if (strcmp(users[i].name, name) == 0) {
            return true; 
        }
    }
    return false;
}

void addUser() {  //adding user function
    FILE *file = fopen("userInfor.bin", "ab");  
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    User newUser;
    User users[1000];
    int n = readUsers(users);

    while (1) {
        printf("Enter ID (12 digits exactly): ");
        fgets(newUser.userId, sizeof(newUser.userId), stdin);
        newUser.userId[strcspn(newUser.userId, "\n")] = 0;

        if (strlen(newUser.userId) == 12) {
            if (wasDuplicated(users, n, newUser.userId, "", "", "")) {
                printf("ID already exists. Please enter a different ID.\n");
                continue; 
            }
            break;
        }
        printf("ID must be exactly 12 digits. Please try again\n");
        
    }
	
	
	while(1){
		printf("Enter email: ");
    	fgets(newUser.email, sizeof(newUser.email), stdin);
    	newUser.email[strcspn(newUser.email, "\n")] = 0;

    	while (wasDuplicated(users, n, "", newUser.email, "", "")) {
        printf("Email already exists. Enter a new email: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strcspn(newUser.email, "\n")] = 0;
   		}
   		if (strlen(newUser.email) < 5){
   			printf("Can't let empty, try again\n");
   			continue;
		}
		break;
	}

    while (1) {
        printf("Enter password (Your phone number): ");
        fgets(newUser.password, sizeof(newUser.password), stdin);
        newUser.password[strcspn(newUser.password, "\n")] = 0;

        if (strlen(newUser.password) == 10) {
            break;
        }
        printf("Password must be 10 digits. Try again \n");
    }

    while(1){
    	printf("Enter your name: ");
    	fgets(newUser.name, sizeof(newUser.name), stdin);
    	newUser.name[strcspn(newUser.name, "\n")] = 0;

    	while (wasDuplicated(users, n, "", "", "", newUser.name)) {
        printf("Name already exists. Enter a new name: ");
        fgets(newUser.name, sizeof(newUser.name), stdin);
        newUser.name[strcspn(newUser.name, "\n")] = 0;
   		}
   		if (strlen(newUser.name) < 2){
   			printf("Can't let empty or smaller than 2 characters, try again\n");
   			continue;
		}
		break;
	}

    while (1){
    	printf("Enter phone number: ");
    	fgets(newUser.phone, sizeof(newUser.phone), stdin);
    	newUser.phone[strcspn(newUser.phone, "\n")] = 0;

    	while (wasDuplicated(users, n, "", "", newUser.phone, "")) {
        printf("Phone number already exists. Enter a new phone number: ");
        fgets(newUser.phone, sizeof(newUser.phone), stdin);
        newUser.phone[strcspn(newUser.phone, "\n")] = 0;
    	}
    	if (strlen(newUser.phone) < 10){
   			printf("Can't let empty or smaller than 10 digits, try again\n");
   			continue;
    	}
    	break;
	}

    if (fwrite(&newUser, sizeof(User), 1, file) != 1) {
        printf("Error writing to file.\n");
    } else {
        printf("User successfully added!\n");
    }

    fclose(file);
}


int compareNameByAlphabet(const void *a, const void *b) {  //compare first letter in users name
    User *userA = (User *)a; 
    User *userB = (User *)b; 
    return strcmp(userA->name, userB->name); 
}


void sortUsersByAlphabet() {    //arrange users
    User users[1000];
    int n = readUsers(users); 

    if (n == 0) {
        printf("No user data available!\n");
        return;
    }
    qsort(users, n, sizeof(User), compareNameByAlphabet);

    printf("|===============|======================|==============================|======================|==========|\n");
    printf("|      ID       |         NAME         |             EMAIL            |         PHONE        |  STATUS  |\n");
    printf("|===============|======================|==============================|======================|==========|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-15s | %-20s | %-28s | %-20s | %-8s |\n", 
                users[i].userId, users[i].name, users[i].email, users[i].phone, users[i].lock ? "Locked" : "Unlocked");
        printf("|---------------|----------------------|------------------------------|----------------------|----------|\n");
    }
}

void showAllUser(char *filename) { // show all users account
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    User user;
    printf("|===============|======================|==============================|======================|==========|\n");
    printf("|      ID       |         NAME         |             EMAIL            |         Phone        |  Status  |\n");
    printf("|===============|======================|==============================|======================|==========|\n");

    while (fread(&user, sizeof(User), 1, file) == 1) {
        printf("| %-15s | %-20s | %-28s | %-20s | %-8s |\n", 
                user.userId, user.name, user.email, user.phone, user.lock ? "Locked" : "Unlocked");
    		printf("|---------------|----------------------|------------------------------|----------------------|----------|\n");
    }

    fclose(file);
}


void showOneUser(char *filename) {  //show only 1 person
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    User user;
    char IdSearching[20];
    int found = 0;
    fflush(stdin);
    printf("Enter the ID to search: ");
    fgets(IdSearching, sizeof(IdSearching), stdin);
    IdSearching[strcspn(IdSearching, "\n")] = 0; 


    printf("|===============|======================|==============================|======================|==========|\n");
    printf("|      ID       |         NAME         |             EMAIL            |         Phone        |  Status  |\n");
    printf("|===============|======================|==============================|======================|==========|\n");

    while (fread(&user, sizeof(User), 1, file) == 1) {
        if (strcmp(user.userId, IdSearching) == 0) {
            printf("| %-15s | %-20s | %-28s | %-20s | %-8s |\n", 
                    user.userId, user.name, user.email, user.phone, user.lock ? "Locked" : "Unlocked");
            printf("|---------------|----------------------|------------------------------|----------------------|----------|\n");
            found = 1;
            break; 
        }
    }

    if (!found) {
        printf("User with ID '%s' does't exist'\n", IdSearching);
    }

    fclose(file);
}

void lockUnlockAccount(char *filename) {  //lock or unlock user account
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    char userIdToSearch[20];
    bool newLockStatus;
    User user;
    int found = 0;
    
	fflush(stdin);
    printf("\t **Lock (Unlock) an user**\n");
    printf("\n");
    printf("Enter the User ID you want to unlock/ lock: ");
    fgets(userIdToSearch, sizeof(userIdToSearch), stdin);
    userIdToSearch[strcspn(userIdToSearch, "\n")] = 0; 
	
	while (fread(&user, sizeof(User), 1, file) == 1) {
        if (strcmp(user.userId, userIdToSearch) == 0) {
            found = 1;
            printf("One user was found for ID: %s\n", user.userId);
            printf("Current lock status: %s\n", user.lock ? "Locked" : "Unlocked");
            printf("Do you want to lock the account (1 for Lock, 0 for Unlock)? ");
            scanf("%d", &newLockStatus);
            user.lock = newLockStatus;
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);
            printf("Lock status updated successfully.\n");
            break;
        }
        printf("Can't find user with ID '%s' \n", userIdToSearch);
    }
    fclose(file);
}

void end(){
	printf("========== Thank You =============\n");
	printf("======== See You Soon ============\n");
	printf("\n");
	printf("------------------------------------");
	return 0;
}
