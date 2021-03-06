#ifdef HAVE_CONFIG_H
# include "elementary_config.h"
#endif
#include <Elementary.h>
#ifndef ELM_LIB_QUICKLAUNCH
static void
my_entry_bt_1(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_object_text_set(en, "");
}

static void
my_entry_bt_2(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_object_text_get(en);
   printf("ENTRY:\n");
   if (s) printf("%s\n", s);
   printf("ENTRY PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_entry_bt_3(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_entry_selection_get(en);
   printf("SELECTION:\n");
   if (s) printf("%s\n", s);
   printf("SELECTION PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_entry_bt_4(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_entry_insert(en, "Insert some <b>BOLD</> text");
}

static void
my_entry_bt_5(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_scrollable_set(en, !elm_entry_scrollable_get(en));
}

static void
my_entry_bt_6(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   static Elm_Wrap_Type wr = ELM_WRAP_NONE;

   wr++;
   if (wr == ELM_WRAP_LAST) wr = ELM_WRAP_NONE;
   printf("wr: %i\n", wr);
   elm_entry_line_wrap_set(en, wr);
}

void
test_entry(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *bx2, *bt, *en;
   char buf[4096];

   win = elm_win_util_standard_add("entry", "Entry");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   en = elm_entry_add(win);
   elm_entry_line_wrap_set(en, ELM_WRAP_NONE);
   snprintf(buf, sizeof(buf),
            "This is an entry widget in this window that<br/>"
            "uses markup <b>like this</> for styling and<br/>"
            "formatting <em>like this</>, as well as<br/>"
            "<a href=X><link>links in the text</></a>, so enter text<br/>"
            "in here to edit it. By the way, links are<br/>"
            "called <a href=anc-02>Anchors</a> so you will need<br/>"
            "to refer to them this way.<br/>"
            "<br/>"

            "Also you can stick in items with (relsize + ascent): "
            "<item relsize=16x16 vsize=ascent href=emoticon/evil-laugh></item>"
            " (full) "
            "<item relsize=16x16 vsize=full href=emoticon/guilty-smile></item>"
            " (to the left)<br/>"

            "Also (size + ascent): "
            "<item size=16x16 vsize=ascent href=emoticon/haha></item>"
            " (full) "
            "<item size=16x16 vsize=full href=emoticon/happy-panting></item>"
            " (before this)<br/>"

            "And as well (absize + ascent): "
            "<item absize=64x64 vsize=ascent href=emoticon/knowing-grin></item>"
            " (full) "
            "<item absize=64x64 vsize=full href=emoticon/not-impressed></item>"
            " or even paths to image files on disk too like: "
            "<item absize=96x128 vsize=full href=file://%s/images/sky_01.jpg></item>"
            " ... end."
            , elm_app_data_dir_get()
            );
   elm_object_text_set(en, buf);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clr");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_1, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Prnt");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_2, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Sel");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_3, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Ins");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_4, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Scrl");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_5, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Wr");
   evas_object_smart_callback_add(bt, "clicked", my_entry_bt_6, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   elm_object_focus_set(en, EINA_TRUE);
   evas_object_show(win);
}

static void
my_scrolled_entry_bt_1(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_object_text_set(en, "");
}

