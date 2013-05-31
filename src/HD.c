#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
//#include "myPebbleFunctions.h"


#define MY_UUID { 0xD6, 0x66, 0xC2, 0x7E, 0xE6, 0x5C, 0x46, 0x55, 0x81, 0x5F, 0xB4, 0x58, 0xD9, 0x47, 0xBD, 0x9B }
PBL_APP_INFO(MY_UUID,
             "Harley Davidson 1", "mApps Lab",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);


// GLOBAL DECLARATION //
Window window;
//Bitmap area for logo
BmpContainer background_image;
Layer background_layer;

TextLayer text_time_layer;
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

char* get_short_month(char *month_text)
{
  // Month Logic 
	char *short_month_text;
	if(strncmp(month_text, "January", sizeof(month_text)) == 0)
		{
			return short_month_text = "JAN";
		}
	else if(strncmp(month_text, "February", sizeof(month_text)) == 0)
		{
			return short_month_text = "FEB";
		}
	else if(strncmp(month_text, "March", sizeof(month_text)) == 0)
		{
			return short_month_text = "MAR";
		}
	else if(strncmp(month_text, "April", sizeof(month_text)) == 0)
		{
			return short_month_text = "APR";
		}
	else if(strncmp(month_text, "May", sizeof(month_text)) == 0)
		{
			return short_month_text = "MAY";
		}
	else if(strncmp(month_text, "June", sizeof(month_text)) == 0)
		{
			return short_month_text = "JUN";
		}
	else if(strncmp(month_text, "July", sizeof(month_text)) == 0)
		{
			return short_month_text = "JUL";
		}
	else if(strncmp(month_text, "August", sizeof(month_text)) == 0)
		{
			return short_month_text = "AUG";
		}
	else if(strncmp(month_text, "September", sizeof(month_text)) == 0)
		{
			return short_month_text = "SEP";
		}
	else if(strncmp(month_text, "October", sizeof(month_text)) == 0)
		{
			return short_month_text = "OCT";
		}
	else if(strncmp(month_text, "November", sizeof(month_text)) == 0)
		{
			return short_month_text = "NOV";
		}
	else if(strncmp(month_text, "December", sizeof(month_text)) == 0)
		{
			return short_month_text = "DEC";
		}
	else
		{
			return short_month_text = "N/A";
		 }
	

}

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
  layer_init(&background_layer, window.layer.frame);
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
  
  //initilizing the day of week layer  
  //text_layer_init(&text_day_layer, window.layer.frame);
 //layer_set_frame(&text_day_layer.layer, GRect(10,143,30,148));
  text_layer_init(&text_day_layer, GRect(5,143,40,20));
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
  text_layer_init(&text_month_layer, GRect(30,143,40,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_month_layer, GColorBlack);
  text_layer_set_background_color(&text_month_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_month_layer, GTextAlignmentLeft);
  //Font attribute
  text_layer_set_font(&text_month_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_month_layer.layer);
  
  
  //initilizing the date layer  
  //text_layer_init(&text_date_layer, window.layer.frame);
  //layer_set_frame(&text_date_layer.layer, GRect(60,143,65,148));
  //instead of above two line line below can be used.
  text_layer_init(&text_date_layer, GRect(60,143,20,20));
  //setting the layer attributes 
  text_layer_set_text_color(&text_date_layer, GColorBlack);
  text_layer_set_background_color(&text_date_layer, GColorClear);
  //positiong attribute
  text_layer_set_text_alignment(&text_date_layer, GTextAlignmentCenter);
  
  //Font attribute
  text_layer_set_font(&text_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(&window.layer, &text_date_layer.layer);
  
  creditBanner();
  
  PblTm tick_time;
  get_time(&tick_time);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {

  (void)ctx;
  
  static char time_text[] = "00:00";
  static char day_text[] = "XX";
  static char new_day_text[] = "YY";
  static char long_month_text[] = "Xxxxxx";
  static char date_text[] = "XX";
  static char new_date_text[] = "00";
  
  char *time_format; // TODO for 12 or 24 hrs suuport
  PblTm current_time;
  get_time(&current_time);
  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }
 
 // Hiding the credit line layers
 psleep(1000);
 layer_set_hidden((Layer *)&text_creditLine1_layer, true);
 layer_set_hidden((Layer *)&text_creditLine2_layer, true);
 layer_set_hidden((Layer *)&text_versionInfo_layer, true);
 
 string_format_time(time_text, sizeof(time_text), time_format, &current_time);
/* if (!clock_is_24h_style() && (time_text[0] == '0')) 
 {
             memmove(time_text, &time_text[1], sizeof(time_text) - 1);
 } */

text_layer_set_text(&text_time_layer, time_text);

//populating day layer
//Not pupulating unless day is different
  string_format_time(new_day_text,sizeof(date_text), "%A", &current_time);
  if(strncmp(new_day_text, day_text, sizeof(day_text)) != 0)
  	{
  		strncpy(day_text, new_day_text, sizeof(day_text));
  		text_layer_set_text(&text_day_layer, day_text);
  	}
//populating month layer
 string_format_time(long_month_text, sizeof(long_month_text), "%B", &current_time);
//text_layer_set_text(&text_month_layer, get_short_month(long_month_text));
text_layer_set_text(&text_month_layer, long_month_text);

//populating date field 
//Not pupulating unless date is different
  string_format_time(new_date_text,sizeof(date_text), "%e", &current_time);
  if(strncmp(new_date_text, date_text, sizeof(date_text)) != 0)
  	{
  		strncpy(date_text, new_date_text, sizeof(date_text));
  		text_layer_set_text(&text_date_layer, date_text);
  	}

}

//dealloccation when watchface is close
void handle_deinit(AppContextRef ctx) {
        (void)ctx;

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

    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
