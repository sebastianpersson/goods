#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
//#include "goods.h"



typedef struct db_t *Db_t;

typedef struct vara_t vara_t;

typedef struct tempdb_t *tempDb_t;

struct plats_t{
  char shelf; 
  int location;};

struct vara_t{
  char* name; //namnet på varan
  char* info; // beskriver varan
  int price;    //priset
  int amount; //antalet
  struct plats_t place;};

struct db_t{
  struct vara_t lager[20];
  int counter;};

struct tempdb_t{
  struct vara_t temp[1];};

void list_db(Db_t db){
  puts("\n");
  
  for(int i = 0; i < 20; i++){
    if(db->lager[i].amount != 0){
      printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n[%d]: %s\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", (i+1), db->lager[i].name);
    }
    else printf ("[%d]: Hyllan är tom \n", (i+1));
  }
}

void print_item_info_add(vara_t item){
  
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n        VARA\n        ‾‾‾‾\n[N]amn: %s \n[B]eskrivning: %s \n[P]ris: %dkr \n[A]ntal: %dst  \n[H]yllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n",
item.name, item.info, item.price, item.amount, item.place.shelf, item.place.location);}

void print_item_info(Db_t db){
  int number = (db->counter+1);
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n          [%d]\n[N]amn: %s \n[B]eskrivning: %s \n[P]ris: %dkr \n[A]ntal: %dst  \n[H]yllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n",number, db->lager[db->counter].name, db->lager[db->counter].info, db->lager[db->counter].price, db->lager[db->counter].amount, db->lager[db->counter].place.shelf, db->lager[db->counter].place.location);}

void print_item_info_temp(tempDb_t temp){
  
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n          []\n1. Namn: %s \n2. Beskrivning: %s \n3. Pris: %dkr \n4. Antal: %dst  \n5. Hyllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", temp->temp[0].name, temp->temp[0].info, temp->temp[0].price, temp->temp[0].amount, temp->temp[0].place.shelf, temp->temp[0].place.location);}

void save_to_db(Db_t db, vara_t item){
  db->lager[db->counter] = item;}

void save_temp_to_db(Db_t db, tempDb_t temp){

  strcpy (db->lager[db->counter].name, temp->temp[0].name);
  strcpy (db->lager[db->counter].info, temp->temp[0].info);
  db->lager[db->counter].price = temp->temp[0].price;
  db->lager[db->counter].amount = temp->temp[0].amount;
  db->lager[db->counter].place.shelf = temp->temp[0].place.shelf;
  db->lager[db->counter].place.location = temp->temp[0].place.location;
}

void undo_action(Db_t db, tempDb_t temp){
  save_temp_to_db(db, temp);
  int number = (db->counter+1);
  printf("Du har nu ångrat den senaste ändringen på varan från plats %d*\n\n" , number); 
}

void save_to_temp(Db_t db, tempDb_t temp){
 
  strcpy (temp->temp[0].name, db->lager[db->counter].name);
  strcpy (temp->temp[0].info, db->lager[db->counter].info);
  temp->temp[0].price = db->lager[db->counter].price;
  temp->temp[0].amount = db->lager[db->counter].amount;
  temp->temp[0].place.shelf = db->lager[db->counter].place.shelf;
  temp->temp[0].place.location = db->lager[db->counter].place.location;}


void start_counter(Db_t db){
  db->counter = 0;}


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

bool get_goods_for_storage_location(Db_t db, tempDb_t temp){
  for(int i = 0; i < 20; i++){
    if (!(db->lager[i].place.location != temp->temp[0].place.location || db->lager[i].place.shelf != temp->temp[0].place.shelf)){
      return true;}
  }
  return false;
}

bool ask_yes_no(char* question){
  printf("%s ",question);
  char buffert[20];
  char reply;
  while(true){    
    //while (getchar() != '\n');
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
void which_edit_item(Db_t db, tempDb_t temp){
  char reply;
  ask_char_question("Vilken egenskap skulle du vilja redigera?:", &reply);
  switch(reply){
      case 'N':
	save_to_temp(db, temp);
	ask_string_question("Namn:", db->lager[db->counter].name);
	break;
      case 'B':;
	save_to_temp(db, temp);
	ask_string_question("Beskrivning:", db->lager[db->counter].info);
	break;
      case 'P':
	save_to_temp(db, temp);
	db->lager[db->counter].price = ask_int_question("Pris:");
	break;
      case 'A':
	save_to_temp(db, temp);
       	db->lager[db->counter].amount = ask_int_question("Antal:");
	break;
      case 'H':
	save_to_temp(db, temp);

	do{
	  ask_char_question("Vänligen ange hyllplan (tex, A, B eller C):", &temp->temp[0].place.shelf);
	  temp->temp[0].place.location = ask_int_question("Ange vilket hyllnummer varan ligger på:"); 
	}while(get_goods_for_storage_location(db, temp));
	
	db->lager[db->counter].place.location = temp->temp[0].place.location;
	db->lager[db->counter].place.shelf = temp->temp[0].place.shelf;
 break;
 default:
   puts("Vänligen ange ett nummer mellan 1-5");
}
}


void add_item(Db_t db, tempDb_t temp){
  vara_t item;

  item.name = malloc(sizeof(char)*30);
  ask_string_question("Namn:",item.name);
  
  item.info = malloc(sizeof(char)*100);
  ask_string_question("Beskrivning:", item.info);
  
  item.amount = ask_int_question("Antal:");
  item.price = ask_int_question("Pris:");
  int x = 0;
  do{
    if(x>0){
      printf("Denna lagerplats är redan upptagen, vänligen välj en annan plats\n");
    }
    ask_char_question("Vänligen ange hyllplan (tex, A, B eller C):", &temp->temp[0].place.shelf);
    temp->temp[0].place.location = ask_int_question("Ange vilket hyllnummer varan ligger på:"); 
    ++x;
  }while(get_goods_for_storage_location(db, temp));

  item.place.shelf = temp->temp[0].place.shelf;
  item.place.location = temp->temp[0].place.location;
  
  list_db(db);  
  print_item_info_add(item);

  do{
  db->counter = ask_int_question("På vilken plats i databasen vill du spara din vara? (Mellan 1-20):")-1;
  if(db->counter > 19 || db->lager[db->counter].amount != 0){
    puts("Var god ange en LEDIG plats mellan 1-20.");}
  }while(db->counter > 19 || db->lager[db->counter].amount != 0);
  
  while(ask_yes_no("Vill du ändra på någon egenskap innan du sparar? (Y/N):")){
    int x = 0;
    char reply;
    ask_char_question("Vänligen välj det du vill redigera", &reply);
    switch(reply){
    case 'N':
	ask_string_question("Namn:", item.name);
	break;
    case 'B':
	ask_string_question("Beskrivning:", item.info);
	break;
    case 'P':
	item.price = ask_int_question("Pris:");
	break;
    case 'A':
	item.amount = ask_int_question("Antal:");
	break;
    case 'H':
      do{
	if(x>0){
	  printf("Denna lagerplats är redan upptagen, vänligen välj en annan plats\n");
	}
	  ask_char_question("Vänligen ange hyllplan (tex, A, B eller C):", &temp->temp[0].place.shelf);
	temp->temp[0].place.location = ask_int_question("Ange vilket hyllnummer varan ligger på:"); 
	++x;
      }while(get_goods_for_storage_location(db, temp));
      item.place.location = temp->temp[0].place.location;
	  item.place.shelf = temp->temp[0].place.shelf;
	  break;
    default:
      puts("Vänligen ange en bokstav som matchar en egenskap");
    }
  }
  
  
  if(ask_yes_no("Spara till databasen? (Y/N):")){    
    save_to_db(db, item);
    int number = db->counter+1;
    printf("\nDu har nu spara din vara på plats nummer %d i databasen*\n", number);
    temp->temp[0].amount = 0;
  }
  else{
    puts("Varan sparades ej i databasen");
  }
}


void remove_item(Db_t db, tempDb_t temp){
  bool should_continue = true;
  list_db(db);
  while(should_continue){    
    do{
      db->counter = ask_int_question("\nVilken plats har varan du vill ta bort i databasen? (Mellan 1-20):")-1;
      if(db->counter > 19 || db->lager[db->counter].amount == 0){
	puts("Var god ange en plats som innehåller en vara.");
	if(!ask_yes_no("Vill du fortsätta ta bort en vara? (Y/N)")){
	  puts("Du har nu avslutat operationen -Ta bort en vara");
	  should_continue = false;
	  break;
	}
      }
    }while(db->counter > 19 || db->lager[db->counter].amount == 0);
    if(should_continue){
      if(ask_yes_no("Vill du verkligen ta bort denna vara? (Y/N)")){
      save_to_temp(db, temp);
      db->lager[db->counter].amount = 0;
      int number = db->counter+1;
      printf("Varan på plats nummer %d har tagits bort*\n", number );
      
      }else printf("Varan har inte tagits bort");
      
    }
    break;
  }
}

void edit_item(Db_t db, tempDb_t temp){
  bool should_continue = true;
  list_db(db);
  while(should_continue){    
    do{
      db->counter = ask_int_question("\nVilken plats har varan i ditt lager som du vill redigera?:")-1;
      if(db->counter > 19 || db->lager[db->counter].amount == 0){
	puts("Var god ange en plats som innehåller en vara.");
	if(!ask_yes_no("Vill du fortsätta redigera en vara? (Y/N)")){
	  puts("Du har nu avslutat operationen -Redigera en vara");
	  should_continue = false;
	  break;
	}
      }
    }while(db->counter > 19 || db->lager[db->counter].amount == 0);
    print_item_info(db);
    while(should_continue){
      which_edit_item(db, temp);
      should_continue = ask_yes_no("Vill du fortsätta redigera egenskaper för varan? (Y/N) "); 
    }
    }
  print_item_info(db);
}


void show_info(Db_t db){
  list_db(db);
  bool should_continue = true ;
    while(should_continue){
      do{
	db->counter = ask_int_question("Vilken vara vill du ha information om?:")-1;
	if(db->counter > 19 || db->lager[db->counter].amount == 0){
	  printf("Var god ange en plats som innehåller en vara\n");
	  if(!ask_yes_no("Vill du fortsätta visa en vara? (Y/N)")){
	    puts("Du har nu avslutat operationen -Visa en vara");
	    should_continue = false;
	    break;
	  }
	}
      }while(db->counter > 19 || db->lager[db->counter].amount == 0);     
      if(should_continue){
	print_item_info(db);
	should_continue = ask_yes_no("Vill du ha information om fler varor? (Y/N): ");	
      }     
    }
}


void print_main_menu(){

  printf("%-5s","\n");
  printf("%s", "Hej, välkommen till din varuhantering");
  printf("%-5s", "\n");
  printf("%s", "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
  /*printf("1. Lägg till en vara \n");
  printf("2. Ta bort en vara \n");
  printf("3. Redigera en vara \n");
  printf("4. Lista varor \n");
  printf("5. Ångra tillägg av vara \n");
  printf("6. Lista meny igen \n");
  printf("7. Avsluta programmet \n");
  */
  printf("[L]ägga till en vara\n");
  printf("[T]a bort en vara\n");
  printf("[R]edigera en vara\n");
  printf("Ån[g]ra senaste ändringen\n");
  printf("List [h]ela varukatalogen \n");
  printf("[V]isa menyn igen\n");
  printf("[A]vsluta\n");
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
};

void avslut(){
  puts("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
  puts("Vad skulle du vilja göra nu? ([V]isa menyn igen)");
};

int main(void){
  bool should_continue = true;
  print_main_menu();
  Db_t warehouse = malloc (sizeof (struct db_t));
  tempDb_t temp = malloc (sizeof (struct tempdb_t));
  temp->temp->name = malloc (sizeof (char)*30);
  temp->temp->info = malloc (sizeof (char)*100);
  start_counter(warehouse);
  while(should_continue){
    char reply;
    ask_char_question("Vad vill du göra idag?:", &reply);
    switch (reply) {
    case 'L':
      add_item(warehouse, temp);
      avslut();
      break;
    case 'T':
      remove_item(warehouse, temp);
      avslut();
      break;
    case 'R':
      edit_item(warehouse,temp);
      avslut();
      break;
    case 'H':
      show_info(warehouse);
      avslut();
      break;
    case 'G':
      undo_action(warehouse, temp);
      break;
    case 'V':
      print_main_menu();
      avslut();
      break;
    case 'A':
      should_continue = false;
      break;
    default:
      printf("Vänligen välj ett alternativ med en giltig bokstav\n");
    }
  }
  return 0;
}