static void
my_scrolled_entry_bt_2(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_object_text_get(en);
   printf("ENTRY:\n");
   if (s) printf("%s\n", s);
   printf("ENTRY PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_scrolled_entry_bt_3(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_entry_selection_get(en);
   printf("SELECTION:\n");
   if (s) printf("%s\n", s);
   printf("SELECTION PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_scrolled_entry_bt_4(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_entry_insert(en, "Insert some <b>BOLD</> text");
}

static void
my_scrolled_entry_bt_5(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_object_text_get(en);
   printf("PASSWORD: '%s'\n", s ? s : "");
}

static void
scrolled_anchor_test(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_entry_insert(en, "ANCHOR CLICKED");
}

void
test_entry_scrolled(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *bx2, *bt, *en, *en_p, *sp;
   static Elm_Entry_Filter_Accept_Set digits_filter_data, digits_filter_data2;
   static Elm_Entry_Filter_Limit_Size limit_filter_data, limit_filter_data2;

   win = elm_win_util_standard_add("entry-scrolled", "Entry Scrolled");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   /* disabled entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_object_text_set(en, "Disabled entry");
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_object_disabled_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   /* password entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_password_set(en, EINA_TRUE);
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_object_text_set(en, "Access denied, give up!");
   elm_object_disabled_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   /* multi-line disable entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
   elm_object_disabled_set(en, EINA_TRUE);
   elm_entry_context_menu_item_add(en, "Hello", NULL, ELM_ICON_NONE, NULL, NULL);
   elm_entry_context_menu_item_add(en, "World", NULL, ELM_ICON_NONE, NULL, NULL);
   elm_object_text_set(en,
                       "Multi-line disabled entry widget :)<br/>"
                       "We can use markup <b>like this</> for styling and<br/>"
                       "formatting <em>like this</>, as well as<br/>"
                       "<a href=X><link>links in the text</></a>,"
                       "but it won't be editable or clickable.");
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   sp = elm_separator_add(win);
   elm_separator_horizontal_set(sp, EINA_TRUE);
   elm_box_pack_end(bx, sp);
   evas_object_show(sp);

   /* Single line selected entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "This is a single line");
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_entry_select_all(en);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   /* Only digits entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "01234");
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   digits_filter_data.accepted = "0123456789";
   digits_filter_data.rejected = NULL;
   elm_entry_markup_filter_append(en, elm_entry_filter_accept_set, &digits_filter_data);

   /* No digits entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "No numbers here");
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   digits_filter_data2.accepted = NULL;
   digits_filter_data2.rejected = "0123456789";
   elm_entry_markup_filter_append(en, elm_entry_filter_accept_set, &digits_filter_data2);

   /* Size limited entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "Just 20 chars");
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   limit_filter_data.max_char_count = 20;
   limit_filter_data.max_byte_count = 0;
   elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data);

   /* Byte size limited entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_object_text_set(en, "And now only 30 bytes");
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   limit_filter_data2.max_char_count = 0;
   limit_filter_data2.max_byte_count = 30;
   elm_entry_markup_filter_append(en, elm_entry_filter_limit_size, &limit_filter_data2);

   /* Single line password entry */
   en_p = elm_entry_add(win);
   elm_entry_scrollable_set(en_p, EINA_TRUE);
   evas_object_size_hint_weight_set(en_p, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en_p, EVAS_HINT_FILL, 0.5);
   elm_scroller_policy_set(en_p, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_object_text_set(en_p, "Password here");
   elm_entry_single_line_set(en_p, EINA_TRUE);
   elm_entry_password_set(en_p, EINA_TRUE);
   evas_object_show(en_p);
   elm_box_pack_end(bx, en_p);

   /* entry with icon/end widgets*/
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   bt = elm_icon_add(win);
   elm_icon_standard_set(bt, "home");
   evas_object_size_hint_min_set(bt, 48, 48);
   evas_object_color_set(bt, 128, 0, 0, 128);
   evas_object_show(bt);
   elm_object_part_content_set(en, "icon", bt);
   bt = elm_icon_add(win);
   elm_icon_standard_set(bt, "delete");
   evas_object_color_set(bt, 128, 0, 0, 128);
   evas_object_size_hint_min_set(bt, 48, 48);
   evas_object_show(bt);
   elm_object_part_content_set(en, "end", bt);
   elm_object_text_set(en, "entry with icon and end objects");
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   /* markup entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_ON, ELM_SCROLLER_POLICY_ON);
   elm_object_text_set(en,
                       "This is an entry widget in this window that<br/>"
                       "uses markup <b>like this</> for styling and<br/>"
                       "formatting <em>like this</>, as well as<br/>"
                       "<a href=X><link>links in the text</></a>, so enter text<br/>"
                       "in here to edit it. By them way, links are<br/>"
                       "called <a href=anc-02>Anchors</a> so you will need<br/>"
                       "to refer to them this way. At the end here is a really long "
                       "line to test line wrapping to see if it works. But just in "
                       "case this line is not long enough I will add more here to "
                       "really test it out, as Elementary really needs some "
                       "good testing to see if entry widgets work as advertised.");
   evas_object_smart_callback_add(en, "anchor,clicked", scrolled_anchor_test, en);
   evas_object_show(en);
   elm_box_pack_end(bx, en);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clear");
   evas_object_smart_callback_add(bt, "clicked", my_scrolled_entry_bt_1, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Print");
   evas_object_smart_callback_add(bt, "clicked", my_scrolled_entry_bt_2, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Print pwd");
   evas_object_smart_callback_add(bt, "clicked", my_scrolled_entry_bt_5, en_p);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Selection");
   evas_object_smart_callback_add(bt, "clicked", my_scrolled_entry_bt_3, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Insert");
   evas_object_smart_callback_add(bt, "clicked", my_scrolled_entry_bt_4, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 320, 300);

   elm_object_focus_set(win, EINA_TRUE);
   evas_object_show(win);
}

static void
my_ent_bt_clr(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_object_text_set(en, "");
}

static void
my_ent_bt_pri(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_object_text_get(en);
   printf("ENTRY:\n");
   if (s) printf("%s\n", s);
   printf("ENTRY PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_ent_bt_sel(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char *s = elm_entry_selection_get(en);
   printf("SELECTION:\n");
   if (s) printf("%s\n", s);
   printf("SELECTION PLAIN UTF8:\n");
   if (s)
     {
        s = elm_entry_markup_to_utf8(s);
        if (s)
          {
             printf("%s\n", s);
             free((char *)s);
          }
     }
}

static void
my_ent_bt_all(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_select_all(en);
}

static void
my_ent_bt_non(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_select_none(en);
}

static void
my_ent_bt_ins(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_entry_insert(en, "Insert text");
}

static void
my_ent_bt_lef(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_prev(en);
}

static void
my_ent_bt_rig(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_next(en);
}

static void
my_ent_bt_up_(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_up(en);
}

static void
my_ent_bt_dow(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_down(en);
}

static void
my_ent_bt_beg(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_begin_set(en);
}

static void
my_ent_bt_end(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_end_set(en);
}

static void
my_ent_bt_lbe(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_line_begin_set(en);
}

static void
my_ent_bt_len(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_line_end_set(en);
}

static void
my_ent_bt_sbe(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_selection_begin(en);
}

static void
my_ent_bt_sen(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_cursor_selection_end(en);
}

static void
my_ent_bt_fmt(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   printf("IS FORMAT: %i\n",
          (int)elm_entry_cursor_is_format_get(en));
}

static void
my_ent_bt_vfm(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   printf("IS VISIBLE FORMAT %i\n",
          (int)elm_entry_cursor_is_visible_format_get(en));
}

static void
my_ent_bt_chr(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   printf("CHAR '%s'\n", elm_entry_cursor_content_get(en));
}

static void
my_ent_bt_cut(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_selection_cut(en);
}

static void
my_ent_bt_cop(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_selection_copy(en);
}

static void
my_ent_bt_pas(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_selection_paste(en);
}

static void
ent_bt_style_user_peek(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   const char* cur_style = elm_entry_text_style_user_peek(en);
   if (cur_style)
     printf("Current style user: %s\n", cur_style);
   else
     printf("Style user stack is empty.\n");
}

static void
ent_bt_style_user_pop(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_text_style_user_pop(en);
   printf("Style user popped\n");
}

void
test_entry_style_user(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *en, *bt, *bt2;

   win = elm_win_util_standard_add("entry-style", "Entry Style");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_resize(win, 300, 300);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);


   en = elm_entry_add(win);
   elm_entry_line_wrap_set(en, ELM_WRAP_MIXED);

   elm_entry_text_style_user_push(en, "DEFAULT='font_size=40 color=#FF0000'");
   elm_object_text_set(en, "Testing Text");

   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, en);
   evas_object_resize(en, 200, 200);
   evas_object_show(en);

   bt = elm_button_add(win);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(bt, "Peek");
   evas_object_smart_callback_add(bt, "clicked", ent_bt_style_user_peek, en);
   evas_object_size_hint_weight_set(bt, 0.0, 0.0);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, 0.5);
   elm_box_pack_end(bx, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt2 = elm_button_add(win);
   evas_object_size_hint_weight_set(bt2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_text_set(bt2, "Pop");
   evas_object_smart_callback_add(bt2, "clicked", ent_bt_style_user_pop, en);
   evas_object_size_hint_weight_set(bt2, 0.0, 0.0);
   evas_object_size_hint_align_set(bt2, EVAS_HINT_FILL, 0.5);
   elm_box_pack_end(bx, bt2);
   evas_object_propagate_events_set(bt2, 0);
   elm_object_focus_allow_set(bt2, 0);
   evas_object_show(bt2);

   elm_object_focus_set(en, EINA_TRUE);
   evas_object_show(win);
}

void
test_entry3(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *bx2, *bt, *en;

   win = elm_win_util_standard_add("entry3", "Entry 3");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   /* Single line selected entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_object_text_set(en, "This is a single line");
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_clr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pri");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pri, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Sel");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sel, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "All");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_all, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Non");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_non, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Ins");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_ins, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Lef");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lef, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Rig");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_rig, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Up ");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_up_, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Dow");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_dow, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Beg");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_beg, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "End");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_end, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_len, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sen, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Fmt");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_fmt, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "VFm");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_vfm, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Chr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_chr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cut");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cut, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cop");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cop, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pas");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pas, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   /* markup entry */
   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en,
                       "This is an entry widget in this window that<br/>"
                       "uses markup <b>like this</> for styling and<br/>"
                       "formatting <em>like this</>, as well as<br/>"
                       "<a href=X><link>links in the text</></a>, so enter text<br/>"
                       "in here to edit it. By them way, links are<br/>"
                       "called <a href=anc-02>Anchors</a> so you will need<br/>"
                       "to refer to them this way. At the end here is a really long "
                       "line to test line wrapping to see if it works. But just in "
                       "case this line is not long enough I will add more here to "
                       "really test it out, as Elementary really needs some "
                       "good testing to see if entry widgets work as advertised."
                      );
   evas_object_smart_callback_add(en, "anchor,clicked", scrolled_anchor_test, en);
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_clr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pri");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pri, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Sel");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sel, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "All");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_all, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Non");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_non, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Ins");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_ins, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Lef");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lef, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Rig");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_rig, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Up ");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_up_, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Dow");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_dow, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Beg");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_beg, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "End");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_end, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_len, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sen, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Fmt");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_fmt, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "VFm");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_vfm, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Chr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_chr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cut");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cut, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cop");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cop, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pas");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pas, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 320, 480);

   elm_object_focus_set(win, EINA_TRUE);
   evas_object_show(win);
}

