#include "mode7.h"
#include "MonochromeLib.h"

// M7_get_tmap
// gets the value of a pixel located at (y,x) of a 256*256 tilemap of 8x8 tiles from a sprite table
#ifndef M7_GET_TMAP
unsigned char M7_get_tmap(unsigned char *tmap, unsigned char *sprtbl, int x, int y)
{
	return (sprtbl[((tmap[((y&0x07F8)<<5)|((x&0x07F8)>>3)])<<3)|(y&7)])>>(x&7);
}
#endif

void mode_7 (M7_TiledMap tmap, M7_Parameters params)
{

    // current screen position
	int screen_x, screen_y;

    // the distance and horizontal scale of the line we are drawing
	fix distance, horizontal_scale;

    // masks to make sure we don't read pixels outside the tile
	const int mask = 0x7;

    // step for points in space between two pixels on a horizontal line
	fix line_dx, line_dy;

    // current space position
	fix space_x, space_y;

	int sx, sy;

	const int map_width = tmap.width <<3;
	const int map_height = tmap.height<<3;

	char value;
	char* tile;

	// Trig optimisation
	const fix ca = fcos(params.camera_angle), sa = fsin(params.camera_angle);

	for (screen_y = 0; screen_y < 64; screen_y++)
	{

		if(!(screen_y + params.horizon)) continue;
        // first calculate the distance of the line we are drawing
		distance = fmul (params.camera_z, params.scale_y) /
		(screen_y + params.horizon);

		if(distance < 0 && (params.render_mode == FLOOR))
			continue;
		if(distance > 0 && (params.render_mode == CEIL))
			continue;

        // then calculate the horizontal scale, or the distance between
        // space points on this horizontal line
		horizontal_scale = fdiv (distance, params.scale_x);

        // calculate the dx and dy of points in space when we step
        // through all points on this line
		line_dx = fmul (-sa, horizontal_scale);
		line_dy = fmul (ca, horizontal_scale);

        // calculate the starting position
		space_x = params.camera_x + fmul (distance, ca) - 64 * line_dx;
		space_y = params.camera_y + fmul (distance, sa) - 64 * line_dy;

        // go through all points in this screen line
		for (screen_x = 0; screen_x < 128; screen_x++)
		{
			sx = UNFIX(space_x);
			sy = UNFIX(space_y);
			if(sx >= 0 && sy >= 0 && sx < map_width && sy < map_height) {
	            // get a pixel from the tile and put it on the screen
				tile = tmap.tiles + ((tmap.map[((sy>>3)&255)*tmap.width + tmap.width - 1 - ((sx>>3)&255)])<<3);
				value = (tile[sy&mask] & (1<<(sx&mask))) != 0;
			}
			else 
				value = ML_CHECKER;
			ML_pixel(screen_x, screen_y, value);

            // advance to the next position in space
			space_x += line_dx;
			space_y += line_dy;
		}
	}
}

/* draw_object just draws a single object at a fixed position, although
this can easily be modified to allow for more objects.
bmp = bitmap to draw to. obj = sprite for the object.
angle, params.camera_x, params.camera_y define the camera position.
*/
void draw_object (unsigned char *spr, fix angle, fix ox, fix oy, M7_Parameters params)
{
	int width, height;
	int screen_y, screen_x;
	// Trig optimisation
	const fix ca = fcos(params.camera_angle), sa = fsin(params.camera_angle);

    // The object in this case is at a fixed position of (160, 100).
    // Calculate the position relative to the camera.
	fix obj_x = ox - params.camera_x;
	fix obj_y = oy - params.camera_y;

    // use a rotation transformation to rotate the object by the camera
    // angle
	fix space_x = fmul (obj_x, ca) + fmul (obj_y, sa);
	fix space_y = -fmul (obj_x, sa) + fmul (obj_y, ca);

    // calculate the screen coordinates that go with these space coordinates
    // by dividing everything by space_x (the distance)
	screen_x = 64 + UNFIX (fmul (fdiv (params.scale_x, space_x), space_y));
	screen_y = UNFIX (fdiv (fmul (params.camera_z, params.scale_y), space_x)) - params.horizon;

    // the size of the object has to be scaled according to the distance
	height = UNFIX (fdiv(params.obj_scale_y, space_x)<<3);
	width = UNFIX (fdiv(params.obj_scale_x, space_x)<<3);

    // draw the object
    //stretch_sprite (bmp, obj, screen_x - width / 2, screen_y - height, width, height);
	ML_point(screen_x, screen_y - height, height*2, 1);
}
