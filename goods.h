#ifndef _goods_h
#define _goods_h

typedef struct db_t *Db_t;

typedef struct vara_t vara_t;

typedef struct tempdb_t *tempDb_t;

void print_item_info_add(vara_t item); //Tar en variabel men structen vara_t och presenterar de olika egenskaperna.

void print_item_info(Db_t db); // Tar structen Db_t som i sin tur innehåller en counter och ett lager[20]

void save_db_from_add(Db_t db, vara_t item);

void save_db_from_temp(Db_t db, tempDb_t temp);

void undo_action(Db_t db, tempDb_t temp);

void save_to_temp(Db_t db, tempDb_t temp);

void start_counter(Db_t db);

int ask_int_question(char* question);

void ask_string_question(char* question, char* reply);

bool get_goods_for_storage_location(Db_t db, tempDb_t temp);

bool ask_yes_no_question(char* question);

void ask_char_question(char* question, char* reply);

void which_edit_item(Db_t db, tempDb_t temp);

void add_item(Db_t db, tempDb_t temp);

void remove_item(Db_t db, tempDb_t temp);

void edit_item(Db_t db, tempDb_t temp);

void show_info(Db_t db);

void print_main_menu();

void avslut();

int main(void);  

#endif