void
test_entry4(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *ly, *en;
   char buf[PATH_MAX];

   win = elm_win_util_standard_add("entry4", "Entry 4");
   elm_win_autodel_set(win, EINA_TRUE);

   ly = elm_layout_add(win);
   snprintf(buf, sizeof(buf), "%s/objects/test.edj", elm_app_data_dir_get());
   elm_layout_file_set(ly, buf, "layout");
   evas_object_size_hint_weight_set(ly, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, ly);
   evas_object_show(ly);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, 0.5);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_object_text_set(en, "This is a single line");
   elm_entry_single_line_set(en, EINA_TRUE);
   elm_object_part_content_set(ly, "element1", en);
   evas_object_show(en);

   en = elm_entry_add(win);
   elm_entry_line_wrap_set(en, ELM_WRAP_NONE);
   elm_object_text_set(en,
                       "This is an entry widget<br/>"
                       "that uses markup<br/>"
                       "<b>like this</> and has<br/>"
                       "no scroller, so you can<br/>"
                       "use it more flexibly.");
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_part_content_set(ly, "element2", en);
   evas_object_show(en);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en,
                       "This is an entry widget in this window that<br/>"
                       "uses markup <b>like this</> for styling and<br/>"
                       "formatting <em>like this</>, as well as<br/>"
                       "<a href=X><link>links in the text</></a>, so enter text<br/>"
                       "in here to edit it. By them way, links are<br/>"
                       "called <a href=anc-02>Anchors</a> so you will need<br/>"
                       "to refer to them this way. At the end here is a really long "
                       "line to test line wrapping to see if it works. But just in "
                       "case this line is not long enough I will add more here to "
                       "really test it out, as Elementary really needs some "
                       "good testing to see if entry widgets work as advertised."
                      );
   evas_object_smart_callback_add(en, "anchor,clicked", scrolled_anchor_test, en);
   elm_object_part_content_set(ly, "element3", en);
   evas_object_show(en);

   evas_object_show(win);
}

