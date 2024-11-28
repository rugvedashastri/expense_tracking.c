#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EXPENSES 1000
#define MAX_CATEGORY_LENGTH 20
#define MAX_DESC_LENGTH 50

// Struct to hold an expense
typedef struct {
    int day, month, year;
    double amount;
    char category[MAX_CATEGORY_LENGTH];
    char description[MAX_DESC_LENGTH];
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function declarations
void addExpense();
void viewExpenses();
void generateReport(int month, int year);
void annualReport(int year);
void budgetManagement(double monthlyBudget);

int main() {
    int choice, month, year;
    double monthlyBudget;

    printf("=== Expense Tracker ===\n");

    while (1) {
        printf("\n1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Generate Monthly Report\n");
        printf("4. Generate Annual Report\n");
        printf("5. Budget Management\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                printf("Enter month and year (MM YYYY): ");
                scanf("%d %d", &month, &year);
                generateReport(month, year);
                break;
            case 4:
                printf("Enter year (YYYY): ");
                scanf("%d", &year);
                annualReport(year);
                break;
            case 5:
                printf("Enter your monthly budget: ");
                scanf("%lf", &monthlyBudget);
                budgetManagement(monthlyBudget);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

// Function to add an expense
void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense storage full!\n");
        return;
    }

    Expense newExpense;
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &newExpense.day, &newExpense.month, &newExpense.year);
    printf("Enter amount: ");
    scanf("%lf", &newExpense.amount);
    printf("Enter category: ");
    scanf("%s", newExpense.category);
    printf("Enter description: ");
    scanf(" %[^\n]", newExpense.description);

    expenses[expenseCount++] = newExpense;
    printf("Expense added successfully.\n");
}

// Function to view all expenses
void viewExpenses() {
    if (expenseCount == 0) {
        printf("No expenses to display.\n");
        return;
    }

    printf("\n--- All Expenses ---\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("Date: %02d-%02d-%04d, Amount: %.2f, Category: %s, Description: %s\n",
               expenses[i].day, expenses[i].month, expenses[i].year,
               expenses[i].amount, expenses[i].category, expenses[i].description);
    }
}

// Function to generate monthly report
void generateReport(int month, int year) {
    double total = 0;
    int found = 0;

    printf("\n--- Monthly Report for %02d-%04d ---\n", month, year);
    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].month == month && expenses[i].year == year) {
            printf("Date: %02d, Amount: %.2f, Category: %s, Description: %s\n",
                   expenses[i].day, expenses[i].amount, expenses[i].category, expenses[i].description);
            total += expenses[i].amount;
            found = 1;
        }
    }

    if (found) {
        printf("Total Expenses: %.2f\n", total);
    } else {
        printf("No expenses recorded for this month.\n");
    }
}

// Function to generate annual report
void annualReport(int year) {
    double monthlyTotals[12] = {0};
    int found = 0;

    printf("\n--- Annual Report for %04d ---\n", year);
    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].year == year) {
            monthlyTotals[expenses[i].month - 1] += expenses[i].amount;
            found = 1;
        }
    }

    if (found) {
        for (int i = 0; i < 12; i++) {
            printf("Month %02d: Total Expenses: %.2f\n", i + 1, monthlyTotals[i]);
        }
    } else {
        printf("No expenses recorded for this year.\n");
    }
}

// Function for budget management
void budgetManagement(double monthlyBudget) {
    double monthlyTotals[12] = {0};

    for (int i = 0; i < expenseCount; i++) {
        monthlyTotals[expenses[i].month - 1] += expenses[i].amount;
    }

    printf("\n--- Budget Management ---\n");
    for (int i = 0; i < 12; i++) {
        printf("Month %02d: Total Expenses: %.2f | Budget: %.2f | Status: %s\n",
               i + 1, monthlyTotals[i], monthlyBudget,
               monthlyTotals[i] <= monthlyBudget ? "Within Budget" : "Over Budget");
    }
}
