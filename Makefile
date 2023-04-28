SOURCE_DIR=.
RESCOMP ?= ../rescomp/target/rescomp.jar
BUILD_DIR ?= bin
CFG ?= ../dclib/cfg/durango16k.cfg
DCLIB ?= ../dclib/bin
DCINC ?= ../dclib/inc

all: hangout.dux

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/sprites.h: sprites.png $(BUILD_DIR)
	java -jar ${RESCOMP} -n sprites -m BACKGROUND -i sprites.png -o $(BUILD_DIR)/sprites.h
	
$(BUILD_DIR)/main.casm: $(SOURCE_DIR)/main.c $(BUILD_DIR) $(BUILD_DIR)/sprites.h
	cc65 -I $(DCINC) $(SOURCE_DIR)/main.c -t none --cpu 6502 -o $(BUILD_DIR)/main.casm

$(BUILD_DIR)/main.o: $(BUILD_DIR)/main.casm $(BUILD_DIR)
	ca65 -t none $(BUILD_DIR)/main.casm -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/hangout.bin: $(BUILD_DIR) $(BUILD_DIR)/main.o
	ld65 -m $(BUILD_DIR)/hangout.txt -C $(CFG) $(BUILD_DIR)/main.o $(DCLIB)/glyph.lib $(DCLIB)/qgraph.lib $(DCLIB)/sprites.lib $(DCLIB)/system.lib $(DCLIB)/durango.lib $(DCLIB)/psv.lib -o $(BUILD_DIR)/hangout.bin	

hangout.dux: $(BUILD_DIR)/hangout.bin $(BUILD_DIR)
	java -jar ${RESCOMP} -m SIGNER -n $$(git log -1 | head -1 | sed 's/commit //' | cut -c1-8) -t hangout -d "Pesca todos los peces que puedas. ¡Ojo al color del cebo!" -i $(BUILD_DIR)/hangout.bin -o hangout.dux

clean:
	rm -Rf $(BUILD_DIR) hangout.dux
