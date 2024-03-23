build:
	gcc -Wall -I libraries/include -L libraries/lib -o game.exe src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

testBuild:
	gcc -Wall -I libraries/include -L libraries/lib -o test.exe test.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run:
	./game.exe

runTest:
	./test.exe