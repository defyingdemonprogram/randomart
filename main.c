#include <stdio.h>
#include <stdint.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH 400
#define HEIGHT 400
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} RBGA32;

static RBGA32 pixels[WIDTH*HEIGHT];

typedef struct {
	float x, y;
} Vector2;

typedef struct {
	float r, g, b;
} Color;

Color gray_gradient(float x, float y) {
	(void)y;
	return (Color) { x, x, x };
}

Color cool(float x, float y) {
	if (x*y > 0) return (Color){x, y, 1};
	float r = fmodf(x + 1e-3, y + 1e-3);
	return (Color) {r, r, r};
}

void render_pixels(Color (*f)(float x, float y)) {
	for (size_t y = 0; y < HEIGHT; ++y) {
		// Normalize the value between -1..1
		float ny = (float)y/HEIGHT*2.0f - 1;
		for (size_t x = 0; x < WIDTH; ++x) {
			float nx = (float)x/WIDTH*2.0f - 1;
			Color c = f(nx, ny);
			// -1..1 => 0..2 => 0..255
			size_t index = y*WIDTH + x;
			pixels[index].r = (c.r + 1)/2*255;
			pixels[index].g = (c.g + 1)/2*255;
			pixels[index].b = (c.b + 1)/2*255;
			pixels[index].a = 255;;
		}
	}
}

int main() {
	// render_pixels(gray_gradient);
	render_pixels(cool);
	const char *output_path = "output.png";
	if (!stbi_write_png(output_path, WIDTH, HEIGHT, 4, pixels, WIDTH*sizeof(RBGA32))) {
		fprintf(stderr, "Could not save image %s", output_path);
		return 1;
	};
	printf("File Saved in %s\n", output_path);
	return 0;
}
