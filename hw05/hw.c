#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

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

	int count = 0;
    while (fgets(line, sizeof(line), file)) {
    	count++;
    	if (count==10)
    		break;
    	GString *gline = g_string_new(line);
    	g_strstrip(gline->str);
    	gsize len = gline->len;
        g_hash_table_insert(hist, (gpointer)gline, (gpointer)&len);
    	print_hash_table(hist);
    }
    return 0;
}