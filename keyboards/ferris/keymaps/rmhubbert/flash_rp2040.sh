#!/bin/bash

KEYMAP_SOURCE=~/Downloads/ferris_sweep_rmhubbert.json
KEYMAP_TARGET=keymap.json
RULES_SOURCE=rules_rp2040.mk
RULES_TARGET=rules.mk

if [[ -f "$KEYMAP_SOURCE" ]]; then
    mv "$KEYMAP_SOURCE" "$KEYMAP_TARGET"
    echo "Moving '$KEYMAP_SOURCE' to '$KEYMAP_TARGET'."
else
    echo "'$KEYMAP_SOURCE' not found. Using existing keymap.json"
fi

if [[ -f "$RULES_SOURCE" ]]; then
    cp "$RULES_SOURCE" "$RULES_TARGET"
    echo "Copying '$RULES_SOURCE' to '$RULES_TARGET'."
else
    echo "Error: rules file '$RULES_SOURCE' not found. Exiting."
    exit 1
fi

if [[ ! -f "$KEYMAP_TARGET" ]]; then
    echo "Error: keymap file '$KEYMAP_TARGET' is missing. Exiting."
    exit 1
fi

echo "Converting to RP2040 format and flashing Ferris Sweep with the new firmware."
qmk flash -kb ferris/sweep -km rmhubbert -e CONVERT_TO=rp2040_ce
