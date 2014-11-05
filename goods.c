#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>




typedef struct db_t *Db_t;

typedef struct vara_t vara_t;

typedef struct tempdb_t *tempDb_t;

struct plats_t{
  char shelf; //hyllan ex. A
  int location; //platsen på hyllan ex. 25
};

struct vara_t{
  char* name; //namnet på varan
  char* info; // beskriver varan
  int price;    //priset
  int amount; //antalet
  struct plats_t place; // T.ex. A25
};

struct db_t{
  struct vara_t lager[20];
  int counter;
};


struct tempdb_t{
};


void save_to_db(Db_t db, vara_t item){
  db->lager[db->counter] = item;
}

void start_counter(Db_t db){
  db->counter = 0;
}

void list_db(Db_t db){
  puts("\n");

  for(int i = 0; i < 20; i++){
    if(db->lager[i].amount != 0){
      printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n[%d]: Namn: %s \n     Beskrivning: %s \n     Pris: %dkr \n     Antal: %dst  \n     Hyllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", (i+1), db->lager[i].name, db->lager[i].info, db->lager[i].price, db->lager[i].amount, db->lager[i].place.shelf, db->lager[i].place.location);
    }
    else printf ("[%d]: Hyllan är tom \n", (i+1));
  }
}

int ask_int_question(char* question){  
  while (true){
    printf("%s ",question);
    int reply;
    if (scanf("%d",&reply)){
      return reply;
    }
    printf("Fel format på inmatning, vänligen försök igen med siffror! \n");
    while (getchar() != '\n');
  }

}

void ask_string_question(char* question, char* reply){
  do{
    while (getchar() != '\n');
    printf("%s ",question);
    scanf("%[^\n]s*", reply);
  }while(strlen(reply) < 1);
}



bool ask_yes_no(char* question){
  puts(question);
  char buffert[32];
  char reply;
  while (getchar() != '\n');
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
  while (getchar() != '\n');
  do {
    fgets(buffert, sizeof(buffert), stdin);
    // gets(buffert);
    if(buffert[2] != '\0'){
      printf("Du har angett för många bokstäver, vänligen ange enbart EN bokstav: ");
    }
  }while(buffert[2] != '\0');  
  *reply = toupper(buffert[0]);
}

void print_item_info_edit(Db_t db){
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n[%d]: Namn: %s \n     Beskrivning: %s \n     Pris: %dkr \n     Antal: %dst  \n     Hyllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", ++db->counter, db->lager[db->counter].name, db->lager[db->counter].info, db->lager[db->counter].price, db->lager[db->counter].amount, db->lager[db->counter].place.shelf, db->lager[db->counter].place.location); 
}


void print_item_info(vara_t item){
  
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n        VARA\n        ‾‾‾‾\n Namn: %s \n Beskrivning: %s \n Pris: %dkr \n Antal: %dst  \n Hyllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n",
item.name, item.info, item.price, item.amount, item.place.shelf, item.place.location);
}


void edit_item(Db_t db){
  bool should_continue = true;
  while(should_continue){
    list_db(db);
    
    do{
      db->counter = ask_int_question("På vilken plats i databasen vill du spara din vara? (Mellan 1-20):")-1;
	if(db->counter > 19 || db->lager[db->counter].amount == 0){
	  puts("Var god ange en plats som innehåller en vara.");
	  if(!ask_yes_no("Vill du fortsätta redigera en vara? (Y/N)")){
	    puts("Du har nu avslutat operationen -Redigera en vara");
	    should_continue = false;
	    break;
	  }
	}
    }while(db->counter > 19 || db->lager[db->counter].amount == 0);
    
    print_item_info_edit(db);
    break;
  }
  
}

