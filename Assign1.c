#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIGITS 310
typedef struct BigInt_tag
{
    int *array;
    int size;
    int sign;
} BigInt;
BigInt* addition(BigInt* ,BigInt* );
void input(BigInt *Numptr)
{
    char str[DIGITS];
    printf("Enter the number:\n");
    scanf("%s",str);
    int length=strlen(str);
    int ind=0;
    if(str[0]=='-')
    {
        Numptr->sign=-1;       //-1 indicates number is negative
        int j=1;
        while(str[j]=='0')
        {
            j++;
        }
        Numptr->array=(int *)malloc(sizeof(int)*(length-j));
        for(int i=length-1;i>=j;i--)
        {
               Numptr->array[ind]=str[i]-'0';
               ind++; 
        }
    }
    else
    {
        Numptr->sign=1;       //1 indicates number is positive
        int j=0;
        while(str[j]=='0')
        {
            j++;
        }
        Numptr->array=(int *)malloc(sizeof(int)*(length-j));
        for(int i=length-1;i>=0;i--)
        {
               Numptr->array[ind]=str[i]-'0';
               ind++; 
        }
    }
    Numptr->size=ind;
}
void printBigInt(BigInt *Numptr)
{
    int i=Numptr->size-1;
    if(Numptr->sign==-1)
    {
        printf("-");
    }
    while(Numptr->array[i]==0)
    {
        Numptr->size--;
        i--;
    }
    for(int i=(Numptr->size)-1;i>=0;i--)
    {
        printf("%d",Numptr->array[i]);
    }
    printf("\n");
}
int Compare_numbers(BigInt *Num1, BigInt *Num2) {
    //printf("Check Compare\n");
    if (Num1->sign != Num2->sign) {
        // If signs are different, return based on signs
        if(Num1->sign==1)
        {
            return 1;
        }
        else return -1;
    }

    if (Num1->size != Num2->size) {
        // If sizes are different, return based on sizes
        if(Num1->size > Num2->size)
        {
            return 1;
        }
        else return -1;
    }

    // Compare array elements from most significant digit to least significant digit
    if(Num1->sign==-1 && Num2->sign==-1)
    {
    for (int i = Num1->size - 1; i >= 0; i--) {
        if (Num1->array[i] != Num2->array[i]) {
            if(Num1->array[i] > Num2->array[i])
            {
                return -1;
            }
            else 
            {
                return 1;
            }
        }
    }
    }
    else
    {
    for (int i = Num1->size - 1; i >= 0; i--) {
        if (Num1->array[i] != Num2->array[i]) {
            if(Num1->array[i] > Num2->array[i])
            {
                return 1;
            }
            else 
            {
                return -1;
            }
        }
    }
    }

    // Numbers are equal
    return 0;
}
BigInt* subtract(BigInt *Num1, BigInt *Num2) {
    //printf("Checksub\n");
    BigInt *result=(BigInt *)malloc(sizeof(BigInt));
    int cmp = Compare_numbers(Num1,Num2);

    if (cmp == 0) {
        // Numbers are equal, return zero
        result->array=(int *)malloc(sizeof(int));
        result->size = 1;
        result->array[0] = 0;
        result->sign = 1;
        return result;
    }

    if (Num1->sign != Num2->sign) {
        // Signs are different, perform addition with proper sign
        if (Num1->sign == -1) {
            Num2->sign = -1;
            result = addition(Num1, Num2);
        } else {
            Num2->sign = 1;
            result = addition(Num1, Num2);
            //result.sign = -1;
        }
        return result;
    }
    result->array=(int *)malloc(sizeof(int)*(Num1->size));
    // Signs are the same, perform subtraction
    if (cmp < 0) {
        // Swap Num1 and Num2 if Num1 < Num2
        if(Num1->sign==1 && Num2->sign==1){
        BigInt *temp = Num1;
        Num1 = Num2;
        Num2 = temp;
        }
        result->sign = -1;
        //printf("Check\n");
    } else {
        result->sign = 1;
        if(Num1->sign==-1 && Num2->sign==-1){
        BigInt *temp = Num1;
        Num1 = Num2;
        Num2 = temp;
        }
    }

    int i;
    for (i = 0; i < Num2->size; i++) {
        int diff = Num1->array[i] -Num2->array[i];
        if (diff < 0) {
            diff += 10;
            Num1->array[i+1]--;
        } 
        result->array[i] = diff;
    }
    while(i<Num1->size)
    {
        if(Num1->array[i]<0)
        {
            Num1->array[i]+=10;
            Num1->array[i+1]--;
        }
        result->array[i]=Num1->array[i];
        i++;
    }
    result->size = Num1->size;
    return result;
}
BigInt *addition(BigInt *Num1, BigInt *Num2) {
    //printf("checkadd\n");
    BigInt *result=(BigInt *)malloc(sizeof(BigInt));
    // Handle signs
    if (Num1->sign == -1 && Num2->sign == -1) {
        result->sign = -1;
    } else if (Num1->sign == 1 && Num2->sign == -1) {
        Num2->sign = 1;
        return subtract(Num1, Num2);
    } else if (Num1->sign == -1 && Num2->sign == 1) {
        Num1->sign = 1;
        return subtract(Num2, Num1);
    } else {
        result->sign = 1;
    }
    int i,sum,carry=0;
    int n1=Num1->size;
    int n2=Num2->size;
    if(n1>n2)
    {
        result->array=(int *)malloc(sizeof(int)*(n1+1));
    }
    else
    {
        result->array=(int *)malloc(sizeof(int)*(n2+1));
    }
    for(i=0;i<Num1->size && i<Num2->size;i++)
    {
        sum=Num1->array[i]+Num2->array[i]+carry;
        carry=sum/10;
        result->array[i]=sum%10;
    }
    while(i<Num1->size)
    {
        sum=Num1->array[i]+carry;
        carry=sum/10;
        result->array[i]=sum%10;
        i++;
    }
    while(i<Num2->size)
    {
        sum=Num2->array[i]+carry;
        carry=sum/10;
        result->array[i]=sum%10;
        i++;
    }
    if(carry>0)
    {
        result->array[i]=carry;
        i++;
    }
    result->size=i;
    return result;
}

