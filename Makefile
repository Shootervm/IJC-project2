#
#Makefile
#IJC-DU2, příklad b), 29.4.2014
#Autor: Vojtech Mašek, FIT 1BIB xmasek15
#
#Poznamka: wordcount-dymamic je potrebne spustat ako " LD_LIBRARY_PATH="." ./wordcount-dynamic "

#####################\--FLAGS--\#########################

CFLAGS = -std=c99 -pedantic -g -Wall -Wextra -O2

CPPFLAGS = -std=c++11 -pedantic -Wall -Wextra -O2

LIB_OBJ = htab_init.o htab_lookup.o htab_foreach.o htab_clear.o htab_free.o htab_remove.o htab_statistics.o hash_function.o

#########################################################

all: fold fold2 wordcount wordcount-dynamic

###################\--LIBRARIES--\#######################
libhtable.a: $(LIB_OBJ)
	ar crs libhtable.a $(LIB_OBJ)

# dynamicka knihovna
libhtable.so: $(LIB_OBJ)
	gcc $(CFLAGS) -shared -fPIC -o libhtable.so $(LIB_OBJ)
#########################################################

# $@ nahradza vysledne meno pri zostavovani

io.o: io.c io.h
	gcc $(CFLAGS) -c io.c -o $@

wordcount.o: wordcount.c io.h htable.h
	gcc $(CFLAGS) -c wordcount.c -o $@


htab_init.o: htab_init.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_init.c -o $@

htab_lookup.o: htab_lookup.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_lookup.c -o $@

htab_foreach.o: htab_foreach.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_foreach.c -o $@

htab_clear.o: htab_clear.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_clear.c -o $@

htab_free.o: htab_free.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_free.c -o $@

htab_remove.o: htab_remove.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_remove.c -o $@

htab_statistics.o: htab_statistics.c htable.h
	gcc $(CFLAGS) -c -fPIC htab_statistics.c -o $@

hash_function.o: hash_function.c htable.h
	gcc $(CFLAGS) -c -fPIC hash_function.c -o $@

#########################################################

fold:
	gcc $(CFLAGS) -o $@ fold.c

fold2:
	g++ $(CPPFLAGS) -o $@ fold2.cc

wordcount: wordcount.o io.o libhtable.a
	gcc $(CFLAGS) wordcount.o io.o libhtable.a -o $@

wordcount-dynamic: wordcount.o io.o libhtable.so
	gcc $(CFLAGS) -dynamic wordcount.o io.o libhtable.so -o $@


#########################################################

clean:
	rm -f *.o

clean-lib:
	rm -f *.so *.a

clean-all: clean clean-lib
