

CC			:= $(CC_PATH)g++
CFLAGS		:= -c -Wall -std=c++11 
LDFLAGS		:= --static
EXECUTABLE	:= xattrScanner
OBJS_DIR	:= ./objs
OUT_DIR		:= ./
INC_DIR 	:= ./inc/
MKDIR_P 	:= mkdir -p

SRCEXT		:= cpp
OBJEXT		:= o
SRCDIR		:= ./src

SOURCES     := $(shell find $(SRCDIR) -type f -name \*.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(OBJS_DIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


all: directories $(SOURCES) $(EXECUTABLE)

directories:
	echo $(OBJECTS)
	${MKDIR_P} ${OBJS_DIR} ${OUT_DIR}


    
$(EXECUTABLE): $(OBJECTS) 
	echo $(SOURCES)
	echo $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(OUT_DIR)/$@

objs/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -I$(INC_DIR) $< -o $@

clean:
	rm -rf $(OBJS_DIR)/*.o
	rmdir $(OBJS_DIR)
	rm $(EXECUTABLE)