BigInt *multiply(BigInt *Num1, BigInt *Num2) {
    BigInt *result=(BigInt *)malloc(sizeof(BigInt));
    int sum,i,j,carry=0;
    int n1=Num1->size;
    int n2=Num2->size;
    result->array=(int *)malloc(sizeof(int)*(n1+n2+1));
    //Initialize result array
    for(i=0;i<n1+n2+1;i++)
    {
        result->array[i]=0;
    }
    for(int i=0;i<Num1->size;i++)
    {
        for(j=0;j<Num2->size;j++)
        {
            result->array[i+j]+=Num1->array[i]*Num2->array[j];
            result->array[i+j+1]+=result->array[i+j]/10;
            result->array[i+j]%=10;
        }
    }
    // Find the actual size of the result
    int size = n1+n2+1;
    while (size > 0 && result->array[size - 1] == 0)
        size--;

    result->size = size;
    // Determine the sign of the result
    result->sign = Num1->sign * Num2->sign;

    return result;
    
}
int main()
{
    BigInt a,b;
    BigInt *ans;
    int choice;
    printf("Enter the choice\n1.Addition of bigInt Numbers\n2.Subtaction of BigInt numbers\n3.Multiplication of BigInt Numbers\n");
    scanf("%d",&choice);
    switch (choice)
        {
        case 1:
            input(&a);
            // printBigInt(a);
            input(&b);
            // printBigInt(b);
            printf("\naddition of two big integers is : ");
            ans=addition(&a,&b);
            printBigInt(ans);
            free(ans);
            break;
        case 2:
            input(&a);
            // printBigInt(a);
            input(&b);
            // printBigInt(b);
            printf("\nsubtraction of two big integers is : ");
            ans=subtract(&a,&b);
            printBigInt(ans);
            free(ans);
            break;
        case 3:
            input(&a);
            // printBigInt(a);
            input(&b);
            // printBigInt(b);
            printf("\nmultiplication of two big integers is : ");
            ans=multiply(&a,&b);
            printBigInt(ans);
            free(ans);
            break;
        default:
        printf("Invalid choice\n");
        break;
    return 0;
    }
}