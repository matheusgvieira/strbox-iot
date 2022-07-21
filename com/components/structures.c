//
// Created by Matheus Gois Vieira on 27/06/22.
//

#include "structures.h"

void split_tag_value(char *tag_value, split *tag_value_splited) {
    tag_value_splited->tag = strtok(tag_value, "-");
    tag_value_splited->value = strtok(NULL, "-");
}

void setTypeData(com_module *module) {
    split tag_value_splited = {.tag = "", .value = ""};
    float voltage = 0.0, current = 0.0;

    split_tag_value(module ->read_uart, &tag_value_splited);

    if(strcmp(tag_value_splited.tag, "V") == 0) {
        voltage = atof(tag_value_splited.value);

        if(module -> voltage != voltage) {
            module -> voltage = voltage;
            module -> update = 1;
        }
    }
    if(strcmp(tag_value_splited.tag, "C") == 0) {
        current = atof(tag_value_splited.value);

        if(module -> current != current) {
            module -> current = current;
            module -> update = 1;
        }
    }
};

void get_init_nvs(com_module *data) {
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);

    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        // read voltage in nvs
        printf("Reading voltage from NVS ... ");
        size_t required_size_voltage;
        nvs_get_str(my_handle, "voltage", NULL, &required_size_voltage);
        char *voltage = malloc(required_size_voltage); // value will default to 0, if not set yet in NVS
        err = nvs_get_str(my_handle, "voltage", voltage, &required_size_voltage);

        switch (err) {
            case ESP_OK:
                printf("Done\n");
                printf("Get in nvs voltage = %s\n", voltage);
                data -> voltage = atof(voltage);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The voltage is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }
        // read current in nvs
        printf("Reading current from NVS ... ");
        size_t required_size_current;
        nvs_get_str(my_handle, "current", NULL, &required_size_current);
        char *current = malloc(required_size_current); // value will default to 0, if not set yet in NVS
        err = nvs_get_str(my_handle, "current", current, &required_size_current);

        switch (err) {
            case ESP_OK:
                printf("Get in nvs current = %s\n", current);
                data -> current = atof(current);
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("The current is not initialized yet!\n");
                break;
            default :
                printf("Error (%s) reading!\n", esp_err_to_name(err));
        }

        nvs_close(my_handle);
    }
}
void set_init_nvs(com_module *data){
    esp_err_t err = nvs_flash_init();
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);

    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        // Write voltage
        printf("Updating voltage in NVS ... ");
        char voltage[50];
        sprintf(voltage, "%f", data->voltage);
        err = nvs_set_str(my_handle, "voltage", voltage);

        printf((err != ESP_OK) ? "Voltage no update nvs!\n" : "Voltage update nvs.\n");

        // Write current
        printf("Updating current in NVS ... ");
        char current[50];
        sprintf(current, "%f", data->current);
        err = nvs_set_str(my_handle, "current", current);

        printf((err != ESP_OK) ? "Current no update nvs!\n" : "Current update nvs.\n");

        // Write power
        printf("Updating power in NVS ... ");
        char power[50];
        sprintf(power, "%f", data->power);
        err = nvs_set_str(my_handle, "power", power);

        printf((err != ESP_OK) ? "Power no update nvs!\n" : "Power update nvs.\n");

        // Write energy
        printf("Updating energy in NVS ... ");
        char energy[50];
        sprintf(energy, "%f", data->energy);
        err = nvs_set_str(my_handle, "energy", energy);

        printf((err != ESP_OK) ? "Energy no update nvs!\n" : "Energy update nvs.\n");

        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "No commit nvs!!\n" : "Commit nvs!\n");

        // Close
        nvs_close(my_handle);
    }
};
