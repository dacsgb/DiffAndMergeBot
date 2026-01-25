# DiffAndMergeBot Systemd Services

Install the following services in the `/etc/systemd/system/` directory to enable systemd to control and manage the Docker services for this application.
Once copied, execute `sudo systemctl daemon-reload` to add the services to the systemd manager list.
From here, services can be started with `sudo systemctl start <service>`.

If services should be executed on startup, then enable them in the systemd manager by executing the following:

```bash
sudo systemctl enable <service>
```

## Usage

### Micro-ROS Agent

> This service should be enabled to run on system startup for deployed applications

The `micro-ros_agent.service` service launches the image with the micro-ROS agent entrypoint, quickly enabling an agent on the network to bridge micro-ROS components and a ROS2 bus.
The behavior of the micro-ROS agent is determined by the `command` tag within the docker compose file.
