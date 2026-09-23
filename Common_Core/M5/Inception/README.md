_This project has been created as part of the 42 curriculum by egoh._

## Description

The **Inception** project is a System Administration exercise aimed at broadening knowledge of system architecture, virtualization, and containerization. The main goal of the project is to set up a small infrastructure composed of different services (NGINX, WordPress + PHP-FPM, and MariaDB) under specific rules. 

Each service runs in a dedicated container built from a custom Dockerfile, ensuring a deep understanding of how containerization works under the hood without relying on pre-built images from DockerHub.

This project heavily relies on Docker to virtualize the different services required for a functional LEMP (Linux, Nginx, MariaDB, PHP) stack customized for WordPress.

## Prerequisites
Before running the project, ensure you have the following installed on your host machine:
- A Virtual Machine (e.g., using VirtualBox, VMware, or UTM) running a Linux distribution (like Debian or Ubuntu).
- Docker and Docker Compose installed inside the VM.
- Git to clone the repository.

## Compilation and Execution
1. Clone the repository
2. Ensure your `.env` file is present in the `srcs/` directory. An example env file has been provided.
3. Ensure that the secrets directory has been populated. (db_password.txt, and db_root_password.txt)
4. Launch the project using the primary Makefile target. This will build the custom Docker images and start the containers in detached mode.

## Main Design Choices
- All Dockerfiles were built from the penultimate stable version of Alpine or Debian.
- All containers are orchestrated using a `docker-compose.yml` file, ensuring they share a dedicated custom network and properly linked & named volumes.
- Sensitive information is handled using a combination of environment variables (`.env`) and Docker secrets where applicable. The NGINX container acts as the sole entrypoint and is restricted to TLSv1.2/TLSv1.3 over port 443.

## Comparisons

### Virtual Machines vs Docker
- **Virtual Machines (VMs)** virtualize hardware, allowing multiple full operating systems to run on a single physical machine. Each VM includes a full guest OS, which consumes significant memory and CPU overhead.
- **Docker (Containers)** virtualizes the operating system. Containers share the host system's kernel but run in isolated user spaces. This makes them significantly lighter, faster to start, and more resource-efficient than VMs.

### Secrets vs Environment Variables
- **Environment Variables (.env)** are simple key-value pairs passed to containers. While easy to use for general configuration, they can be exposed in logs or process lists if not handled carefully.
- **Secrets** are specifically designed to securely store sensitive data like passwords and API keys. In Docker, secrets provide a more secure mechanism than plain-text environment variables by keeping sensitive data out of the container's environment variables and logs.

### Docker Network vs Host Network
- **Docker Network** creates isolated virtual networks for containers to communicate. It allows precise control over which containers can talk to each other and which ports are exposed to the host. This is the recommended approach for security and isolation.
- **Host Network** removes network isolation between the container and the host. The container shares the host's networking namespace and its IP address. While this can reduce NAT overhead, it exposes all container ports directly to the host and is generally less secure and less portable. (Host network is strictly forbidden in this project).

### Docker Volumes vs Bind Mounts
- **Docker Volumes** are completely managed by Docker and are stored in a specific part of the host filesystem (`/var/lib/docker/volumes/` on Linux). They are the preferred mechanism for persisting data because they offer better performance, can be backed up easily, and work seamlessly across different OS environments.
- **Bind Mounts** map a specific file or directory on the host machine directly into the container. They rely entirely on the host's directory structure and permissions, making them less portable and potentially more prone to accidental modification from the host side. (Bind mounts are not used for persistent storage in this project as named volumes are required).

## Resources, Documentation & Tutorials
- [Docker Official Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [Nginx Documentation](https://nginx.org/en/docs/)
- [WordPress Installation Guide](https://wordpress.org/support/article/how-to-install-wordpress/)
- [MariaDB Knowledge Base](https://mariadb.com/kb/en/documentation/)

## AI Usage
- When encountering errors during the Docker build process or container networking, AI tools provided insights into troubleshooting Nginx configuration syntax errors and `docker compose` volume mounting issues.
- AI was used to summarize best practices for PID 1 in Docker containers.

## Bonus: ASCII Art
[Click here for the full ASCII art shown during post-initalization. (probably not worth the 2-3hrs spent on this but wtv)](bubbles.png)