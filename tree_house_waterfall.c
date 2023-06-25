#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 20
#define MAX_PRODUCTS 10

// Struct for keeping track of product information
typedef struct {
    char name[20];
    double price;
    int quantity;
} Product;

// Struct for keeping track of employee information
typedef struct {
    char name[20];
    Product products[MAX_PRODUCTS];
    int num_products;
} Employee;

Employee employees[MAX_EMPLOYEES];
int num_employees = 0;

// Function prototypes
void printEmployees();
void enrollEmployee();
void removeEmployee();
void printEmployeeProducts();
void addProduct();
void removeProduct();
void salesTraining();

// Main program loop
int main(void) {
    char choice;
    do {
        printf("---Sales Training Program---\n");
        printf("1. Print Employees\n");
        printf("2. Enroll Employee\n");
        printf("3. Remove Employee\n");
        printf("4. Print Employee Products\n");
        printf("5. Add Product\n");
        printf("6. Remove Product\n");
        printf("7. Run Sales Training Program\n");
        printf("Q. Quit\n");
        printf("Choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printEmployees();
                break;
            case '2':
                enrollEmployee();
                break;
            case '3':
                removeEmployee();
                break;
            case '4':
                printEmployeeProducts();
                break;
            case '5':
                addProduct();
                break;
            case '6':
                removeProduct();
                break;
            case '7':
                salesTraining();
                break;
            case 'q':
            case 'Q':
                printf("\nExiting program...\n");
                break;
            default:
                printf("\nInvalid choice!\n");
                break;
        }
    } while (choice != 'q' && choice != 'Q');

    return 0;
}

// Prints a list of all employees
void printEmployees() {
    printf("\nEmployees:\n");
    for (int i = 0; i < num_employees; i++) {
        printf("%d: %s\n", i + 1, employees[i].name);
    }
    printf("\n");
}

// Enrolls a new employee
void enrollEmployee() {
    if (num_employees == MAX_EMPLOYEES) {
        printf("\nMaximum number of employees reached!\n\n");
        return;
    }

    char name[20];
    printf("\nName: ");
    scanf("%s", name);

    // Check if employee already exists
    for (int i = 0; i < num_employees; i++) {
        if (strcmp(name, employees[i].name) == 0) {
            printf("\nEmployee already exists!\n\n");
            return;
        }
    }

    strcpy(employees[num_employees].name, name);
    employees[num_employees].num_products = 0;

    printf("\nEmployee enrolled!\n\n");
    num_employees++;
}

// Removes an existing employee
void removeEmployee() {
    int index;
    printf("\nEmployee index: ");
    scanf("%d", &index);
    index--; // Convert to 0-based index

    if (index >= num_employees || index < 0) {
        printf("\nInvalid employee index!\n\n");
        return;
    }

    // Shift employees after the removed one up
    for (int i = index; i < num_employees - 1; i++) {
        employees[i] = employees[i + 1];
    }
    num_employees--;

    printf("\nEmployee removed!\n\n");
}

// Prints products for a given employee
void printEmployeeProducts() {
    int index;
    printf("\nEmployee index: ");
    scanf("%d", &index);
    index--; // Convert to 0-based index

    if (index >= num_employees || index < 0) {
        printf("\nInvalid employee index!\n\n");
        return;
    }

    Employee e = employees[index];
    printf("\nProducts for %s:\n", e.name);
    for (int i = 0; i < e.num_products; i++) {
        Product p = e.products[i];
        printf("%d: %s (Price: %.2f, Quantity: %d)\n", i + 1, p.name, p.price,
               p.quantity);
    }
    printf("\n");
}

// Adds a product for a given employee
void addProduct() {
    int index;
    printf("\nEmployee index: ");
    scanf("%d", &index);
    index--; // Convert to 0-based index

    if (index >= num_employees || index < 0) {
        printf("\nInvalid employee index!\n\n");
        return;
    }

    Employee e = employees[index];
    if (e.num_products == MAX_PRODUCTS) {
        printf("\nMaximum number of products reached!\n\n");
        return;
    }

    printf("\nProduct name: ");
    scanf("%s", e.products[e.num_products].name);

    printf("Product price: ");
    scanf("%lf", &e.products[e.num_products].price);

    printf("Product quantity: ");
    scanf("%d", &e.products[e.num_products].quantity);

    printf("\nProduct added!\n\n");
    e.num_products++;
}

// Removes a product for a given employee
void removeProduct() {
    int index;
    printf("\nEmployee index: ");
    scanf("%d", &index);
    index--; // Convert to 0-based index

    if (index >= num_employees || index < 0) {
        printf("\nInvalid employee index!\n\n");
        return;
    }

    Employee e = employees[index];
    int productIndex;
    printf("\nProduct index: ");
    scanf("%d", &productIndex);
    productIndex--; // Convert to 0-based index

    if (productIndex >= e.num_products || productIndex < 0) {
        printf("\nInvalid product index!\n\n");
        return;
    }

    // Shift products after the removed one up
    for (int i = productIndex; i < e.num_products - 1; i++) {
        e.products[i] = e.products[i + 1];
    }
    e.num_products--;

    printf("\nProduct removed!\n\n");
}

// Runs the Sales Training Program
void salesTraining() {
    printf("\nRunning Sales Training Program...\n\n");
    printf("Product Training:\n");
    for (int i = 0; i < num_employees; i++) {
        Employee e = employees[i];
        printf("\n%s's products:\n", e.name);
        for (int j = 0; j < e.num_products; j++) {
            Product p = e.products[j];
            printf("%s: Price: %.2f, Quantity: %d\n", p.name, p.price,
                   p.quantity);
        }
    }
    printf("\n");
}