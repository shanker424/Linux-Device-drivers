cmd_/home/hex/Documents/LDD/Linux-Device-drivers/Fileoperation/Module.symvers := sed 's/ko$$/o/' /home/hex/Documents/LDD/Linux-Device-drivers/Fileoperation/modules.order | scripts/mod/modpost -m -a   -o /home/hex/Documents/LDD/Linux-Device-drivers/Fileoperation/Module.symvers -e -i Module.symvers   -T -