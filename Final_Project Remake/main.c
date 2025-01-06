#include <stdio.h>
#include <stdlib.h>
#include "function2.h"
#include <stdbool.h>
#include <string.h>
#include "functionUser.h"
//Name admin: Hoang
//Password admin: Xuan


int main() {
    int mainMenuChoice;
	
    while (1) {
    	MAIN_MENU:
        mainMenu(); 

        printf("Enter your choice: ");
        scanf("%d", &mainMenuChoice);
        clearScreen();

        switch (mainMenuChoice) {
            case 1: {
                ADMIN_MENU_BACK: 
                adminMenu(); 

                int adminRegisterAndLogIn;
                adminAccount acc[100];
                int n = readAccount(acc);

                do {
                    printf("Register or Log in or Back: ");
                    scanf("%d", &adminRegisterAndLogIn);
                

                    switch (adminRegisterAndLogIn) {
                        case 1: {
                            while (getchar() != '\n');
                            registerAdminAccount(acc, &n);
                            break;
                        }
                        case 2: {
                            logInAdminAccount(acc, n);
                            clearScreen();
                            adminMenuAfterLogin();
                            int adminChoice;
                            while (1) {
                                printf("Enter your choice admin: ");
                                scanf("%d", &adminChoice);
                                switch (adminChoice) {
                                    case 1: {
                                        while (getchar() != '\n');
                                        addUser();
                                        break;
                                    }
                                    case 2: {
                                        showAllUser("userInfor.bin");
                                        break;
                                    }
                                    case 3: {
                                        showOneUser("userInfor.bin");
                                        break;
                                    }
                                    case 4:{
                                    	lockUnlockAccount("userInfor.bin");
										break;
									}
									case 5:{
										sortUsersByAlphabet();
										break;
									}
									
                                    case 0: {
                                        clearScreen();
                                        goto ADMIN_MENU_BACK; 
                                    }
                                }
                            }
                            break;
                        }
                        case 3: {
                            clearScreen();
                            goto MAIN_MENU; 
                        }
                    }
                } while (1);

                 
                break;
            }
            
          	case 2:{
          		int userChoice;
          		User acc[100];
             
			    int n = readAccountUser(acc);
          		userMenu();
          		do {
				printf("Enter your choice: ");
          		scanf("%d", &userChoice);
          		while (getchar() != '\n');
          		
          		switch (userChoice){
          			case 1:{
          				char loggedInEmail[30];
                		char loggedInPhone[20];
          				if (logInUserAccount(acc, n, loggedInEmail, loggedInPhone)) {
          				clearScreen();
          				userMenuAfterLogin();
          				int userAterLoginChoice;
          				while(1) {
          					printf("Enter function: ");
          					scanf("%d", &userAterLoginChoice);
          					while (getchar() != '\n');
          					switch (userAterLoginChoice){
          					case 1: {
    							
        						showLoggedInUser(acc, n, loggedInEmail, loggedInPhone);
								break;
						 	}
						 	case 0: {
						 		clearScreen();
                                goto MAIN_MENU;
							 }
						}	
					}	
				}			
		  	}
					  case 2:
					  	clearScreen();
					  	goto MAIN_MENU;
				  }
				} while(1);
				
			}
            case 0: {
                end();
                return 0; 
            }
            break;
        }

        if (mainMenuChoice > 2) {
            printf("Invalid choice. Please try again!\n");
            printf("\n");
        }
    }
    return 0;
}
