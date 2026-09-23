# Developer Documentation
This guide provides technical instructions for developers looking to set up, maintain, or modify the Inception project. This is a addition to the USER_DOC.md, thus it assumes familiarity with what is stated inside the USER_DOC.md.

## 1. Setting Up the Environment from Scratch
To run this project, you need a Virtual Machine (VM) and a few basic tools.

### Prerequisites
1. **Virtual Machine**: Install a hypervisor (VirtualBox, VMware, UTM, etc.) and create a new VM running a minimal Linux distribution (e.g., Debian or Ubuntu).
2. **System Updates**: Inside the VM, update your package lists:
	```bash
	sudo apt update && sudo apt upgrade -y
	```
3. **Install Docker & Docker Compose**:
	```bash
	sudo apt install docker.io -y
 	sudo usermod -aG docker $USER && newgrp docker
	sudo mkdir -p /usr/local/lib/docker/cli-plugins && sudo curl -SL https://github.com/docker/compose/releases/latest/download/docker-compose-linux-x86_64 -o /usr/local/lib/docker/cli-plugins/docker-compose && sudo chmod +x /usr/local/lib/docker/cli-plugins/docker-compose
	```
4. **Install Necessary Prerequisites**:
	```bash
	sudo apt install git make mkcert curl -y
	```

### Configuration Files and Secrets
1. Clone the project repository.
2. Navigate to the `srcs/` directory.
3. Create your environment file:
	```bash
	cp .env.example .env
	nano .env
	```
	Replace the environment variables with the values stated in the subject PDF.
4. Place your secrets inside the `secrets/` directory.
- `db_root_password.txt` will be used as the MariaDB root password
- `db_password.txt` will be used as the WordPress database & panel admin password

## 2. Building and Launching the Project
The project is orchestrated via a `Makefile` at the root directory, which calls `docker-compose.yml` located in the `srcs/` directory.

- **Build & Start**:
	```bash
	make
	```
- **Rebuild Project**:
	```bash
	make re
	```
- **Stop Project**:
  ```bash
  make stop
  ```
## 3. Managing Containers and Volumes
- **List running containers**:
  ```bash
  docker ps
  ```
- **Access a container's shell** (useful for debugging Nginx configs or WordPress files):
  ```bash
  docker exec -it <container_name> bash
  # Example: docker exec -it nginx bash
  ```
- **View real-time logs**:
  ```bash
  docker logs -f <container_name>
  ```
- **List/Inspect Volumes**:

	List volumes:
	```bash
	docker volume ls
	```
	Inspect a volume (to see where it is mounted on the host):
	```bash
	docker volume inspect <volume_name>
	```

## 4. Data Storage and Persistence
The project relies on Docker named volumes to ensure data persists across container restarts or recreations. Bind mounts are not used for persistent storage.

- A dedicated named volume stores the MariaDB data directory (`/var/lib/mysql`). This is used by the MariaDB container to persist database data across container restarts or recreations.
- A second named volume stores the WordPress website files (`/var/www/html`). This is used by NGINX and WordPress to serve the website content.
- Per subject requirements, all named volumes can be found at `/home/<login>/data` on the host machine (specifically the VM's filesystem). This ensures that even if the containers are removed, the data remains intact and can be reused when the containers are recreated.

Both named volumes are configured in the `docker-compose.yml` file with a specific driver configuration so that their underlying data is ultimately stored in the `/home/<login>/data` directory on the host machine (specifically the VM's filesystem).

To completely wipe all data and start fresh, you can run:
```bash
make fclean
rm -rf ~/data
```
## 5. WordPress Configuration
- **Administrator Username**: `wproot`
- **Administrator Password**: Stored in `srcs/secrets/db_password.txt`
- **Second User**: A non-admin account (`wpuser`) is created during initialization to satisfy the two-user requirement.
- **Admin Username Restriction**: Per project requirements, the administrator username cannot contain "admin" or "administrator" in any case variation.