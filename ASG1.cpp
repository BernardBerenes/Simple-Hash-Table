#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>

struct Node{
	char name[255];
	int dd, mm, yyyy;
	char age[255];
	char gender[255];
	double weight;
	Node *next;
};

Node *head[25];
int flag;
int flagPop;

Node *createNode(char name[], int dd, int mm, int yyyy, char age[], char gender[], double weight){
	Node *newNode = (Node*) malloc(sizeof(Node));
	strcpy(newNode->name, name);
	newNode->dd = dd;
	newNode->mm = mm;
	newNode->yyyy = yyyy;
	strcpy(newNode->age, age);
	strcpy(newNode->gender, gender);
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

int hashFormula(char name[]){
	int hashKey = 0;
	for(int i = 0; i < strlen(name); i++){
		hashKey += name[i];
	}
	return hashKey % 25;
}

void insertTable(char name[], int dd, int mm, int yyyy, char age[], char gender[], double weight){
	int hashKey = hashFormula(name);
	Node *newNode = createNode(name, dd, mm, yyyy, age, gender, weight);
	
	if(head[hashKey] == NULL){
		head[hashKey] = newNode;
	} else{
		Node *curr = head[hashKey];
		while(curr->next){
			curr = curr->next;
		}
		curr->next = newNode;
	}
}

void viewAll(){
	int iterate = 1;
	int empty = 0;
	system("cls");
	for(int i = 0; i < 25; i++){
		if(head[i] != NULL){
			Node *curr = head[i];
			while(curr != NULL){
				empty = 1;
				printf("No %d\n", iterate);
				printf("Pet Name   : %s\n", curr->name);
				printf("Pet DOB    : %d-%d-%d\n", curr->dd, curr->mm, curr->yyyy);
				printf("Pet Age    : %s\n", curr->age);
				printf("Pet Sex    : %s\n", curr->gender);
				if(curr->weight - (int)curr->weight == 0){
					printf("Pet Weight : %d\n", (int)curr->weight);
				} else{
					printf("Pet Weight : %.2lf\n", curr->weight);
				}
				printf("==========================================\n");
				iterate++;
				curr = curr->next;
			}
		}
	}
	if(empty == 0){
		printf("Theres no pet yet :D\n");
	}
}

void viewPop(){
	int empty = 0;
	system("cls");
	for(int i = 0; i < 25; i++){
		if(head[i] != NULL){
			empty = 1;
			break;
		}
	}
	if(empty == 1){
		char str = '|';
		printf("=================================\n");
		printf("|            Pet List           |\n");
		printf("=================================\n");
		for(int i = 0; i < 25; i++){
			if(head[i] != NULL){
				Node *curr = head[i];
				while(curr){
					printf("| %-29s |\n", curr->name, str);
					curr = curr->next;
				}
			}
		}
		printf("=================================\n");
		flag = 1;
	} else{
		flag = 0;
		printf("Theres no pet yet :D\n");
	}
}

void pop(char search[]){
	int hashKey = hashFormula(search);
	if(head[hashKey] == NULL){
		printf("Name are not available on the list !\n");
		return;
	} else if(head[hashKey] != NULL && strcmp(head[hashKey]->name, search) == 0){
		if(head[hashKey]->next == NULL){
			printf("Name has been deleted\n");
			flagPop = 1;
			free(head[hashKey]);
			head[hashKey] = NULL;
			return;
		} else if(head[hashKey]->next != NULL){
			printf("Name has been deleted\n");
			flagPop = 1;
			head[hashKey] = head[hashKey]->next;
			return;
		}
	} else{
		Node *curr = head[hashKey];
		while(curr->next != NULL){
			if(curr->next == NULL && strcmp(curr->name, search) != 0){
				printf("Name are not available on the list !\n");
				return;
			} else if(strcmp(curr->next->name, search) == 0){
				printf("Name has been deleted\n");
				flagPop = 1;
				Node *toDel = curr->next;
				curr->next = toDel->next;
				return;
			}
			curr = curr->next;
		}
	}
}

void menu(){
	system("cls");
	printf("PetShop\n");
	printf("===========================\n");
	printf("1. Pet Management\n");
	printf("2. View all pet\n");
	printf("3. Exit\n");
	printf("Choose [1-3] >> ");
}

void petManage(){
	system("cls");
	printf("Welcome to Pet Management System\n");
	printf("===========================\n");
	printf("1. Add a new pet\n");
	printf("2. Remove a pet\n");
	printf("3. Back\n");
	printf("Choose [1-3] >> ");
}

int main(){
	
	int choice = -1;
	int choiceManage = -1;
	int lenstring;
	while(choice != 3){
		menu();
		scanf("%d", &choice); getchar();
		
		switch(choice){
			case 1: // Pet Management
				do{
					petManage();
					scanf("%d", &choiceManage); getchar();
				
					switch(choiceManage){
						case 1: // Add
							char name[255];
							int dd, mm, yyyy;
							char age[255];
							char gender[255];
							double weight;
							system("cls");
							do{
								printf("Insert pet name [5 - 30 characters] : ");
								scanf("%s", &name); getchar();
								lenstring = strlen(name);
								if(lenstring < 5 || lenstring > 30){
									printf("pet name length must be between 5 - 30 characters!\n");
								}
							} while(lenstring < 5 || lenstring > 30);
							
							do{
								flag = 1;
								printf("Insert pet Date of Birth [dd-mm-yyyy] : ");
								scanf("%d-%d-%d", &dd, &mm, &yyyy); getchar();
								if(dd < 1 || dd > 30){
									flag = 0;
									printf("Please input a valid date\n");
								} else if(mm < 1 || mm > 12){
									flag = 0;
									printf("Please input a valid date\n");
								} else if(yyyy < 0 || yyyy > 9999){
									flag = 0;
									printf("Please input a valid date\n");
								}
							} while(flag != 1);
							
							do{
								flag = 1;
								printf("Insert pet age [Must be a number]: ");
								scanf("%s", &age); getchar();
								
								for(int i = 0; i < strlen(age); i++){
									if(isdigit(age[i]) == 0){
										flag = 0;
										printf("Input must be a number!\n");
										break;
									}
								}
								
							} while(flag != 1);
							
							do{
								flag = 1;
								printf("Insert pet gender [Male | Female] (Case Insensitive) : ");
								scanf("%s", &gender); getchar();
								
								if(strcmpi(gender, "male") != 0 && strcmpi(gender, "female") != 0){
									flag = 0;
									printf("Gender must be between Male or Female!\n");
								}
								
								for(int i = 0; i < strlen(gender); i++){
									if(i == 0 && gender[i] >= 'a' && gender[i] <= 'z'){
										gender[i] -= 32;
									} else if(gender[i] >= 'A' && gender[i] <= 'Z' && i > 0){
										gender[i] += 32;
									}
								}
								
							} while(flag != 1);
							
							do{
								printf("Insert pet weight (not more than 80kg) : ");
								scanf("%lf", &weight); getchar();
								
								if(weight <= 0 || weight > 80){
									printf("Please input a valid weight\n");
								}
								
							} while(weight <= 0 || weight > 80);
							
							insertTable(name, dd, mm, yyyy, age, gender, weight);
							
							printf("Data has been recorded :D\n");
							printf("Press enter to continue.."); getchar();
							
							break;
							
						case 2: // Remove
							flagPop = 0;
							viewPop();
							char popSearch[255];
							if(flag == 1){
								do{
									printf("Please input pet name to be removed [0 to exit] : ");
									scanf("%s", &popSearch); getchar();
									
									pop(popSearch);
									if(strcmpi(popSearch, "0") == 0){
										flag = 2;
									} else if(flagPop == 1){
										break;
									}
								} while(flag != 2);
							}
							if(flag != 2){
								printf("Press enter to continue.."); getchar();
							}
							break;
							
						case 3: // Back
							break;
					}
				} while(choiceManage != 3);
				break;
				
			case 2: // View
				viewAll();
				printf("Press enter to continue.."); getchar();
				break;
				
			case 3: // Exit
				break;
		}
	}
	
	return 0;
}
