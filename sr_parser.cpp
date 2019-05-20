#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[3];
char act[15];
void check();
int main()
{
    printf("Grammar\n");
    printf("E -> E + T | T\n");
    printf("T -> T * F | F\n");
    printf("F -> (E) | id \n");
    printf("Enter the input expression:\n");
    scanf("%s", ip_sym);
    printf("Stack\t\t\tInput Dymbol\t\t\tAction\n");
    printf("$\t\t\t%s$\t\t\t--\n", ip_sym);
   
    len = strlen(ip_sym);

    for ( i = 0; i <= len - 1; i++)
    {
        if (ip_sym[ip_ptr] == 'i' && ip_sym[ip_ptr + 1] == 'd')
        {
            stack[st_ptr] = ip_sym[ip_ptr];
            temp[0] = ip_sym[ip_ptr];
            st_ptr++;
            ip_sym[ip_ptr] = ' ';
            ip_ptr++;
            stack[st_ptr] = ip_sym[ip_ptr];
            temp[1] = ip_sym[ip_ptr];
            stack[st_ptr + 1] = '\0';
            ip_sym[ip_ptr] = ' ';
            ip_ptr++;
            temp[2] = '\0';
        }
        else
        {
            stack[st_ptr] = ip_sym[ip_ptr];
            temp[0] = ip_sym[ip_ptr];
            stack[st_ptr + 1] = '\0';
            ip_sym[ip_ptr] = ' ';
            ip_ptr++;
            temp[1] = '\0';
        }
        printf("$%s\t\t\t%s$\t\t\tShift %s  lol \n", stack, ip_sym, temp);
        check();
        st_ptr++;
    }
    st_ptr++;
    check();
}

void disp(char const *temp){
    printf("$%s\t\t\t%s$\t\t\t%s\n", stack, ip_sym, temp);

}


void check()
{
    int flag = 0;
    while (1)
    {
        if (stack[st_ptr] == 'd' && stack[st_ptr - 1] == 'i')
        {
            stack[st_ptr - 1] = 'F';
            stack[st_ptr] = '\0';
            st_ptr--;
            flag = 1;
            disp("F->id");
        }

        if (stack[st_ptr] == ')' && stack[st_ptr - 1] == 'E' && stack[st_ptr - 2] == '(')
        {
            stack[st_ptr - 2] = 'F';
            stack[st_ptr - 1] = '\0';
            flag = 1;
            st_ptr = st_ptr - 2;
            disp("F->(E)");
        }

        if (stack[st_ptr] == 'F' && stack[st_ptr - 1] == '*' && stack[st_ptr - 2] == 'T')
        {
            stack[st_ptr - 1] = '\0';
            st_ptr = st_ptr - 2;
            flag = 1;
            disp("T->T*F");
        }
        if (stack[st_ptr] == 'F')
        {
            stack[st_ptr] = 'T';
            flag = 1;
            disp("T->F");
        }

        if (stack[st_ptr] == 'T' && stack[st_ptr - 1] == '+' && stack[st_ptr - 2] == 'E' && ip_sym[ip_ptr] != '*')
        {
            stack[st_ptr - 1] = '\0';
            st_ptr = st_ptr - 2;
            flag = 1;
            disp("E->E+T");
        }
        if ((stack[st_ptr] == 'T' && ip_sym[ip_ptr] == '+') || (stack[0] == 'T' && ip_sym[ip_ptr] == '\0') ||
                 (stack[st_ptr] == 'T' && ip_sym[ip_ptr] == ')'))
        {
            stack[st_ptr] = 'E';
            flag = 1;
            disp("E->T");
        }

        if (ip_sym[ip_ptr] != '\0' && flag != 1)
        {
            flag = 2;
        }

        if (!strcmp(stack, "E") && ip_sym[ip_ptr] == '\0')
        {
            disp("Accept");
            exit(0);
        }

        if (flag == 0)
        {
            disp("Reject");
            exit(0);
        }

        if (flag == 2)
        {
            return;
        }

        flag = 0;
    }
}

/*
Output:

Grammar
E -> E + T | T
T -> T * F | F
F -> (E) | id 
Enter the input expression:
id+id*id
Stack			Input Dymbol		Action
$			    id+id*id$			--
$id			      +id*id$			Shift id
$F			      +id*id$			F->id
$T			      +id*id$			T->F
$E			      +id*id$			E->T
$E+			       id*id$			Shift +
$E+id			     *id$			Shift id
$E+F			     *id$			F->id
$E+T			     *id$			T->F
$E+T*			      id$			Shift *
$E+T*id			        $			Shift id
$E+T*F			        $			F->id
$E+T			        $			T->T*F
$E			            $			E->E+T
$E			            $			Accept
*/
