#ifndef MODE_7_H
#define MODE_7_H
#include "fixed.h"

typedef enum {FLOOR, CEIL, BOTH} M7_RenderMode;

/* MODE_7_PARAMS is a struct containing all the different parameters
that are relevant for Mode 7, so you can pass them to the functions
as a single unit */
typedef struct M7_Parameters
{
	fix camera_x;
	fix camera_y;
    fix camera_z; // this is the height of the camera above the plane
	fix camera_angle;

    int horizon; // this is the number of pixels line 0 is below the horizon
    fix scale_x, scale_y; // this determines the scale of space coordinates
    // to screen coordinates
    fix obj_scale_x, obj_scale_y; // this determines the relative size of
    // the objects
    M7_RenderMode render_mode;
} M7_Parameters;

typedef struct M7_TiledMap
{
	char* map;
	char* tiles;
	unsigned width;
	unsigned height;
} M7_TiledMap;

void mode_7 (M7_TiledMap tmap, M7_Parameters params);

/* draw_object just draws a single object at a fixed position, although
this can easily be modified to allow for more objects.
bmp = bitmap to draw to. obj = sprite for the object.
angle, cx, cy define the camera position.
*/
void draw_object (unsigned char *spr, fix angle, fix ox, fix oy, M7_Parameters params);

#endif