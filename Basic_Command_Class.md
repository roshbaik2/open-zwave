# Introduction #

The Basic Command Class is primarily intended to allow devices to control each other. As the name implies, it can only convey very simple information, and does not contain information about the actual event/trigger that it controls. Unfortunately from a OZW perspective, its not really intended to integrate well into a software controller, hence its often a topic on the mailing list.

The Basic CC will often just duplicate the functionality of a another CommandClass, for instance, a Light Switch might implement the BinarySwitch CC as well as the Basic CC. Setting ValueID for the BinarySwitch CC to turn the light on can also be accomplished via the Basic CC ValueID as well. Another example might be a PIR sensor. It could report movement via the BinarySensor CC as well as the Basic CC.

There are a number of "gotcha's" you should be aware of when dealing with devices that default to using the Basic CC as below


# Basic SET messages #

Often devices allow you to add other Nodes to a association group for control purposes. OZW also adds the Controller Node to these association groups as well so we get updates on events.

Other CC's usually send a Report message when a event has happened to all nodes in that relevant Association Group

In the case of the Basic CC, it usually would send a Basic SET message instead. The reason it sends a Basic SET message is to control those other devices (eg, a PIR sensor turning on a light switch via the BASIC set message. This means the PIR sensor does not have to implement the BinarySwitch CC that the light switch supports in order to control it)

When OZW receives a Basic SET message, we translate it to a report message, and determine which "real" command class its mapped to. We then request that CommandClass to do a GET on the Values so we can get the real value of whatever changeed on that CC rather than rely on the limited information in the Basic SET/REPORT message.

There are two potential issues here:

  1. If the device is a sleeping device, although we receive the BASIC Set message, the device might be asleep still and thus our request to refresh the actual values from the CC would be queued up and only be processed when the device next awakes. This can cause some lag.
  1. If OZW was recently started up, it might not have reached the stage where the device is fully "known" to OZW (see here: [for more information](http://openzwave.com/knowledge-base/slowresponseduringstartup)). If OZW receives a Basic Set message during this time, it would not have enough information yet to map it to a real command class and thus the message is dropped without further processing.

# Recommendations #

  1. Try to use devices that allow you to configure what type of message to send to each association group. Some devices such as PIR sensors allow you to set a configuration parameter that either sends a BASIC SET or a relevant CC Report message. This would work much more cleanly in OZW (and reduce extra traffic on your network). when purchasing devices, you should check that your intended device does all you to configure this. Devices that don't often end up being very troublesome to make it work reliably.
  1. If you have just restarted your OZW based application, try waking up all the sleeping devices that support the Basic CC so the basic mapping may complete.
  1. Application Developers can also use the Basic ValueID thats exported by OZW for updates/notifications, but then you must perform your own internal mapping of that ValueID to the real Value it represents. It should be noted that the Byte that the ValueID exports from the CC has no real meaning. a PIR sensor might send 0x01, 0xFF or 0x55 when it detects movement. A temp Sensor might send the temperature in C or F. It is completely upto the device manufacturer and not standardized.