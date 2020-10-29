CODE_DIR = customer_app

.PHONY: app

app:
	$(MAKE) -C $(CODE_DIR)
clean:
	find . -name build_out|xargs rm -rf
	find . -name __pycache__|xargs rm -rf
	find . -type f -name "*.pyc" -delete
	rm -rf tools/sdk_pub_tool/bouffalolab*
