#ifndef THREE_ADDRESS_CODE_H
#define THREE_ADDRESS_CODE_H
#include <stdio.h>

int label_count = 0;
int temp_count = 0;

char* new_label()
{
    char label[50];
    sprintf(label, "L%d", label_count++);
    return label;
}

char* new_temp()
{
    char temp[50];
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

void generate_expression(char* result, char* left_operand, char* operator, char* right_operand)
{
    char* temp = new_temp();

    printf("%s = %s %s %s\n", temp, left_operand, operator, right_operand);
    printf("%s = %s\n", result, temp);
}

void generate_if_else(
    char* condition_left, char* condition_operator, char* condition_right, char* result_1, char* left_operand_1,
    char* operator_1, char* right_operand_1, char* result_2, char* left_operand_2, char* operator_2,
    char* right_operand_2
)
{
    char* label_1 = new_label();
    char* label_2 = new_label();
    char* label_3 = new_label();

    printf("IF %s %s %s GOTO %s\n", condition_left, condition_operator, condition_right, label_1);
    printf("GOTO %s\n", label_2);

    printf("%s:\n", label_1);
    generate_expression(result_1, left_operand_1, operator_1, right_operand_1);
    printf("GOTO: %s\n", label_3);

    printf("%s:\n", label_2);
    generate_expression(result_2, left_operand_2, operator_2, right_operand_2);
    printf("GOTO: %s\n", label_3);
}

void generateWhile(
    char* condition_left, char* conditional_operator, char* condition_right, char* result, char* left_operand,
    char* operator, char* right_operand
)
{
    char* label_1 = new_label();
    char* label_2 = new_label();
    char* label_3 = new_label();

    printf("%s:\n", label_1);
    printf("IF %s %s %s GOTO %s\n", condition_left, conditional_operator, condition_right, label_2);
    printf("GOTO %s\n", label_3);

    printf("%s:\n", label_2);
    generate_expression(result, left_operand, operator, right_operand);
    printf("GOTO %s\n", label_1);

    printf("%s:\n", label_3);
}

#endif
