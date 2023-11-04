is-root:
ifneq '$(shell id -u)' '0'
	@echo 'You must be logged as root'
	@exit 1
endif

perm: is-root
	chown root:root /usr/bin/spwd
	chmod 755 /usr/bin/spwd

clean: is-root
	rm -f /usr/bin/spwd

install-prep: is-root
	gcc spwd.c -o /usr/bin/spwd

install: is-root install-prep perm