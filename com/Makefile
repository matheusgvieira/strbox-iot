ESP32_PORT := /dev/cu.usbserial-0001
export ESP32_PORT

espbuild:
	idf.py build

espflash:
	idf.py -p $ESP32_PORT flash
