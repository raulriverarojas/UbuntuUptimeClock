#!/bin/bash

#Exit on error and log errors
set -e
trap 'echo "Error on line $LINENO" >> installer_errors.log' ERR
# Install necessary packages
sudo apt-get install -y python-appindicator

# Copy Python script to /usr/local/bin
if [ -f /usr/local/bin/UptimeAppIndicator.py ]; then
    echo "UptimeAppIndicator.py already exists in /usr/local/bin/, overwriting..."
fi
sudo cp UptimeAppIndicator.py /usr/local/bin/

# Make the script executable
sudo chmod +x /usr/local/bin/UptimeAppIndicator.py

# Kill running UptimeAppIndicator.py if it exists
if pgrep -f UptimeAppIndicator.py > /dev/null
then
    echo "UptimeAppIndicator.py is already running, killing it..."
    pkill -f UptimeAppIndicator.py
fi

#Run the script
/usr/local/bin/UptimeAppIndicator.py &
echo "UptimeAppIndicator.py started"

# Add script to startup applications
mkdir -p ~/.config/autostart
if [ ! -f ~/.config/autostart/UptimeAppIndicator.desktop ]; then
    cat > ~/.config/autostart/UptimeAppIndicator.desktop << EOF
[Desktop Entry]
Type=Application
Exec=/usr/local/bin/UptimeAppIndicator.py
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name[en_US]=Uptime AppIndicator
Name=Uptime AppIndicator
Comment[en_US]=
Comment=
EOF
fi