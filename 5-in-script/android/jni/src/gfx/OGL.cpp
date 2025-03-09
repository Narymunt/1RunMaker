#include "OGL.h"
#include "SDL_error.h"

#define OGL_MAX(a, b) (a) < (b) ? (b) : (a)	
#define OGL_MIN(a, b) (a) > (b) ? (b) : (a)	

#define OGL_UNKNOWN 0

// Compares two SDL_PixelFormat structures, only works with RGBA or RGB surfaces and disregards everything but the color masks 

int oglCompareFormat(SDL_PixelFormat* a, SDL_PixelFormat* b)
{

	if(a->BytesPerPixel == b->BytesPerPixel)
	{
		if(a->BytesPerPixel == 3)
		{
			if(a->Rmask == b->Rmask && a->Gmask == b->Gmask && a->Bmask == b->Bmask)
				return 1;			
		}
		else
		{
			if (a->Rmask == b->Rmask &&	a->Gmask == b->Gmask &&	a->Bmask == b->Bmask &&	a->Amask == b->Amask )
				return 1;		
		}
	}
	else
	{
		return -1; // BytesPerPixel differs
	}

	return 0;
}

//  Returns an SDL_PixelFormat from GL_RGBA or GL_RGBA for the current machine

SDL_PixelFormat oglGetPixelFormat(GLenum glFormat)
{
	SDL_PixelFormat format;
	if(glFormat == GL_RGBA)
	{
		format.BytesPerPixel = 4;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff000000;
		format.Gmask = 0x00ff0000;
		format.Bmask = 0x0000ff00;
		format.Amask = 0x000000ff;
#else	
		format.Rmask = 0x000000ff; 
		format.Gmask = 0x0000ff00;
		format.Bmask = 0x00ff0000;
		format.Amask = 0xff000000;
#endif
	}
	else
	{
		format.BytesPerPixel = 3;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		format.Rmask = 0xff0000;
		format.Gmask = 0x00ff00;
		format.Bmask = 0x0000ff;
#else
		format.Rmask = 0x0000ff;
		format.Gmask = 0x00ff00;
		format.Bmask = 0xff0000;
#endif
		format.Amask = 0;
	}
	
	return format;
}

// init sdl with opengl with flags

bool oglInit(int iScreenX, int iScreenY, int bpp, Uint32 flags)
{

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, iScreenX, iScreenY);

//	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrthof(0.0f, iScreenX, iScreenY, 0.0f, -1.0f, 1.0f);
	glViewport( 0, 0, iScreenX, iScreenY );
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();

	return true;
}

// free oglTexture created with oglFromSurface

void oglFreeTexture(oglTexture *texture)
{
	glDeleteTextures(1, &texture->name);
	free(texture);
}

// blit texture to the screen

void oglBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw ) * hZoom;
	hch = ((GLfloat)ch ) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	GLfloat box[] = {x,y+hch,0,x+hcw,y+hch,0,x+hcw,y,0,x,y,0};
	GLfloat tex[] = {0,1, 1,1, 1,0, 0,0};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_SRC_ALPHA);

	glVertexPointer(3, GL_FLOAT, 0,box);
	glTexCoordPointer(2, GL_FLOAT, 0, tex);
	glBindTexture(GL_TEXTURE_2D,texture->name);
	glDrawArrays(GL_TRIANGLE_FAN,0,4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix();	
}

// blit texture to the screen

void oglBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, GLfloat Alfa, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
/*	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glBindTexture( GL_TEXTURE_2D, texture->name );

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw ) * hZoom;
	hch = ((GLfloat)ch ) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	glBegin( GL_QUADS );

	// Top-left 
	glTexCoord2f(l, t);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(0, 0, 0);

	// Top-right 
	glTexCoord2f(r, t);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(hcw, 0, 0 );
	
	// Bottom-right 
	glTexCoord2f(r, b);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(hcw, hch, 0);

	// Bottom-left 
	glTexCoord2f(l, b);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(0, hch, 0);
	
	glEnd();

	glPopMatrix();	
*/
}


// blit texture giving center x & y

void oglCBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
/*	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glBindTexture( GL_TEXTURE_2D, texture->name );

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw / 2) * hZoom;
	hch = ((GLfloat)ch / 2) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	glBegin( GL_QUADS );

	// Top-left 
	glTexCoord2f(l, t);
	glColor4f(1,1,1,1);	
	glVertex3f(-hcw, -hch, 0);

	// Top-right 
	glTexCoord2f(r, t);
	glColor4f(1,1,1,1);	
	glVertex3f(hcw, -hch, 0 );
	
	// Bottom-right 
	glTexCoord2f(r, b);
	glColor4f(1,1,1,1);	
	glVertex3f(hcw, hch, 0);

	// Bottom-left 
	glTexCoord2f(l, b);
	glColor4f(1,1,1,1);	
	glVertex3f(-hcw, hch, 0);
	
	glEnd();

	glPopMatrix();	
*/
}

// blit texture giving center x & y

void oglCBlit(oglTexture *texture, SDL_Rect* clipping, int x, int y, GLfloat Alfa, GLfloat hZoom, GLfloat vZoom, GLfloat rotation)
{
/*	GLfloat l, r, t, b;
	GLuint ch, cw;
	GLfloat hch, hcw;

	glBindTexture( GL_TEXTURE_2D, texture->name );

	glPushMatrix();

	if(clipping)
	{
		l = (GLfloat)clipping->x / texture->wTex;
		t = (GLfloat)clipping->y / texture->hTex;

		r = (GLfloat)(clipping->x + clipping->w) / texture->wTex;
		b = (GLfloat)(clipping->y + clipping->h) / texture->hTex;

		cw = clipping->w;
		ch = clipping->h;
	}
	else
	{
		cw = texture->w;
		ch = texture->h;	

		l = t = 0;
		r = b = 1;
	}

	hcw = ((GLfloat)cw / 2) * hZoom;
	hch = ((GLfloat)ch / 2) * vZoom;

	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	glRotatef(rotation, 0, 0, 1.0f);

	glBegin( GL_QUADS );

	// Top-left 
	glTexCoord2f(l, t);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(-hcw, -hch, 0);

	// Top-right 
	glTexCoord2f(r, t);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(hcw, -hch, 0 );
	
	// Bottom-right 
	glTexCoord2f(r, b);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(hcw, hch, 0);

	// Bottom-left 
	glTexCoord2f(l, b);
	glColor4f(1,1,1,Alfa);	
	glVertex3f(-hcw, hch, 0);
	
	glEnd();

	glPopMatrix();	
	*/
}


// return the smallest power of two value in which 'val' fits, with a max size of 'max'

GLint oglGetPT(GLint val, GLint max)
{
	GLint i, count, high;

	count = 0;

	for (i = 0; i < sizeof(val) * 8; i++)
	{
		if((val >> i) & 1)
		{
			high = i;
			count++;
		}
	}

	if(count != 1)
		val = 1 << (high + 1);

	return OGL_MIN(val, max);
}

// (internal) Probes the OpenGL driver with a specified texture size and format. 
// Returns true if the size and format is ok. 

int oglProbeTexture(GLint w, GLint h, GLenum format)
{
	GLint bpp;
	GLint width;
/*
	if(format == GL_RGB || format == GL_BGR)
	{
		bpp = 3;
	}
	else
	{
		bpp = 4;
	}

	glTexImage2D(GL_PROXY_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, NULL);  
	glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);

	if(!width)
		return -1;	// Texture probing failed 
*/
	return !!width;
}


// (internal) Checks if a surface with the given format needs to be resized or converted before
// turning it into an OpenGL surface. Returns true if the surface is "ok", ie. doesn't have to
// be resized. Suggests what a good texture size is by changing 'size' if the original size
// didn't work. 

int oglGetTexSize(SDL_Rect* size, GLenum format)
{
	GLint maxSize;
	int ret;

	ret = 1;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);

	if(size->x > maxSize || size->y > maxSize)
	{
		size->x = OGL_MIN(size->x, maxSize);
		size->y = OGL_MIN(size->y, maxSize);
		ret = 0;
	}

	if(!oglProbeTexture(size->x, size->y, format))
	{
		size->x = oglGetPT(size->x, maxSize);
		size->y = oglGetPT(size->y, maxSize);
	
		if(!oglProbeTexture(size->x, size->y, format))
			size->x = size->y = 0;
		
		ret = 0;
	}

	return ret;
}


// (internal) Determines the corresponding OpenGL texture color format from an SDL_Surface.
//  Returns OGL_UNKNOWN if it has an unsupported color format. 

