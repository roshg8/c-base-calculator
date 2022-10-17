#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"

typedef char bin_str[20];

unsigned short get_binary_op (char *bin) {
    unsigned short val = 0;
    int times = 15;
    int i;
    for (i=0; i<16; i++){
      if (bin[i] == '1'){
        val = val + (1 << times);
      }
      times = times - 1;
    }
    return val;
}

void convert_to_binary (short acc, char *bin) {
  bin_str b="0000000000000000";
  int ds;
  unsigned short accum;
  int i, j = 0;
  ds = pow(2,15);      
  accum = acc;
  for (i = 0; i <= 15; i++){
    if (accum >= ds){
      b[i] = '1';
      accum -= ds;
      }
      ds = ds/2;
    }
    for (i = 1; i <= 20; i++){
      if (i % 5 == 0){
        bin[i - 1] = ' ';
        i++;
      }
      bin[i - 1]=b[j];        
      j++;
    }
}

short get_operand(char mode) { 
    short user;
    bin_str b;
    switch (mode) {
      case 'B': {
        printf("Enter binary value: ");
        scanf("%s", b);
        printf("%s\n", b);
        user=get_binary_op(b);
        break;
      }
      case 'O': {
        printf("Enter octal value: "); 
        scanf("%ho", &user); 
        printf("%ho\n", user);
        break;
      }
      case 'H': {
        printf("Enter hex value: ");
        scanf("%hx", &user); 
        printf("%hx\n", user);
        break; 
      }
      case 'D': {
        printf("Enter decimal value: "); 
        scanf("%hd", &user); 
        printf("%hd\n", user);
        break;
      }
    }
    return user;
}

void add (short *acc, char mode)
{
    short int addacc, curradd;
    addacc=*acc;
    curradd=get_operand(mode);
    *acc+=curradd;
    if (addacc>0 && curradd>0 && *acc<0){
        printf("Positive Overflow\n");
    }
    if (addacc<0 && curradd<0 && *acc>0){
        printf("Negative Overflow\n");
    }
}

void subtract (short *acc, char mode) {
    short subacc;
    short currsub;
    currsub=get_operand(mode);
    subacc = *acc;
    *acc-=currsub;
    if (subacc>0 && (-currsub)>0 && *acc<0){
        printf("Positive Overflow\n");
    }
    if (subacc<0 && (-currsub)<0 && *acc>0){
        printf("Negative Overflow\n");
    }
}

void print_acc(short acc, char mode) {   
    char* acc_mode[]={"Bin","Hex","Oct","Dec"};
    int val;
    bin_str o;
    convert_to_binary(acc, o);
    switch(mode)
    {
        case 'B': {
          val=0;
          break;
        }
        case 'H': {
          val=1;
          break;
        }
        case 'O': {
          val=2;
          break;
        }
        case 'D': {
          val=3;
          break;
        }
    }
    printf("\n****************************************\n");
    printf("* Accumulator:         Input Mode: %s *\n", acc_mode[val]);
    printf("*   Binary  :  %s    *\n", o);
    printf("*   Hex     :  %04hx                    *\n", acc);
    printf("*   Octal   :  %06ho                  *\n", acc);
    printf("*   Decimal :  %-6hd                  *\n", acc);
    printf("****************************************\n");
    
}

char print_menu(void) {
    char sofar[10];
    char curr;
    char options[]="BOHDCSQ&|^~<>+-N";
    printf("\nPlease select one of the following options:\n\n");
    printf("B  Binary Mode             &  AND with Accumulator           +  Add to Accumulator\n");
    printf("O  Octal Mode              |  OR  with Accumulator           -  Subtract from Accumulator\n");
    printf("H  Hexadecimal Mode        ^  XOR with Accumulator           N  Negate Accumulator\n");
    printf("D  Decimal Mode            ~  Complement Accumulator\n\n");
    printf("C  Clear Accumulator       <  Shift Accumulator Left\n");
    printf("S  Set Accumulator         >  Shift Accumulator Right\n\n");
    printf("Q  Quit\n\n");
    printf("Option: ");
    scanf("%s",sofar);
    printf("%s\n",sofar);
    curr=toupper(sofar[0]);
    if (strlen(sofar)>1 || !strchr(options, curr)){
        printf("\nInvalid option: %s\n", sofar);
        print_menu();
    }
    else {
        return curr;
    }
}

int main(void) {
  char mode='D';
  char selection='D';
  short acc=0, second_acc=0;
  int bit_shift;
  while (selection != 'Q') {
    print_acc(acc, mode);
    selection=print_menu();
    switch (selection) {
      case 'B': {
        mode='B';
        printf("Mode is Binary\n");
        break;
      }
      case 'O': {
        mode='O'; 
        printf("Mode is Octal\n");
        break;
      }
      case 'H': {
        mode='H'; 
        printf("Mode is Hexidecimal\n");
        break;
      }
      case 'D': {
        mode='D'; 
        printf("Mode is Decimal\n");
        break;
      }
      case 'C': {
        acc=0; 
        mode='D';
        break;
      }
      case 'S': {
        acc=get_operand(mode);
        break;
      }
      case '&': {
        second_acc=get_operand(mode);
        acc=second_acc&acc;
        break;
      }
      case '|': {
        second_acc=get_operand(mode);
        acc=second_acc|acc;
        break;
      }
      case '^': {
        second_acc=get_operand(mode);
        acc=second_acc^acc;
        break;
      }
      case '~': {
        acc=~acc;
        break;
      }
      case 'N': {
        acc=-acc;
        break;
      }
      case '<': {
          printf("Enter number of positions to left shift accumulator: ");
          scanf("%d", &bit_shift);
          printf("%d\n", bit_shift);
          acc=acc<<bit_shift;
          break;
      }
      case '>': {
        printf("Enter number of positions to right shift accumulator: ");
        scanf("%d", &bit_shift);
        printf("%d\n", bit_shift);
        acc=acc>>bit_shift;
        break;
      }
      case '+': {
        add(&acc, mode);
        break;
      }
      case '-': {
        subtract(&acc, mode);
        break;
      }
    }
  }
  return 0;
}