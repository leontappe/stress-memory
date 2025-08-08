FROM debian:sid-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
	ca-certificates \
	python3 \
	&& rm -rf /var/lib/apt/lists/*

COPY load_filecache.py /load_filecache.py

ENTRYPOINT ["/load_filecache.py"]

