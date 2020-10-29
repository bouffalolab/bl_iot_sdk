.PHONY: app

app:
	find . -maxdepth 2 -mindepth 2 -type d -execdir ./genromap {} \;
clean:
	find . -name build_out|xargs rm -rf
