#!/usr/bin/env bash

set -e

# Start nginx in foreground
exec nginx -g "daemon off;"