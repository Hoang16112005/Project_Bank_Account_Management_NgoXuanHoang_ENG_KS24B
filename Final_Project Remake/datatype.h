#include <stdbool.h>

typedef struct {
	char nameAdmin[50];
	char passAdmin[50];
}adminAccount;




typedef struct {
    char userId[20];
    char email[30];
    char password[20];
    char name[50];
    char phone[20];
    bool lock;
} User;
