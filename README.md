This is a simple AppIndicator for Ubuntu that displays the system uptime in hh:ss format. It uses a python script and the python-appindicator library to work. The time is formatted manually so time format will always be hh:mm even when hours > 23.

Installation:
The script comes with a installer script that installs the python-appindicator, moves the script to /usr/local/bin/ and adds the script to the users start app applications
This installer requires that the installer bash script to be in the same directory as the AppIndicator script.

To install:
Unzip folder
Run install.sh

