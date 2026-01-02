#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1024

typedef struct {
    char a[MAX];
    int top;
} CharStack;

void cs_init(CharStack *s){ s->top = -1; }
int cs_empty(CharStack *s){ return s->top < 0; }
char cs_peek(CharStack *s){ return s->a[s->top]; }
void cs_push(CharStack *s, char x){ s->a[++s->top] = x; }
char cs_pop(CharStack *s){ return s->a[s->top--]; }

int prec(char op) {
    switch(op){
        case '^': return 3;
        case '*': case '/': return 2;
        case '+': case '-': return 1;
        default: return 0;
    }
}
int right_assoc(char op){ return op == '^'; }

int is_op(char c){
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}

void infix_to_postfix(const char *infix, char *out) {
    CharStack st; cs_init(&st);
    out[0] = '\0';
    size_t n = strlen(infix);

    for (size_t i = 0; i < n; ) {
        if (isspace((unsigned char)infix[i])) { i++; continue; }

        // number (multi-digit)
        if (isdigit((unsigned char)infix[i])) {
            char buf[64]; int b = 0;
            while (i < n && isdigit((unsigned char)infix[i])) {
                buf[b++] = infix[i++];
                if (b >= 63) break;
            }
            buf[b] = '\0';
            strcat(out, buf);
            strcat(out, " ");
            continue;
        }

        char c = infix[i];

        if (c == '(') {
            cs_push(&st, c);
            i++;
        } else if (c == ')') {
            while (!cs_empty(&st) && cs_peek(&st) != '(') {
                char op = cs_pop(&st);
                strncat(out, &op, 1);
                strcat(out, " ");
            }
            if (!cs_empty(&st) && cs_peek(&st) == '(') cs_pop(&st);
            i++;
        } else if (is_op(c)) {
            while (!cs_empty(&st) && is_op(cs_peek(&st))) {
                char top = cs_peek(&st);
                int p1 = prec(c), p2 = prec(top);
                if ((right_assoc(c) && p1 < p2) || (!right_assoc(c) && p1 <= p2)) {
                    char op = cs_pop(&st);
                    strncat(out, &op, 1);
                    strcat(out, " ");
                } else break;
            }
            cs_push(&st, c);
            i++;
        } else {
            i++;
        }
    }

    while (!cs_empty(&st)) {
        char op = cs_pop(&st);
        if (op == '(') continue;
        strncat(out, &op, 1);
        strcat(out, " ");
    }
}

int main(void) {
    const char *infix = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
    char postfix[MAX];
    infix_to_postfix(infix, postfix);
    printf("Infix : %s\n", infix);
    printf("Postfix: %s\n", postfix);
    return 0;
}
