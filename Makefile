RUN = g++ -Wall -Werror -Wextra -O2 --pedantic -std=c++17 -g
ifeq ($(shell uname),Linux)
	OS= -lpthread -lrt -lm -lsubunit
else
	OS= -lm
endif
all:	uninstall clean install
view.a:	view.o
	ar rcs view.a *.o
	ranlib view.a
view.o:	*.cpp *.h
	$(RUN) *.cpp
view_install.o:	*.cpp *.h
clean:
	rm -rf *.gcda *.gcno *.o *.info *.a *.tar.gz docs/html
install:
	mkdir 3DView && mkdir tmp
	install *.cpp *.h *.pro *.pro.* 3DView
	echo "" > tmp/Makefile
	cp -rf Makefile tmp/Makefile
	qmake -o Makefile 3DView/3DVision.pro
	make
	mv ./3DVision 3DView
	cp -rf tmp/Makefile Makefile
	rm -rf tmp
	./3DView/3DVision
uninstall:	clean
	rm -rf 3DView .qmake.* *.txt
viewer:	view_install.o
	$(RUN) *.cpp -o 3DVision $(OS)
dist:
	tar czvf 3DVision.tar.gz --ignore-failed-read objes *.cpp *.h *.pro.* *.pro Makefile

