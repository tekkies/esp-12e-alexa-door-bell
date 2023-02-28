#docker build --tag esp-12e-alexa-door-bell-build --progress=plain .



FROM solarbotics/arduino-cli-esp8266:2.0-0.25.0-python3.6


WORKDIR ~
RUN mkdir actions-runner; cd actions-runner
WORKDIR ~/actions-runner
RUN curl -o actions-runner-linux-x64-2.301.1.tar.gz -L https://github.com/actions/runner/releases/download/v2.301.1/actions-runner-linux-x64-2.301.1.tar.gz




