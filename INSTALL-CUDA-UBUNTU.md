<!-- Create directory -->
mkdir -p ~/src

<!-- Install dependencies -->
sudo apt-get install build-essential libssl-dev git yasm libgmp-dev libpcap-dev pkg-config libbz2-dev nvidia-cuda-toolkit nvidia-opencl-dev cmake bison flex libicu-dev

<!-- Clone and install rexgen -->
cd ~/src
git clone --recursive https://github.com/teeshop/rexgen.git
cd rexgen/src
./install.sh

<!-- Clone and install JohnTheRipper -->
cd ~/src
git clone git://github.com/magnumripper/JohnTheRipper -b CUDA john

<!-- Run TEST -->
../run/john --test=0
../run/john --test

<!--  Optional: Create shortcuts -->
for tool in john unshadow unique zip2john rar2john keepass2john pfx2john dmg2john putty2john gpg2john hccap2john racf2john undrop base64conv; do
    sudo ln -sf $(pwd)/$tool /usr/local/bin/$tool
done