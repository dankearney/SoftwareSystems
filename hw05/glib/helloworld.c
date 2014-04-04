#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


int main(int argc, char* argv[])
{
    GString *g = g_string_new("Hello GLIB!");
    puts(g->str);
    return 0;
}
