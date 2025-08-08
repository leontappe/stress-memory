FROM gcc:14 AS builder

RUN apt-get update && apt-get install -y make \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN make clean && make

# Runtime stage
FROM debian:stable-slim

COPY --from=builder /app/stress /usr/local/bin/stress
COPY --from=builder /app/stress-file /usr/local/bin/stress-file

ENTRYPOINT ["/usr/local/bin/stress-file"]
CMD ["1G"]
