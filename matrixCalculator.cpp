#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 10

// Get matrix input with clear row labels
int getMatrix(int rows, int cols, int **matrix){
    printf("Enter the matrix elements (enter all %d elements of each row on same line):\n", cols);
    for(int i = 0; i < rows; i++){
        printf("Row %d: ", i + 1);
        for(int j = 0; j < cols; j++){
            if(scanf("%d", &matrix[i][j]) != 1){
                printf("\nINVALID INPUT! Enter integers only\n");
                while(getchar() != '\n'); // Clear buffer
                return 0;
            }
        }
    }
    return 1;
}

// Display matrix
void display(int rows, int cols, int **matrix){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Show menu
void showMenu(){
    printf("\n=======================================\n");
    printf("        MATRIX CALCULATOR MENU\n");
    printf("=======================================\n");
    printf("  1. Addition\n");
    printf("  2. Subtraction\n");
    printf("  3. Multiplication\n");
    printf("  4. Transpose\n");
    printf("  5. Determinant\n");
    printf("  6. Exit\n");
    printf("=======================================\n");
}

// Addition
void add(int rows1, int cols1, int rows2, int cols2, int **m1, int **m2){
    if(rows1 != rows2 || cols1 != cols2){
        printf("\nERROR! Matrices must have same dimensions\n");
        return;
    }
    printf("\n------- ADDITION RESULT -------\n");
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols1; j++){
            printf("%4d ", m1[i][j] + m2[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------\n");
}

// Subtraction
void subtract(int rows1, int cols1, int rows2, int cols2, int **m1, int **m2){
    if(rows1 != rows2 || cols1 != cols2){
        printf("\nERROR! Matrices must have same dimensions\n");
        return;
    }
    printf("\n------- SUBTRACTION RESULT -------\n");
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols1; j++){
            printf("%4d ", m1[i][j] - m2[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
}

// Multiplication
void multiply(int rows1, int cols1, int rows2, int cols2, int **m1, int **m2){
    if(cols1 != rows2){
        printf("\nERROR! Columns of Matrix1 must equal Rows of Matrix2\n");
        return;
    }
    
    // Allocate result matrix
    int **result = (int**)malloc(rows1 * sizeof(int*));
    for(int i = 0; i < rows1; i++){
        result[i] = (int*)malloc(cols2 * sizeof(int));
    }
    
    // Multiply
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            result[i][j] = 0;
            for(int k = 0; k < cols1; k++){
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    
    printf("\n------- MULTIPLICATION RESULT -------\n");
    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            printf("%4d ", result[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    
    // Free result
    for(int i = 0; i < rows1; i++){
        free(result[i]);
    }
    free(result);
}

// Transpose
void transpose(int rows1, int cols1, int rows2, int cols2, int **m1, int **m2){
    // Transpose matrix 1
    int **t1 = (int**)malloc(cols1 * sizeof(int*));
    for(int i = 0; i < cols1; i++){
        t1[i] = (int*)malloc(rows1 * sizeof(int));
    }
    
    printf("\n------- TRANSPOSE MATRIX 1 -------\n");
    for(int i = 0; i < cols1; i++){
        for(int j = 0; j < rows1; j++){
            t1[i][j] = m1[j][i];
            printf("%4d ", t1[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
    
    // Transpose matrix 2
    int **t2 = (int**)malloc(cols2 * sizeof(int*));
    for(int i = 0; i < cols2; i++){
        t2[i] = (int*)malloc(rows2 * sizeof(int));
    }
    
    printf("\n------- TRANSPOSE MATRIX 2 -------\n");
    for(int i = 0; i < cols2; i++){
        for(int j = 0; j < rows2; j++){
            t2[i][j] = m2[j][i];
            printf("%4d ", t2[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------\n");
    
    // Free memory
    for(int i = 0; i < cols1; i++) free(t1[i]);
    free(t1);
    for(int i = 0; i < cols2; i++) free(t2[i]);
    free(t2);
}

// Determinant (Recursive)
int determinant(int n, int **matrix){
    // Base case: 1x1
    if(n == 1) return matrix[0][0];
    
    // Base case: 2x2
    if(n == 2)
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    
    // Recursive case
    int result = 0;
    for(int col = 0; col < n; col++){
        // Create minor matrix
        int **minor = (int**)malloc((n-1) * sizeof(int*));
        for(int i = 0; i < n-1; i++){
            minor[i] = (int*)malloc((n-1) * sizeof(int));
        }
        
        // Fill minor matrix (skip first row and current column)
        for(int i = 1; i < n; i++){
            int minorCol = 0;
            for(int j = 0; j < n; j++){
                if(j == col) continue;
                minor[i-1][minorCol++] = matrix[i][j];
            }
        }
        
        // Calculate using cofactor expansion
        int sign = (col % 2 == 0) ? 1 : -1;
        result += sign * matrix[0][col] * determinant(n-1, minor);
        
        // Free minor
        for(int i = 0; i < n-1; i++) free(minor[i]);
        free(minor);
    }
    return result;
}

int main(){
    int rows1, cols1, rows2, cols2;
    
    printf("\n=======================================\n");
    printf("    MATRIX CALCULATOR PROGRAM\n");
    printf("=======================================\n\n");
    
    // Get Matrix 1
    printf("--- MATRIX 1 INPUT ---\n");
    printf("Enter rows and columns (space separated): ");
    scanf("%d %d", &rows1, &cols1);
    
    if(rows1 <= 0 || cols1 <= 0 || rows1 > MAX_SIZE || cols1 > MAX_SIZE){
        printf("ERROR! Dimensions must be 1-%d\n", MAX_SIZE);
        return 1;
    }
    
    int **matrix1 = (int**)malloc(rows1 * sizeof(int*));
    for(int i = 0; i < rows1; i++){
        matrix1[i] = (int*)malloc(cols1 * sizeof(int));
    }
    
    if(!getMatrix(rows1, cols1, matrix1)){
        return 1;
    }
    
    // Get Matrix 2
    printf("\n--- MATRIX 2 INPUT ---\n");
    printf("Enter rows and columns (space separated): ");
    scanf("%d %d", &rows2, &cols2);
    
    if(rows2 <= 0 || cols2 <= 0 || rows2 > MAX_SIZE || cols2 > MAX_SIZE){
        printf("ERROR! Dimensions must be 1-%d\n", MAX_SIZE);
        return 1;
    }
    
    int **matrix2 = (int**)malloc(rows2 * sizeof(int*));
    for(int i = 0; i < rows2; i++){
        matrix2[i] = (int*)malloc(cols2 * sizeof(int));
    }
    
    if(!getMatrix(rows2, cols2, matrix2)){
        return 1;
    }
    
    // Display matrices
    printf("\nClearing screen in 2 seconds...");
    Sleep(2000);
    system("cls");
    
    printf("\n======= YOUR MATRICES =======\n");
    printf("\nMatrix 1 [%dx%d]:\n", rows1, cols1);
    display(rows1, cols1, matrix1);
    printf("\nMatrix 2 [%dx%d]:\n", rows2, cols2);
    display(rows2, cols2, matrix2);
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
    system("cls");
    
    // Menu loop
    int choice;
    while(1){
        showMenu();
        printf("\nYour choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                add(rows1, cols1, rows2, cols2, matrix1, matrix2);
                break;
            case 2:
                subtract(rows1, cols1, rows2, cols2, matrix1, matrix2);
                break;
            case 3:
                multiply(rows1, cols1, rows2, cols2, matrix1, matrix2);
                break;
            case 4:
                transpose(rows1, cols1, rows2, cols2, matrix1, matrix2);
                break;
            case 5:
                printf("\n------- DETERMINANT -------\n");
                if(rows1 == cols1){
                    printf("Matrix 1: %d\n", determinant(rows1, matrix1));
                } else {
                    printf("Matrix 1: Not square\n");
                }
                if(rows2 == cols2){
                    printf("Matrix 2: %d\n", determinant(rows2, matrix2));
                } else {
                    printf("Matrix 2: Not square\n");
                }
                printf("---------------------------\n");
                break;
            case 6:
                printf("\n=======================================\n");
                printf("  Thank you! Exiting program...\n");
                printf("=======================================\n\n");
                // Free memory
                for(int i = 0; i < rows1; i++) free(matrix1[i]);
                free(matrix1);
                for(int i = 0; i < rows2; i++) free(matrix2[i]);
                free(matrix2);
                return 0;
            default:
                printf("\nInvalid choice! Choose 1-6\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        system("cls");
    }
    
    return 0;
}
