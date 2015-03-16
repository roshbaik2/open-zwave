# Introduction #

The options file allows you to fine tune the operation and logging of the Open-ZWave library. The sections below specify the various options you can set.

Please refer to the Configuration Page for more information on the various files Open-ZWave uses.

# options.xml #

An Example options.xml file is below
```
<Options xmlns='http://code.google.com/p/open-zwave/'>
  <Option name="logging" value="true" />
  <Option name="Associate" value="true" />
  <Option name="NotifyTransactions" value="false" />
  <Option name="DriverMaxAttempts" value="0" />
  <Option name="SaveConfiguration" value="true" />
</Options>
```

The Various Options you can specify are:


|UserPath|String|This is the directory location where various files created by the library are stored. Examples include the zwcfg_.xml and LogFiles_|
|:-------|:-----|:---------------------------------------------------------------------------------------------------------------|
|ConfigPath|String|This is the directory where the device database resides|
|Logging|Bool|Enable Logging in the Library or not.|
|ConsoleOutput|Bool| Enable log output to stdout (or console)|
|LogFileName|String| The Log File Name to use (will be output in the UserPath Directory|
|AppendLogFile|Bool| On Restart, should we erase old log files, or append to existing log files|
|SaveLogLevel|LogLevel|
|QueueLogLevel|LogLevel|
|DumpTriggerLevel|LogLevel|
|Associate|Bool|Automatically Associate the Control with any Groups that have be flagged by specific devices in the Device Database|
|NotifyTransactions|Bool|When a Message Transaction (via the Zwave Protocol) has been completed, receive a Code\_MsgComplete notification via the Notification Interface.|
|DriverMaxAttempts|Integer|Maximum Attempts the Library will try to Initialize the controller|
|SaveConfiguration|Bool|When Shutting Down, should the library automatically save the Network Configuration in zwcfg_.xml_|
|PollInterval|Integer|How long we should spend polling the entire network, or how long between polls we should wait. (See IntervalBetweenPolls)|
|IntervalBetweenPolls|Bool|Should the above value be how long to wait between polling the network devices, or how often all devices should be polled|
|PerformReturnRoutes|Bool|After Processing a Group Changed Notification, should we update the Return Routes Map on affected devices|
|Include|String|Specify Which Command Classes the Library will support|
|Exclude|String|Specifically Exclude Command Classes from the Library|
|SuppressValueRefresh|Bool|After a Value is Refreshed, should we send a notification to the application|
|RetryTimeout|Integer|Timeout before retrying to send a message. Defaults to 40 Seconds|
|NetworkKey|16 Byte Key|Network Key to use for Encrypting Secure Messages over the Network|
|EnableSIS|Bool|Automatically become a SUC if there is No SUC on the network|
|AssumeAwake|Bool|Assume Devices that support the Wakeup Class are awake when starting up OZW|
|RefreshAllUserCodes|Bool|Should we refresh all UserCodes in the UserCode CC when we start up |




## Log Levels ##

The Following Values can be used for the various LogLevel options above. Use the numeric value in options.xml to specify the actual log level.

|**value**|**Logging Level**|
|:--------|:----------------|
|0 |No Logging|
|1 |All Messages|
|2 |Fatal Messages Only|
|3 |Error Messages and Higher|
|4 |Warning Messages and Higher|
|5 |Alert Messages and Higher|
|6 |Info Messages and Higher|
|7 |Detailed Messages and Higher|
|8 |Debug Messages and Higher|
|9 |Protocol Information and Higher|