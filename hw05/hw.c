#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <ctype.h>

typedef struct value {
	int val;
	GString * str;
} Value;

Value * make_value(int val, GString * str) {
	Value *v = malloc(sizeof(Value));
	v->val = val;
	v->str = g_string_new(g_strdup(str->str));
	return v;
}

int cmp_values(gconstpointer a, gconstpointer b) {
	Value *vala = (Value *) a;
	Value *valb = (Value *) b;
	return valb->val - vala->val;
}

void increment_val(Value *v) {
	(v->val)++;
}


void print_hash_table(GHashTable *h) 
{
	guint size = g_hash_table_size(h);
	GList *vals = g_hash_table_get_values (h);
	vals = g_list_sort(vals, (GCompareFunc) cmp_values);
	Value *val;
	int i;
	for (i=0; i<size; i++) {
		val = (Value *) g_list_nth_data(vals, i);
		printf("key: %s; val: %i\n", val->str->str, val->val);
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

//http://stackoverflow.com/questions/1841758/how-to-remove-punctuation-from-a-string-in-c
void remove_punct_and_make_lower_case(char *p)
{
    char *src = p, *dst = p;
    while (*src)
    {
       if (ispunct((unsigned char)*src))
       {
          /* Skip this character */
          src++;
       }
       else if (isupper((unsigned char)*src))
       {
          /* Make it lowercase */
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst)
       {
          /* Increment both pointers without copying */
          src++;
          dst++;
       }
       else
       {
          /* Copy character */
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("no file given\n");
		exit(-1);
	}
    const char* fileName = argv[1]; 
    FILE* file = fopen(fileName, "r"); 
	GHashTable *hist = g_hash_table_new ((GHashFunc)g_string_hash, (GEqualFunc)g_string_equal);
	char line[1024];
	const int MAX_WORDS_IN_LINE = 50;
	gchar ** words;
	int i;
    while (fgets(line, sizeof(line), file)) {
    	words = g_strsplit(line, " ", MAX_WORDS_IN_LINE);
    	for (i=0; i<MAX_WORDS_IN_LINE; i++) {
    		if (words[i] == NULL) 
    			break;
    		remove_punct_and_make_lower_case(words[i]);
    		add_to_hist(hist, g_string_new(words[i]));
    	}
    	
    }    
    print_hash_table(hist);
    return 0;
}