#include "builtinpix.h"

Glib::RefPtr<Gdk::Pixbuf> redDot;
Glib::RefPtr<Gdk::Pixbuf> yellowDot;
Glib::RefPtr<Gdk::Pixbuf> blackLoop;
Glib::RefPtr<Gdk::Pixbuf> grayLoop;

extern const unsigned char red_dot_rgba[];
extern const unsigned char yellow_dot_rgba[];
extern const unsigned char black_loop_rgba[];
extern const unsigned char gray_loop_rgba[];

extern const int red_dot_rgba_size;
extern const int yellow_dot_rgba_size;
extern const int black_loop_rgba_size;
extern const int gray_loop_rgba_size;

static struct _BuiltInPixMap {
    Glib::RefPtr<Gdk::Pixbuf>* pixbuf;
    const unsigned char* raw;
    int size;
} builtInPixMap[] = {
    { &redDot, red_dot_rgba, red_dot_rgba_size },
    { &yellowDot, yellow_dot_rgba, yellow_dot_rgba_size },
    { &blackLoop, black_loop_rgba, black_loop_rgba_size },
    { &grayLoop, gray_loop_rgba, gray_loop_rgba_size },
};

void loadBuiltInPix() {
    if (*builtInPixMap[0].pixbuf) return;
    const int n = sizeof(builtInPixMap) / sizeof(_BuiltInPixMap);
    for (int i = 0; i < n; ++i) {
        *builtInPixMap[i].pixbuf = Gdk::Pixbuf::create_from_inline(
            builtInPixMap[i].size,
            builtInPixMap[i].raw
        );
    }
}