void add_item(Db_t db){
  vara_t item;
  item.name = malloc(sizeof(char)*30);
  ask_string_question("Namn:",item.name);
  
  item.info = malloc(sizeof(char)*100);
  ask_string_question("Beskrivning:", item.info);
  
  item.amount = ask_int_question("Antal:");
  item.price = ask_int_question("Pris:");

  ask_char_question("Vänligen ange hyllplan (tex, A, B eller C):", &item.place.shelf);
  item.place.location = ask_int_question("Ange vilket hyllnummer varan ligger på:");  
  
  list_db(db);  
  print_item_info(item);
  do{
  db->counter = ask_int_question("På vilken plats i databasen vill du spara din vara? (Mellan 1-20):")-1;
  if(db->counter > 19 || db->lager[db->counter].amount != 0){
    puts("Var god ange en LEDIG plats mellan 1-20.");}
  }while(db->counter > 19 || db->lager[db->counter].amount != 0);

  if(ask_yes_no("Spara till databasen? (Y/N)")){
    save_to_db(db, item);
    
    puts("\nDu har nu sparat din vara till databasen*");
  }
  else{
    puts("Varan sparades ej i databasen");
  }
}

void remove_item(Db_t db){
  bool should_continue = true;
  while(should_continue){
    
    do{
      db->counter = ask_int_question("Vilken plats har varan du vill ta bort i databasen? (Mellan 1-20):")-1;
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
      db->lager[db->counter].amount = 0;
      printf("Varan på plats nummer %d har tagits bort\n", ++db->counter);
    }
    break;
  }
}


/*do{
    printf("Vilket nummer har varan du vill ta bort?: ");
    while(true){
    int reply;
      if(scanf("%d", &reply)){
      if(db->counter > 20 || db->lager[db->counter].amount != 0);{
	db->lager[reply - 1].amount = 0;
	printf("Varan på plats nummer %d har tagits bort\n", reply);
      break;
      }
      puts("Vänligen ange en siffra");  
  }
}
*/

void print_main_menu(){
  printf("\nHej, välkommen till din varuhantering \n");
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
  printf("1. Lägg till en vara \n");
  printf("2. Ta bort en vara \n");
  printf("3. Redigera en vara \n");
  printf("4. Lista varor \n");
  printf("5. Ångra tillägg av vara \n");
  printf("6. Lista meny igen \n");
  printf("7. Avsluta programmet \n");
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ \n");
};

void avslut(){

  puts("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
  // puts("Tack för ditt val");
  //puts("------------------\n");
  puts("Vad skulle du vilja göra nu? (6. visa menyn igen)");

};

int main(void){
  bool should_continue = true;
  print_main_menu();
  Db_t warehouse = malloc (sizeof (struct db_t));
  
  start_counter(warehouse);
  
  while(should_continue){
    int reply = ask_int_question("Vänligen ange ett nummer:");
    
    switch (reply) {
    case 1:
      add_item(warehouse);
      avslut();
      break;
    case 2:
      remove_item(warehouse);
      avslut();
      break;
    case 3:
      edit_item(warehouse);
      avslut();
      break;
    case 4:
      list_db(warehouse);
      avslut();
      break;
    case 5:
      // undo_item();
      break;
    case 6:
      print_main_menu();
      avslut();
      break;
    case 7:
      should_continue = false;
      break;
    default:
      printf("Vänligen ange ett nummer mellan 1-7 \n");
    }
  }
  return 0;
}







/*bool ask_yes_no(char* question){

  printf("%s ", question);
  char reply[32];
  while (getchar() != '\n');
  do {
    gets(reply);
    if(reply[1] != '\0'){
      puts("Vänligen ange bara en bokstav");
    }
    
  }while(reply[1] != '\0');

   switch (reply){
      case 'y' :
	return true;
	break;
      case 'n':
	return false;
	break;
      default:
	puts("Vänligen använd y / n");
   }
      
}

*/

/*
bool ask_yes_no(char* question){
  puts(question);
  char reply;
  while(true){    
    while (getchar () != '\n');
    reply = tolower(getchar());
      switch (reply){
      case 'y' :
	return true;
	break;
      case 'n':
	return false;
	break;
      default:
	puts("Vänligen använd y / n");
      }
      
  }
} 
*/
