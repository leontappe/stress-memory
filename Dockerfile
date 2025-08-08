FROM debian:bookworm-slim AS builder

RUN apt-get update && apt-get install -y make gcc \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN make clean && make

# Runtime stage
FROM debian:bookworm-slim

COPY --from=builder /app/stress /usr/local/bin/stress
COPY --from=builder /app/stress-file /usr/local/bin/stress-file

ENTRYPOINT ["/usr/local/bin/stress-file"]
CMD ["1G"]
