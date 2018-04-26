test : mfrc522.c client.c shujuku.c main.c
	gcc -Wall mfrc522.c client.c shujuku.c main.c -o test -lbcm2835 -lsqlite3
clean :
	rm -rf *.c *.h
