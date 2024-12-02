# 编译C++代码并加入-O2优化
all: heapsort
	./heapsort

heapsort: test.cpp
	g++ -o heapsort test.cpp -O2

report: report.tex
	xelatex report.tex

clean:
	rm -f heapsort *.aux *.log *.pdf