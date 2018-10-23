################################################################################
# c_client_simple_make:  makefile for geosupport c_client_simple applicatioon 
################################################################################
CFLAGS = -g -W -fPIC -D__linux__ -trigraphs

################################################################################
# replace /devgeo below with the location you have installed Linux Geosupport to 
################################################################################
INC = $(HOME)/version-18c_18.3/include/foruser
BIN = $(HOME)/version-18c_18.3/bin
LIBS = $(HOME)/version-18c_18.3/lib

##############################################
# compile objects used in c_client
##############################################

# c_client.o: c_client.c 
#	 gcc -c $(CFLAGS) -I$(INC) c_client.c

################################################################################

c_client_all:   
	gcc $(CFLAGS) -I$(INC) -o $(BIN)/c_client c_client.c \
	-L$(LIBS) -lgeo -lapequiv -ledequiv -lsan -lsnd -lstExcpt -lStdLast -lStdUniv -lstEnder -lstretch -lthined \
	-L. -L/usr/local/lib -lm -lc -lgcc_s 
