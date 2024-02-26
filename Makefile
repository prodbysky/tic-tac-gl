copy_resources:
	cp src/vertex.glsl build/resources/vertex.glsl
	cp src/fragment.glsl build/resources/fragment.glsl
	cp -r resources/ build/


main: src/main.c copy_resources
	gcc src/stb_image.o src/texture.c src/window.c src/ebo.c src/vbo.c src/vao.c src/shader.c src/application.c src/main.c -o build/main -Iinclude/ -Llib/ -lglfw3 -lGL -lGLEW -lX11 -lm -Wall -Werror -ggdb

run: main
	cd build; ./main; cd ..

debug: main
	cd build; gdb ./main; cd ..