void
test_entry5(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *bx2, *bt, *en;

   win = elm_win_util_standard_add("entry5", "Entry 5");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_entry_line_wrap_set(en, ELM_WRAP_CHAR);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en,
                       "This is an entry widget in this window that "
                       "uses markup like this for styling and "
                       "formatting like this, as well as "
                       "to refer to them this way. At the end here is a really long "
                       "line to test line wrapping to see if it works. But just in "
                       "case this line is not long enough I will add more here to "
                       "really test it out, as Elementary really needs some "
                       "good testing to see if entry widgets work as advertised."
                      );
   evas_object_smart_callback_add(en, "anchor,clicked", scrolled_anchor_test, en);
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_clr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pri");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pri, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Sel");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sel, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "All");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_all, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Non");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_non, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Ins");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_ins, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Lef");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lef, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Rig");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_rig, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Up ");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_up_, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Dow");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_dow, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Beg");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_beg, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "End");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_end, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_lbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "LEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_len, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SBe");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sbe, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "SEn");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_sen, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Fmt");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_fmt, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "VFm");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_vfm, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Chr");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_chr, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cut");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cut, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Cop");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_cop, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Pas");
   evas_object_smart_callback_add(bt, "clicked", my_ent_bt_pas, en);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_propagate_events_set(bt, 0);
   elm_object_focus_allow_set(bt, 0);
   evas_object_show(bt);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 320, 480);

   elm_object_focus_set(win, EINA_TRUE);
   evas_object_show(win);
}

