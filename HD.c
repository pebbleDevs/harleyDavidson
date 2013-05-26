#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
//#include "myPebbleFunctions.h"


#define MY_UUID { 0xD6, 0x66, 0xC2, 0x7E, 0xE6, 0x5C, 0x46, 0x55, 0x81, 0x5F, 0xB4, 0x58, 0xD9, 0x47, 0xBD, 0x9B }
PBL_APP_INFO(MY_UUID,
             "Harley Davidson", "mApps Lab",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;
//Bitmap area for logo
BmpContainer background_image;
Layer background_layer;

TextLayer text_time_layer;
TextLayer text_date_layer;
TextLayer text_string_layer;

GFont time_font;

TextLayer text_creditLine1_layer;
TextLayer text_creditLine2_layer;

//GFont time_font;

void creditBanner()
{
 time_font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
 //initilizing the creditline layer
  text_layer_init(&text_creditLine1_layer, window.layer.frame);
  //setting the layer attributes
  text_layer_set_text_color(&text_creditLine1_layer, GColorBlack);
  text_layer_set_background_color(&text_creditLine1_layer, GColorClear);
  //positing attributes
  layer_set_frame(&text_creditLine1_layer.layer, GRect(15,80,150,90));
  //Font attribute
  text_layer_set_font(&text_creditLine1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(&window.layer, &text_creditLine1_layer.layer);
  text_layer_set_text(&text_creditLine1_layer,"Created By");
  
  //initilizing the layer  
  text_layer_init(&text_creditLine2_layer, window.layer.frame);
  //setting the layer attributes 
  text_layer_set_text_color(&text_creditLine2_layer, GColorBlack);
  text_layer_set_background_color(&text_creditLine2_layer, GColorClear);
  //positiong attribute
  layer_set_frame(&text_creditLine2_layer.layer, GRect(20,100,160,120));
  //Font attribute
  text_layer_set_font(&text_creditLine2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(&window.layer, &text_creditLine2_layer.layer);
  text_layer_set_text(&text_creditLine2_layer,"alokc83");
}


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
  layer_set_frame(&background_image.layer.layer, GRect(0,0,70,70));
  layer_add_child(&window.layer, &background_image.layer.layer);

 
  //initilizing the text time layer
  text_layer_init(&text_time_layer, window.layer.frame);
  text_layer_set_text_color(&text_time_layer, GColorBlack);
  text_layer_set_background_color(&text_time_layer, GColorClear);
  layer_set_frame(&text_time_layer.layer, GRect(10,10,140,30));
  //Font atterbutes
  //time_font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  text_layer_set_font(&text_time_layer, time_font);
  layer_add_child(&window.layer, &text_time_layer.layer);
  
  //creditBanner();
  
  PblTm tick_time;
  get_time(&tick_time);
}

void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {

  (void)ctx;
  
  static char time_text[] = "00:00";
  char *time_format="%R"; // TODO for 12 or 24 hrs suuport
 
 // Hiding the credit line layers
 //psleep(1000);
 //layer_set_hidden((Layer *)&text_creditLine1_layer, true);
 //layer_set_hidden((Layer *)&text_creditLine2_layer, true);
 
 string_format_time(time_text, sizeof(time_text), time_format, t->tick_time);
 text_layer_set_text(&text_time_layer, time_text);

}

//dealloccation when watchface is close
void handle_deinit(AppContextRef ctx) {
        (void)ctx;

      bmp_deinit_container(&background_image);
      //  fonts_unload_custom_font(batman_letters_15);
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
