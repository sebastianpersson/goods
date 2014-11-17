#ifndef _goods_h
#define _goods_h

/*! \file goods.h
    \brief Headfunctions
    
    This is the main module of the program goods.
    This module links the whole program  
*/

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


typedef struct db_t *Db_t;

typedef struct vara_t vara_t;

typedef struct tempdb_t *tempDb_t;

/**
*Takes a variable and presents it contents
@param item a variable with the struct vara_t
@return void
 */
void print_item_info_add(vara_t item);
/**
 *Return true if the properties place in db and temp match eachother.
@param db a database with the struct Db_t
@param temp a database with the struct tempDb_t
@return true or false depending if its a match
*/
bool get_goods_for_storage_location(Db_t db, tempDb_t temp);
/**
 *Creates another struct item where replies for subsequent questions are entered as values. Afterwards stored in db.
@param db a database with the struct Db_t
@param temp a database with the struct tempDb_t
@return void
*/
void add_item(Db_t db, tempDb_t temp);
/**
*Questions which item to be removed. Copies the chosen item into temp_item and then removes it from db.
@param db a database with the struct Db_t
@param temp a database with the struct tempDb_t
@return void
*/
void remove_item(Db_t db, tempDb_t temp);
/**
Questions which item in db to modify.
Modifies a propertie uppon the users request. Previous value store in temp
@param db a database with the struct Db_t
@param temp a database with the struct tempDb_t
@return void 
*/
void edit_item(Db_t db, tempDb_t temp);
/**
*Shows all the information about a chosed item.
@param db a database with the struct Db_t
@return void
*/
void show_info(Db_t db);
/**
*Prints a graphical menu with all the options the user can do
@return void
*/
void print_main_menu();
/**
 * Shows a quit note to the user, so the user know when one of the headfunctions has quit.
@return void
*/
void avslut();
/**
 *Allocates space for Db_t warehouse and Tempdb_t temp_item. 
 *Questions user for action. Depending on user input, calls on function.
@returns int when quit return 1 as true
*/
int main(void);
#endif
