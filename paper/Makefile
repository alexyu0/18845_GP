all:
	latex example # format paper
	bibtex example # generate references
	latex example 
	latex example # once more to resolve references
	dvips -o example.ps example.dvi # generate ps file
	ps2pdf example.ps # generate pdf file

clean:
	rm -rf *.dvi *.aux *.log *.blg *.bbl example.ps example.pdf *~




