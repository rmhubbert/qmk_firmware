#!/bin/bash

KEYMAP_SOURCE=~/Downloads/ferris_sweep_rmhubbert.json
KEYMAP_TARGET=keymap.json
RULES_SOURCE=rules_elite_c.mk
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

echo "Flashing the Ferris Sweep with the new Elite-C firmware."
qmk flash -kb ferris/sweep -km rmhubbert
