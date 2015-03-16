# Introduction #

We will try to answer common questions and issues here in this FAQ.


# User Related #

## I have a Device that is "unknown" in OpenZWave ##

In OZW we maintain a [Device\_Database](Device_Database.md) of all Devices that have been tested and work with OZW. Its possible your device is a new device we have not come across yet. Depending upon how conform-ant the device is to the Z-Wave Spec and how configurable it is, Adding the device to our database can be a simple one line change, to adding a complex xml file describing the devices configuration and quirks.

For instructions on adding devices, please consult this [page](Adding_Devices.md)

## I remove my ZWave USB Dongle and my PC starts using 100% CPU ##

This is a known issue - You can track updates at [issue 111](https://code.google.com/p/open-zwave/issues/detail?id=111)

## Sometimes when a perform a action in my Application, it takes anywhere from several seconds to several minutes before the device response ##

This can be caused by a number of issues:

1) you should ensure that OZW has fully started up. During the startup phase, OZW can be busy querying the capabilities and latest values from nodes. OZW has probably received your command, but has queued it up to be sent out, and the reason it takes a while, is your command would most likely be at the end of the Queue. You should ensure that OZW has fully started up (in our Code we emit at AllNodesQueried(_SomeFailed/_asleep) Notification that indicates OZW is ready for "normal" operations. Trying to do anything before that can take a while.

We are investigating reducing this startup time (or eliminating it completely), but this might take a while todo.


2) Your Network might have what I term "unhealthy" devices. When I say unhealthy, I mean that devices that might have quirks in the way they support Z-Wave, and thus, often don't work reliably. The problem with this, is that these devices can "block" OZW for upto 120 seconds (by not acknowledging or sending correct replies). You can see if this is the case, by searching the OZW\_Log.txt file for "Retries" or "Timeout". If you see this happening often with a single device, you should check for updated versions of OZW (or at least the Device\_Database) to see if these quirks have been fixed, and if not, report to our Mailing List.

3) You are Polling Lots of Values - Polling should be a last resort for getting "updated" values from devices. Unlike modern Wifi, Z-Wave is a low bandwidth protocol. If you are polling to much, then you might be putting a lot of stress on your network. Polling was implemented in OZW to support devices that did not have the option to automatically report updates etc, and should only be used for those devices.

Most devices on the market now days support reporting real time updates via Associations (and in OZW, we always try to add the Controller node to these associations automatically). For other devices, that say report temperature or environmental data, most of the time, you can configure them to automatically push "updates" to your application, rather than have OZW pull the updates. You should consult the Configuration Options for your device in your application, and also consult the user manual that comes with your device to see if you can configure it.

Polling Security enabled Devices (such as door locks etc) is going to be even worse. In Secured devices, for every command we transmit, we have to exchange 2-3 additional packets before hand. Due to the tight timing requirements for the Security Class, these messages "jump the queue" so to say, and thus would starve the rest of the normal classes on OZW. (Additionally, most Security Devices, such as Door Locks are battery powered - Polling them is a great way to start investing in battery companies - As you are going to use lots of batteries)

4) The device you are attempting to talk to is Battery Powered and supports the Wakeup Class. These devices are not always listening to the network, so if you send them a command (or request a updated value), OZW can't actually transmit it till the device "wakes up". Wakeup times are generally configurable, but again at the expense of battery life. Most of these devices will wake up and send update messages when a certain action occurs (such as detecting motion) but will not accept new commands till their wakeup time expires.

Sometimes you can manually wakeup the device by hitting a button etc on the device. This might only be useful during start-up phase if you quickly want the device to wake up and appear in your application.