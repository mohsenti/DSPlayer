//
// Created by mohsen on 1/8/17.
//

#include <gtk/gtk.h>
#include <string.h>
#include <iostream>

gint main(gint argc, gchar **argv) {
    GtkWidget *window;
    GtkWidget *bar;
    GdkColor color;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    bar = gtk_progress_bar_new();
    std::cout << gtk_widget_get_name(bar) << std::endl;
    auto style = gtk_style_new();
    for (int i = 0; i < 1; i++) {
        gdk_color_parse("red", &style->bg[GTK_STATE_PRELIGHT]);
    }
    gtk_widget_set_style(bar, style);
    g_object_unref(style);
    gtk_widget_modify_bg(bar, GTK_STATE_PRELIGHT, &color);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(bar), 0.5);
    gtk_container_add(GTK_CONTAINER(window), bar);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

//auto style = Gtk::Style::create();
//style->set_bg(Gtk::STATE_PRELIGHT, Gdk::Color("red"));
//progressbar->set_style(style);