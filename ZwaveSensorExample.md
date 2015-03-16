# The Setup #
This example shows how to use the open-zwave example program, an Aeon Labs Z-Stick S2, and a Home Manageables HM-DW001 Door/Window sensor.  The process should be pretty similar for most other sensors.

# How it Works #
First include your sensor with your Z-Stick controller by pressing the big button on it while it's unplugged, pressing the button on the back of the sensor, then pressing the big button on the Z-Stick again to get out of inclusion mode.

Build the open-zwave library and see the example program in examples/YOUR\_PLATFORM/MinOZW.  Plug in your Z-Stick to the computer and look at the device name it comes up with (e.g., on Linux something like /dev/ttyUSB0). Find the line in Main.cpp that looks like:
```
    Manager::Get()->AddDriver( "THE_DEVICE_NAME" );
```
and modify it if necessary.

Build and run the MinOZW example, push the button on the sensor to force it to report into the controller, then look in a file called zwcfg\_0xYOUR\_HOMEID.xml. In that file you should see a Node tag for your controller and another for your sensor. You should see COMMAND\_CLASS\_ASSOCIATION and a Group 1 tag somewhere under your sensor's Node tag, which indicate that the sensor supports a special group-based callback mechanism for reporting its status.

Now open up Main.cpp again and find a line that says:
```
    case Notification::Type_NodeAdded:
```
Before the "break;" in that block, add a line that says:
```
    Manager::Get()->AddAssociation(nodeInfo->m_homeId, nodeInfo->m_nodeId, 1, 1);
```
> _Note: this is too early in the code, so it will only work the **second** time OZW detects your sensor. You might as well just put it in the main thread until I find a better place for it._
Rebuild the example program, run it, and push the button on the back of your sensor again. If everything worked correctly, you should now be getting log messages immediately every time your sensor changes state.