void
test_entry6(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *en;

   win = elm_win_util_standard_add("entry6", "Entry 6");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_entry_line_wrap_set(en, ELM_WRAP_CHAR);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en,
                       "input_panel_enabled: TRUE.<br>"
                       "When this entry gets a focus, virtual keyboard will be shown "
                       "in illume environment.");
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_entry_line_wrap_set(en, ELM_WRAP_CHAR);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en,
                       "input_panel_enabled: FALSE.<br>"
                       "This entry doesn't allow to show virtual keyboard automatically.<br>"
                       "it is used in case that wants its own keypad such as calculator.");
   elm_entry_input_panel_enabled_set(en, EINA_FALSE);
   elm_box_pack_end(bx, en);
   evas_object_show(en);

   evas_object_resize(win, 320, 300);

   elm_object_focus_set(win, EINA_TRUE);
   evas_object_show(win);
}

static void
changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object*)data;

   elm_entry_editable_set(en, elm_check_state_get(obj));
}

static void
en_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *sp, *en;
   sp = (Evas_Object *)data;
   en = (Evas_Object *)obj;
   elm_spinner_min_max_set(sp, 0, strlen(elm_object_text_get(en)));
}

static void
sp_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en, *sp;
   en = (Evas_Object *)data;
   sp = (Evas_Object *)obj;
   elm_entry_cursor_pos_set(en, elm_spinner_value_get(sp));
   elm_object_focus_set(en, EINA_TRUE);
}

static void
add_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object *)data;

   elm_entry_context_menu_item_add(en, "item", NULL, ELM_ICON_NONE, NULL, NULL);
}

static void
clear_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object *)data;

   elm_entry_context_menu_clear(en);
}

static Evas_Object *
item_provider(void *images __UNUSED__, Evas_Object *en, const char *item)
{
   Evas_Object *o = NULL;;
   char buf[1024];

   if (!strcmp(item, "itemprovider"))
     {
        snprintf(buf, sizeof(buf), "%s/images/icon_00.png",
                 elm_app_data_dir_get());
        o = evas_object_image_filled_add(evas_object_evas_get(en));
        evas_object_image_file_set(o, buf, NULL);
     }

   return o;
}

static Evas_Object *
prepend_item_provider(void *images __UNUSED__, Evas_Object *en, const char *item)
{
   Evas_Object *o = NULL;;
   char buf[1024];

   if (!strcmp(item, "itemprovider"))
     {
        snprintf(buf, sizeof(buf), "%s/images/icon_10.png",
                 elm_app_data_dir_get());
        o = evas_object_image_filled_add(evas_object_evas_get(en));
        evas_object_image_file_set(o, buf, NULL);
     }

   return o;
}

static void
prepend_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object *)data;

   elm_entry_item_provider_prepend(en, prepend_item_provider, NULL);
   elm_object_text_set(en,
                       "Item Provider"
                       "<item size=50x50 vsize=full href=itemprovider></item>"
                      );
}

static void
remove_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object *)data;

   elm_entry_item_provider_remove(en, item_provider, NULL);
   elm_entry_item_provider_remove(en, prepend_item_provider, NULL);
   elm_object_text_set(en,
                       "Item Provider"
                       "<item size=50x50 vsize=full href=itemprovider></item>"
                      );
}

static void
enable_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object*)data;

   elm_entry_context_menu_disabled_set(en, elm_check_state_get(obj));
}

