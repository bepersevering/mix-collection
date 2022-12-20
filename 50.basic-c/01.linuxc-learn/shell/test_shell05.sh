#! /bin/bash

echo "Enter password:"
read TRY
while [ "$TRY" != "secret" ]; do
    echo "Sorry, try again"
    read TRY
done
