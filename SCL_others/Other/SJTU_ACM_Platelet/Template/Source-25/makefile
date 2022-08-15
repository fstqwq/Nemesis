release.pdf: */* *.tex
	./xelatex-repeat.sh 5
	mv source.pdf release.pdf

clean:
	rm *.log *.aux *.synctex.gz *.toc source.pdf || printf ""
