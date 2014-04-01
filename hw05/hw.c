#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

void print_hash_table(GHashTable *h) 
{
	guint size = g_hash_table_size(h);
	GList *keys = g_hash_table_get_keys (h);
	GList *vals = g_hash_table_get_values (h);
	GString *key;
	int *val;
	int i;
	for (i=0; i<size; i++) {
		key = (GString*) g_list_nth_data(keys, i);
		val = (int *) g_list_nth_data(vals, i);
		printf("key: %s; val: %i\n", key->str, *val);
	}
}

void add_to_hist(GHashTable *h, GString *s) 
{
    int *val = g_hash_table_lookup(h, (gpointer)s);
    int *newVal = malloc(sizeof(int));
    if (val == NULL)
    	*newVal = 1;
    else {
    	*newVal = *val + 1;
    }
    g_hash_table_insert(h, (gpointer)s, (gpointer)newVal);	
}

GString* substring(const char* str, int begin, int len) 
{ 
  char *slice = strndup(str + begin, sizeof(char) * len); 
  GString *g = g_string_new(slice);
  free(slice);
  return g;
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
	gchar ** words = malloc(sizeof(line)*sizeof(char));
	int i;
    while (fgets(line, sizeof(line), file)) {
    	words = g_strsplit(line, " ", MAX_WORDS_IN_LINE);
    	for (i=0; i<MAX_WORDS_IN_LINE; i++) {
    		if (words[i] == NULL) {
    			printf("DETECTED");
    			break;
    	}
    		add_to_hist(hist, g_string_new(words[i]));
    	}
    	
    }    
    print_hash_table(hist);
    return 0;
}