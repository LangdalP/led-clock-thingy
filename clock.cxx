#include "libs/rpi-rgb-led-matrix/include/led-matrix.h"
#include "libs/rpi-rgb-led-matrix/include/graphics.h"

const rgb_matrix::Color border_color(102, 58, 0);
const rgb_matrix::Color border_color2(0, 36, 43);

const rgb_matrix::Color progress_color(0, 36, 43);

rgb_matrix::Color text_color(102, 58, 0);

static void DrawClockScreen(rgb_matrix::RGBMatrix *matrix, rgb_matrix::FrameCanvas *offscreen)
{

  // rgb_matrix::Color text_color(255, 128, 0); // Orange
  // rgb_matrix::Color text_color(255, 0, 119); // Pink
  int letter_spacing = 0;

  rgb_matrix::Font font;
  // if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/7x13.bdf"))
  if (!font.LoadFont("libs/rpi-rgb-led-matrix/fonts/6x10.bdf"))
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
    strftime(text_buffer, sizeof(text_buffer), "%H:%M", &time_parts);
    rgb_matrix::DrawText(offscreen, font,
                         TEXT_X, TEXT_Y + font.baseline(),
                         text_color, NULL, text_buffer,
                         letter_spacing);

    // Draw border
    DrawBorder(offscreen, border_color, 33, 14, 1, 1);

    float progress_fraction = (float)time_parts.tm_sec / 60.0f;
    int progress_width = (int) (29.0f * progress_fraction);
    // std::cout << progress_width << std::endl;

    rgb_matrix::DrawLine(offscreen, 3, 12, 3 + progress_width, 12, progress_color);

    DrawBorder(offscreen, border_color2, 62, 15, 1, 16);

    offscreen = matrix->SwapOnVSync(offscreen);
    // TODO: Consider improving wait logic
    // Advantage of sleeping for 1 second: Always ~one second between changes from one second to the next.
    usleep(100 * 1000);
  }
}