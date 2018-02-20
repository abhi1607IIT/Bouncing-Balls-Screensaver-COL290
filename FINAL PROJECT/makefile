num_threads=15
compile:
	g++ ./src/ScreenSaver.cpp -lpthread -lGL -lGLU -lglut -std=c++11;
	touch compile
execute:compile
	./a.out 2 $(num_threads)
	touch execute
DEBUG:
	g++ ./src/ScreenSaver.cpp -lpthread -lGL -lGLU -lglut;
	./a.out 2 $(num_thread)
doc:./doc/COP290-Ass1-Doc.tex
	cp ./doc/diagram.jpg ./diagram.jpg
	pdflatex ./doc/COP290-Ass1-Doc.tex
	rm diagram.jpg

.PHONY : clean
clean:
	\rm -rf *.out *~ *.pdf *.aux *.log compile execute *.log