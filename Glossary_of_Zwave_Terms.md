**Association** - The linking together of two nodes (units) so that one node will send information to the other node automatically when a value or level changes. The node doing the sending is the source and the node receiving the information is the target node.

**Group** - Nodes/Modules that are put into a logical group will collectively operate so when a command is sent to the group such as "turn on", all the modules that are in that group will respond and turn on together. Dimmers will return to their previous level (varies from module to module), and basic binary switches will either turn on or off.


**Node** (Unit or module) - A single module entity within the Z-Wave network such as a plug in switch, light dimmer, controller. The main controller is typically node #1 and is consider also a device.

**Replicate** - To transfer or copy the setup and configuration information between a handheld Primary Controller and a Secondary Controller.

**Route** - If two devices cannot communicate due to physical distance or other radio interference, Z-Wave automatically repeats or passes the signal from one device to the next, effectively extending the range of the network by passing the request from one node to another (maximum 4 hops) . Likewise, if two devices are not within range of one another, a route can be manually assigned to the source module (the module sending the information). This essentially enables devices to communicate at long ranges since the signal is repeated or "bounced" until it reaches the receiving module.

**Scene** - To link or ’associate’ one or more modules, except that the controller stores not only the association, but also the dim level for each Module. The dim level is stored at the time that a Module is added to a scene. Consequently, when a scene is activated, the Modules will all go to their previously defined dim levels regardless of what their most recent dim level may have been. Some Modules may get brighter while others may be pre-programmed by the user to become dimmer. Because Appliance and Wall Switch Modules are switching devices without dimming capability, they will either be defined as on or off when added to a scene.

**Status Reply** - The process of a device transmitting its current state (on, off, dim, etc.) in response to an individual node or unit change command from a controller. At the present time, Z-Wave devices ONLY respond with their status to the specific controller that commanded their change. Secondly, Z-Wave devices DO NOT respond with their status when a Group or Scene command is issued.

**Driver** - Typically, each serial port device used for controlling the zwave network requires a driver to also be installed to operate the USB stick. However, some controller devices that plug into the serial port also have NO driver and will communicate with standard serial port commands such as with the ztroller.