#ifndef _goods_input_h
#define _goods_input_h


/*!
\file goods_input.h
\brief Input functions
Input function, all the functions in this module are depening on the user and the users input.
*/

/**
 *Prints the question and writes the input information to reply
@param question A string that will be presented as input question
@param reply a place where the reply information will be saved 
@return void
*/
void ask_char_question(char* question, char* reply);
/**
 *Prints the question and returns true or false depending on the input
Warning and loop if input not correct or to many letters.
@param question A string that will be presented as input question
@return True or false, if user types 'Y','y' then true, if 'N','n' then false
*/
bool ask_yes_no_question(char* question);
/**
 *Prints the question and writes the input info to reply.
Input can be any letter, number etc.
@param question A string that will be presented as input question
@param reply a place where the reply information will be saved
@return void
*/
void ask_string_question(char* question, char* reply);
/**
 *Prints the question and returns the input integer
 *Warning and loop if not an integer
@param question A string that will be presented as input question
@return An integer from inpu
*/
int ask_int_question(char* question);

#endif
