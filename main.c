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
#include "bin/dic.h"

int main(void);

void load_word(void);
void update_game(void);
void init_game(void);
void fail(void);
void next_word(void);

char* word;
char len;
char secret[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char current;
char fail_count;

int main() {
	int seed;
	clear_screen();
    load_background(hang10);
    clrscr();
	printStr(80, 10, font, WHITE, BLACK, "HANGMAN");
	printStr(10, 110, font, WHITE, BLACK, "Press enter...");
	
    waitStart();
	seed=get_time();
	random_init(seed);
	
	init_game();
    
    printStr(10, 110, font, WHITE, BLACK, (char*)secret);
    
    while(1) {
        update_game();
    };
    
    return 0;
}

void init_game() {
    fail_count=0;
    clear_screen();
    word=(char*) words;
    load_word();
}

void load_word() {
    char i, ran, current;
    
    // Search random word
    ran = random();
    i=0;
    do {
        next_word();
        i++;
    } while(i<ran);
    
    // Initialize secret
    i=0;
    do {
        current=word[i];
        if(current != 0) {
            secret[i]='_';
        }
        i++;
    } while(current != 0);
}

void fail() {
    fail_count++;
    if(fail_count==1) {
        load_background(hang01);
    }
    if(fail_count==2) {
        load_background(hang02);
    }
    if(fail_count==3) {
        load_background(hang03);
    }
    if(fail_count==4) {
        load_background(hang04);
    }
    if(fail_count==5) {
        load_background(hang05);
    }
    if(fail_count==6) {
        load_background(hang06);
    }
    if(fail_count==7) {
        load_background(hang07);
    }
    if(fail_count==8) {
        load_background(hang08);
    }
    if(fail_count==9) {
        load_background(hang09);
    }
    if(fail_count==10) {
        load_background(hang10);
    }
    
    clrscr();
}

void update_game() {
    char i, search, current, found;
    search = getchar();
    i=0;
    found = 0;
    do {
        current=word[i];
        if(search == current) {
            secret[i]=word[i];
            found = 1;
        }
        i++;
    } while(current != 0);
    
    if(found==0) {
        fail();
    }
    
    printStr(10, 110, font, WHITE, BLACK, (char*)secret);
}

void next_word(void) {
    do {
        word++;
    } while(word[0]!=0);
    word++;
    if(word[0]<32) {
        word=(char*) words;
    }
}
