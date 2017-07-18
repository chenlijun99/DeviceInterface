#!/bin/bash

if ! [[ -e driver_load.sh ]]; then
	echo "No \"driver_load.sh\" found in current directory"
	exit -1
fi

echo "# autobind the driver of mcp2221 usb-i2c/uart device
ACTION==\"add\", SUBSYSTEM==\"tty\", ATTRS{idProduct}==\"00dd\", ATTRS{idVendor}==\"04d8\", RUN+=\"$(pwd)/driver_load.sh\", OPTIONS+=\"last_rule\"
ACTION==\"add\", SUBSYSTEM==\"i2c-dev\", ATTRS{idProduct}==\"00dd\", ATTRS{idVendor}==\"04d8\", MODE=\"0666\", OPTIONS+=\"last_rule\"" > ./100-DeviceInterface.rules

