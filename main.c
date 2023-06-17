#include <system.h>
#include <sprites.h>
#include <glyph.h>
#include <font.h>
#include <psv.h>
#include "bin/hang01.h"
#include "bin/hang02.h"
#include "bin/hang03.h"
#include "bin/hang04.h"
#include "bin/hang05.h"
#include "bin/hang06.h"
#include "bin/hang07.h"
#include "bin/hang08.h"
#include "bin/hang09.h"
#include "bin/hang10.h"

int main(void);


int main() {
    load_background(hang10);
    clrscr();
    printStr(10, 110, font, WHITE, BLACK, "A________");
    
    while(1) {
    };
}

