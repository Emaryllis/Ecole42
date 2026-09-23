# Inception Notes

---

## Docker Compose:

### args (Build time)

```yaml
build:
  args:
    DOMAIN_NAME: ${DOMAIN_NAME}
```

- Docker reads this **during `docker compose build`**
- Passes to Dockerfile as `ARG DOMAIN_NAME`
- Available **only during image construction**
- Used to customize the image itself (e.g., which files to include, what config to bake in)
- Once image is built, args are gone
- Each time you rebuild with different args = different image

### environment (Runtime)

```yaml
environment:
  MYSQL_DATABASE: ${MYSQL_DATABASE}
```

- Docker reads this **during** `docker compose up`
- Passes to container as environment variables
- Available **only while container is running**
- Used by the process inside the container (MariaDB reads `MYSQL_DATABASE` env var)
- Same image can run with different environment vars
- Each time you restart with different env vars = same image, different behavior

`docker-compose.yml`:

```yaml
build:
  args:
    DOMAIN_NAME: example.com   # -> affects image construction
environment:
  MYSQL_DATABASE: mydb         # -> affects running container
```

TLDR; args changes the image, environment changes the container behavior.