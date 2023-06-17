SOURCE_DIR=.
RESCOMP ?= ../rescomp/target/rescomp.jar
BUILD_DIR ?= bin
CFG ?= ../dclib/cfg/durango16k.cfg
DCLIB ?= ../dclib/bin
DCINC ?= ../dclib/inc

all: hangout.dux

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/hang01.h: hang01.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang01 -m BACKGROUND -i hang01.png -o $(BUILD_DIR)/hang01.h
$(BUILD_DIR)/hang02.h: hang02.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang02 -m BACKGROUND -i hang02.png -o $(BUILD_DIR)/hang02.h
$(BUILD_DIR)/hang03.h: hang03.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang03 -m BACKGROUND -i hang03.png -o $(BUILD_DIR)/hang03.h
$(BUILD_DIR)/hang04.h: hang04.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang04 -m BACKGROUND -i hang04.png -o $(BUILD_DIR)/hang04.h
$(BUILD_DIR)/hang05.h: hang05.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang05 -m BACKGROUND -i hang05.png -o $(BUILD_DIR)/hang05.h
$(BUILD_DIR)/hang06.h: hang06.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang06 -m BACKGROUND -i hang06.png -o $(BUILD_DIR)/hang06.h
$(BUILD_DIR)/hang07.h: hang07.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang07 -m BACKGROUND -i hang07.png -o $(BUILD_DIR)/hang07.h
$(BUILD_DIR)/hang08.h: hang08.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang08 -m BACKGROUND -i hang08.png -o $(BUILD_DIR)/hang08.h
$(BUILD_DIR)/hang09.h: hang09.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang09 -m BACKGROUND -i hang09.png -o $(BUILD_DIR)/hang09.h
$(BUILD_DIR)/hang10.h: hang10.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n hang10 -m BACKGROUND -i hang10.png -o $(BUILD_DIR)/hang10.h
	
$(BUILD_DIR)/main.casm: $(SOURCE_DIR)/main.c $(BUILD_DIR) $(BUILD_DIR)/hang01.h $(BUILD_DIR)/hang02.h $(BUILD_DIR)/hang03.h $(BUILD_DIR)/hang04.h $(BUILD_DIR)/hang05.h $(BUILD_DIR)/hang06.h $(BUILD_DIR)/hang07.h $(BUILD_DIR)/hang08.h $(BUILD_DIR)/hang09.h $(BUILD_DIR)/hang10.h
	cc65 -I $(DCINC) $(SOURCE_DIR)/main.c -t none --cpu 6502 -o $(BUILD_DIR)/main.casm

$(BUILD_DIR)/main.o: $(BUILD_DIR)/main.casm $(BUILD_DIR)
	ca65 -t none $(BUILD_DIR)/main.casm -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/hangout.bin: $(BUILD_DIR) $(BUILD_DIR)/main.o
	ld65 -m $(BUILD_DIR)/hangout.txt -C $(CFG) $(BUILD_DIR)/main.o $(DCLIB)/glyph.lib $(DCLIB)/qgraph.lib $(DCLIB)/sprites.lib $(DCLIB)/system.lib $(DCLIB)/durango.lib $(DCLIB)/psv.lib $(DCLIB)/glyph.lib -o $(BUILD_DIR)/hangout.bin	

hangout.dux: $(BUILD_DIR)/hangout.bin $(BUILD_DIR)
	java -jar ${RESCOMP} -m SIGNER -n $$(git log -1 | head -1 | sed 's/commit //' | cut -c1-8) -t hangout -d "Pesca todos los peces que puedas. ¡Ojo al color del cebo!" -i $(BUILD_DIR)/hangout.bin -o hangout.dux

clean:
	rm -Rf $(BUILD_DIR) hangout.dux
