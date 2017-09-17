make satan-60_iso -C ~/Developer/qmk_firmware
echo "Y" | ~/Developer/tkg-toolkit/mac/reflash.sh ~/Developer/qmk_firmware/.build/satan_60_iso.hex
