#include <system.h>
#include <sprites.h>
#include <glyph.h>
#include <font.h>
#include <qgraph.h>
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
void next_myword(void);
void success(void);

char* myword;
char len;
char secret[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char current;
char fail_count;

int main() {
	int seed;
	clear_screen();
    load_background(hang10);
    clrscr();
	printStr(80, 10, font, WHITE, BLACK, "AHORCADO");
	printStr(10, 110, font, WHITE, BLACK, "Presiona enter...");
	
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
    myword=(char*) dictionary;
    load_word();
}

void load_word() {
    char i, ran, current;
    
    // Search random myword
    ran = random();
    i=0;
    do {
        next_myword();
        i++;
    } while(i<ran);
    
    // Initialize secret
    i=0;
    do {
        current=myword[i];
        if(current != 0) {
            secret[i]='_';
        }
        i++;
    } while(current != 0);
    secret[i]=0;
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
    // Put matching letters
    do {
        current=myword[i];
        if(search == current) {
            secret[i]=myword[i];
            found = 1;
        }
        i++;
    } while(current != 0);
    
    if(found==0) {
        fail();
    }
    
    // Check if myword is found
    i=0;
    found = 1;
    do {
        if(secret[i]=='_') {
            found = 0;
        }
        i++;
    } while(secret[i] != 0);
    
    if(found==1) {
        success();
        waitStart();
        fail_count=0;
        clear_screen();
        load_word();
    }
        
    printStr(10, 110, font, WHITE, BLACK, (char*)secret);
}

void next_myword(void) {
    do {
        myword++;
    } while(myword[0]!=0);
    myword++;
    if(myword[0]<32) {
        myword=(char*) dictionary;
    }
}

void success(void) {
    rectangle rect;
    
    rect.x=18;
    rect.y=28;
    rect.width=84;
    rect.height=34;
    rect.color=WHITE;
    drawRect(&rect);
    
    rect.x=20;
    rect.y=30;
    rect.width=80;
    rect.height=30;
    rect.color=BLACK;
    drawRect(&rect);
        
    printStr(30, 40, font, WHITE, BLACK, "!TU GANAS!");
    printStr(10, 110, font, WHITE, BLACK, "Presiona enter...");
}
