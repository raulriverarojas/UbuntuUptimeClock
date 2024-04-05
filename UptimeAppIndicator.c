#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_uptime(char *uptime_str) {
    FILE *uptime_file = fopen("/proc/uptime", "r");
    if (uptime_file == NULL) {
        strcpy(uptime_str, "Error: Unable to read /proc/uptime");
        return;
    }

    double uptime_seconds;
    if (fscanf(uptime_file, "%lf", &uptime_seconds) != 1) {
        strcpy(uptime_str, "Error: Unable to parse uptime");
        return;
    }

    fclose(uptime_file);

    int hours = (int)uptime_seconds / 3600;
    int minutes = ((int)uptime_seconds % 3600) / 60;

    sprintf(uptime_str, "%02d:%02d", hours, minutes);
}

void exit_item(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    AppIndicator *ind = app_indicator_new("uptime_indicator", "indicator-messages", APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status(ind, APP_INDICATOR_STATUS_ACTIVE);

    char uptime_str[100];
    get_uptime(uptime_str);
    app_indicator_set_label(ind, uptime_str, "");

    GtkWidget *menu = gtk_menu_new();

    GtkWidget *exit = gtk_menu_item_new_with_label("Exit");
    g_signal_connect(exit, "activate", G_CALLBACK(exit_item), NULL);
    gtk_widget_show(exit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), exit);

    app_indicator_set_menu(ind, GTK_MENU(menu));

    g_timeout_add(60000, (GSourceFunc)get_uptime, uptime_str);

    gtk_main();

    return 0;
}