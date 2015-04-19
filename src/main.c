#include <pebble.h>
	
// Dictionary keys to send data between the Pebble and the phone.  
#define KEY_TEMPERATURE_C 0
#define KEY_TEMPERATURE_F 1
#define KEY_CONDITIONS 2

//static pointers
static Window *s_main_window;

//time layer
static TextLayer *s_time_layer;
static GFont s_time_font;

//weather layer
static TextLayer *s_weather_layer;
static GFont s_weather_font;

//image section
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

//static fucntions
static void update_time();

//window handler functions
static void main_window_load(Window *window){
	//image section
	//it must be fraw first to be in the background
	s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BAR_AND_SHIELD_LOGO);
	s_background_layer = bitmap_layer_create(GRect(3,10,138,105));
	bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer
																		 ));
	//Create Time text Layer
	s_time_layer = text_layer_create(GRect(5,105,139,50));
	text_layer_set_background_color(s_time_layer, GColorClear);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "00:00");
	
	//imporove the layout to be more like watchface
	// Create GFont
	s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_VIKINGS_SUBSET_40));
	// Apply to TextLayer
	text_layer_set_font(s_time_layer, s_time_font);
	text_layer_set_text_alignment(s_time_layer,GTextAlignmentCenter);
	
	//add it as a child layer to the Window root layer
	layer_add_child(window_get_root_layer(window),text_layer_get_layer(s_time_layer));
	
	//create weather layer
	s_weather_layer = text_layer_create(GRect(0, 150, 144, 25));
	text_layer_set_background_color(s_weather_layer, GColorClear);
	text_layer_set_text_color(s_weather_layer, GColorBlack);
	text_layer_set_text_alignment(s_weather_layer, GTextAlignmentCenter);
	text_layer_set_text(s_weather_layer, "Loading ...");
	
	//loading weather font
	s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_KEEP_CALM_SUBSET_10));
	text_layer_set_font(s_weather_layer, s_weather_font);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
					
}

static void main_window_unload(Window *window){
	//destroy textLayer
	text_layer_destroy(s_time_layer);
	
	// Unload GFont
	fonts_unload_custom_font(s_time_font);
	
	//unload GBitmap
	gbitmap_destroy(s_background_bitmap);
	//dratroy BitmapLayer
	bitmap_layer_destroy(s_background_layer);
	
	//destroy weather layer and font
	text_layer_destroy(s_weather_layer);
	fonts_unload_custom_font(s_weather_font);

}

//subscribe to tickService
static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
	update_time();
	
	//get weather update every 30 minutes
	if(tick_time->tm_min % 1 == 0){
		//begin dictonary
		DictionaryIterator *iter;
		app_message_outbox_begin(&iter);
		
		//ass key_value pair
		dict_write_uint8(iter, 0, 0);
		
		//send the message
		app_message_outbox_send();
	}
}

static void update_time(){
	//get a tm struct
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);
	
	//create a long lived buffer
	static char buffer[] = "00:00";
	
	//Write the current hours and minutes into the buffer
	if(clock_is_24h_style() == true){
		//use 24 hours format
		strftime(buffer, sizeof(buffer), "%I:%M", tick_time);
	}
	else{
		//use 12 hours format
		strftime(buffer, sizeof(buffer), "%I:%M", tick_time);
	}
	
	//display this time on text layer
	text_layer_set_text(s_time_layer, buffer);
}

//APP_message to communicate with phone
static void inbox_received_callback(DictionaryIterator *iterator, void *context){
	//Store incoming info
	static char temprature_C_buffer[8];
	static char temprature_F_buffer[8];
	static char conditions_buffer[32];
	static char weather_layer_buffer[32];
	
	//read first item
	Tuple *t = dict_read_first(iterator);
	
	//For all item
	while(t != NULL){
		//which key was received ?
		switch(t->key){
			case KEY_TEMPERATURE_C:
			snprintf(temprature_C_buffer, sizeof(temprature_C_buffer), "%dC", (int)t->value->int32);
			break;
			case KEY_TEMPERATURE_F:
			snprintf(temprature_F_buffer, sizeof(temprature_F_buffer), "%dF", (int)t->value->int32);
			break;
			case KEY_CONDITIONS:
			snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
			break;
			
			default:
			APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognised!", (int)t->key);
			break;
		}
		//look for next item
		t = dict_read_next(iterator);
	}
	
	//assemble full string and display
	snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s/%s %s", temprature_C_buffer,temprature_F_buffer, conditions_buffer);
	text_layer_set_text(s_weather_layer, weather_layer_buffer);
}

static void inbox_dropped_callback(AppMessageResult reason, void *content){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *itrator, AppMessageResult reason, void *context){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outboc send failed");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send success");
}

static void init(){
	//create main wondow element and assign to pointer 
	s_main_window = window_create();
	
	//set handlers to manage the element inside the window
	window_set_window_handlers(s_main_window, (WindowHandlers){
		.load = main_window_load,
		.unload = main_window_unload
	});
	
		//register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
	
	//register callbacls 
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	
	//open app messsage
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	
	//show the window on the watch, with animated=true
	window_stack_push(s_main_window, true);
	
	//update time layer as soon as window is pushed 
	update_time();

}

static void deinit(){
	//destrory window
	window_destroy(s_main_window);

}

// main loop which have main event loop
int main(void){
	init();
	app_event_loop();
	deinit();
}
