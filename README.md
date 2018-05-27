Library for simple storage of values in EEPROM

Usage
=====
Create object of propper type with offset (EByte byte(0) - creates storage of byte at offset 0) and use it like normal variable. Each write operation updates value in EEPROM, each read operation gets cached value from RAM.

Types supported

* template<class C> class EType - stores custom objects in EEPROM
* EString - stores strings with maximum length of 32 chars
* EByte
* EChar
* EInt
* EIPaddress
