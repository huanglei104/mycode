#include <xcb/xcb.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	xcb_connection_t *connection = xcb_connect (":99", NULL);

	const xcb_setup_t      *setup  = xcb_get_setup (connection);
	xcb_screen_iterator_t   iter   = xcb_setup_roots_iterator (setup);
	xcb_screen_t           *screen = iter.data;


	int ret = xcb_connection_has_error(connection);
	if (ret > 0){
		printf("error\n");
		return 0;
	}

	/* Create the window */
	xcb_window_t window = xcb_generate_id (connection);
	xcb_create_window (connection,                    /* Connection          */
			XCB_COPY_FROM_PARENT,          /* depth (same as root)*/
			window,                        /* window Id           */
			screen->root,                  /* parent window       */
			0, 0,                          /* x, y                */
			150, 150,                      /* width, height       */
			10,                            /* border_width        */
			XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
			screen->root_visual,           /* visual              */
			0, NULL );                     /* masks, not used yet */


	/* Map the window on the screen */
	xcb_map_window (connection, window);


	/* Make sure commands are sent before we pause so that the window gets shown */
	xcb_flush (connection);


	pause();    /* hold client until Ctrl-C */

	xcb_disconnect(connection);

	return 0;
}
