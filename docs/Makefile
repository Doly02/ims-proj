.PHONY: all clean

all: documentation.pdf

documentation.pdf: documentation.dvi
	dvips -sPAPERSIZE=a4 documentation.dvi
	ps2pdf documentation.ps

documentation.dvi: documentation.tex resources.bib
	latex documentation.tex
	bibtex documentation
	latex documentation.tex
	latex documentation.tex

clean:
	rm -f documentation.aux documentation.bbl documentation.blg documentation.dvi documentation.log documentation.ps documentation.pdf
