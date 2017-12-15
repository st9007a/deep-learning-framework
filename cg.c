#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cg.h"

static inline float box_muller_sampling()
{
    int mean = 0;
    int std = 1;

    return sqrt(-2 * log(rand() / (float)RAND_MAX)) * cos(2 * M_PI * rand() / (float)RAND_MAX) * std + mean;
}

void node_info(Node *n)
{
    printf("---------------------\n");
    printf("Type: ");
    switch (n->type) {
        case CONST:
            printf("Constant\n");
            break;
        case VAR:
            printf("Variable\n");
            break;
        case PLACEHOLDER:
            printf("Placeholder\n");
            break;
        default:
            printf("Unknown type\n");
    }

    printf("Name: %s\n", n->name);
    printf("Value: %f\n", n->val);

    printf("Expression Type: ");
    if (n->expr.type == NONE) {
        printf("None\n");
    }
    else {
        switch (n->expr.type) {
            case ADD:
                printf("Add\n");
                break;
            case SUB:
                printf("Sub\n");
                break;
            case MUL:
                printf("Mul\n");
                break;
            case DIV:
                printf("Div\n");
                break;
            default:
                printf("Unknown\n");
        }

        printf("Arg 1: %s\n", n->expr.args[0]->name);
        printf("Arg 2: %s\n", n->expr.args[1]->name);
    }

    if (n->ref != NULL) {
        printf("Ref: %s\n", n->ref->name);
    }
    printf("---------------------\n");
}

Node *create_variable (char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);
    n->type = VAR;
    n->val = box_muller_sampling();
    n->expr.type = NONE;
    n->ref = NULL;

    return n;
}

Node *create_constant(char *name, float val)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);
    n->type = CONST;
    n->val = val;
    n->expr.type = NONE;
    n->ref = NULL;

    return n;
}

Node *create_placeholder(char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);
    n->type = PLACEHOLDER;
    n->expr.type = NONE;
    n->ref = NULL;

    return n;
}

Node *node_add(Node *n1, Node *n2, char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);

    if (n1->type == CONST && n2->type == CONST) {
        n->type = CONST;
        n->val = n1->val + n2->val;
    } else {
        n->type = PLACEHOLDER;
    }

    n->expr.type = ADD;
    n->expr.args[0] = n1;
    n->expr.args[1] = n2;
    n->ref = NULL;

    n1->ref = n;
    n2->ref = n;

    return n;
}

Node *node_sub(Node *n1, Node *n2, char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);

    if (n1->type == CONST && n2->type == CONST) {
        n->type = CONST;
        n->val = n1->val - n2->val;
    } else {
        n->type = PLACEHOLDER;
    }

    n->expr.type = SUB;
    n->expr.args[0] = n1;
    n->expr.args[1] = n2;
    n->ref = NULL;

    n1->ref = n;
    n2->ref = n;

    return n;
}

Node *node_mul(Node *n1, Node *n2, char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);

    if (n1->type == CONST && n2->type == CONST) {
        n->type = CONST;
        n->val = n1->val * n2->val;
    } else {
        n->type = PLACEHOLDER;
    }

    n->expr.type = MUL;
    n->expr.args[0] = n1;
    n->expr.args[1] = n2;
    n->ref = NULL;

    n1->ref = n;
    n2->ref = n;

    return n;
}

Node *node_div(Node *n1, Node *n2, char *name)
{
    Node *n = malloc(sizeof(Node));

    strcpy(n->name, name);

    if (n1->type == CONST && n2->type == CONST) {
        n->type = CONST;
        n->val = n1->val / n2->val;
    } else {
        n->type = PLACEHOLDER;
    }

    n->expr.type = DIV;
    n->expr.args[0] = n1;
    n->expr.args[1] = n2;
    n->ref = NULL;

    n1->ref = n;
    n2->ref = n;

    return n;
}

void optimize(Node *root)
{

}
