/* comic.c
 * Copyright (C) 2014 Iris Connect Ltd
 * This file is a Frei0r plugin.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <stdio.h>

#include "frei0r.h"


const uint32_t white = 0x00FFFFFF;
const uint32_t honeyDew = 0x00F0FFF0;
const uint32_t mintCream = 0x00F5FFFA;


/* Clamps a int32-range int between 0 and 255 inclusive. */
unsigned char CLAMP0255(int32_t a)
{
  return (unsigned char)
    ( (((-a) >> 31) & a)  // 0 if the number was negative
      | (255 - a) >> 31); // -1 if the number was greater than 255
}

typedef struct comic_instance {
  unsigned int width;
  unsigned int height;
} comic_instance_t;


uint32_t reify_pixel(uint32_t inPixel) {

  uint32_t tmp = 0;
  uint32_t alpha = inPixel & 0xFF0000;
  uint32_t purePxl = inPixel & 0x00FFFFFF;

  
  //Craft back the pixel, preserving the alpha
  return (purePxl + 20) | alpha;

}


int f0r_init()
{
  return 1;
}

void f0r_deinit()
{ /* no de-initialization required */ }

void f0r_get_plugin_info(f0r_plugin_info_t* inverterInfo)
{
  inverterInfo->name = "Comic";
  inverterInfo->author = "adinapoli";
  inverterInfo->plugin_type = F0R_PLUGIN_TYPE_FILTER;
  inverterInfo->color_model = F0R_COLOR_MODEL_RGBA8888;
  inverterInfo->frei0r_version = FREI0R_MAJOR_VERSION;
  inverterInfo->major_version = 0; 
  inverterInfo->minor_version = 1; 
  inverterInfo->num_params =  2; 
  inverterInfo->explanation = "Comicbook effect";
}

void f0r_get_param_info(f0r_param_info_t* info, int param_index)
{
}

f0r_instance_t f0r_construct(unsigned int width, unsigned int height) {
  //build colour palette here
  comic_instance_t* inst = (comic_instance_t*)calloc(1, sizeof(*inst));

  inst->width = width; 
  inst->height = height;
  return (f0r_instance_t)inst;
}

void f0r_destruct(f0r_instance_t instance)
{
  free(instance);
}

void f0r_set_param_value(f0r_instance_t instance, 
                         f0r_param_t param, int param_index)
{
  assert(instance);
}

void f0r_get_param_value(f0r_instance_t instance,
                         f0r_param_t param, int param_index)
{
  assert(instance);
}

void f0r_update(f0r_instance_t instance, double time,
                const uint32_t* inframe, uint32_t* outframe)
{
  assert(instance);
  comic_instance_t* inst = (comic_instance_t*)instance;
  
  for (int w = 0; w < inst->width; w++) {
    for (int h = 0; h < inst->height; h++) {
      uint32_t inPixel = inframe[inst->width * h + w];

      //const char alpha = inPixel[0];
      //const char red   = inPixel[1];
      //const char green = inPixel[2];
      //const char blue  = inPixel[3];

      // Do a stupid chroma-shift
      //unsigned char* outPixel = (unsigned char*)(&outframe[inst->width * h + w]);
      uint32_t* outPixel = &outframe[inst->width * h + w];
      *outPixel = reify_pixel(inPixel);
    }
  }
}

