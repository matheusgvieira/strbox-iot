//
// Created by Matheus Gois Vieira on 27/06/22.
//

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

// Structures
typedef struct {
    char * read_uart;

    float current;
    float voltage;
    float power;
    float energy;

   char * topic_current;
   char * topic_voltage;
   char * topic_power;
   char * topic_energy;

    int8_t relay1;
    int8_t relay2;

    int8_t update;

} com_module;

typedef struct
{
    char *tag;
    char *value;
} split;

// Functions
void setTypeData(com_module *data);
void get_init_nvs(com_module *data);
void set_init_nvs(com_module *data);
void split_tag_value(char *tag_value, split *tag_value_splited);

#ifdef __cplusplus
}
#endif