GLenum oglGetFormat(SDL_Surface* surface)
{
	
	if(surface->format->BytesPerPixel == 4)
	{
		SDL_PixelFormat rgba = oglGetPixelFormat(GL_RGBA);
		
		if(oglCompareFormat(&rgba, surface->format))
			return GL_RGBA;
	}
	else if(surface->format->BytesPerPixel == 3)
	{
		SDL_PixelFormat rgb = oglGetPixelFormat(GL_RGB);
		
		if(oglCompareFormat(&rgb, surface->format))	
			return GL_RGB;	
	}

	return OGL_UNKNOWN;	
}

// (internal) Converts an SDL_Surface with a compatible color format to an OGL_Texture

oglTexture *oglFromSurfaceConvert(SDL_Surface* surface, GLenum format, SDL_Rect origSize)
{
	oglTexture *texture = NULL;
	
	if(surface)
	{
		texture = (oglTexture*)malloc(sizeof(oglTexture));
		
		if(texture)
		{
			texture->w = origSize.x;
			texture->h = origSize.y;
			texture->hTex = surface->h;
			texture->wTex = surface->w;

			texture->format = format;

			glGenTextures(1, &texture->name);
			glBindTexture(GL_TEXTURE_2D, texture->name);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			if(SDL_MUSTLOCK(surface))
				SDL_LockSurface(surface);
			

			glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0, texture->format, GL_UNSIGNED_BYTE, surface->pixels );

			if(SDL_MUSTLOCK(surface))
				SDL_UnlockSurface(surface);		
		}
	}
	return texture;
}

// (internal) Makes an RGBA-copy of a given SDL_Surface with the given new size 

SDL_Surface *oglCopySurface(SDL_Surface* from, SDL_Rect size)
{
	SDL_Surface* ret=NULL;
	SDL_PixelFormat fmt;

	fmt = oglGetPixelFormat(GL_RGBA);

	ret = SDL_CreateRGBSurface(SDL_SWSURFACE, size.x, size.y, 32, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

	if(ret)
		SDL_BlitSurface(from, NULL, ret, NULL);

	return ret;
}

// Creates an OGL_Texture from an SDL_Surface and frees the SDL_Surface

oglTexture *oglFromSurfaceFree(SDL_Surface* surface)
{
	oglTexture* ret;
	
	ret = oglFromSurface(surface);

	if(ret)
		SDL_FreeSurface(surface);	

	return ret;	
}

// Creates an OGL_Texture from an SDL_Surface 

oglTexture *oglFromSurface(SDL_Surface* surface)
{
	GLenum format;
	SDL_Rect size, origSize;
	int reBlit, error;
	oglTexture* ret;

	error = reBlit = 0;
	ret = NULL;

	if(!surface)
	{
		SDL_Log("ERROR: Empty surface!\n");
		return ret;
	}

	/* Get the color format of the surface */
	oglGetFormat(surface);

	origSize.x = size.x = surface->w;
	origSize.y = size.y = surface->h;

	if(format == OGL_UNKNOWN)
	{
		// Unsupported color format for direct conversion, see if the size is ok 
		oglGetTexSize(&size, GL_RGBA);
		reBlit = 1;
	}
	else
	{
		// Supported color format, see if the size is ok 
		reBlit = !oglGetTexSize(&size, format);
	}

	// If a OGL_GetTexSize didn't fail to find a texture size 
	if(size.x != 0 && size.y != 0)
	{
		if(!reBlit)
		{
			// The original surface size and color format was ok for direct conversion 
			ret = oglFromSurfaceConvert(surface, format, origSize);
		}
		else
		{
			// The original surface size and/or color format wasn't ok for direct conversion.
 			//   Do an RGBA-copy of it with the suggested size and then convert it.
			SDL_Surface* tmp;
			tmp = oglCopySurface(surface, size);
	
			if(tmp)
			{
				if(! (ret = oglFromSurfaceConvert(tmp, GL_RGBA, origSize)) )
					error = 1;
				
				SDL_FreeSurface(tmp);
			}
			else
			{
				// SDL_oglblit: Couldn't copy an unsupported surface to an RGBA surface
				error = 1;
			}
		}
	}
	else
	{
		// SDL_oglblit: Couldn't find a suitable texture size for the given surface.
		error = 1;
	}

	if(!ret && !error)
	{
		// Unknown error while converting surface to texture.
	}
	return ret;
}


