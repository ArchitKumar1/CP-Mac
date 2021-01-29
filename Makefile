clean:
	ls | grep -v "\." | xargs rm

test:
	echo "hello"
push:
	make test
	git status && git add . && git commit -m 'regular commit' && git push