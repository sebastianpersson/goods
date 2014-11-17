#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "goods_input.h"
#include "goods_db.h"
#include "goods.h"


void save_to_temp(Db_t db, tempDb_t temp){
 
  strcpy (temp->temp[0].name, db->lager[db->counter].name);
  strcpy (temp->temp[0].info, db->lager[db->counter].info);
  temp->temp[0].price = db->lager[db->counter].price;
  temp->temp[0].amount = db->lager[db->counter].amount;
  temp->temp[0].place.shelf = db->lager[db->counter].place.shelf;
  temp->temp[0].place.location = db->lager[db->counter].place.location;}


void save_db_from_add(Db_t db, vara_t item){
  db->lager[db->counter] = item;}


void save_db_from_temp(Db_t db, tempDb_t temp){

  strcpy (db->lager[db->counter].name, temp->temp[0].name);
  strcpy (db->lager[db->counter].info, temp->temp[0].info);
  db->lager[db->counter].price = temp->temp[0].price;
  db->lager[db->counter].amount = temp->temp[0].amount;
  db->lager[db->counter].place.shelf = temp->temp[0].place.shelf;
  db->lager[db->counter].place.location = temp->temp[0].place.location;
}

bool get_goods_for_storage_location(Db_t db, tempDb_t temp){
  for(int i = 0; i < 20; i++){
    if (!(db->lager[i].place.location != temp->temp[0].place.location || db->lager[i].place.shelf != temp->temp[0].place.shelf)){
      return true;}
  }
  return false;
}


void undo_action(Db_t db, tempDb_t temp){
  save_db_from_temp(db, temp);
  int number = (db->counter+1);
  printf("Du har nu ångrat den senaste ändringen på varan från plats %d*\n\n" , number); 
}


void list_db(Db_t db){
  puts("\n");
  
  for(int i = 0; i < 20; i++){
    if(db->lager[i].amount != 0){
      printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n[%d]: %s\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n", (i+1), db->lager[i].name);
    }
    else printf ("[%d]: Hyllan är tom \n", (i+1));
  }
}


void print_item_info_db(Db_t db){
  int number = (db->counter+1);
  printf("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n          [%d]\n[N]amn: %s \n[B]eskrivning: %s \n[P]ris: %dkr \n[A]ntal: %dst  \n[H]yllinfo: %c%d \n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n",number, db->lager[db->counter].name, db->lager[db->counter].info, db->lager[db->counter].price, db->lager[db->counter].amount, db->lager[db->counter].place.shelf, db->lager[db->counter].place.location);}


void start_counter(Db_t db){
  db->counter = 0;}
