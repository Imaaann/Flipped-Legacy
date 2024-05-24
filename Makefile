build:
	gcc -Wall -I libraries/include -L libraries/lib -o game.exe src/main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && ./game.exe

testBuild:
	gcc -Wall -I libraries/include -L libraries/lib -o Test/test.exe Test/test.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && Test/test.exe

Edit:
	gcc -Wall -o Editor/Editor.exe Editor/Editor.c -lmingw32 -lncurses -DNCURSES_STATIC && Editor/Editor.exe