void
test_entry7(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *gd, *bg, *en, *tg, *lb, *sp;
   Evas_Object *bt, *en2;

   win = elm_win_util_standard_add("entry7", "Entry 7");
   elm_win_autodel_set(win, EINA_TRUE);

   gd = elm_grid_add(win);
   elm_grid_size_set(gd, 100, 100);
   evas_object_size_hint_weight_set(gd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, gd);
   evas_object_show(gd);

   /* upper entry group */
   bg = elm_bg_add(win);
   elm_bg_color_set(bg, 255, 0, 0);
   elm_grid_pack(gd, bg, 10, 10, 60, 30);
   evas_object_show(bg);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en, "Editable, Cursor Positioin");
   evas_object_show(en);
   elm_grid_pack(gd, en, 10, 10, 60, 30);

   tg = elm_check_add(win);
   evas_object_size_hint_weight_set(tg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(tg, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(tg, "Editable");
   elm_check_state_set(tg, EINA_TRUE);
   evas_object_smart_callback_add(tg, "changed", changed_cb, en);
   elm_grid_pack(gd, tg, 70, 10, 22, 10);
   evas_object_show(tg);

   lb = elm_label_add(win);
   elm_object_text_set(lb, "Cursor position:");
   evas_object_size_hint_weight_set(lb, 0.0, 0.0);
   evas_object_size_hint_align_set(lb, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_grid_pack(gd, lb, 70, 25, 25, 5);
   evas_object_show(lb);

   sp = elm_spinner_add(win);
   elm_spinner_label_format_set(sp, "%1.0f");
   elm_spinner_step_set(sp, 1);
   elm_spinner_wrap_set(sp, ELM_WRAP_CHAR);
   elm_spinner_min_max_set(sp, 0, strlen(elm_object_text_get(en)));
   evas_object_size_hint_align_set(sp, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(sp, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_grid_pack(gd, sp, 70, 30, 25, 10);
   evas_object_smart_callback_add(en, "changed", en_changed_cb, sp);
   evas_object_smart_callback_add(sp, "delay,changed", sp_changed_cb, en);
   evas_object_show(sp);

   /* bottom entry group */
   bg = elm_bg_add(win);
   elm_bg_color_set(bg, 0, 255, 0);
   elm_grid_pack(gd, bg, 10, 50, 45, 30);
   evas_object_show(bg);

   en2 = elm_entry_add(win);
   elm_entry_scrollable_set(en2, EINA_TRUE);
   evas_object_size_hint_weight_set(en2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en2,
                       "Item Provider"
                       "<item size=50x50 vsize=full href=itemprovider></item>"
                      );
   elm_entry_item_provider_append(en2, item_provider, NULL);
   elm_entry_context_menu_disabled_set(en, EINA_TRUE);
   elm_grid_pack(gd, en2, 10, 50, 45, 30);
   evas_object_show(en2);

   tg = elm_check_add(win);
   evas_object_size_hint_weight_set(tg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(tg, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(tg, "Disable Context Menu");
   elm_check_state_set(tg, EINA_TRUE);
   evas_object_smart_callback_add(tg, "changed", enable_changed_cb, en2);
   elm_grid_pack(gd, tg, 55, 50, 40, 10);
   evas_object_show(tg);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Add Context Menu");
   elm_grid_pack(gd, bt, 55, 60, 40, 10);
   evas_object_smart_callback_add(bt, "clicked", add_bt_clicked, en2);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clear Context Menu");
   elm_grid_pack(gd, bt, 55, 70, 40, 10);
   evas_object_smart_callback_add(bt, "clicked", clear_bt_clicked, en2);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Prepend Item Provider");
   elm_grid_pack(gd, bt, 10, 80, 45, 10);
   evas_object_smart_callback_add(bt, "clicked", prepend_bt_clicked, en2);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Remove Item Provider");
   elm_grid_pack(gd, bt, 55, 80, 40, 10);
   evas_object_smart_callback_add(bt, "clicked", remove_bt_clicked, en2);
   evas_object_show(bt);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

static void
filter_prepend_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en, *en2;
   static Elm_Entry_Filter_Accept_Set digits_filter_data;

   en = (Evas_Object *)data;
   en2 = evas_object_data_get(en, "filter-entry");
   digits_filter_data.accepted = elm_object_text_get(en2);
   digits_filter_data.rejected = NULL;

   elm_entry_markup_filter_append(en, elm_entry_filter_accept_set,
                                  &digits_filter_data);
   elm_object_text_set(en, "Markup Filter Prepend Test:");
}

static void
filter_remove_bt_clicked(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object *)data;

   elm_entry_markup_filter_remove(en, elm_entry_filter_accept_set, NULL);
   elm_object_text_set(en, "Markup Filter Prepend Test:");
}

static void
icon_visible_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object*)data;

   elm_entry_icon_visible_set(en, elm_check_state_get(obj));
}

static void
end_visible_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object*)data;

   elm_entry_end_visible_set(en, elm_check_state_get(obj));
}

static void
horizontal_bounce_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   Eina_Bool vb;
   Eina_Bool bounce = elm_check_state_get(obj);
   en = (Evas_Object*)data;

   elm_scroller_bounce_get(en, NULL, &vb);
   elm_scroller_bounce_set(en, bounce, bounce);
}

