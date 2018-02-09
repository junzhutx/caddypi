/**
 *  @filename   :   main.cpp
 *  @brief      :   2.13inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 9 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#if 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "epd2in13.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED      0
#define UNCOLORED    1

int main(void)
{
    time_t now;
    struct tm* timenow;

    Epd2in13 epd;
    if (epd.Init(false) != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }

    unsigned char* frame_buffer = (unsigned char*)malloc(epd.width / 8 * epd.height);

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.SetInvertColor(true);
    paint.Clear(UNCOLORED);

    /* For simplicity, the arguments are explicit numerical coordinates */
    /* Write strings to the buffer */
    paint.DrawFilledRectangle(0, 10, 128, 30, COLORED);
    paint.DrawStringAt(30, 14, "Hello world!", &Font12, UNCOLORED);
    paint.DrawStringAt(30, 34, "e-Paper Demo", &Font12, COLORED);

    /* Draw something to the frame_buffer */
    paint.DrawRectangle(10, 60, 50, 100, COLORED);
    paint.DrawLine(10, 60, 50, 100, COLORED);
    paint.DrawLine(50, 60, 10, 100, COLORED);
    paint.DrawCircle(88, 80, 30, COLORED);
    paint.DrawFilledRectangle(10, 120, 50, 180, COLORED);
    paint.DrawFilledCircle(88, 150, 30, COLORED);

    /* Display the frame_buffer */
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    epd.DelayMs(2000);

    if (epd.Init(true) != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }

  /**
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to set the frame memory and refresh the display twice.
   */
    epd.SetFrameMemory(IMAGE_DATA, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();
    epd.SetFrameMemory(IMAGE_DATA, 0, 0, epd.width, epd.height);
    epd.DisplayFrame();

    char time_string[] = {'0', '0', ':', '0', '0', '\0'};
    while (1) {
        time(&now);
        timenow = localtime(&now);
        time_string[0] = timenow->tm_min / 10 + '0';
        time_string[1] = timenow->tm_min % 10 + '0';
        time_string[3] = timenow->tm_sec / 10 + '0';
        time_string[4] = timenow->tm_sec % 10 + '0';

        paint.SetWidth(32);
        paint.SetHeight(96);
        paint.SetRotate(ROTATE_90);
        paint.Clear(UNCOLORED);
        paint.DrawStringAt(8, 4, time_string, &Font24, COLORED);

        epd.SetFrameMemory(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
        epd.DisplayFrame();
        epd.DelayMs(500);
    }
    return 0;
}
#else
#include <stdlib.h>
#include <stdio.h>
#include "epd1in54b.h"
#include "imagedata_1in54b.h"
#include "epdpaint.h"

#define COLORED      1
#define UNCOLORED    0

int main(void)
{
    Epd1in54b epd;
    if (epd.Init(false) != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }
    
    unsigned char* frame_black = (unsigned char*)malloc(epd.width * epd.height / 8);
    unsigned char* frame_red = (unsigned char*)malloc(epd.width * epd.height / 8);

    Paint paint_black(frame_black, epd.width, epd.height);
    Paint paint_red(frame_red, epd.width, epd.height);
    paint_black.Clear(UNCOLORED);
    paint_red.Clear(UNCOLORED);

    /* Draw something to the frame buffer */
    /* For simplicity, the arguments are explicit numerical coordinates */
    paint_black.DrawRectangle(10, 60, 50, 110, COLORED);
    paint_black.DrawLine(10, 60, 50, 110, COLORED);
    paint_black.DrawLine(50, 60, 10, 110, COLORED);
    paint_black.DrawCircle(120, 80, 30, COLORED);
    paint_red.DrawFilledRectangle(10, 130, 50, 180, COLORED);
    paint_red.DrawFilledRectangle(0, 6, 200, 26, COLORED);
    paint_red.DrawFilledCircle(120, 150, 30, COLORED);

    /*Write strings to the buffer */
    paint_black.DrawStringAt(30, 30, "e-Paper Demo", &Font16, COLORED);
    paint_red.DrawStringAt(28, 10, "Hello world!", &Font16, UNCOLORED);
   
    /* Display the frame buffer */
    epd.DisplayFrame(frame_black, frame_red);

    /* Display the image buffer */
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
    return 0;
}

#endif
