#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <ctype.h>

typedef struct value {
	int val;
	GString * str;
} Value;


const int MAX_WORDS_IN_LINE = 50;
const int DEFAULT_NUM_TO_PRINT = 10;	


Value * make_value(int val, GString * str) {
	Value *v = malloc(sizeof(Value));
	if (v==NULL) {
		fprintf(stderr, "Malloc failed to make Value");
		exit(-1);
	}
	v->val = val;
	v->str = g_string_new(g_strdup(str->str));
	return v;
}


int cmp_values(gconstpointer a, gconstpointer b) {
	return ((Value *)b)->val - ((Value *)a)->val;
}


void increment_val(Value *v) {
	(v->val)++;
}


void print_hash_table(GHashTable *h, int num_to_print) 
{
	GList *vals = g_hash_table_get_values (h);
	vals = g_list_sort(vals, (GCompareFunc) cmp_values);
	Value *val;
	int i;
	for (i=0; i<num_to_print; i++) {
		val = (Value *) g_list_nth_data(vals, i);
		printf("key: %s; count: %i\n", val->str->str, val->val);
	}
}


void add_to_hist(GHashTable *h, GString *s) 
{
	Value *val = g_hash_table_lookup(h, (gpointer)s);
	if (val == NULL) {
		val = make_value(1, s);
		g_hash_table_insert(h, (gpointer)s, (gpointer)val);	
	}
	else {
		increment_val(val);
	}

}


void remove_nonchars_and_set_lowercase(char *p)
{
	char *src =p, *dst = p;
	while (*src) {
		if (ispunct(*src) || isspace(*src)) {
			src++;
		} else if (isupper(*src)) {
			*dst = tolower(*src);
			src++; dst++;
		} else {
			*dst = *src;
			src++; dst++;
		}
	}
	*dst = 0;
}


void format_and_add_to_hist(GHashTable *h, char *s) {
	remove_nonchars_and_set_lowercase(s);
	if (!*s) 
		return;
	GString *g = g_string_new(s);
	add_to_hist(h, g);
} 


int handle_args_and_get_num_print(int argc, char** argv) 
{
	char *num;
	if (argc < 2) {
		printf("no file given\n");
		exit(-1);	
	} else if (argc == 2) {
		return DEFAULT_NUM_TO_PRINT; 
	} else {
		printf("%s", argv[2]);
		return strtol(argv[2], &num, 10);
	}
}


gchar ** split_line(char *buf)
{
	return g_strsplit(buf, " ", MAX_WORDS_IN_LINE);
}


int main(int argc, char* argv[])
{
	int num_to_print = handle_args_and_get_num_print(argc, argv);
	FILE* file = fopen(argv[1], "r");
	GHashTable *hist = g_hash_table_new ((GHashFunc)g_string_hash, (GEqualFunc)g_string_equal);
	char line_buf[1024]; gchar ** words; int i;
	while (fgets(line_buf, sizeof(line_buf), file)) {
		words = split_line(line_buf);
		for (i=0; i<MAX_WORDS_IN_LINE; i++) {
			if (words[i] == NULL) 
				break;
			format_and_add_to_hist(hist, words[i]);
		}
		
	}
	print_hash_table(hist, num_to_print);
	return 0;
}