clean:
	ls | grep -v "\." | xargs rm

push:
	git status && git add . && git commit -m 'regular commit' && git push