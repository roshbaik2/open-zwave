# Style #

Everyone has their own style when writing code - indentation, the use of whitespace and the positioning of braces can be contentious issues.

There is no "right" way to lay out code, but when working as part of a team or collaboration, it is important that everyone follow the same style as far as possible, in order to maximize the readability of the code for others.

If you contribute to OpenZWave, we ask that you respect the existing style of the code, refrain from reformatting code into their own style and do not start debates on our coding style in the discussion group.



# Adding/Deleting files #

If you are adding/deleting any files (xml, c++ files, header files) and those files should be included in any tar.gz or zip file distribution the follow the following commands:
  1. create/move the new file into place and test your builds
  1. svn add "newfile"
  1. make dist-update from the root directory
  1. svn commit -m "whatever message"

# Snapshot releases #

Snapshot releases (http://www.openzwave.com/snapshots/ are built automatically after each commit to the repository. A Build server at http://bamboo.my-ho.st/bamboo/ does a test compile and runs the "make test" target. If it compiles, and all tests pass (currently only xmllint tests on the config files) then the tar.gz. and zip source files are uploaded to the snapshots directory of the webserver.

The distribution packages are then triggered, and it could take anywhere from 30 minutes to several days for them to be updated. (they are built on a private instance of OpenBuildServer which has other packages it also handles so its load can be high at times).

if any distribution package fails to update, its possible that the packaging failed for that distro. Contact Justin so he can check the logs.

Also, the Doxygen documentation on http://www.openzwave.com/dev/ is also automatically updated with each new commit to the repository. Again, it could take anywhere from 30 minutes to several days to be updated though.

# Full Releases #

Full Releases are still somewhat manual as far as the source and distribution packages are concerned.
  1. you should update version numbers in cpp/build/support.mk file, (VERSION\_MAJ and VERSION\_MIN - Revision is automatically pulled from the svn repository).
  1. Update the cpp/build/windows/winversion.ini and winversion.tmpl (ini file is used when we can find TortiseSVN in the system - tmpl is used when its not present).
  1. Update the version number in openzwave.spec file (Look for Version: 1.1.730 and replace with 1.2.0 - the last revision number will automaticlally be pulled from the svn repository when the packages are built)
  1. update the openzwave.dsc and debian/ files for your new version.
  1. commit your changes then tag the release:
> svn copy https://open-zwave.googlecode.com/svn/trunk/ https://open-zwave.googlecode.com/svn/tags/Rel-1.2
  1. Contact Justin to update the build server, and trigger the release builds.