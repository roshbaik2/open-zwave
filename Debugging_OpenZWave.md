# Summary #

Although many parts of OpenZWave work, the library is still in "alpha" stage development.  And with a wide variety of Z-Wave devices in the market, it can sometimes be difficult to ascertain whether an issue is with existing library code, unsupported or unusual aspects of the Z-Wave device being used, or "programmer error" in the code making use of the library.  So you should not be surprised to find problems when executing the library.  This pages provides some guidance as to how to request assistance from the developers and other members of the OpenZWave group.

# Have a Problem? #

If you think you have identified a problem with the library, consider doing the following before requesting assistance from the forum.  Of course, different problem types will require different diagnostic or descriptive steps, but these can provide a good baseline for assessing the issue.

  1. Look at the code in the examples provided: MinOZW and, if you're using Windows, OZWForm.  OZWForm demonstrates a substantial portion of the library's functionality: startup, device discovery, notification handling, node value display, setting node values and polling (at least if you look at the log file (OZWlog.txt) generated.
  1. Replicate the issue, if possible, using tweaks to the MinOZW or OZWForm example programs.
  1. Provide a description of the problem (or what you're trying to accomplish) and the manufacturer/product name of the device in question.
  1. Delete any zwcfg`*`.xml files before running MinOZW or OZWForm.  This will provide a "full" execution log, including discovery of the devices on the network and each device's capabilities.
  1. Attach a copy of the OZWlog.txt file generated when MinOZW or OZWForm is run.  This can be a very helpful diagnostic tool.

We hope this helps...it will certainly facilitate getting better answers, faster.