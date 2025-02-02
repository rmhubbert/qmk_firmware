#!/bin/bash

SOURCE_FILE=~/Downloads/ferris_sweep_rmhubbert.json
DEST_FILE=keymap.json

if [[ -f "$SOURCE_FILE" ]]; then
    cp "$SOURCE_FILE" "$DEST_FILE"
    echo "Copying '$SOURCE_FILE' to '$DEST_FILE'."
else
    echo "Warning: Source file '$SOURCE_FILE' not found. Skipping copy."
fi

if [[ ! -f "$DEST_FILE" ]]; then
    echo "Error: keymap file '$DEST_FILE' is missing. Exiting."
    exit 1
fi

echo "Flashing the Ferris Sweep with the new Elite-C firmware."
qmk flash -kb ferris/sweep -km rmhubbert
