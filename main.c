#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent an order
struct Order {
    int orderNumber;
    char customerName[100];
    char itemsOrdered[100];
    int isCompleted;
    struct Order* next;
};

struct Order* front = NULL;
struct Order* rear = NULL;
int orderCount = 1;

// Function to add an order to the queue
void placeOrder(char customerName[], char itemsOrdered[]) {
    struct Order* newOrder = (struct Order*)malloc(sizeof(struct Order));
    newOrder->orderNumber = orderCount++;
    strcpy(newOrder->customerName, customerName);
    strcpy(newOrder->itemsOrdered, itemsOrdered);
    newOrder->isCompleted = 0;
    newOrder->next = NULL;

    if (rear == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf("Order #%d placed for %s\n", newOrder->orderNumber, newOrder->customerName);
}

// Function to mark an order as completed
void completeOrder(int orderNumber) {
    struct Order* current = front;
    while (current != NULL) {
        if (current->orderNumber == orderNumber) {
            current->isCompleted = 1;
            printf("Order #%d completed for %s\n", current->orderNumber, current->customerName);
            return;
        }
        current = current->next;
    }

    printf("Order #%d not found.\n", orderNumber);
}

// Function to display orders in the kitchen queue
void displayOrders() {
    if (front == NULL) {
        printf("No orders in the queue.\n");
        return;
    }

    printf("Kitchen Queue:\n");
    struct Order* current = front;
    while (current != NULL) {
        if (current->isCompleted == 0) {
            printf("Order #%d for %s: %s\n", current->orderNumber, current->customerName, current->itemsOrdered);
        }
        current = current->next;
    }
}

int main() {
    int choice;
    char customerName[100];
    char itemsOrdered[100];

    while (1) {
        printf("\nRestaurant Order Management System\n");
        printf("1. Place Order\n");
        printf("2. Complete Order\n");
        printf("3. Display Kitchen Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                scanf(" %[^\n]", customerName);
                printf("Enter items ordered: ");
                scanf(" %[^\n]", itemsOrdered);
                placeOrder(customerName, itemsOrdered);
                break;
            case 2:
                printf("Enter order number to mark as completed: ");
                int orderNumber;
                scanf("%d", &orderNumber);
                completeOrder(orderNumber);
                break;
            case 3:
                displayOrders();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}