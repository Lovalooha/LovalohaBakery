#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

struct Node{
	char id[10],name[30], street[50], flavour[20];
	int diameter,height;
	struct Node *left,*right;
};

struct Node *createNewNode(char id[],char name[],char street[], char flavour[], int diameter){
	struct Node *newNode = (struct Node*)malloc(sizeof(Node));
	newNode->diameter = diameter;
	strcpy(newNode->id, id);
	strcpy(newNode->name, name);
	strcpy(newNode->street, street);
	strcpy(newNode->flavour, flavour);
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

int max(int a,int b){
	if(a>=b){
		return a;
	}
	return b;
}

int getHeight(struct Node* temp){
	if(temp == NULL){
		return 0;
	}
	return temp->height;
}

int getBalance(struct Node *root){
	if(root == NULL){
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}

struct Node *Rrotate(struct Node *node){
	struct Node *tempL = node->left;
	struct Node *tempLR = tempL->right;
	
	tempL->right = node;
	node->left = tempLR;
	node->height = max(getHeight(node->left), getHeight(node->right))+1;
	tempL->height = max(getHeight(tempL->left), getHeight(tempL->right))+1;
	
	return tempL;
}

struct Node* Lrotate(struct Node *node){
	struct Node *tempR = node->right;
	struct Node *tempRL = tempR->left;
	
	tempR->left = node;
	node->right = tempRL;
	node->height = max(getHeight(node->left), getHeight(node->right))+1;
	tempR->height = max(getHeight(tempR->left), getHeight(tempR->right))+1;
	
	return tempR;
}

struct Node *insert(struct Node *root, struct Node* newNode){
	if(root == NULL){
		return newNode;
	}else if(strcmp(newNode->id, root->id) < 0){
		root->left = insert(root->left,newNode);
	}else if(strcmp(newNode->id, root->id) > 0){
		root->right = insert(root->right, newNode);
	}
	root->height = max(getHeight(root->left), getHeight(root->right))+1;
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >= 0){
		root = Rrotate(root);
	}else if(balance > 1 && getBalance(root->left) < 0){
		root->left = Lrotate(root->left);
		root = Rrotate(root);
	}else if(balance < -1 && getBalance(root->right) <= 0){
		root = Lrotate(root);
	}else if(balance < -1 && getBalance(root->right) > 0){
		root->right = Rrotate(root->right);
		root = Lrotate(root);
	}
	return root;
}

struct Node *deleteNode(struct Node *root, char id[]){
	if(root == NULL){
		return root;
	}else if(strcmp(id, root->id) < 0){
		root->left = deleteNode(root->left, id);
	}else if(strcmp(id, root->id) > 0){
		root->right = deleteNode(root->right, id);
	}else{
		if(root->right ==  NULL && root->left == NULL){
			free(root);
			root = NULL;
		}else if(root->right == NULL || root->left == NULL){
			struct Node *temp = root->right ? root->right : root->left;
			free(root);
			root = temp;
		}else{
			struct Node *temp = root->left;
			while(temp->right){
				temp = temp->right;
			}
			strcpy(root->id, temp->id);
			strcpy(root->name, temp->name);
			strcpy(root->street, temp->street);
			strcpy(root->flavour, temp->flavour);
			root->diameter = temp->diameter;
			root->left = deleteNode(root->left, temp->id);
		}
	}
	
	if(root == NULL){
		return root;
	}
	
	root->height = max(getHeight(root->left), getHeight(root->right))+1;
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >= 0){
		root = Rrotate(root);
	}else if(balance > 1 && getBalance(root->left) < 0){
		root->left = Lrotate(root->left);
		root = Rrotate(root);
	}else if(balance < -1 && getBalance(root->right) <= 0){
		root = Lrotate(root);
	}else if(balance < -1 && getBalance(root->right) > 0){
		root->right = Rrotate(root->right);
		root = Lrotate(root);
	}
	return root;
}

void printPreOrder(struct Node *root){
	if(root == NULL){
		return;
	}
	
	printf("| %s | %-20s | %-20s | %-15s | %-10d |\n", root->id, root->name, root->street, root->flavour, root->diameter);
	printPreOrder(root->left);
	printPreOrder(root->right);
}

void printInOrder(struct Node *root){
	if(root == NULL){
		return;
	}
	
	printInOrder(root->left);
	printf("| %s | %-20s | %-20s | %-15s | %-10d |\n", root->id, root->name, root->street, root->flavour, root->diameter);
	printInOrder(root->right);
}

void printPostOrder(struct Node *root){
	if(root == NULL){
		return;
	}
	
	printPostOrder(root->left);
	printPostOrder(root->right);
	printf("| %s | %-20s | %-20s | %-15s | %-10d |\n", root->id, root->name, root->street, root->flavour, root->diameter);
}

struct Node *search(struct Node *root, char id[]){
	if(root == NULL){
		return NULL;
	}
	else if(strcmp(id, root->id) < 0) return search(root->left,id);
	else if(strcmp(id, root->id) > 0) return search(root->right,id);
	else return root;
}

void deleteAll(struct Node *root){
	if(root == NULL){
		return;
	}
	deleteAll(root->left);
	deleteAll(root->right);
	root = deleteNode(root,root->id);
	
	return;
}

