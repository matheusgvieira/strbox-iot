idf_component_register(SRCS "led.c" "buzzer.c" "uart.c" "wifi.c" "mqtt.c" "structures.c" "mqtt_publish.c" "mqtt_subscriber.c" "mqtt_publish_state.c" "mqtt_subscriber_rele2.c"
                    INCLUDE_DIRS "include"
                    REQUIRES "driver" "json" "mqtt" "spiffs" "esp_http_server"
                    PRIV_REQUIRES nvs_flash)

