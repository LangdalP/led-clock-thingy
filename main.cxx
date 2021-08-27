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
#include <signal.h>

const int TEXT_X = 3;
const int TEXT_Y = 2;

volatile bool interrupt_received = false;
volatile bool next_received = false;

enum Scene : short { Clock, Other, NUM_SCENE_ITEMS };
short currentScene = Clock;


static void QuitHandler(int signo)
{
  interrupt_received = true;
}

static void NextHandler(int signo)
{
  next_received = true;
}

static void SetNext() {
  currentScene = (currentScene + 1) % NUM_SCENE_ITEMS;
  next_received = false;
}

#include "clock.cxx"
/*
static void DrawClock(rgb_matrix::RGBMatrix *matrix, rgb_matrix::FrameCanvas *offscreen)
{
  rgb_matrix::Color border_color(214, 39, 39); // Pretty Red
  rgb_matrix::Color border_color2(36, 116, 201); // Pretty Blue

  // rgb_matrix::Color text_color(255, 128, 0); // Orange
  // rgb_matrix::Color text_color(255, 0, 119); // Pink
  rgb_matrix::Color text_color(0, 255, 179); // Turqoise
  int letter_spacing = 0;

  rgb_matrix::Font font;
  if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/7x13.bdf"))
  {
    std::cerr << "Couldn't load font" << std::endl;
    return;
  }

  time_t time_since_epoch;
  struct tm time_parts;

  char text_buffer[64];
  matrix->Clear();

  while (!interrupt_received)
  {
    if (next_received) {
      SetNext();
      return;
    }
    // Draw time text
    offscreen->Clear();
    time_since_epoch = time(NULL);
    localtime_r(&time_since_epoch, &time_parts);
    strftime(text_buffer, sizeof(text_buffer), "%H:%M:%S", &time_parts);
    rgb_matrix::DrawText(offscreen, font,
                         TEXT_X, TEXT_Y + font.baseline(),
                         text_color, NULL, text_buffer,
                         letter_spacing);

    // Draw border
    DrawBorder(offscreen, border_color, 0);
    DrawBorder(offscreen, border_color2, 1);

    offscreen = matrix->SwapOnVSync(offscreen);
    // TODO: Consider improving wait logic
    // Advantage of sleeping for 1 second: Always ~one second between changes from one second to the next.
    usleep(100 * 1000);
  }
}
*/

static void DrawOther(rgb_matrix::RGBMatrix *matrix, rgb_matrix::FrameCanvas *offscreen)
{
  rgb_matrix::Color text_color(0, 255, 179); // Turqoise
  int letter_spacing = 0;

  rgb_matrix::Font font;
  if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/7x13.bdf"))
  {
    std::cerr << "Couldn't load font" << std::endl;
    return;
  }

  char text_buffer[64] = "Hei!";
  matrix->Clear();

  while (!interrupt_received)
  {
    if (next_received) {
      SetNext();
      return;
    }
    offscreen->Clear();
    rgb_matrix::DrawText(offscreen, font,
                         TEXT_X, TEXT_Y + font.baseline(),
                         text_color, NULL, text_buffer,
                         letter_spacing);

    offscreen = matrix->SwapOnVSync(offscreen);
    usleep(100 * 1000);
  }
}

int main(int argc, char *argv[])
{
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

/*
  signal(SIGTERM, QuitHandler);
  signal(SIGQUIT, QuitHandler);  // Ctrl+D
  signal(SIGINT, NextHandler);   // Ctrl+C
  */


  while(true) {
    switch (currentScene)
    {
    case Clock:
      DrawClockScreen(matrix, offscreen);
      break;
    case Other:
      DrawOther(matrix, offscreen);
      break;
    default:
      break;
    }
  }

  delete matrix;

  return 0;
}
