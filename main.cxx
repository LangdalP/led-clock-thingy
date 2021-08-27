// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

    /*
 * TODO:
 * 1: Finn kode for å vise klokke
 * 2: Gjer noko anna kult
 * 3: ???
 * 4: Profit!
 */

#include "gfxutils.cxx"

#include "libs/rpi-rgb-led-matrix/include/led-matrix.h"
#include "libs/rpi-rgb-led-matrix/include/graphics.h"

#include <iostream>

#include <unistd.h>
#include <math.h>
#include <stdio.h>

const int TEXT_X = 3;
const int TEXT_Y = 2;

const int letter_spacing = 0;

const rgb_matrix::Color border_color(102, 58, 0);
const rgb_matrix::Color border_color2(0, 36, 43);
const rgb_matrix::Color progress_color(0, 36, 43);
const rgb_matrix::Color text_color(102, 58, 0);

typedef struct DrawClockDependencies {
  time_t time_since_epoch;
  struct tm time_parts;
  char* text_buffer;
} DrawClockDependencies;

static void DrawClockScreen(rgb_matrix::RGBMatrix *matrix, rgb_matrix::FrameCanvas *offscreen, DrawClockDependencies& deps, rgb_matrix::Font& font)
{
  // Draw time text
  offscreen->Clear();
  deps.time_since_epoch = time(NULL);
  localtime_r(&(deps.time_since_epoch), &(deps.time_parts));
  strftime(deps.text_buffer, 64, "%H:%M", &(deps.time_parts));
  rgb_matrix::DrawText(offscreen, font,
                        TEXT_X, TEXT_Y + font.baseline(),
                        text_color, NULL, deps.text_buffer,
                        letter_spacing);

  // Draw border
  DrawBorder(offscreen, border_color, 33, 14, 1, 1);

  float progress_fraction = (float)deps.time_parts.tm_sec / 60.0f;
  int progress_width = (int) (29.0f * progress_fraction);
  // std::cout << progress_width << std::endl;

  // draw progress bar
  rgb_matrix::DrawLine(offscreen, 3, 12, 3 + progress_width, 12, progress_color);
}

static void DrawWeatherScreen(rgb_matrix::RGBMatrix *matrix, rgb_matrix::FrameCanvas *offscreen)
{
  // draw border for weather widget
  DrawBorder(offscreen, border_color2, 62, 15, 1, 16);

  offscreen = matrix->SwapOnVSync(offscreen);
}

int main(int argc, char *argv[])
{
  std::cout << "----------" << std::endl;
  std::cout << "Starting awesome clock program!" << std::endl;
  std::cout << "----------" << std::endl;

  rgb_matrix::RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular"; // or e.g. "adafruit-hat"
  defaults.rows = 32;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  rgb_matrix::RGBMatrix *matrix = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  rgb_matrix::FrameCanvas *offscreen = matrix->CreateFrameCanvas();
  if (matrix == NULL || offscreen == NULL) {
    std::cerr << "Failed to init matrix or offscreen. Aborting." << std::endl;
    return 1;
  }

  rgb_matrix::Font font;
  // if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/7x13.bdf"))
  if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/6x10.bdf"))
  {
    std::cerr << "Couldn't load font" << std::endl;
    return 1;
  }

  struct DrawClockDependencies deps;
  deps.text_buffer = (char*)malloc(64);

  while (true) {
    DrawClockScreen(matrix, offscreen, deps, font);
    DrawWeatherScreen(matrix, offscreen);

    // usleep(100 * 1000);
    usleep(100 * 1000);
  }

  delete matrix;

  return 0;
}
