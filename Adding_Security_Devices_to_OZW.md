# Introduction #

Devices that Support the Security Command Class expect some of their communication to be encrypted with a Network Key that is negotiated with the application (OZW) when the device is first discovered. For this reason, Security Enabled Devices must be included into your network via the application and NOT via the include buttons present on some controllers like the AEON Z-Stick II.

This Page will walk through the pre-requisites and steps to include a Security Enabled Device.

For Developers, please consult the end of this page for details on how your application should interact with OZW to perform this "Secure Inclusion"

# Pre-Requisites #

The Security Command Class is very susceptible to time-outs on your network. If you have what we will term a "unhealthy" network, then its likely you will experience problems including your device, or operating it later. Before beginning the inclusion process, please check the following and try to correct them before continuing.

  * Dead Nodes - You should ensure that all the nodes that the controller reports are alive before beginning. Any dead nodes (say a old device you threw away but never "removed" from the network should be removed. Consult your application or controller documentation on how this is performed.

  * Phantom Nodes - These are Nodes that still believe they are part of the network, but the controller does not know about them. In general, you will only get these if you have performed a Hard Reset of your controller and not added these nodes back into the network. Either perform a factory reset on these nodes or add them back to your network.

  * Z-Wave Network Timeouts - Timeouts in OZW occur when we do not receive a response form a device when sending it a packet. This often occurs during startup phase when we are discovering the devices capabilities, but can also occur during normal operations. Timeouts are often the result of a Device incorrectly advertising the command classes it supports, or due to buggy firmware. You should investigate your device and search our mailing list of possible solutions to this issue. you can quickly check for timeouts in your network by searching the OZW log file for Timeout and looking for a string similar to this:
```
Notification: Notification home 0161d480 node 19 Timeout
```

  * Reset/Remove the Device you want to add - If you previously have attempted to add the device to your network, chances are its operating in "Unsecured" mode, and needs to be reset so it can accept the Network Key. As mentioned above, in Z-Wave, the Network Key can only be negotiated with the device during the inclusion phase. For best results, you should remove the device from the Network (via your Application or Controller), and perform a factory reset on it (if available). Only after that, continue with this process.

  * Distance/Location Considerations - Unlike the Standard Inclusion Process that Z-Wave advertises where you need to ensure the controller is within very close proximity to the device being included, in OZW we implement "High Power Secure Inclusion". This means that you might be able to perform it at a bit of a distance, but the controller must still be able to directly reach the device (ie, controller on one side of the house and the device on the other side is not likely to work for Secure Inclusion (but after inclusion it should work fine) as the Inclusion Process does not take advantage of the Mesh Technology in Z-Wave. Testing of upto 10M with direct line of sight worked for us. If you are having problems discovering the device when including it via your application, try moving the controller and device a bit closer together.

  * Application Pre-Requisites - The application you use to perform the Inclusion **MUST** support at the very least adding devices. If you application does not offer this functionality, you can use a 3rd party application like Open-ZWave Control Panel to perform the Secure Inclusion and then go back to your application. Removing devices is only essential if your first attempt did not work.

# Performing Secure Inclusion #

The following steps outline what is required to perform Secure Inclusion

## Setting your Network Key ##
You must choose a 16 byte value as your network key. This will be the master key that is used to encrypt communications over the Z-Wave Network. Its a good idea to write down this Network Key somewhere safe as well, as if you loose data or the PC that your application runs on, you will have to reset all your security devices in the future.
  1. Location your options.xml file. On `*`nix platforms, this can reside in either /etc/openzwave, /usr/local/etc/openzwave or your application folder. (if options.xml exists in both the system directories and the local application folder, then best to set it on the system directory version)
  1. Open it up and towards the end of the file (assuming a recent copy of OZW is present) you should see the following commented out block:
```
  <!-- <Option name="NetworkKey" value="0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F 0x10" /> -->
```
> Uncomment it looks like this:
```
   <Option name="NetworkKey" value="0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10" />
```
> And now replace the values 0x01 to 0x10 with your own Network Key. Each Individual value can be anywhere from 0x00 to 0xFF. You **MUST** ensure that there are exactly 16 entries, separated by comma's otherwise OZW will not start-up correctly

> Save the file and move onto the next step.

## Starting the Inclusion Process ##
  1. Start up your application and let it run through the discovery process of OZW. You should not proceed to the next step till at least all the awake devices are discovered. In OZW Control Panel, this is indicated by the Status Column showing "Ready" for each **awake** device. (you can should be able to complete the process with sleeping devices but if they wake up during the inclusion of the Secure Device, you might have to restart the inclusion process again if its causes timeouts - See the [TroubleShooting](TroubleShooting.md) Section for more info.

> if your Application does not present the status of each device, watching the OZW Log file for the following message will let you know when to continue:
```
Notification: Awake Nodes Queried
```
> or
```
Node query processing complete except for sleeping nodes.
```

  1. Using your application, place your Controller into the "Add Node" mode. This is done on the OZW Control Panel by selecting "Add Device" option from the select box on the "Controller" section of the page and then hitting "Go". You should then recieve a update message saying "Pending User Action"
  1. On the Device, Hit the Include Button, or perform whatever action the Device Manual instructs you to perform for Inclusion. (Some Locks require you to enter a special code and then lock or unlock the door manually)
  1. Watch the OZW Log Files. You should see something like the following after placing your Controller into "Add Node" Mode and performing the steps on your device to include it:
```
2014-06-09 22:58:54.595 contrlr, Queuing (Controller) Add Device
2014-06-09 22:58:54.595 Add Device
2014-06-09 22:58:54.595 contrlr, Queuing (Command) AddDevice: 0x01, 0x05, 0x00, 0x4a, 0x81, 0x5f, 0x6e
2014-06-09 22:58:54.595 
2014-06-09 22:58:54.595 contrlr, Sending (Command) message (Callback ID=0x5f, Expected Reply=0x4a) - AddDevice: 0x01, 0x05, 0x00, 0x4a, 0x81, 0x5f, 0x6e
2014-06-09 22:58:54.598 contrlr,   Received: 0x01, 0x07, 0x00, 0x4a, 0x5f, 0x01, 0x00, 0x00, 0xec
2014-06-09 22:58:54.598 
2014-06-09 22:58:54.598 contrlr, FUNC_ID_ZW_ADD_NODE_TO_NETWORK:
2014-06-09 22:58:54.598 contrlr, ADD_NODE_STATUS_LEARN_READY
2014-06-09 22:58:54.598 contrlr,   Expected callbackId was received
2014-06-09 22:58:54.598 contrlr,   Expected reply was received
2014-06-09 22:58:54.598 contrlr,   Message transaction complete
2014-06-09 22:58:54.598 
2014-06-09 22:58:54.598 contrlr, Removing current message
2014-06-09 22:58:54.598 WriteNextMsg Controller nothing to do
2014-06-09 22:58:59.522   Received: 0x01, 0x07, 0x00, 0x4a, 0x5f, 0x02, 0x00, 0x00, 0xef
2014-06-09 22:58:59.522 
2014-06-09 22:58:59.522 FUNC_ID_ZW_ADD_NODE_TO_NETWORK:
2014-06-09 22:58:59.522 ADD_NODE_STATUS_NODE_FOUND
2014-06-09 22:58:59.664   Received: 0x01, 0x0e, 0x00, 0x4a, 0x5f, 0x03, 0x14, 0x07, 0x04, 0x40, 0x03, 0x80, 0x72, 0x86, 0x98, 0x5f
2014-06-09 22:58:59.665 
2014-06-09 22:58:59.665 FUNC_ID_ZW_ADD_NODE_TO_NETWORK:
2014-06-09 22:58:59.665 ADD_NODE_STATUS_ADDING_SLAVE
2014-06-09 22:58:59.665 Adding node ID 20
2014-06-09 22:59:04.671   Received: 0x01, 0x07, 0x00, 0x4a, 0x5f, 0x05, 0x14, 0x00, 0xfc
2014-06-09 22:59:04.671 
2014-06-09 22:59:04.671 FUNC_ID_ZW_ADD_NODE_TO_NETWORK:
2014-06-09 22:59:04.671 ADD_NODE_STATUS_PROTOCOL_DONE
2014-06-09 22:59:04.671 contrlr, Queuing (Command) Add Node Stop: 0x01, 0x04, 0x00, 0x4a, 0x05, 0xb4
2014-06-09 22:59:04.671 
2014-06-09 22:59:04.671 contrlr, Sending (Command) message (Callback ID=0x00, Expected Reply=0x4a) - Add Node Stop: 0x01, 0x04, 0x00, 0x4a, 0x05, 0xb4
2014-06-09 22:59:04.724 contrlr,   Received: 0x01, 0x07, 0x00, 0x4a, 0x5f, 0x06, 0x14, 0x00, 0xff
2014-06-09 22:59:04.724 
2014-06-09 22:59:04.724 contrlr, FUNC_ID_ZW_ADD_NODE_TO_NETWORK:
2014-06-09 22:59:04.724 contrlr, ADD_NODE_STATUS_DONE
```

> This indicates that the Controller has at least discovered your device and is starting the Secure Inclusion Mode. If you do not get this (Particularly the "Adding Node ID XX" message), then it means that the Controller cannot reach your device. Try moving Closer and retrying this step.
  1. A Lot of Log Messages will now scroll by. If all things go well, you should see the Status Column of the Device (if your application shows it) pause for a while on "SecurityReport", and depending upon your device, also pause a while on "Session" and "Dynamic" phases. If things are not progressing, at least check if the following SecurityReport Message has been logged (Actual contents will differ depending upon device):
```
2014-06-09 22:59:16.671 Node020,   Secured command classes for node 20:
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_ASSOCIATION (Secured)
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_BASIC (Secured)
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_BATTERY (Secured)
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_DOOR_LOCK (Secured)
2014-06-09 22:59:16.672 Node020,     Secure CommandClass 0x4c - NOT SUPPORTED
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_MANUFACTURER_SPECIFIC (Secured)
2014-06-09 22:59:16.672 Node020,     Secure CommandClass 0x4e - NOT SUPPORTED
2014-06-09 22:59:16.672 Node020,     Secure CommandClass 0x8b - NOT SUPPORTED
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_USER_CODE (Secured)
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_VERSION (Secured)
2014-06-09 22:59:16.672 Node020,   UnSecured command classes for node 20:
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_NO_OPERATION (Unsecured)
2014-06-09 22:59:16.672 Node020,     COMMAND_CLASS_SECURITY (Unsecured)
```
> If your Log Does not include such a message, then check again for any messages prior to that about Timeouts or Retries, and if they exist, post a question to the OZW Google Groups Mailing list attaching your log file and details of what device you are trying to include, etc etc

  1. Finally, If your Device Reaches the Ready Stage, then test that it works as advertised (eg, if its a lock, test that you can lock and unlock it via your application, and also test that manually locking/unlocking sends a update back)

### Thats It! ###
Your Device is now Securely Included in your network. There should be no need to perform the above steps again unless you have reset your network or removed the secure device from it. A few Questions/Answers to note though:
  1. Q: Start-Up Time in OZW has increased now! - A: Unfortunately, yes. With the Security Class, we now have to exchange 2-3 additional messages with these devices before sending the Encrypted Command. This makes for good security (its much harder for someone to sniff your network and determine keys etc) but unfortunately adds some overhead. I've noticed about a 1 second delay between issuing the command, and the device actually acting on it due to this overhead.
  1. Q: Are you going to fix the startup time? - A: Hopefully. There is some work going on to refactor our discovery code. there is no ETA on that at the moment.
  1. Q: Not all the features of my device are available: - A: That is quite possible. The initial work just focused on enabling the Security Command Class. Now that that class has been implemented, there is a whole range of additional command classes that we need to investigate and implement. Our focus initially will be the "Door Lock" and "Door Lock Logging" classes as door locks seem to be the most requested feature for OZW, and after that, we will investigate other command classes. If you have a device other than a Door Lock, and it supports the Security Command Class and some other classes that we don't implement - We would love to hear from you! Also, we should point out, that Applications that use OZW may have to update to support the Door Locks etc. This entirely depends upon how the application was created/coded etc. Best to ask the people developing your application if it will work now, or if they need to implement something.
  1. Q: I use pyopenzwave, or the dotNet wrapper or "insert your favourite language wrapper here" etc. Will the Security Command Class work with these wrappers - A: It should. There are no new Public API's that have been implemented. Most of the work is internal, but this also depends on how those language wrappers have been written. In general, as long as the wrapper supports the Manager::Get()->BeginControllerCommand call then nothing else should be required.
  1. Q: My Question isn't answered Here! - A: Post your question to https://groups.google.com/forum/#!forum/openzwave

# Developer Information #
As mentioned above, as long as your Application has implemented support to add a device, then potentially the only thing you need to worry about is implementing the new Command Classes that we will introduce now (Such as Door Lock etc). These new "Secured" Command Classes operate no differently from our standard command classes, so there is nothing special that needs to be done. (but some of the new Command Classes might implement different types of Values - Something to watch out for)

If your application does not support adding new devices to a network, then you should implement this by calling:
```
Manager::Get()->BeginControllerCommand(homeId, Driver::ControllerCommand_AddDevice,
callbackfn, context, true));
```
Make sure you enable "high power" mode (the last true arguement above) and implement whatever callbacks you need to tell your users success/failure. this method is documented at the [OZW API](http://openzwave.com/dev/classOpenZWave_1_1Manager.html#aa11faf40f19f0cda202d2353a60dbf7b) page.
An example can be found in the OZW Control Panel code, in webserver.cpp, around line 1169

We might add a additional command line tool that we will ship with OZW to perform Inclusions and Exclusions soon.