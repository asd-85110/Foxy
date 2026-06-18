/*
Note: This license has also been called the “New BSD License” or “Modified BSD License”. See also the 2-clause BSD License.

Copyright 2026-2028 asd-85110

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <GLFW/glfw3.h>
#include <csetjmp>
#include <cstdlib>
#include <cstring>
#include <libpng18/png.h>
#include <libpng18/pngconf.h>
#include <new>
namespace Tools {
GLFWimage*
load_png(const char* filename, int* width, int* height) {
    FILE* fp = fopen(filename, "rb");
    if(!fp)
        return nullptr;
    png_byte header[8];
    fread(header, 1, 8, fp);
    if(png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        return nullptr;
    }
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if(!png) {
        fclose(fp);
        return nullptr;
    }
    png_infop info = png_create_info_struct(png);
    if(!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return nullptr;
    }
    if(setjmp(png_jmpbuf(png))) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return nullptr;
    }
    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);
    int w = png_get_image_width(png, info);
    int h = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    if(bit_depth == 16) {
        png_set_strip_16(png);
    }
    if(color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png);
    }
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png);
    }
    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    png_read_update_info(png, info);
    try {
        png_bytep* row_pointers = new png_bytep[h];
        for(int y = 0; y < h; ++y) {
            row_pointers[y] = new png_byte[png_get_rowbytes(png, info)];
        }
        png_read_image(png, row_pointers);
        fclose(fp);
        GLFWimage* image = new GLFWimage;
        image->width = w;
        image->height = h;
        image->pixels = new unsigned char[w * h * 4];
        for(int y = 0; y < h; ++y) {
            memcpy(image->pixels + y * w * 4, row_pointers[y], w * 4);
        }
        for(int y = 0; y < h; ++y) {
            delete[] row_pointers[y];
        }
        delete[] row_pointers;
        png_destroy_read_struct(&png, &info, nullptr);
        if(width)
            *width = w;
        if(height)
            *height = h;
        return image;
    } catch(const std::bad_alloc&) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return nullptr;
    }
}
int Values[4];
}// namespace Tools