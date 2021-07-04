#include<gtk/gtk.h>
#include"get.h"
#include"list.h"
#include<stdio.h>
struct info{
struct list*a;
GtkTextBuffer *buff;
GtkTextIter* iter;
GtkWidget *entry;
};
static void enter_callback(GtkWidget*widget, GtkWidget *entry)
{	

	struct info* hi=(struct info*)entry;
	const gchar *entry_text;
	entry_text=gtk_entry_get_text(GTK_ENTRY(hi->entry));
	printf("Entry content:%s\n",entry_text);
	//gtk_text_buffer_get_iter_at_offset(hi->buff,hi->iter,0);
	struct list*l=revokes("GET",entry_text, hi->a);
	gtk_text_buffer_set_text(hi->buff,"",-1);
	gtk_text_buffer_get_iter_at_offset(hi->buff,hi->iter,0);
	if(l==NULL)
	{
		//gtk_text_buffer_insert_with_tags_by_name(hi->buff, hi->iter,"",-1, "black_fg", NULL,NULL);
		return;
	}
	//gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,"Plain text\n",-1,"black_fg", NULL,NULL);
	printf("Start set up text buffer\n");
	gtk_text_buffer_insert_with_tags_by_name(hi->buff, hi->iter,l->body->content,-1, "black_fg", NULL,NULL);
	//gtk_text_buffer_apply_tag(hi->buff, "black_fg",NULL,NULL);
	printf("Finish set up text buffer\n");
	//*(hi->iter)=0;
    //pop_front_list(l);
    //pop_front_list(l);
    pop_front_list(hi->a);
    pop_front_list(hi->a);
	printf("Start empty node\n");
    if(l->body)
    	empty_node(l->body);
    printf("empty node OK\n");

	

}
int main(void)
{
	struct list* l=create_list();
    initialize_list(l);
	default_host(l);
	 //struct list *c;

	GtkWidget *window;
	gtk_init(NULL,NULL);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(GTK_WIDGET(window), 1200, 800);
	gtk_window_set_title(GTK_WINDOW(window), "simple web browser~");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit),NULL);

	GtkWidget *vbox;
	vbox=gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show(vbox);



	GtkWidget *entry;
	entry=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry),250);
	//g_signal_connect_swapped(window,"delete-event", G_CALLBACK(gtk_widget_destroy),window);
	GdkColor color;
	//gdk_color_parse("red", &color);
	gdk_color_parse("white", &color);
	//gtk_widget_modify_fg(GTK_WIDGET(entry), GTK_STATE_NORMAL, &color);
	//gtk_widget_modify_bg(GTK_WIDGET(entry), GTK_STATE_NORMAL, &color);
	//gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);
	//gtk_widget_modify_text(entry, GTK_STATE_NORMAL, &color);
	//gtk_container_add(GTK_CONTAINER(window),entry);
	gtk_box_pack_start(GTK_BOX(vbox),entry,FALSE,FALSE,0);
//##########  Fail, can't modify the background color of entry ###############
//
//	gdk_color_parse("yellow", &color);
//	gtk_widget_modify_bg(GTK_WIDGET(vbox), GTK_STATE_NORMAL, &color);
	GtkWidget * show_text=gtk_text_view_new();
//	gtk_widget_modify_bg(GTK_WIDGET(show_text), GTK_STATE_NORMAL, &color);
	gtk_widget_modify_base(GTK_WIDGET(show_text), GTK_STATE_NORMAL,&color);
	
	gtk_box_pack_start(GTK_BOX(vbox),show_text,TRUE,TRUE,0);
	GtkTextBuffer *buffer;
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(show_text));
	gtk_text_buffer_create_tag(buffer, "black_fg","foreground","black",NULL);

	GtkTextIter iter;
	//gtk_text_buffer_get_iter_at_offset(buffer,&iter,0);
	//gtk_text_buffer_insert(buffer, &iter,"Plain text\n",-1);
	//gtk_text_buffer_insert_with_tags_by_name(buffer, &iter,"Plain text\n",-1,"black_fg", NULL,NULL);
	struct info hi;
	hi.a=l;
	hi.buff=buffer;
	hi.iter=&iter;
	hi.entry=entry;
	//g_signal_connect(entry,"activate", G_CALLBACK(enter_callback),entry);
	g_signal_connect(entry,"activate", G_CALLBACK(enter_callback),(GtkWidget *)&hi);
//	gtk_widget_show(vbox);
	gtk_widget_show(entry);
	gtk_widget_show(show_text);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
