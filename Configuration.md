# Introduction #
Open-ZWave uses various configuration files in its operation. This page aims to describe what each one performs, and what, if any, options are available for the user/application develop to modify.


## Details ##

There are 3 main configuration sets within Open-ZWave. They are:

  * options.xml - Controls various aspects of how the library works
  * zwcfg files - Is a Cache of the current network configuration
  * Device Database - This is a database of zwave devices


### options.xml ###
This file is the main file users/application developers can modify to alter the behavior of Open-ZWave. It Controls various attributes such as logging, and how Open-ZWave should react to events in the ZWave Network.

More Details are at Config\_Options

### zwcfg files ###
This file is basically a cache of the current network configuration. It is created the first time Open-ZWave discovers your network and is subsequently used on future restarts to speed up the discovery of the network.

Generally, users, and application developers should never modify this file, but sometimes it might be required to delete the file, so the library can refresh the network devices and configurations.

### Device Database ###
This is a directory of various xml files, that contain descriptions of various ZWave devices and allows the library to deal with bugs or peculiarities of particular devices.

In most Cases, this just maps devices ID's to the Manufacturer and Product Name. In other cases, it sets up OpenZWave to alter the way it communicates with the device.

More Details are at Device\_Database