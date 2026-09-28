#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Stack
{
    int top;
    char stk[MAX];
};

void push(struct Stack *s, char ch)
{
    s->stk[++s->top] = ch;
}

char pop(struct Stack *s)
{
    return s->stk[s->top--];
}

int main()
{
    struct Stack s;
    char infix[MAX], prefix[MAX];
    int i, j = 0;
    char ch;

    s.top = -1;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    // Reverse infix
    strrev(infix);

    // Convert reversed infix to postfix
    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if (isalnum(ch))
        {
            prefix[j++] = ch;
        }
        else if (ch == ')')
        {
            push(&s, ch);
        }
        else if (ch == '(')
        {
            while (s.top != -1 && s.stk[s.top] != ')')
                prefix[j++] = pop(&s);

            if (s.top != -1)
                pop(&s);
        }
        else
        {
            while (s.top != -1 &&
                   s.stk[s.top] != ')' &&
                   ((ch != '^' && 
                     ((ch == '+' || ch == '-') &&
                      (s.stk[s.top] == '*' || s.stk[s.top] == '/')))
                    ||
                    ((ch == '*' || ch == '/') &&
                     s.stk[s.top] == '^')))
            {
                prefix[j++] = pop(&s);
            }

            push(&s, ch);
        }
    }

    while (s.top != -1)
        prefix[j++] = pop(&s);

    prefix[j] = '\0';

    // Reverse postfix to get prefix
    strrev(prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}