int main(){
	
	struct Node *root = NULL;
	char id[10],name[30], street[50], flavour[20],sell[10],yesno[10];
	int menu,diameter,flag,count=0,num,print,res;
	
	do{
		system("cls");
		printf(" Lovaloha Bakery\n");
		printf("=======================\n");
		printf("1. Insert order\n");
		printf("2. View all order\n");
		printf("3. Delete order\n");
		printf("4. Clear all orders\n");
		printf("5. Exit\n");
		printf(">> ");
		scanf("%d", &menu);getchar();
		
		if(menu == 1){
			
			system("cls");
			do{
				printf("Input customer name [between 5-20 characters]: ");
				scanf("%s", name); getchar();
				
				if(strlen(name)<5 || strlen(name)>20){
					printf("Customer name length must be between 5-20 characters!\n");
				}
				
			}while(strlen(name)<5 || strlen(name)>20);
			
			do{
				flag = 0;
				printf("Input address [ends with 'Street']: ");
				scanf("%[^\n]", street); getchar();
				
				if(street[strlen(street)-1] != 't' || street[strlen(street)-2] != 'e'|| street[strlen(street)-3] != 'e'||
				street[strlen(street)-4] != 'r' || street[strlen(street)-5] != 't' || street[strlen(street)-6] != 'S'){
					printf("Address must end with 'Street'!\n");
					flag = 1;
				}
				
			}while(flag == 1);
			
			do{
				flag = 0;
				printf("Input cake flavour [Vanilla | Chocolate]: ");
				scanf("%s", flavour); getchar();
				
				if(strcmp(flavour,"Vanilla")!=0 && strcmp(flavour,"Chocolate")!=0){
					printf("Flavour must be either Vanilla or Chocolate!\n");
					flag = 1;
				}
				
			}while(flag == 1);
			
			do{
				flag = 0;
				printf("Input cake diameter [16 | 18 | 21]: ");
				scanf("%d", &diameter); getchar();
				
				if(diameter != 16 && diameter != 18 && diameter != 21){
					printf("Diameter must be either 16 / 18 / 21!\n");
					flag = 1;
				}
				
			}while(flag == 1);
			
			srand(time(0));
			num = rand()%100;
			res = (num+diameter)%100;
//			printf("%d\n", num);
			sprintf(id,"%c%c%c%02d", toupper(name[0]), toupper(name[1]), toupper(name[2]),res);
//			printf("id = %s\n", id);
			count++;
			root = insert(root, createNewNode(id,name,street,flavour,diameter));
			printf("successfully add data!"); getchar();			
		}
		else if(menu == 2){
			system("cls");
			if(count == 0){
				printf("no cake order\n");
			}else{
				do{
					printf("+================+\n");
					printf("|   View Menus   |\n");
					printf("+================+\n");
					printf("| 1. Pre-orde    |\n");
					printf("| 2. In-order    |\n");
					printf("| 3. Post-order  |\n");
					printf("+================+\n");
					printf(">> ");
					scanf("%d", &print);
				}while(print < 1 || print > 3);
					if(print == 1){
						
						printf("+====================================================================================+\n");
						printf("|  ID   |         Name         |       Address        |   Flavour       | Diameter   |\n");
						printf("+====================================================================================+\n");
						printPreOrder(root);
						
						printf("+====================================================================================+\n");
						getchar();
					}else if(print == 2){
						
						printf("+====================================================================================+\n");
						printf("|  ID   |         Name         |       Address        |   Flavour       | Diameter   |\n");
						printf("+====================================================================================+\n");
						
						printInOrder(root);
						
						printf("+====================================================================================+\n");
						getchar();
					}else if(print == 3){
						
						printf("+====================================================================================+\n");
						printf("|  ID   |         Name         |       Address        |   Flavour       | Diameter   |\n");
						printf("+====================================================================================+\n");
						
						printPostOrder(root);
						
						printf("+====================================================================================+\n");
						getchar();
					}
			}
			printf("Back to home");
			getchar();
		}else if(menu == 3){
			system("cls");
			flag = 0;
			if(count == 0){
				printf("no cake order\n");
			}else{
				printf("+====================================================================================+\n");
				printf("|  ID   |         Name         |       Address        |   Flavour       | Diameter   |\n");
				printf("+====================================================================================+\n");
				printInOrder(root);
				printf("+====================================================================================+\n");
				
				do{
					printf("Input Cake ID: ");
					scanf("%s", sell); getchar();	
					struct Node *searchNode = search(root, sell);
					if(searchNode == NULL){
						flag = 1;
					}else{
						flag = 2;
					}
					if(flag == 1){
						printf("id not found!\n");
					}else if(flag == 2){
						do{
							printf("are you sure? [Yes | No]: ");
							scanf("%s", yesno); getchar();	
						}while(strcmp(yesno,"Yes")!= 0 && strcmp(yesno,"No")!= 0);
						if(strcmp(yesno,"Yes")==0){
							root=deleteNode(root,sell);
							count--;
							printf("data successfully removed!\n");
						}	
					}
				}while(flag == 1);
			}
				printf("Back to home"); getchar();
		}else if(menu == 4){
			system("cls");
			if(count ==0){
				printf("no cake order\n");
			}else{
				deleteAll(root);
				printf("All data successfully removed!\n");
			}
			printf("Back to home"); getchar();
		}
		
		
	}while(menu != 5);
	
	return 0;
}
