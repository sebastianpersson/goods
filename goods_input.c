#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "goods_input.h"
#include "goods_db.h"
#include "goods.h"


int ask_int_question(char* question){  
  while (true){
    printf("%s ",question);
    int reply;
    if (scanf("%d",&reply)){
      while (getchar() != '\n');
      return reply;
      
    }
    printf("Fel format på inmatning, vänligen försök igen med siffror! \n");
    while (getchar() != '\n');
  }
}


void ask_string_question(char* question, char* reply){
  do{
    printf("%s ",question);
    scanf("%[^\n]s*", reply);
    while (getchar() != '\n');
  }while(strlen(reply) < 1);
}


bool ask_yes_no_question(char* question){
  printf("%s ",question);
  char buffert[20];
  char reply;
  while(true){    
    do{
       fgets(buffert, sizeof(buffert), stdin);
     if(buffert[2] != '\0'){
       puts("Vänligen ange enbart en bokstav (Y/N)");
     }
     }while(buffert[2] != '\0');    
  reply = tolower(buffert[0]);
  switch (reply){
  case 'y' :
    return true;
    break;
  case 'n':
    return false;
    break;
  default:
    puts("Vänligen använd (Y/N)");
  }
  }
}


void ask_char_question(char* question, char* reply){
  printf("%s " ,question);
  char buffert[32];
  do {
    fgets(buffert, sizeof(buffert), stdin);
    if(buffert[2] != '\0'){
      printf("Du har angett för många bokstäver, vänligen ange enbart EN bokstav: ");
    }
  }while(buffert[2] != '\0');  
  *reply = toupper(buffert[0]);
}
