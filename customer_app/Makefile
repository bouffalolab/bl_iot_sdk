.PHONY: app clean

DIRECTORIES := $(wildcard */)

app: $(DIRECTORIES)

$(DIRECTORIES)::
	echo building $@...
	cd $@ && ./genromap

clean:
	find . -name build_out | xargs rm -rf
