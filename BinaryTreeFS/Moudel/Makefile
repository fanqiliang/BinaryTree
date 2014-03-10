OBJ = Linktabel.o countMAIN.o getRBtopten.o RBTree.o \
	  bullbesort.o getLNtopten.o getwords.o

edit : $(OBJ)
	gcc -o edit $(OBJ)

countMAIN.o : WordCount.h RBTree.o getwords.o getLNtopten.o getRBtopten.o

Linktabel.o : WordCount.h Linktabel.c

bullbesort.o : WordCount.h bullbesort.c

getRBtopten.o : WordCount.h bullbesort.o getRBtopten.c

getLNtopten.o : WordCount.h bullbesort.o getLNtopten.c

RBTree.o : WordCount.h RBTree.c

getwords.o : WordCount.h RBTree.o Linktabel.o getwords.c

.PHONY:clean
clean :
	rm edit $(OBJ)

