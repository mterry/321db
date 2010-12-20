# variable declarations
OBJS = dbcompile.o dbfill.o common/trim.o common/crel.o
INCLUDE = -I../include -I../include/common
LIBS = -lform -lncurses
CC = gcc
LFLAGS = -g
CFLAGS = -g -c
SUBDIRS = common

for i in $(SUBDIRS) ; do \
(cd $$i ; make ) ; \
done

321db: dbcompile.o dbfill.o
	$(CC) $(LFLAGS) dbmenu.c $(OBJS) $(LIBS) $(INCLUDE) -o 321db
	mv 321db ../bin/321db

dbcompile.o: dbcompile.c
	$(CC) $(CFLAGS) dbcompile.c $(LIBS) $(INCLUDE)

dbfill.o: dbcompile.c
	$(CC) $(CFLAGS) dbfill.c $(LIBS) $(INCLUDE)

clean:
	rm -f *~ *.o
	rm ../bin/321db
	for i in $(SUBDIRS) ; do \
	( cd $$i ; make clean) ; \
	done
