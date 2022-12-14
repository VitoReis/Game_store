#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Client{
    int id;
    char name[50];
    struct Client *next;
}clients;
int clientCount = 0;


typedef struct Product{
    int id;
    float price;
    char product[50];
    struct Product *next;
}products;
int productCount = 0;


typedef struct Purchase{
    int id;
    float total;
    char client[50];
    char productName[1000];
    struct Purchase *next;
}purchases;
int purchaseCount = 0;


void registerClient(clients *newClient){
    printf("\n\nWhat is your client name? ");
    fflush(stdin);
    scanf("%50[^\n]", &newClient->name);                      // Reads input until it finds \n or reaches 50 characters
    newClient->id = clientCount;
    clientCount++;
    printf("\n");
}


void showClients(clients *clientsPointer){
    for(int i = 0; i < clientCount; i++){
        printf("\n************************\n");
        printf("Name: %s\nId: %d", clientsPointer->name, clientsPointer->id);
        printf("\n************************\n");
        clientsPointer = clientsPointer->next;
    }
}


void registerProduct(products *newProducts){
    printf("\n\nWhat is your product name? ");
    fflush(stdin);
    scanf("%50[^\n]", newProducts->product);
    printf("\n\nWhat is the price of your product? ");
    scanf("%f", &newProducts->price);
    newProducts->id = productCount;
    productCount++;
    printf("\n");
}


void showProducts(products *productsPointer){
    for(int i = 0; i < productCount; i++){
        printf("\n************************\n");
        printf("Product: %s\nPrice: %.2f\nId: %d", productsPointer->product, productsPointer->price, productsPointer->id);
        printf("\n************************\n");
        productsPointer = productsPointer->next;
    }
}


int registerPurchase(clients *clientsPointer, products *productsPointer, purchases *newPurchases){
    int id, found = 0, choice = 1;
    float totalPrice = 0;
    char product[50], clientName[50], purchasedProducts[1000] = "";
    printf("\n\nWhat is your client id? ");                 // Check for client
    scanf("%i", &id);

    for(int i = 0; i < clientCount; i++){
        if(clientsPointer->id == id){
            strcpy(clientName, clientsPointer->name);
            found = 1;
            break;
        }
        clientsPointer = clientsPointer->next;
    }
    if(!found){
        printf("\nERRO: Client not found\n");
        return 0;
    }

    do{
        found = 0;
        printf("\n\nWhat is your product id? ");                 // Check for product
        scanf("%i", &id);
        for(int i = 0; i < productCount; i++){
            if(productsPointer->id == id){
                if(strlen(purchasedProducts) > 0){
                    strcat(purchasedProducts, ", ");            // Add ', ' after the last product name
                }
                strcat(purchasedProducts, productsPointer->product);
                totalPrice += productsPointer->price;
                found = 1;
                break;
            }
            productsPointer = productsPointer->next;
        }
        if(!found){
            printf("\nERRO: Product not found\n");
            return 0;
        }
        printf("Do you want to add one more product?\n1 - Yes\n2 - No\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
            break;
            case 2:
            break;
            default:
                printf("\nERROR: Option not available, returning to main menu...\n");
                return 0;
            break;
        }
    }while(choice != 2);
    
    // Saves data at the end to avoid errors
    strcpy(newPurchases->client, clientName);
    strcpy(newPurchases->productName, purchasedProducts);
    newPurchases->total = totalPrice;
    newPurchases->id = purchaseCount;
    purchaseCount++;
    printf("\n");
}


void showPurchases(purchases *purchasesPointer){
    for(int i = 0; i < purchaseCount; i++){
        printf("\n************************\n");
        printf("Client: %s\nProducts: %s\nPrice: %.2f\nId: %d", purchasesPointer->client, purchasesPointer->productName, purchasesPointer->total, purchasesPointer->id);
        printf("\n************************\n");
        purchasesPointer = purchasesPointer->next;
    }
}


void main(){
    int choice = 0;

    clients *headClients;
    headClients = (clients*)malloc(sizeof(clients));
    clients *clientsPointer;

    products *headProducts;
    headProducts = (products*)malloc(sizeof(products));
    products *productsPointer;

    purchases *headPurchases;
    headPurchases = (purchases*)malloc(sizeof(purchases));
    purchases *purchasesPointer;

    do{
        printf("\n************************\n\tMenu\n************************\n");
        printf("1 - Register client\n2 - Register product\n3 - Register purchase\n4 - Show all clients\n5 - Show all products\n6 - Show all purchases\n7 - Exit");
        printf("\n************************\n");
        scanf("%i", &choice);
        switch(choice){
            case 1:
                if(clientCount <= 0){                       // If it's the first client
                    registerClient(headClients);
                }else{
                    clientsPointer = headClients;
                    while(clientsPointer->next != NULL){       // Points to the next client until it finds the last client
                        clientsPointer = clientsPointer->next;
                    }
                    clientsPointer->next = (clients*)malloc(sizeof(clients));  // Reserves memory space for the next client
                    clientsPointer = clientsPointer->next;                        // Points to the new client
                    registerClient(clientsPointer);  
                } 
            break;
            case 2:
                if(productCount <= 0){
                    registerProduct(headProducts);
                }else{
                    productsPointer = headProducts;
                    while(productsPointer->next != NULL){
                        productsPointer = productsPointer->next;
                    }
                    productsPointer->next = (products*)malloc(sizeof(products));
                    productsPointer = productsPointer->next;
                    registerProduct(productsPointer);  
                }
            break;
            case 3:
                if(purchaseCount <= 0){
                    clientsPointer = headClients;
                    productsPointer = headProducts;
                    registerPurchase(clientsPointer, productsPointer, headPurchases);
                }else{
                    clientsPointer = headClients;
                    productsPointer = headProducts;
                    purchasesPointer = headPurchases;
                    while(productsPointer->next != NULL){
                        productsPointer = productsPointer->next;
                    }
                    purchasesPointer->next = (purchases*)malloc(sizeof(purchases));
                    purchasesPointer = purchasesPointer->next;
                    registerPurchase(clientsPointer, productsPointer, purchasesPointer);
                }
                
            break;
            case 4:
                clientsPointer = headClients;
                showClients(clientsPointer);
            break;
            case 5:
                productsPointer = headProducts;
                showProducts(productsPointer);
            break;
            case 6:
                purchasesPointer = headPurchases;
                showPurchases(purchasesPointer);
            break;
            case 7:
                choice = 7;
            break;
            default:
                printf("\nERROR: Option unavailable");
            break;
        }
    }while(choice != 7);
}