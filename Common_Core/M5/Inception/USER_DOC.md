# User Documentation

## For End Users

### Accessing the Website
1. Open your web browser and navigate to `https://egoh.42.fr`
   (Ensure your `/etc/hosts` file maps this domain to the VM's IP address)
2. Log in at `https://egoh.42.fr/wp-admin` using credentials provided by your administrator

### Using WordPress
This project uses WordPress as its content management system. For complete usage instructions:
- [WordPress User Manual](https://wordpress.org/documentation/)
- [Getting Started with WordPress](https://wordpress.org/documentation/article/getting-started-with-wordpress/)

### Getting Help
If you experience issues accessing the website or need account assistance, contact your system administrator.

---

## For Administrators

> [!NOTE]
> This section extends the end user documentation with infrastructure management details.

### Starting and Stopping the Project
All interactions are handled via the `Makefile` at the repository root:
- **Start**: `make`
- **Stop**: `make stop`

### Locating and Managing Credentials
For security reasons, no passwords are hardcoded or committed to Git:
- **Secrets Directory**: `srcs/secrets/`
	- `db_root_password.txt`: MariaDB root password
	- `db_password.txt`: WordPress database user password
- **Environment Variables**: `srcs/.env` (domain name, database name, usernames)
- **WordPress Admin**: Username is `wproot`. Password matches `srcs/secrets/db_password.txt`.

### Checking Service Health
- `make ps`: Lists all running containers and their status
- `make logs`: Displays real-time logs for all containers (CTRL-C to exit.)