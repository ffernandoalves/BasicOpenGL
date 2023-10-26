@REM compila glad como lib: -> gl.o
@REM obs: alterei a importação no gl.c [<glad/gl.h>] para ["gl.h"]
g++ -c -Iextern\glad\include\glad .\extern\glad\src\gl.c -o build/deps/gl.o

g++ -Wall -c .\src\main.cpp -Iextern\glfw\include\GLFW -Iinclude -Iextern\glad\include\glad -o build/deps/test_gl.o
g++ -fPIC .\build\deps\test_gl.o .\build\deps\gl.o -Lextern\glfw\lib-static-ucrt -lglfw3dll -o build/bin/test_gl
copy extern\glfw\lib-static-ucrt\glfw3.dll build\bin\glfw3.dll

