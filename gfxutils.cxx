
#include "libs/rpi-rgb-led-matrix/include/led-matrix.h"
#include "libs/rpi-rgb-led-matrix/include/graphics.h"

static void DrawBorder(rgb_matrix::Canvas *canvas, rgb_matrix::Color &color, int edge_offset) {
  int width = canvas->width();
  int height = canvas->height();
  rgb_matrix::DrawLine(canvas, edge_offset, edge_offset, width - 1 - edge_offset, edge_offset, color);
  rgb_matrix::DrawLine(canvas, edge_offset, edge_offset, edge_offset, height - 1 - edge_offset, color);
  rgb_matrix::DrawLine(canvas, edge_offset, height - 1 - edge_offset, width - 1 - edge_offset, height - 1 - edge_offset, color);
  rgb_matrix::DrawLine(canvas, width - 1 - edge_offset, edge_offset, width - 1 - edge_offset, height - 1 - edge_offset, color);
}