static void
vertical_bounce_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   Eina_Bool hb;
   Eina_Bool bounce = elm_check_state_get(obj);
   en = (Evas_Object*)data;

   elm_scroller_bounce_get(en, &hb, NULL);
   elm_scroller_bounce_set(en, hb, bounce);
}

void
test_entry8(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *gd, *rect, *en, *lb;
   Evas_Object *bt, *en2;
   Evas_Object *ch, *en3;
   Evas_Object *en4;
   static Elm_Entry_Filter_Limit_Size limit_filter_data;

   win = elm_win_util_standard_add("entry8", "Entry 8");
   elm_win_autodel_set(win, EINA_TRUE);

   gd = elm_grid_add(win);
   elm_grid_size_set(gd, 100, 100);
   elm_win_resize_object_add(win, gd);
   evas_object_size_hint_weight_set(gd, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(gd);

   rect = evas_object_rectangle_add(evas_object_evas_get(win));
   elm_grid_pack(gd, rect, 5, 5, 90, 10);
   evas_object_color_set(rect, 125, 125, 255, 255);
   evas_object_show(rect);

   en = elm_entry_add(win);
   elm_entry_scrollable_set(en, EINA_TRUE);
   elm_scroller_policy_set(en, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(en, "Markup Filter Prepend Test");
   elm_grid_pack(gd, en, 5, 5, 90, 10);
   evas_object_show(en);

   lb = elm_label_add(win);
   elm_object_text_set(lb, "Markup Filter (20 Characters):");
   evas_object_size_hint_weight_set(lb, 0.0, 0.0);
   evas_object_size_hint_align_set(lb, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_grid_pack(gd, lb, 5, 15, 50, 10);
   evas_object_show(lb);

   rect = evas_object_rectangle_add(evas_object_evas_get(win));
   elm_grid_pack(gd, rect, 55, 15, 40, 10);
   evas_object_color_set(rect, 0, 125, 255, 255);
   evas_object_show(rect);

   en2 = elm_entry_add(win);
   elm_entry_scrollable_set(en2, EINA_TRUE);
   elm_scroller_policy_set(en2, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   evas_object_size_hint_weight_set(en2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   limit_filter_data.max_char_count = 20;
   limit_filter_data.max_byte_count = 0;
   elm_entry_markup_filter_append(en2, elm_entry_filter_limit_size, &limit_filter_data);
   evas_object_data_set(en, "filter-entry", en2);
   evas_object_show(en2);
   elm_grid_pack(gd, en2, 55, 15, 40, 10);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Markup Filter Prepend");
   elm_grid_pack(gd, bt, 5, 25, 45, 10);
   evas_object_smart_callback_add(bt, "clicked", filter_prepend_bt_clicked, en);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Markup Filter Remove");
   elm_grid_pack(gd, bt, 50, 25, 45, 10);
   evas_object_smart_callback_add(bt, "clicked", filter_remove_bt_clicked, en);
   evas_object_show(bt);

   en3 = elm_entry_add(win);
   elm_entry_scrollable_set(en3, EINA_TRUE);
   elm_scroller_policy_set(en3, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_OFF);
   elm_entry_single_line_set(en3, EINA_TRUE);
   evas_object_size_hint_weight_set(en3, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en3, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(en3);
   elm_grid_pack(gd, en3, 5, 35, 90, 20);

   bt = elm_icon_add(win);
   elm_icon_standard_set(bt, "home");
   evas_object_size_hint_min_set(bt, 48, 48);
   evas_object_color_set(bt, 128, 0, 0, 128);
   evas_object_show(bt);
   elm_object_part_content_set(en3, "icon", bt);

   bt = elm_icon_add(win);
   elm_icon_standard_set(bt, "delete");
   evas_object_color_set(bt, 128, 0, 0, 128);
   evas_object_size_hint_min_set(bt, 48, 48);
   evas_object_show(bt);
   elm_object_part_content_set(en3, "end", bt);

   ch = elm_check_add(win);
   evas_object_size_hint_weight_set(ch, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ch, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(ch, "Icon Visible");
   elm_check_state_set(ch, EINA_TRUE);
   evas_object_smart_callback_add(ch, "changed", icon_visible_changed_cb, en3);
   elm_grid_pack(gd, ch, 5, 55, 30, 10);
   evas_object_show(ch);

   ch = elm_check_add(win);
   evas_object_size_hint_weight_set(ch, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ch, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(ch, "End Visible");
   elm_check_state_set(ch, EINA_TRUE);
   evas_object_smart_callback_add(ch, "changed", end_visible_changed_cb, en3);
   elm_grid_pack(gd, ch, 70, 55, 25, 10);
   evas_object_show(ch);

   rect = evas_object_rectangle_add(evas_object_evas_get(win));
   elm_grid_pack(gd, rect, 5, 65, 90, 20);
   evas_object_color_set(rect, 255, 125, 125, 255);
   evas_object_show(rect);

   en4 = elm_entry_add(win);
   elm_object_part_text_set(en4, "guide", "Type in here");
   elm_entry_scrollable_set(en4, EINA_TRUE);
   elm_scroller_bounce_set(en4, EINA_TRUE, EINA_TRUE);
   elm_entry_autocapital_type_set(en4, EINA_TRUE);
   evas_object_size_hint_weight_set(en4, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en4, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_grid_pack(gd, en4, 5, 65, 90, 20);
   evas_object_show(en4);

   ch = elm_check_add(win);
   evas_object_size_hint_weight_set(ch, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ch, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(ch, "Horizontal Bounce Set");
   elm_check_state_set(ch, EINA_TRUE);
   evas_object_smart_callback_add(ch, "changed", horizontal_bounce_changed_cb, en4);
   elm_grid_pack(gd, ch, 5, 85, 45, 10);
   evas_object_show(ch);

   ch = elm_check_add(win);
   evas_object_size_hint_weight_set(ch, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ch, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(ch, "Vertical Bounce Set");
   elm_check_state_set(ch, EINA_TRUE);
   evas_object_smart_callback_add(ch, "changed", vertical_bounce_changed_cb, en4);
   elm_grid_pack(gd, ch, 50, 85, 45, 10);
   evas_object_show(ch);

   evas_object_resize(win, 320, 320);
   evas_object_show(win);
}

static void
_scrolled_entry_clear(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_object_text_set(en, "");
}

static void
_scrolled_entry_save(void *data, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *en = data;
   elm_entry_file_save(en);
}

static void
auto_save_changed_cb(void *data, Evas_Object *obj, void *event_info __UNUSED__)
{
   Evas_Object *en;
   en = (Evas_Object*)data;

   elm_entry_autosave_set(en, elm_check_state_get(obj));
}

void
test_entry_notepad(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *bx, *bx2, *bt, *np, *ch;

   win = elm_win_util_standard_add("entry-notepad", "Entry Notepad");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   np = elm_entry_add(win);
   elm_entry_scrollable_set(np, EINA_TRUE);
   elm_entry_file_set(np, "note.txt", ELM_TEXT_FORMAT_PLAIN_UTF8);
   evas_object_size_hint_weight_set(np, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(np, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, np);
   evas_object_show(np);

   bx2 = elm_box_add(win);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_homogeneous_set(bx2, EINA_TRUE);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Clear");
   evas_object_smart_callback_add(bt, "clicked", _scrolled_entry_clear, np);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   bt = elm_button_add(win);
   elm_object_text_set(bt, "Save");
   evas_object_smart_callback_add(bt, "clicked", _scrolled_entry_save, np);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx2, bt);
   evas_object_show(bt);

   ch = elm_check_add(win);
   evas_object_size_hint_weight_set(ch, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(ch, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_object_text_set(ch, "Auto Save");
   elm_check_state_set(ch, EINA_FALSE);
   evas_object_smart_callback_add(ch, "changed", auto_save_changed_cb, np);
   elm_box_pack_end(bx2, ch);
   evas_object_show(ch);

   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   evas_object_resize(win, 320, 300);

   elm_object_focus_set(win, EINA_TRUE);
   evas_object_show(win);
}
#endif
