//
// Created by Matheus Gois Vieira on 27/06/22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *tag;
    char *value;
} split;


void split_tag_value(char *tag_value, split *tag_value_splited) {
    tag_value_splited->tag = strtok(tag_value, "-");
    tag_value_splited->value = strtok(NULL, "-");
}


int main()
{
    char str[] = "V-12.23";
    split tag_value_splited = {.tag="", .value=""};
    split_tag_value(str, &tag_value_splited);

    printf("tag = %s\n", tag_value_splited.tag);
    printf("value = %f\n", atof(tag_value_splited.value));
    printf("\n");

    return 0;
}