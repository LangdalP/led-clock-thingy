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

#include "libs/rpi-rgb-led-matrix/include/led-matrix.h"
#include "libs/rpi-rgb-led-matrix/include/graphics.h"

#include <iostream>

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

using rgb_matrix::Canvas;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Color;

const int TEXT_X = 10;
const int TEXT_Y = 10;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo)
{
  interrupt_received = true;
}

static void DrawStuff(Canvas *canvas)
{
  // TODO:
  // - Consider an "offscreen" buffer

  Color text_color(255, 128, 0);
  int letter_spacing = 0;

  rgb_matrix::Font font;
  if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/8x13.bdf"))
  {
    std::cerr << "Couldn't load font" << std::endl;
    return;
  }

  struct timespec next_time;
  time_t time_since_epoch = time(NULL);
  struct tm time_parts;

  char text_buffer[64];
  canvas->Clear();

  while (!interrupt_received)
  {
    localtime_r(&time_since_epoch, &time_parts);
    strftime(text_buffer, sizeof(text_buffer), "%H:%M:%S", &time_parts);
    rgb_matrix::DrawText(canvas, font,
                         TEXT_X, TEXT_Y + font.baseline(),
                         text_color, NULL, text_buffer,
                         letter_spacing);
  }
  usleep(500 * 1000);
}

int main(int argc, char *argv[])
{
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular"; // or e.g. "adafruit-hat"
  defaults.rows = 32;
  defaults.cols = 64;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  DrawStuff(canvas);

  canvas->Clear();
  delete canvas;

  return 0;
}
