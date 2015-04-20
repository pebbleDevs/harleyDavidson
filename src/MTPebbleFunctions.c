#include <pebble.h>
#include "MTPebbleFunctions.h"
	

int libFunc(int justInt){
	printf("They have just passed a ton of %d",justInt);
	justInt++;
	return justInt;
}

TextLayer* textLayerWithAttributes(TextLayer *textLayer, GRect layerRect, GColor bgColor, GColor textColor, char initialText[]){
	//Create Time text Layer
	textLayer = text_layer_create(layerRect);
	text_layer_set_background_color(textLayer, bgColor);
	text_layer_set_text_color(textLayer, textColor);
	text_layer_set_text(textLayer, initialText);
	return textLayer;

}
