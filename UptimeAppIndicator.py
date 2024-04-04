##!/usr/bin/env python

import gtk
import appindicator
import logging 
import os

# Set up logging
log_file = os.path.expanduser('~/.local/share/UptimeAppIndicator.log')
logging.basicConfig(filename=log_file, level=logging.ERROR, format='%(asctime)s %(message)s')

def get_uptime():
    try:
        with open('/proc/uptime', 'r') as f:
            uptime_seconds = float(f.readline().split()[0])
            hours, remainder = divmod(uptime_seconds, 3600)
            minutes, seconds = divmod(remainder, 60)
            uptime_string = "{:02}:{:02}".format(hours, minutes)
        return uptime_string
    except IOError:
        logging.error("Error: Unable to read /proc/uptime")
        return "Error: Unable to read /proc/uptime"
    except ValueError:
        logging.error("Error: Unable to parse uptime")
        return "Error: Unable to parse uptime"

def exit_item(_):
    gtk.main_quit()

if __name__ == "__main__":
    try:
        ind = appindicator.Indicator("uptime_indicator", "indicator-messages", appindicator.CATEGORY_APPLICATION_STATUS)
        ind.set_status(appindicator.STATUS_ACTIVE)
        ind.set_label(get_uptime(), "")

        # create a menu
        menu = gtk.Menu()

        # create some 
        exit = gtk.MenuItem('Exit')
        exit.connect('activate', exit_item)
        exit.show()
        menu.append(exit)

        ind.set_menu(menu)

        gtk.timeout_add(60000, lambda: ind.set_label(get_uptime(), ""))

        gtk.main()
    except ImportError:
        logging.error("Error: Unable to import necessary libaries")