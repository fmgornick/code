CC 			= gcc
SRC_DIR 	= src
OBJ_DIR 	= obj
CFLAGS 		= -Wall							  	\
			  -Wno-unused-command-line-argument \
			  -DG_DISABLE_DEPRECATED          	\
			  -DGDK_DISABLE_DEPRECATED        	\
			  -DGDK_PIXBUF_DISABLE_DEPRECATED 	\
			  -DGTK_DISABLE_DEPRECATED
EXE			= logic
PACKAGE		= `pkg-config --cflags --libs gtk+-3.0`
LIBS		= `pkg-config --libs gtk+-3.0`

SRCS = $(SRC_DIR)/main2.c 
OBJS = $(OBJ_DIR)/main2.o

main: clean build

clean:
	rm -f $(OBJS) $(EXE)

build: $(OBJS)
	$(CC) $(LIBS) $(CFLAGS) $(OBJS) -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(PACKAGE) $(CFLAGS) -c $< -o $@ 
