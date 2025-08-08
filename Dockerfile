FROM debian:stable-slim AS builder

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN make clean && make

# Runtime stage
FROM debian:stable-slim

COPY --from=builder /app/stress /usr/local/bin/stress
COPY --from=builder /app/stress-file /usr/local/bin/stress-file

RUN useradd -r -s /bin/false stress
USER stress

CMD [ "stress-file", "1G" ]
