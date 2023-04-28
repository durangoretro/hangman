#include <system.h>
#include <sprites.h>
#include <glyph.h>
#include <font.h>
#include <psv.h>
#include "bin/sprites.h"

int main(void);


int main() {
    load_background(sprites);
    printStr(10, 110, font, WHITE, BLACK, "A________");
    
    while(1) {
    };
}

