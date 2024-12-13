#ifndef GL_POLYGONE_MODE_APP_RENDER_ALL_H
#define GL_POLYGONE_MODE_APP_RENDER_ALL_H

#include <iostream>
#include <glad/glad.h>

// This is Singleton wraper class
class GLPolygoneModeAppRenderAll
{
public:

	struct Stats{
		bool fillFront = false;
		bool pointFront = false;
		bool lineFront = false;
	
		bool fillBack = false;
		bool pointBack = false;
		bool lineBack = false;

		bool fillBoth = false;
		bool pointBoth = false;
		bool lineBoth = false;

		float sizeOfPoint;
		float lineWidth;

	};

	static Stats s_stat;

	static Stats& IgetIsOnOrOff()
	{
		return s_stat;
	}
};

#endif // !GL_POLYGONE_MODE_APP_RENDER_ALL_H