#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
//#include "myPebbleFunctions.h"

// MACRO SECTION
#define MY_UUID { 0xD6, 0x66, 0xC2, 0x7E, 0xE6, 0x5C, 0x46, 0x55, 0x81, 0x5F, 0xB4, 0x58, 0xD9, 0x47, 0xBD, 0x9B }
PBL_APP_INFO(MY_UUID,
             "Harley Davidson 1", "mApps Lab",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define IMG1 1; 
#define IMG2 2;

// GLOBAL DECLARATION //
Window window;
//Bitmap area for logo
BmpContainer background_image;
Layer background_layer;

TextLayer text_time_layer;
TextLayer text_ampm_layer;
TextLayer text_date_layer;
TextLayer text_month_layer;
TextLayer text_day_layer;

GFont font_gunplay;

TextLayer text_creditLine1_layer;
TextLayer text_creditLine2_layer;
TextLayer text_versionInfo_layer;

//////////////////////////////////////
////// CUSTOM FUNCTIONS //////////////
/////////////////////////////////////

void creditBanner()
{
 
 //initilizing the creditline layer
  text_layer_init(&text_creditLine1_layer, window.layer.frame);
  //setting the layer attributes
  text_layer_set_text_color(&text_creditLine1_layer, GColorBlack);
  text_layer_set_background_color(&text_creditLine1_layer, GColorClear);
  //positing attributes
  text_layer_set_text_alignment(&text_creditLine1_layer, GTextAlignmentCenter);
  layer_set_frame(&text_creditLine1_layer.layer, GRect(0,95,144,30)); //GRect(X,Y, Width, Height)
  //Font attribute
  //gunplay_40 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GUNPLAY_40));
  text_layer_set_font(&text_creditLine1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(&window.layer, &text_creditLine1_layer.layer);
  text_layer_set_text(&text_creditLine1_layer,"Developed By");
  
  //initilizing the layer  
  text_layer_init(&text_creditLine2_layer, window.layer.frame);
  //setting the layer attributes 
  text_layer_set_text_color(&text_creditLine2_layer, GColorBlack);
  text_layer_set_background_color(&text_creditLine2_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_creditLine2_layer, GTextAlignmentCenter);
  layer_set_frame(&text_creditLine2_layer.layer, GRect(0,115,144,30));
  //Font attribute
  //gunplay_40 = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  text_layer_set_font(&text_creditLine2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(&window.layer, &text_creditLine2_layer.layer);
  text_layer_set_text(&text_creditLine2_layer,"alokc83");
  
      //initilizing the text_versionInfo_layer  
  text_layer_init(&text_versionInfo_layer, window.layer.frame);
  //setting the layer attributes 
  text_layer_set_text_color(&text_versionInfo_layer, GColorBlack);
  text_layer_set_background_color(&text_versionInfo_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_versionInfo_layer, GTextAlignmentLeft);
  layer_set_frame(&text_versionInfo_layer.layer, GRect(55,140,60,20));
  //Font attribute
  text_layer_set_font(&text_versionInfo_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_versionInfo_layer.layer);
  text_layer_set_text(&text_versionInfo_layer, "v1.0");
}

/////////////////////////////////////////////////
///////// END OF CUSTOM FUNCTIONS///////////////
////////////////////////////////////////////////

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Harley Davidson");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorWhite);
  
  //Resource Map initialization
  resource_init_current_app(&APP_RESOURCES);
  
  // gfx layer init 
  layer_init(&background_layer, window.layer.frame); //TODO another logo
  bmp_init_container(RESOURCE_ID_BAR_SHIELD_BOW, &background_image);
  layer_set_frame(&background_image.layer.layer, GRect(1,0,144,105));
  layer_add_child(&window.layer, &background_image.layer.layer);

 
  //initilizing the text time layer
  text_layer_init(&text_time_layer, window.layer.frame);
  text_layer_set_text_color(&text_time_layer, GColorBlack);
  text_layer_set_background_color(&text_time_layer, GColorClear);
  text_layer_set_text_alignment(&text_time_layer, GTextAlignmentCenter);
  layer_set_frame(&text_time_layer.layer, GRect(0,100,144,80));
  //Font atterbutes
  font_gunplay = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GUNPLAY_42));
  //gunplay_40 = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  text_layer_set_font(&text_time_layer, font_gunplay);
  layer_add_child(&window.layer, &text_time_layer.layer);
  
  //initilizing the AM_PM layer  
  text_layer_init(&text_ampm_layer, GRect(116,88,25,20));
  //text_layer_init(&text_ampm_layer, GRect(60,45,25,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_ampm_layer, GColorBlack);
  text_layer_set_background_color(&text_ampm_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_ampm_layer, GTextAlignmentRight);  
  //Font attribute
  text_layer_set_font(&text_ampm_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_ampm_layer.layer);

  
  //initilizing the day of week layer  
  //text_layer_init(&text_day_layer, window.layer.frame);
 //layer_set_frame(&text_day_layer.layer, GRect(10,143,30,148));
  text_layer_init(&text_day_layer, GRect(5,143,30,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_day_layer, GColorBlack);
  text_layer_set_background_color(&text_day_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_day_layer, GTextAlignmentLeft);
  //Font attribute
  text_layer_set_font(&text_day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_day_layer.layer);

  //initilizing the Month layer  
  //text_layer_init(&text_month_layer, window.layer.frame);
 //layer_set_frame(&text_month_layer.layer, GRect(10,143,30,148));
  text_layer_init(&text_month_layer, GRect(98,143,25,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_month_layer, GColorBlack);
  text_layer_set_background_color(&text_month_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_month_layer, GTextAlignmentRight);
  //Font attribute
  text_layer_set_font(&text_month_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_month_layer.layer);
  
  
  //initilizing the date layer  
  //text_layer_init(&text_date_layer, window.layer.frame);
  //layer_set_frame(&text_date_layer.layer, GRect(60,143,65,148));
  //instead of above two line line below can be used.
  text_layer_init(&text_date_layer, GRect(125,143,16,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_date_layer, GColorBlack);
  text_layer_set_background_color(&text_date_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_date_layer, GTextAlignmentRight);
  
  //Font attribute
  text_layer_set_font(&text_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_date_layer.layer);
  
  creditBanner();
  
 // PblTm tick_time;
  //get_time(&tick_time);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {

  (void)ctx;
  
  static char time_text[] = "00:00";
  static char ampm_text[] = "XX";
  static char day_text[] = "XXX";
  static char new_day_text[] = "YYY";
  static char month_text[] = "XXX";
  static char date_text[] = "XX";
  static char new_date_text[] = "00";
  
  char *time_format; // TODO for 12 or 24 hrs support
  PblTm current_time;
  get_time(&current_time);
 
 // Hiding the credit line layers
 psleep(1000);
 layer_set_hidden((Layer *)&text_creditLine1_layer, true);
 layer_set_hidden((Layer *)&text_creditLine2_layer, true);
 layer_set_hidden((Layer *)&text_versionInfo_layer, true);
 
 if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
    //setting am or pm 
    string_format_time(ampm_text,sizeof(ampm_text), "%p", &current_time);
    text_layer_set_text(&text_ampm_layer, ampm_text);
  }
 
 string_format_time(time_text, sizeof(time_text), time_format, &current_time);
/* if (!clock_is_24h_style() && (time_text[0] == '0')) 
 {
             memmove(time_text, &time_text[1], sizeof(time_text) - 1);
 } */

text_layer_set_text(&text_time_layer, time_text);

//populating day layer
//Not pupulating unless day is different
  string_format_time(new_day_text,sizeof(day_text), "%a", &current_time);
  if(strncmp(new_day_text, day_text, sizeof(day_text)) != 0)
  	{
  		strncpy(day_text, new_day_text, sizeof(day_text));
  		text_layer_set_text(&text_day_layer, day_text);
  	}
//populating month layer %b=Jun, %B = June
 string_format_time(month_text, sizeof(month_text), "%b", &current_time);
text_layer_set_text(&text_month_layer, month_text);

//populating date field 
//Not pupulating unless date is different
  string_format_time(new_date_text,sizeof(date_text), "%d", &current_time);
  if(strncmp(new_date_text, date_text, sizeof(date_text)) != 0)
  	{
  		strncpy(date_text, new_date_text, sizeof(date_text));
  		text_layer_set_text(&text_date_layer, date_text);
  	}

}

//dealloccation when watchface is close
void handle_deinit(AppContextRef ctx) {
        (void)ctx;
      vibes_short_pulse();
      bmp_deinit_container(&background_image);
      fonts_unload_custom_font(font_gunplay);
      //  fonts_unload_custom_font(batman_letters_20);
     //   fonts_unload_custom_font(batman_numbers_40);
     
}


/*
void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
} */ // main created by project creator

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .deinit_handler = &handle_deinit,

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
