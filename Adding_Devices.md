# Introduction #

All the devices that are present in the OpenZWave Device Database are community contributed, meaning we rely on users to send patches to us to add the device. We receive on average 2-3 requests for new devices each week. If we were to spend out limited time researching and adding devices, then OZW would not improve as far as code and bug fixes go. Also bear in mind that the OZW developers do not have every single Z-Wave device on the market, nor do we have access to them. (Donations are always welcome though!).

If you have a device that does not appear in the OpenZWave Device Database (manufacturer\_specific.xml file), in 99% of cases, the device will still work flawlessly with OpenZWave. This is because OpenZWave utilizes the "self discovery" features of the Z-Wave Protocol to discovery what capabilities the device has (ie, is it a switch, or dimmer, how many channels it supports etc)

When OZW runs in this mode, the following applies:
  1. the Name (and possibly Manufacturer) will appear as the hexadecimal ID's rather than product names. There is no loss of functionality here.
  1. Device Configuration Variables will not be available (as this is about the only part of Z-Wave that doesn't support any sort of discovery)
  1. If the device has non-standard implementation of the protocol or Command Classes, some functionality might be buggy. (this applies to maybe 2-3% of devices in the database currently, as with more recent devices, Z-Wave Alliance and Sigma have improved the certification testing to catch these types of problems - so its becoming less of a issue now days).

Regardless, the following sections will provide information on how to add a new device to the manufacturer\_specific.xml file and in the case of point 2 & 3 above, how to create configuration files for that device.

## Adding the Device Name to the Database ##

This is the simplest instruction and basically requires you to obtain the Manufacturer ID, Product type and Product ID.

  * **Manufacturer ID** - first, check if the Manufacturer is already defined in the manufacturer\_specific.xml file. This would indicate that we already have added that manufacturer to the database, and thus nothing else is required. We try to keep the file organised alphabetically by Manufacturer, so just scrolling through should reveal it quick.

> A Manufacturer entry looks like this:
```
 <Manufacturer id="002a" name="3e Technologies">
     ...
 </Manufacturer>
```
> If the manufacturer does not exist, please try to find the manufacturer ID. This can either be present in the device documentation, the [pepper1 database](http://www.pepper1.net/zwavedb/) or the zwcfg`_*`.xml config file.

  * **Product Type and Product ID** - This two numbers help identify the actual product. Again, this information can be found usually in the device manual, [pepper1 database](http://www.pepper1.net/zwavedb/), [Z-Wave Alliance Product Database](http://products.z-wavealliance.org/) and the zwcfg file.
> A Basic Product Entry looks like this:
```
 <Product type="4349" id="3130" name="ZCS101 Serial Interface"/>
```

> When specifying the name, please use the use the following format:

> _<Manufacturer Product Code> <Manufacturer Product Description>_

> The Product Code is usually something that the manufacturer uses to identify the device, in the example above, ACT use ZCS101 as the product code. They also refer to the device as a "Serial Interface".

> Please try to keep the entry as short as possible, as longer entries will not format so well on application/gui screens. Also, we currently only accept English entries.

> So, if you had a new device (Say a ABC001 Z-Wave Widget) Aeon Labs, with a Manufacturer ID of 0086, Product Type of 1234 and Product ID of 4567, you would add the following to the Manufacturer\_specific.xml file in the Aeon Labs Section:
```
 <Product type="1234" id="4578" name="ABC001 Z-Wave Widget"/>
```

> if the manufacturer didn't exist in the file, the entry would be:
```
 <Manufacturer id="0086" name="Aeon Labs">
    <Product type="1234" id="4578" name="ABC001 Z-Wave Widget"/>
 </Manufacturer>
```

  * **NOTE:** The manufacturer ID, Product Type and Product ID are entered as Hexadecimal values, so please ensure you do the right conversion if the documentation provides them as decimal.

## Adding Configuration Variables to the Database ##

> Unfortunately the Z-Wave Protocol does not allow us to discover what configuration variables the manufacturer might allow a user to change. While some variables are specified by the Command Classes, device specific variables are not, and the protocol allows the manufacturer to implement there own configuration variables. These variables often allow the user to modify the behaviour of a device, or change the default command classes that a device might advertise.

> These variables are usually documented in the device manual, so to add them to OZW, you must interpret them and create a device configuration file.

> Device Configuration files are placed under the config directory, in subdirectories according to a the manufacturer name. If no subdirectory for a manufacturer exists, there is no strict naming guideline, other than it should be short and easy to determine which manufacturer it represents.

> Likewise, the naming of a configuration file is also not important, but general guideline is to use the Product Code a manufacturer might use to identify their device. (in the example above, it would be ABC001.xml in the aeon\_labs subdirectory)

> A empty configuration file looks like this, ready to add Configuration Variables: (you can copy this into a empty file to get started)
```
1 <?xml version="1.0" encoding="utf-8"?>
2 <Product xmlns='http://code.google.com/p/open-zwave/'>
3  <!-- Configuration Parameters -->
4  <CommandClass id="112">
5  ...
6  </CommandClass>
7  <!-- Association Groups -->
8  <CommandClass id="133">
9    <Associations num_groups="X">
10   ...
11   </Associations>
12  </CommandClass>
13 </Product>
```

> Description:
  * Line 1 - Specify the Encoding for the xml file.
  * Line 2 - Specify this is a Product Configuration Block
  * Line 4 - Specifies all the entries from here to Line 6 are specific to  CommandClass 112 - Which in this case is the Configuration CommandClass.
  * Line 8 - Specifies all the entries from here to Line 12 are specific to CommandClass 133 - in this case, the Association CommandClass.
  * Line 9 to 11 - Allows you to assign friendly names to Association Groups present on the device (normally the device identifies Association groups by numbers. num\_groups specifies the number of groups the device supports

> After creating the configuration file, you need to associate it with a device. Edit the manufacturer\_specific.xml file, and locate the Product line that is applicable to your device (or you added in the step above) and modify it so it points to the config file:
```
<Product type="0002" id="001c" name="Home Energy Meter G2" config="aeon_labs/hemg2.xml"/>
```

In the above example, we added a entry called "config" that points to the relative location of the config file we are creating
### Configuration Variable Types ###

In Z-Wave, there are several different types of variables that can be added. At the most basic level, its either integer or list based. The following section will describe in more detail the different types, and some guidance on using them.

The actual types are:
  * **bool** - The bool type is a Boolean type, or simply either true/false, on/off or 1/0
  * **byte** - A byte can represent a number from 0 to 255 (or 0x00 to 0xFF)
  * **decimal** - A decimal is a fractional number, eg, 25.5. Could also be referred to as a float or double.
  * **int** -  A integer can represent a number from 0 to 4294967295
  * **list** - A list of possible string values, with each string value identified by a number
  * **short** - A Short can represent a number from 0 to 65535
  * **string** - A String - Not often used for Config Variables.
  * **raw** - The value, represented as a series of bytes. Unbounded by the OZW in length, but the device might impose some upper limits. Should not be used unless advised by a developer.

When creating a new configuration value, you will have to determine the correct type to use by consulting the device documentation. Often a incorrect type will mean that the variable will not work. (either setting it, or reading it) so some testing might be required.

### Adding a new Configuration Variable ###

> A number of parameters need to be provided when adding a new configuration variable. For all types except list, the syntax of a configuration variable is as follows:
```
1    <Value type="A" index="B" genre="config" label="C" units="D" min="E" max="F" value="G">
2      <Help>
3        H
4      </Help>
5    </Value>
```

> Description:
  * Line 1 - This defines the Variable Parameters as follows:
    * _type_ This is the variable type as defined above.
    * _index_ This is the position of the Variable on the device. The device manual should specify the variable index
    * _genre_ This will always be config
    * _label_ a Short descriptive name for the Variable
    * _units_ a short description of what the variable represents. Examples might be "watts" for a energy meter, or "%" if it represents a percentage. If there is no logical unit for the variable, you can specify it as blank (eg, "")
    * _min_ The minimum value that is accepted
    * _max_ the maximum value that is accepted
    * _value_ the default value of the variable.
  * Line 2 to 4 - This is help text that describes what the Configuration Item does. in most cases, you should copy verbatim from the device manual (assuming its in English) but sometimes you should also add additional information about how to structure a value if needed (see below for more info)

> To create a variable type of List, the following syntax is used:
```
1    <Value type="list" index="B" genre="config" label="C" units="D" min="E" max="F" value="G" size="H">
2      <Help>
3      ...
4      </Help>
5      <Item label="I" value="J" />
6      <Item label="K" value="L" />
7      ...
8    </Value>
```

> Description:
  * Line 1 - This defines the Variable Parameters as follows:
    * _type_ is always "list"
    * _index_ This is the position of the Variable on the device. The device manual should specify the variable index
    * _genre_ This will always be config
    * _label_ a Short descriptive name for the Variable
    * _units_ a short description of what the variable represents. Examples might be "watts" for a energy meter, or "%" if it represents a percentage. If there is no logical unit for the variable, you can specify it as blank (eg, "")
    * _min_ The minimum value that is accepted
    * _max_ the maximum value that is accepted. Max should be equal to the largest value specified in the Item block.
    * _value_ the default value of the variable. Should equal a valid value in the Item Block
    * _size_ Specify the size of the value in bytes.
  * Line 2 to 4 - This is help text that describes what the Configuration Item does. in most cases, you should copy verbatim from the device manual (assuming its in English) but sometimes you should also add additional information about how to structure a value if needed (see below for more info)
  * Lines 5 to 7 - Each Item entry specifies a individual option and its corresponding value. Value must be a numerical digit, who's size would not exceed the storage space specified in the size parameter. label is a string, and you should keep this as short as possible.

> If you had multiple Configuration Variables to add, you would just repeat the above snippet inside the `<CommandClass id="112">` block of the configuration file.

There are a few other Variable Parameters available as well:
  * read\_only - True/False - If the value is a read only value (meaning the user can't change it.
  * write\_only - true/false - if the value is not readable. A example might be a "reset to defaults" configuration value.



### Example ###

> If we take the Manual for a Aeon Labs Home Energy Meter ([Here](http://ozw.my-ho.st/Aeon/Engineering%20Spec%20-%20Aeon%20Labs%20Home%20Energy%20Meter%282nd%20Edition%29.pdf)) as a example, Section 5.2 Lists the configuration Variables. Parameter's number 3 and 4 would look like:
```
    <Value type="list" index="3" genre="config" label="Power changed" units="" min="0" max="1" value="0" size="1">
      <Help>
        Automatic report only when power is changed.
      </Help>
      <Item label="Disable" value="0" />
      <Item label="Enable" value="1" />
    </Value>
    <Value type="short" index="4" genre="config" label="Wattage Threshold" units="watts" value="50">
      <Help>
        Threshold change in wattage to induce a automatic report (whole HEM).
      </Help>
    </Value>
```

> For Parameter 3 (index 3) we could have also implemented it as a bool type as well, but doing as a list was also valid.

> (The entire config file for this device can be viewed [Here](http://code.google.com/p/open-zwave/source/browse/trunk/config/aeon_labs/hemg2.xml)

> This config file also demonstrates a more complex configuration entry where individual bits enable/disable certain features:
```
    <Value type="int" index="101" genre="config" label="Group 1 Reports" units="" value="0">
      <Help>
        Which reports need to send in group1. Format is as follows:
        Byte 1 (msb): Reserved
        Byte 2: Reserved
        Byte 3: Bit 7: reserved
                Bit 6: reserved
                Bit 5: Auto Send Meter Report (for kWh) at the group time interval (Clamp 3)
                Bit 4: Auto Send Meter Report (for kWh) at the group time interval (Clamp 2)
                Bit 3: Auto Send Meter Report (for kWh) at the group time interval (Clamp 1)
                Bit 2: Auto Send Meter Report (for watts) at the group time interval (Clamp 3)
                Bit 1: Auto Send Meter Report (for watts) at the group time interval (Clamp 2)
                Bit 0: Auto Send Meter Report (for watts) at the group time interval (Clamp 1)
        Byte 4 (lsb): Bit 7: reserved
                Bit 6: reserved
                Bit 5: reserved
                Bit 4: reserved
                Bit 3: Auto Send Meter Report (for kWh) at the group time interval (whole HEM)
                Bit 2: Auto Send Meter Report (for watts) at the group time interval (whole HEM)
                Bit 1: Auto Send Multilevel Sensor Report (for watts) at the group time interval (whole HEM)
                Bit 0: Auto Send Battery Report at the group time interval (whole HEM)
      </Help>
    </Value>
```

> In this case, please ensure that the help text describes the function of each bit (as above example does) to help users. There is a plan to implement a new Value Type called bitset that would simply reading/writing individual bits. You can track its progress at [issue 290](https://code.google.com/p/open-zwave/issues/detail?id=290))

#### Association Groups ####

> Association groups are a fundamental part of Z-Wave that allow automatic reporting of state changes back to OZW, or to allow one device to control another device. A proper understanding of Association Groups is a good idea (but outside the scope of this document). In essence, a device will usually have at least one association group. When the state changes on that device, it sends a "Report" message to all nodes listed in the relevant Association Group.

> The Configuration File allows you to specify:
  1. A Name to each association group the device supports
  1. a option to enable OZW to automatically add the Controller Node to that particular Association Group to receive updates.

An Example is below:
```
1    <CommandClass id="133">
2      <Associations num_groups="2">
3        <Group index="1" max_associations="5" label="Door Sensor" auto="true"/>
4        <Group index="2" max_associations="5" label="PIR Sensor" auto="true" />
5      </Associations>
6    </CommandClass>
```

> Description:
  * Line 1 - Specifies the Following Block is for CommandClass 133 (Association CC)
  * Line 2 - The following option is available:
    * _num\_groups_ is the number of Association Groups the device supports. There should be a equal number of Group Entries.
  * Line 3 to 4 - This is a list of each Group.
    * _index_ indicates the group number
    * _max`_`associations_ is the maximum number of Nodes that can be added to this group.
    * _label_ a friendly description of the Group
    * _auto_ if the Controller Node should automatically be added to this group for reporting. Generally you should set this to true, unless another group that has auto set to true reports the same information.

> If the device had a Generic Group where all state changes are reported to, then you would set auto equal to true. If it had further groups where only specific events (that are already sent in the generic group) are reported, you should not set auto to true here, otherwise OZW will recieve 2 messages (one from each group) when a state change happens.


### Fixing Device Incompatibilities/Bugs ###

> In some cases, some devices have firmware bugs, or the manufacturer has implemented a feature in a "non-standard" way. Where possible, we have implemented workarounds for these issues and they sometimes need to be enabled for individual devices.

> In these cases, after creating a Device Configuration, but things do not appear to be working correctly, you can ask for help on the mailing list. Should we determine its a non-standard implementation, we will advise you what to add to the Config file to test.


## Testing ##

> After you have made your changes to the manufacturer\_specific.xml file, and any device specific configuration file, to test your changes work you can do the following:

  1. run `make xmltest` from the top level directory. This will just check the syntax of the configuration files is correct and you do not have any formating errors.
  1. remove (or backup) any zwcfg`_*`.xml file and restart your application.
  1. after its restarted, check each configuration value you added, to ensure you can change a value, and the device responds appropriately. If you had added additional Association Groups, you should also check if the group names are reflected, as well as if the Controller has been added if auto is equal to true.

## Submitting your Changes to use ##

> Finally, after you have tested your changes, and would like to submit the new device configuration to us, you can perform the following steps:
  1. if you had checked out a copy of OZW from our Subversion repository, from the top directory, run the following command:
```
svn diff > <devicename>.patch
```
> where `<devicename>` is a short name of your device. Create a issue on our bug tracker and attach the `<devicename>`.patch file to the bug tracker. We will add it to our code repository soon.

  1. if you had downloaded a copy of our stable/snapshot releases, then just create a new issue on our bug tracker, listing the Manufacturer, Product Type, Product ID, Product Name, and attach any configuration file you had created.

> We will review your config file, and possibly make some minor changes. we might ask you to perform some additional testing with your device if we had to fix anything up, and the whole community would be grateful for your testing.

> If you have any additional questions, you can always post them to our mailing list