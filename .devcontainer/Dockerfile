FROM gcc:15.2.0-bookworm

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates git \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /bin/bash vscode \
    && mkdir -p /home/vscode/atcoder \
    && git clone --depth 1 --branch v1.6 https://github.com/atcoder/ac-library.git /home/vscode/atcoder/ac-library \
    && chown -R vscode:vscode /home/vscode

COPY start.sh /home/vscode/start.sh
RUN chown vscode:vscode /home/vscode/start.sh \
    && chmod +x /home/vscode/start.sh

USER vscode

RUN cat >> /home/vscode/.bashrc <<'EOF_ALIASES'
alias a='./a.out'
alias g='g++ -O2 -std=gnu++23 -Wall -Wextra -fconstexpr-depth=1024 -fconstexpr-loop-limit=524288 -fconstexpr-ops-limit=2097152 -fmodules -ftrivial-auto-var-init=zero -march=native -pthread -fopenmp -DATCODER -DNOMINMAX -DONLINE_JUDGE -I ~/atcoder/ac-library'
alias start='bash ~/start.sh'
EOF_ALIASES
