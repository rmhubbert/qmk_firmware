#!/bin/bash

SOURCE_FILE=~/Downloads/ferris_sweep_rmhubbert.json
DEST_FILE=keymap.json

if [[ -f "$SOURCE_FILE" ]]; then
    cp "$SOURCE_FILE" "$DEST_FILE"
    echo "Copying '$SOURCE_FILE' to '$DEST_FILE'."
else
    echo "Warning: Source file '$SOURCE_FILE' not found. Skipping copy."
fi

echo "Converting to RP2040 format and flashing Ferris Sweep with the new firmware."
qmk flash -kb ferris/sweep -km rmhubbert -e CONVERT_TO=rp2040_ce
