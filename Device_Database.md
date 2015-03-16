# Introduction #

The Device Database is where Open-ZWave retrieve details about supported devices. It Generally contains mappings between manufacture and product ID's and names, as well as specific configurations for particular devices.

Generally, a user would not need to edit/modify the device database unless they wish to add new zwave products to be supported by the library.

Specifically, the database contains the following information:

  * Map Manufacture and Product ID's to human readable names
  * Describe Device Configuration Variables that are not exposed via the ZWave Protocol
  * Enable work-arounds for buggy or non-conforming devices.

# Details #

The database is a collection of xml files. The main file is manufacturer\_specific.xml file and would be the starting point for anybody that wishes to modify the database. A sample is below:

```
<ManufacturerSpecificData xmlns='http://code.google.com/p/open-zwave/'>
        <Manufacturer id="0040" name="2B Electronics">
        </Manufacturer>
        <Manufacturer id="0098" name="2GIG Technologies">
                <Product type="1e12" id="015c" name="CT30 Thermostat" config="2gig/ct30.xml"/>
                <Product type="6401" id="0105" name="CT100 Thermostat" config="2gig/ct100.xml"/>
        </Manufacturer>
....
</ManufacturerSpecificData>
```

A description of the various tags and elements follows.

**Manufacturer Block**
|id|This is a numerical value that is assigned by the Z-Wave Alliance to manufacturers of Z-Wave devices.|
|:-|:----------------------------------------------------------------------------------------------------|
|name|A human Readable Name of the Manufacturer|

**Product Block**
|type|a number assigned by the Manufacturer to a specific Product(s)|
|:---|:-------------------------------------------------------------|
|id|a number that identifies a specific device|
|name|a human readable name of the device|
|config|a filename that contains product specific workarounds and configuration information (see next section)|
