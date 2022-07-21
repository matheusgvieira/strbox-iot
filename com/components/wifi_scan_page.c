#include "wifi.h"

static const char *TAG = "wifi station";

uint16_t ap_num = MAX_APs;
wifi_ap_record_t ap_records[MAX_APs];


led_rgb led_wifi = {.pin = 26, .color= "blue"};

void wifi_config_initialize() {

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
}

void wifi_initialize_station(void)
{
    wifi_config_t sta_config = {
            .sta = {
                    .ssid = EXAMPLE_ESP_WIFI_SSID,
                    .password = EXAMPLE_ESP_WIFI_PASS,
            },
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
}

void wifi_initialize_acess_point() {
    wifi_config_t ap_config = {
            .ap = {
                    .ssid = AP_SSID,
                    .password = AP_PASSWORD,
                    .ssid_hidden = 0, // Access point in ssid sini wifi scanlarda gizlemek için kullanılan parametre
            },
    };
    ap_config.ap.authmode = WIFI_AUTH_OPEN;
    ap_config.ap.ssid_len = 0;
    ap_config.ap.max_connection = AP_MAX_CONN;
    ap_config.ap.channel = AP_CHANNEL;

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config));
}

void wifi_start() {
    ESP_ERROR_CHECK(esp_wifi_start() );

    printf("Starting Access Point, SSID=%s\n", "COM_MODULE_TRANSMITTER");

    ESP_ERROR_CHECK(esp_wifi_connect());

    esp_netif_ip_info_t ip_info;

    esp_netif_t* netif=NULL;
    netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");

    if (netif == NULL)
        printf("Pointer is NULL.\n");
    else
    {
        esp_netif_get_ip_info(netif, &ip_info);

        printf("My IP: " IPSTR "\n", IP2STR(&ip_info.ip));
        printf("My GW: " IPSTR "\n", IP2STR(&ip_info.gw));
        printf("My NETMASK: " IPSTR "\n", IP2STR(&ip_info.netmask));
    }
}

void scann()
{

    // configure and run the scan process in blocking mode
    wifi_scan_config_t scan_config = {
            .ssid = 0,
            .bssid = 0,
            .channel = 0,
            .show_hidden = false};

    printf("Wifi scanning...");
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_num));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));

    ESP_ERROR_CHECK(esp_wifi_start());
}


esp_err_t get_handler(httpd_req_t *req)
{
    /* Send a simple response */
    const char resp[] = "URI GET Response";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t uri_get = {
        .uri      = "/uri",
        .method   = HTTP_GET,
        .handler  = get_handler,
        .user_ctx = NULL
};

httpd_handle_t start_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

void wifiInit()
{
    //Init led
    init_led(&led_wifi);

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

//    ESP_ERROR_CHECK(init_spiffs());

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_config_initialize();
    wifi_config_initialize();
    wifi_initialize_acess_point();
    wifi_start();

    start_webserver();
}