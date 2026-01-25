# DiffMergeBot Docker Process

> Build process for micro-ros forked from [micro-ROS/docker](https://github.com/micro-ROS/docker/tree/jazzy/micro-ROS-Agent)

## Build

To build the docker container execute the following from the root directory:

```bash
cd docker/ && docker build -t legohead259/diff_merge_bot_ws:test
```

## Usage

The `docker-compose.yml` file in the root directory lists out example services using the `diff_merge_bot` image.

### Micro ROS Agent

One of the services available is a micro-ROS agent application (`micro-ros-agent`) that will launch a micro-ROS agent with the parameters specified in the `command` tag.
To launch this application execute the following from the root directory:

```bash
docker compose run -it --rm micro-ros-agent
```

This will launch the container and execute the micro-ROS agent in an interactive shell session.
The script can be exited using `CTRL+C` to run diagnostics or attach a development environment.
When the shell session is exited, the container will automatically tear itself down.
