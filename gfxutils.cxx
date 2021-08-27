
#include "libs/rpi-rgb-led-matrix/include/led-matrix.h"
#include "libs/rpi-rgb-led-matrix/include/graphics.h"

static void DrawBorder(rgb_matrix::Canvas *canvas, rgb_matrix::Color const &color, int edge_offset) {
  int width = canvas->width();
  int height = canvas->height();
  rgb_matrix::DrawLine(canvas, edge_offset, edge_offset, width - 1 - edge_offset, edge_offset, color);
  rgb_matrix::DrawLine(canvas, edge_offset, edge_offset, edge_offset, height - 1 - edge_offset, color);
  rgb_matrix::DrawLine(canvas, edge_offset, height - 1 - edge_offset, width - 1 - edge_offset, height - 1 - edge_offset, color);
  rgb_matrix::DrawLine(canvas, width - 1 - edge_offset, edge_offset, width - 1 - edge_offset, height - 1 - edge_offset, color);
}

static void DrawBorder(rgb_matrix::Canvas *canvas, rgb_matrix::Color const &color, int width, int height, int offset_x, int offset_y) {
  rgb_matrix::DrawLine(canvas, offset_x, offset_y, offset_x + width - 1, offset_y, color);
  rgb_matrix::DrawLine(canvas, offset_x + width - 1, offset_y, offset_x + width - 1, offset_y + height - 1, color);
  rgb_matrix::DrawLine(canvas, offset_x, offset_y + height - 1, offset_x + width - 1, offset_y + height - 1, color);
  rgb_matrix::DrawLine(canvas, offset_x, offset_y, offset_x, offset_y + height - 1, color);
}