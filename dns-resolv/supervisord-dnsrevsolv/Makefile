all: dnsresolv1 dnsresolv2 dockerbuild

dnsresolv1: 1addrinfo.c
	gcc -o $@ $^

dnsresolv2: 2addrinfo.c
	gcc -o $@ $^

dockerbuild: Dockerfile.mrajaa
	docker build -t mrajaa:latest -f Dockerfile.mrajaa .
	docker save mrajaa:latest > mrajaa-latest.tar

clean:
	-rm -f dnsresolv1 dnsresolv2
	-docker rmi mrajaa:latest
	-rm -f mrajaa-latest.tar
