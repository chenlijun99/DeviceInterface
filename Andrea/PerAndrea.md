# Per Andrea

Prova a eseguire il commando

```sh
$ i2cdetect -l
i2c-0	unknown   	i915 gmbus ssc                  	N/A
i2c-1	unknown   	i915 gmbus vga                  	N/A
i2c-2	unknown   	i915 gmbus panel                	N/A
i2c-3	unknown   	i915 gmbus dpc                  	N/A
i2c-4	unknown   	i915 gmbus dpb                  	N/A
i2c-5	unknown   	i915 gmbus dpd                  	N/A
i2c-6	unknown   	DPDDC-B                         	N/A
i2c-7	unknown   	DPDDC-C                         	N/A
i2c-8	unknown   	Synopsys DesignWare I2C adapter 	N/A
i2c-9	i2c       	i2c-mcp2221 at bus 001 device 011	I2C adapter
```
**i2c-9	i2c       	i2c-mcp2221 at bus 001 device 011	I2C adapter** è quello che ci interessa.

Se non vedi la linea in grassetto, allora o il driver non è stato installato
o non è stato settato per caricarsi automaticamente.

Ci sono allora questi step da fare:

* Installare il driver 
	* Scaricalo da [qui](http://ww1.microchip.com/downloads/en/DeviceDoc/mcp2221_0_1.tar.gz)
	* Decomprimere il file
	* Entrare nella cartella ottenuta e fare `make modules` e `sudo make install`
	* Prova a eseguire lo script fornito nella cartella del driver `sudo ./driver_load.sh`
	* Prova a rieseguire `i2cdetect -l` e adesso dovresti vedere il device desiderato
* Automatizzare il caricamento del driver
	* scaricare e muovere questo [script](https://raw.githubusercontent.com/free-easy/DeviceInterface/personal-use-branch/Andrea/generate_udev_rules.sh) nella cartella del driver
	* Un eventuale `chmod u+x ./generate_udev_rules.sh` potrebbe essere necessario
	* eseguire lo script e copiare il file prodotto `100-DeviceInterface.rules` nella cartella `/etc/udev/rules.d`
	* eseguire questo commando: `sudo udevadm control --reload` per aggiornare le udev-rules

Adesso prova a disconnettere il device e a riconnetterlo (prova anche più volte) e ogni volta che lo riconnetti
con `i2cdetect -l` dovresti automaticamente vedere `i2c-9	i2c				 i2c-mcp2221 at bus 001 device 011	I2C adapter`
