all: dockerbuild

dnsresolv: addrinfo.c
	gcc -o $@ $^

dockerbuild: Dockerfile.dns
	docker build -t dns-resolv:latest -f Dockerfile.dns .
	docker save dns-resolv:latest > dns-resolv-latest.tar

clean:
	-rm -f dnsresolv
	-docker rmi dns-resolv:latest
	-rm -f dns-resolv-latest.tar
