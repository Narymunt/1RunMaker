#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <jni.h>
#include "SDL.h"
#include <GLES/gl.h>
#include <GLES/glext.h>

//#include "SDL_opengl.h"

// openGL texture

typedef struct
{
	GLuint name;		// texture id
	GLenum format;		// color format 
	int w, h;			// width and height of the ORIGINAL SURFACE
	int wTex, hTex;		// actual size of ogl texture 
} oglTexture;

bool		oglInit(int w, int h, int bpp, Uint32 flags);		// init opengl

void		oglFreeTexture(oglTexture	*texture);				// free texture created from oglFromSurface

void		oglBlit(oglTexture* texture, SDL_Rect* clipping, int x, int y, GLfloat hZoom, GLfloat vZoom, GLfloat rotation);	// copy texture to screen, x & y are left top corner of image
void		oglBlit(oglTexture* texture, SDL_Rect* clipping, int x, int y, GLfloat Alfa, GLfloat hZoom, GLfloat vZoom, GLfloat rotation);	// copy texture to screen, x & y are left top corner of image

void		oglCBlit(oglTexture* texture, SDL_Rect* clipping, int x, int y, GLfloat hZoom, GLfloat vZoom, GLfloat rotation);	// copy texture to screen, x & y are center of image
void		oglCBlit(oglTexture* texture, SDL_Rect* clipping, int x, int y, GLfloat Alfa, GLfloat hZoom, GLfloat vZoom, GLfloat rotation);	// copy texture to screen, x & y are center of image

oglTexture	*oglFromSurface(SDL_Surface* surface);				// create texture from SDL_Surface
oglTexture	*oglFromSurfaceFree(SDL_Surface* surface);			// create texture from surface, release the surface


