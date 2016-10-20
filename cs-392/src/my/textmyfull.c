#include "../../include/my.h"
#include <limits.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

int main(int argc, char const *argv[]){

	/*Variable Declarations for Testing*/
	char str[] = {'H','E','L','L','O','\0'};
	int maxneg = INT_MIN;

	/*Testing my_str()*/
	my_str("Testing my_str()\n----------------------------------------------\n");
	my_str(NULL);								my_str("\t|\tNULL\n");
	my_str("");									my_str("\t|\tEmpty String\n");
	my_str("Hello");							my_str("\t|\tHello\n");

	/*Testing my_int()*/
	my_str("\nTesting my_int()\n----------------------------------------------\n");
	my_int(-1); 								my_str("\t|\t-1\n");
	my_int(-156); 								my_str("\t|\t-156\n");
	my_int(0);									my_str("\t|\t0\n");
	my_int(3);									my_str("\t|\t3\n");
	my_int(30);									my_str("\t|\t30\n");
	my_int(maxneg);								my_str("\t|\tMax Neg\n");

	/*Testing my_num_base();*/
	my_str("\nTesting my_num_base()\n----------------------------------------------\n");
	my_num_base(17, NULL);						my_str("\t|\tNULL\n");
	my_num_base(17, "");						my_str("\t|\tEmpty Set\n ");
	my_num_base(5, "A");						my_str("\t|\tSingle Char - \"AAAAA\"\n ");
	my_num_base(-5, "A");						my_str("\t|\tSingle Char Neg - \"-AAAAA\"\n ");
	my_num_base(0, "01");						my_str("\t|\tZero - \"0\"\n ");
	my_num_base(4, "012345");					my_str("\t|\tSingle Digit - \"4\"\n ");
	my_num_base(18, "01");						my_str("\t|\tDouble Digit - \"10010\"\n ");
	my_num_base(-7, "0123456789ABCDEF");		my_str("\t|\tSingle Digit Negative - \"-7\"\n");
	my_num_base(-195, "0123456789ABCDEF");		my_str("\t|\tDouble Digit Negative - \"-C3\"\n");
	my_num_base(maxneg, "0123456789");			my_str("\t|\tTest Max Negative - \""); my_int(maxneg); my_str("\"\n\n");

	/*Testing Alpha and Digits*/
	my_str("\nTesting my_alpha and my_digits()\n----------------------------------------------\n");
	my_alpha();									my_str("\t|\tAlpha - ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	my_digits();								my_str("\t|\tDigits - 0123456789\n");

	/*Testing my_strlen()*/
	my_str("\nTesting my_strlen()\n----------------------------------------------\n");
	my_int(my_strlen(NULL));					my_str("\t|\tNULL - \"-1\"\n");
	my_int(my_strlen(""));						my_str("\t|\tEmpty String - \"0\"\n");
	my_int(my_strlen("Hello"));					my_str("\t|\tRegular String - \"5\"\n");

	/*Testing my_revstr*/
	my_str("\nTesting my_revstr()\n----------------------------------------------\n");
	my_int(my_revstr(NULL));					my_str("\t|\tNULL - \"-1\"\n");
	my_int(my_revstr(""));						my_str("\t|\tEmpty String - \"0\"\n");
	my_int(my_revstr(str));						my_str("\t|\tRegular String Return - \"5\"\n");
	my_str(str);								my_str("\t|\tRegular String Changed - \"OLLEH\"\n");
	
	/*Testing my_strindex*/
	my_str("Testing my_strindex()\n----------------------------------------------\n");
	if(my_strindex(NULL, 'a') == NULL) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strindex("", 'a') == NULL) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strindex(str, 'a') == NULL) my_char('X');				my_str("\t|\tNot Found in String\n");
	my_str(my_strindex(str, 'L'));								my_str("\t|\tFound in String - \"LLEH\"\n");
	
	/*Testing my_strrindex*/
	my_str("\nTesting my_strrindex()\n----------------------------------------------\n");
	if(my_strrindex(NULL, 'a') == NULL) my_char('X');			my_str("\t|\tNull Pointer\n");
	if(my_strrindex("", 'a') == NULL) my_char('X');				my_str("\t|\tEmpty String\n");
	if(my_strrindex(str, 'a') == NULL) my_char('X');			my_str("\t|\tNot Found in String\n");
	my_str(my_strrindex(str, 'L'));								my_str("\t|\tFound in String - \"LEH\"\n");

	return 0;
}
