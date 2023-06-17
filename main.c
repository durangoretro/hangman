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

void load_word(void);

const char word[13] =   {'R','R','I','N','O','C','E','R','O','N','T','E',0};
const char secret[13] = {'_','_','_','_','_','_','_','_','_','_','_','_',0};

int main() {
    load_background(hang10);
    clrscr();
    
    
    
    printStr(10, 110, font, WHITE, BLACK, (char*)secret);
    
    while(1) {
    };
    
    return 0;
}

void load_word() {
    
}

