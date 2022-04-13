
#include "Tile.h"




Tile::Tile(Colour colour, Shape shape ): colour(colour), shape(shape){

}

Tile::Tile(Tile& copy): colour(copy.colour), shape(copy.shape){}
